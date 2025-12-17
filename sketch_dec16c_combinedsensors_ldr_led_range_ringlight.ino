// NeoPixel Ring simple sketch (c) 2013 Shae Erisson adapted
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library
#include <Adafruit_NeoPixel.h>
int digitalPin = 4;
int analogPin = A0;
int trigPin = 8;
int echoPin = 7;
//float v=331.5+0.6*20; // m/s
float v = 343.0;  //edited to speed of sound and commented calculation in line 9 in m/s
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 6
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 12  // Popular NeoPixel ring size
// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(digitalPin, OUTPUT);
  // pinMode(analogRead, INPUT);
  pinMode(trigPin, OUTPUT);  // 1
  pinMode(echoPin, INPUT);   // 2
  pixels.begin();            // INITIALIZE NeoPixel strip object (REQUIRED)
}
float distanceM() {
  // send sound pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);

  // listen for echo
  float tUs = pulseIn(echoPin, HIGH);   // microseconds
  float t = tUs / 1000.0 / 1000.0 / 2;  // s
  float d = t * v;                      // m
  return d * 100;                       // cm
}

void loop() {
  // put your main code here, to run repeatedly:
  int l = analogRead(analogPin);
  Serial.println(l);
  if (l > 40) {
    digitalWrite(digitalPin, HIGH);
  } else {
    digitalWrite(digitalPin, LOW);
  }
  
  int d = distanceM();
  Serial.println(d, DEC);

  if (d > 500) {
    pixels.clear();
    pixels.show();
  } else {
    pixels.clear();                        // Set all pixel colors to 'off'
                                             // The first NeoPixel in a strand is #0, second is 1, all the way up
                                             // to the count of pixels minus one.
    for (int i = 0; i < NUMPIXELS; i++) {  // For each pixel...

        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        // Here we're using a moderately bright green color:
        pixels.setPixelColor(i, pixels.Color(222, 90, 0));
      }
        pixels.show();  // Send the updated pixel colors to the hardware.
      }
}