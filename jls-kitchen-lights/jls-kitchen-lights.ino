#include <FastLED.h>
#include <FiniteStateMachine.h>

#define NUM_LEDS 60 // Number of LEDs in strip
#define MIC_PIN 1

#define DEBUG true

#define SENSITIVITY 80  // lower is more sensitive to sound

CRGB leds[NUM_LEDS];

void setup() {
  // APA102 is dotstars https://github.com/FastLED/FastLED/wiki/Chipset-reference
  //    FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN>(leds, NUM_LEDS);
  // or don't
  FastLED.addLeds<APA102, BGR>(leds, NUM_LEDS);
  FastLED.setBrightness( 80);
}

unsigned long t;
unsigned long t0;
unsigned long dt;

unsigned long transitionTime = 512;

//FSM
State On = State(ledOn);
State Off = State(ledOff);
//State FadeIn = State(ledFadeIn);
//State FadeOut = State(ledFadeOut);
FSM fsm = FSM(On);
//utility functions
void ledOn(){
  if (DEBUG) {
    FastLED.setBrightness(255);
    allBlue();
//    FastLED.delay(500);
  }
  FastLED.setBrightness(255);
}
void ledOff(){
  if (DEBUG) {
    FastLED.setBrightness(255);
    allRed();
//    FastLED.delay(500);
  }
  FastLED.setBrightness(0);
}

//void ledFadeIn(){ led.fadeIn(500); }
//void ledFadeOut(){ led.fadeOut(500); }
//end utility functions
//FSM

void draw() {
//  simpleGradient();
  if (fsm.isInState(On)) {
    larsonScanner();  
  } 
  else if (fsm.isInState(Off)) {
    workingLight();
  } 
}
void loop() {
  // input from mic. twice to allow pin to settle
  analogRead(MIC_PIN);
  delay(10);
  int val = analogRead(MIC_PIN);
  t = millis();
  if (val < SENSITIVITY) {
    t0 = t;
//    FastLED.setBrightness(255);
    
  }
  dt = t - t0;
  if (dt <= transitionTime) {
    fsm.transitionTo(On);
  }
  else if (dt > transitionTime && dt < transitionTime*2) {
    fsm.transitionTo(Off);
    larsonScanner();
//    FastLED.setBrightness(255 - (dt - transitionTime) / 2);
  }
  else if (dt >= transitionTime*2) {
//    larsonScanner();
    fsm.transitionTo(Off);
//    FastLED.setBrightness(0);
  }
  fsm.update();
  draw();
  FastLED.delay(5);
}
