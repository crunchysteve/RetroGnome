#include <TM1637.h>                   //  Include 7-seg display driver
#include <NewEncoder.h>               //  Include rotary encoder driver
#include <TimerOne.h>                 //  Include TimerOne to manage MIDI master clock
#include <MIDI.h>                     //  Include MIDI library

#define STTSTP 2                      //  Hardware interrupt for start/stop button
#define PAUSE  3                      //  Hardware interrupt for pause button

#define TONE_PIN 7                    //  bleep output pin

#define CLK 9                         //  define 7-seg clock pin
#define DIO 10                        //  define 7-seg data I/O pin
#define TMPOCLK 11                    //  menu rotary encoder select button pin alt
#define TMPODTA 12                    //  tempo rotary encoder pin alt
#define TMPOBTN 13                    //  tempo rotary encoder select button pin alt
#define PPQN 24

int pitch  = 880;                     //  declare blip pitch for first beat
int tempo  = 120;                     //  declare default tempo, store in EEPROM later
int pending = tempo;                  //  declare default tempo, store in EEPROM later

bool blip = false;                    //  declare tone state variable (tone off)
bool run  = false;                    //  declare run/stop variable (stopped)

uint32_t ticks = 0;
uint32_t beats = 0;
uint32_t bars = 0;
// uint32_t backThen = 0;                //  placeholder for previous time reading in main loop
// uint32_t period = 60000000 / tempo;   //  calculate beat period      uS
// uint32_t blipPrd = period / 48;       //  calculate tone pulse width uS

// int timeSigBase  = 4;                 //  declare start timeSig, store in EEPROM later
// int timeSigs[] = {2,3,4,5,7,9,11,13,14,15,16}; //  declare timesignatures eg 2/4, 3/4, etc.
                                      //  halve tempo for 2/2, 3/2, 4/2, etc.
                                      //  double tempo for 2/8, 3/8, 4/8, etc.
// int beats  =   timeSigBase;           //  declare beats/bar           - For song position pointer
// int barLen =   timeSigBase;           //  declare bar length in beats - For song position pointer
// int count  =   1;                     //  declare beat count variable - For song position pointer

String hello[] = {"WLCM"," TO ","RTRO","GNME"};

TM1637 tm1637(CLK, DIO);
NewEncoder tempoEncoder;

MIDI_CREATE_DEFAULT_INSTANCE();

void number(int display){
  tm1637.display(display);
}

void text(String display){
  tm1637.display(display);
}

void tick(void){
  MIDI.sendClock();
  if(run) ticks++;
  if(run && !(ticks%24)) beats++;
}

void onStartBtn(){
  run = !run;
  if(run){
    MIDI.sendStart();
  } else {
    MIDI.sendStop();
    ticks = 0;
  }
}

void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);
  tempoEncoder.begin(TMPOCLK, TMPODTA, TMPOBTN);
  Timer1.initialize(1000000/tempo/PPQN);
  Timer1.attachInterrupt(tick);
  attachInterrupt(digitalPinToInterrupt(STTSTP), onStartBtn, RISING);
  for(int val = 0; val < 4; val++){
    text(hello[val]);         //  "Welcome to RetroGnome"
    delay(500);
  }
}

void loop(){
  tempoEncoder.Update();
  if(tempoEncoder.GetDirectionName() == "Clockwise" || tempoEncoder.GetDirectionName() == "Counterlockwise"){
    static int updateTempo = pending + tempoEncoder.GetSteps();
    tempoEncoder.Reset();
  }
  if(pending != tempo && !((millis()/1000)%2)){
    number(pending);
  } else {
    number(tempo);
  }
  
  if(tempoEncoder.ButtonPressed()){
    tempo = pending;
    Timer1.setPeriod(1000000/tempo/24);
    tempoEncoder.Reset();
  }

  //  if run, we might make "bleep, blip, blip, blip"
  if(run){
    tone(TONE_PIN,pitch,15000/pitch);
  }
}
