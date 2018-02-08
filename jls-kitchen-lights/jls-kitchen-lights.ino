#include <FastLED.h>
#include <FiniteStateMachine.h>

#define POT_PIN A5
#define MIC_PIN A1
#define PIEZO_PIN 8

#define DEBUG true

#define NUM_LEDS 38

unsigned long t=millis();
unsigned long t0=t;
unsigned long dt=0;
unsigned long IDLE_TIME=5000;

CRGB leds[NUM_LEDS];

void setup() {
  if (DEBUG) {
    IDLE_TIME=1000;
  }
  wakeUpSound();
  // APA102 is dotstars https://github.com/FastLED/FastLED/wiki/Chipset-reference
  // using SPI pins: 11-data, 13-clock
  FastLED.addLeds<APA102, BGR>(leds, NUM_LEDS);
  clear();
  // warm up inputs / sacrifice chicken
  analogRead(MIC_PIN);
  delay(2);
  analogRead(POT_PIN);
  delay(2);
}

//FSM
State Noop = State(noopUpdate);
State On = State(onEnter, onUpdate, onExit);
State Off = State(offEnter, offUpdate, offExit);
FSM fsm = FSM(Noop);

void noopUpdate() {
    debugLED(1, 0, 0, 255);
}

void onUpdate(){
  FastLED.setBrightness(255);
  workingLight();
}
void onEnter() {
  fadeIn(300, workingLight);
}
void onExit() {
  fadeOut(1500, workingLight);
}

void offUpdate(){
  FastLED.setBrightness(255);
  larsonScanner();  
}
void offEnter() {
  fadeIn(1500, larsonScanner);
}
void offExit() {
  fadeOut(300, larsonScanner);
}

void loop() {
  
  t = millis();
  
  unsigned int soundVal = analogRead(MIC_PIN);
  unsigned int potVal = analogRead(POT_PIN);
  
  if (soundVal > potVal) {
    t0 = t;    
  }
  dt = t - t0;
  
  if (dt <= IDLE_TIME && !fsm.isInState(On)) {
    fsm.transitionTo(On);  
  }
  else if (dt > IDLE_TIME && !fsm.isInState(Off)) {
    fsm.transitionTo(Off);
  }

  fsm.update();  
}
