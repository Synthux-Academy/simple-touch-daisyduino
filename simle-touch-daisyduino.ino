// SYNTHUX ACADEMY /////////////////////////////////////////
// TEMPLATE PROJECT FOR SIMPLE TOUCH BOARD AND DAISY SEED //

////////////////////////////////////////////////////////////
//////////////////////// TESTING ///////////////////////////
// To test knobs uncomment:
// #define TEST_KNOBS

//To test switches uncomment:
// #define TEST_SWITCHES

//To test pads uncomment:
// #define TEST_PADS

#include "simple-daisy-touch.h"

////////////////////////////////////////////////////////////
///////////////////// KNOBS & SWITCHES /////////////////////
static const int knob_a = A(S30);
static const int knob_b = A(S31);
static const int knob_c = A(S32);
static const int knob_d = A(S33);
static const int knob_e = A(S34);
static const int knob_f = A(S35);
static const int left_fader = A(S36);
static const int right_fader = A(S37);

static const int switch_1_a = D(S07);
static const int switch_1_b = D(S08);
static const int switch_2_a = D(S09);
static const int switch_2_b = D(S10);

////////////////////////////////////////////////////////////
////////////////////////// TOUCH  //////////////////////////
static synthux::simpletouch::Touch touch;

void OnTouch(uint16_t pad) {
  // Put here the code that has to run
  // at the moment of touch. If you need to
  // check if the pad is being held, check out
  // IsTouched() call inside the loop() function.

  // Testing code. Can be removed //////////////////////////
  #ifdef TEST_PADS
  Serial.print("JUST TOUCHED ");
  Serial.println(pad);
  #endif
  ///////////////////////////////////////////////////////////
}

void OnRelease(uint16_t pad) {
  // Put here the code that has to run
  // at the moment of release. If you need to
  // check if the pad is being held, check out
  // IsTouched() call inside the loop() function.

  // Testing code. Can be removed ///////////////////////////
  #ifdef TEST_PADS
  Serial.print("JUST RELEASED ");
  Serial.println(pad);
  #endif
  ////////////////////////////////////////////////////////////
}

///////////////////////////////////////////////////////////////
///////////////////// AUDIO CALLBACK //////////////////////////
void AudioCallback(float **in, float **out, size_t size) {
  for (size_t i = 0; i < size; i++) {
    out[0][i] = in[0][i];
    out[1][i] = in[1][i];
  }
}

///////////////////////////////////////////////////////////////
///////////////////// SETUP ///////////////////////////////////
void setup() {
  // SETUP DAISY
  DAISY.init(DAISY_SEED, AUDIO_SR_48K);
  auto sample_rate = DAISY.get_samplerate();

  // Testing code. Can be removed /////////////////////////////
  #if defined(TEST_KNOBS) || defined(TEST_SWITCHES) || defined (TEST_PADS)
  Serial.begin(9600);
  #endif
  /////////////////////////////////////////////////////////////

  // INIT TOUCH SENSOR
  touch.Init();
  touch.SetOnTouch(OnTouch);
  touch.SetOnRelease(OnRelease);

  // INIT SWITCHES
  pinMode(switch_1_a, INPUT_PULLUP);
  pinMode(switch_1_b, INPUT_PULLUP);
  pinMode(switch_2_a, INPUT_PULLUP);
  pinMode(switch_2_b, INPUT_PULLUP);

  // initialize other modules here

  // BEGIN CALLBACK
  DAISY.begin(AudioCallback);
}

void loop() {
  //PROCESS TOUCH SENSOR
  touch.Process();
  
  //Examine whether particular pad (3 in this case) is being touched
  // auto is_pad_touched = touch.IsTouched(3); //0...11

  //Process knob values 
  // auto knob_a_value = analogRead(knob_a);

  //Process switch values
  //The value of digitalRead is inverted
  // auto switch_a_value = digitalRead(switch_1_a);

  auto d = 4; //ms
  //Testing code. Can be renmoved //////////////////////////////////////////
  #ifdef TEST_PADS
  testPads();
  #endif
  #ifdef TEST_KNOBS
  testKnobs();
  #endif
  #ifdef TEST_SWITCHES
  testSwitches();
  #endif
  #if defined(TEST_KNOBS) || defined(TEST_SWITCHES) || defined (TEST_PADS)
  d = 100;
  #endif
  /////////////////////////////////////////////////////////////////////////
  delay(d);
}
