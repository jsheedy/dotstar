#include <FastLED.h>
#include <FiniteStateMachine.h>

#define POT_PIN A5
#define MIC_PIN 4
// #define MIC_PIN A1

#define PIEZO_PIN 8

#define DEBUG false

#define NUM_LEDS 60 //38
#define MAX_BRIGHTNESS 64 // keep this a power of 2 for FastLED reasons (see docs for scale8() )

unsigned long t=millis();
unsigned long t0=t;
unsigned long dt=0;
unsigned long IDLE_TIME=1000;
unsigned long TRANSITION_ON_TIME=500;
unsigned long TRANSITION_OFF_TIME=1000;

CRGB leds[NUM_LEDS];

void setup() {

  wakeUpSound();
  // APA102 is dotstars https://github.com/FastLED/FastLED/wiki/Chipset-reference
  // using SPI pins: 11-data, 13-clock
  FastLED.addLeds<APA102, BGR>(leds, NUM_LEDS);
  clear();
  pinMode(MIC_PIN, INPUT_PULLUP);
  // warm up input / sacrifice chicken
//  analogRead(MIC_PIN);
//  delay(20);
  analogRead(POT_PIN);
  delay(20);
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
  FastLED.setBrightness(MAX_BRIGHTNESS);
  workingLight();
}
void onEnter() {
  fadeIn(TRANSITION_ON_TIME, workingLight);
}
void onExit() {
  fadeOut(TRANSITION_OFF_TIME, workingLight);
}

void offUpdate(){
  FastLED.setBrightness(MAX_BRIGHTNESS);
  larsonScanner();  
}
void offEnter() {
  fadeIn(TRANSITION_OFF_TIME, larsonScanner);
}
void offExit() {
  fadeOut(TRANSITION_ON_TIME, larsonScanner);
}

void loop() {
  
  t = millis();

  bool soundOn = digitalRead(MIC_PIN);
  unsigned int potVal = analogRead(POT_PIN);
  IDLE_TIME = potVal * 30;
  // logic low means sound detected
  if (!soundOn) {
    t0 = t;    
  }
  dt = t - t0;
  
  if (dt <= (IDLE_TIME+TRANSITION_OFF_TIME) && !fsm.isInState(On)) {
    fsm.transitionTo(On);  
  }
  else if (dt > (IDLE_TIME+TRANSITION_ON_TIME) && !fsm.isInState(Off)) {
    fsm.transitionTo(Off);
  }

  fsm.update();

  FastLED.delay(2);
  
//  debugLED(1, soundVal / 4, 0, 0);
//  debugLED(2, potVal / 4, 0, 0);

} 
