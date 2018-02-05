#include <FastLED.h>
#include <FiniteStateMachine.h>

#define NUM_LEDS 60 // Number of LEDs in strip
#define POT_PIN A5
#define MIC_PIN A1

CRGB leds[NUM_LEDS];

void setup() {
  // APA102 is dotstars https://github.com/FastLED/FastLED/wiki/Chipset-reference
  // using SPI pins: 11-data, 13-clock
  FastLED.addLeds<APA102, BGR>(leds, NUM_LEDS);
  clear();

}

unsigned long t;
unsigned long t0;
unsigned long dt;

unsigned long idleTime = 1024;

//FSM
State Noop = State(noopUpdate);
State On = State(onEnter, onUpdate, onExit);
State Off = State(offEnter, offUpdate, offExit);
FSM fsm = FSM(Noop);

void noopUpdate() {}

void onUpdate(){
  workingLight();
}
void onEnter() {
  fadeInWorkingLight();
}
void onExit() {
//  fadeOutWorkingLight();
  allBlue();
  FastLED.delay(1000);
}

void offUpdate(){
  larsonScanner();  
}

void offEnter() {
  fadeInLarsonScanner();
}

void offExit() {
//  fadeOutLarsonScanner();
  allRed();
  FastLED.delay(1000);
}

void loop() {
  // input from mic. twice to allow pin to settle
  analogRead(MIC_PIN);
  delay(1);
  unsigned int soundVal = analogRead(MIC_PIN);
  
  analogRead(POT_PIN);
  delay(1);
  unsigned int potVal = analogRead(POT_PIN);
  
  t = millis();
  if (soundVal > potVal) {
    t0 = t;    
  }
  dt = t - t0;
  if (dt <= idleTime) {
    if (!fsm.isInState(On)) {
      fsm.transitionTo(On);  
    }
  }
  else if (!fsm.isInState(Off)) {
    fsm.transitionTo(Off);
  }

  fsm.update();
//  FastLED.delay(1);
}
