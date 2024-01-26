#include <TM1637TinyDisplay.h>        //  Include 7-seg display driver
#include <EdgieD.h>                   //  Include Edge Detector Library
// #include <NOKIA5110_TEXT.h>             //  Include Nokia Display Library (Maybe later)

#define CLK 4                         //  define 7-seg clock pin
#define DIO 8                         //  define 7-seg data I/O pin
#define STTSTP 3                      //  define start/stop button

int pitch  = 880;                     //  declare blip pitch for first beat
int tempo  = 120;                     //  declare start tempo
int beats  =   4;                     //  declare beats
int barLen =   4;                     //  declare bar length in beats
int count  =   1;                     //  declare beat count variable

uint32_t backThen = 0;                //  placeholder for previous time reading in main loop
uint32_t period = 60000000 / tempo;   //  calculate beat period      uS
uint32_t blipPrd = period / 48;       //  calculate tone pulse width uS

bool state = false;                   //  declare state variable (tone off)
bool run   = false;                   //  declare run/stop variable (stopped)

TM1637TinyDisplay display(CLK, DIO);
Edge button;

void setup() {
  //  Fast analog read - speed up to 6.5 uS
  ADCSRA &= ~(bit (ADPS0) | bit (ADPS1) | bit (ADPS2)); //  clear prescaler bits
  ADCSRA |= bit (ADPS0) | bit (ADPS1);                  //  prescale by 8
  pinMode(STTSTP,INPUT_PULLUP);
  display.begin();                    //  start 7-seg display
  display.showString("WLCM");         //  "Welcome"
  delay(2000);
  display.showString(" TO ");         //  " to "
  delay(2000);
  display.showString("RTRO");         //  "Retro"
  delay(2000);
  display.showString("NOME");         //  "nome"
  delay(2000);
}

void loop() {
  display.showNumber(tempo);          //  display current tempo
  //  check start/stop button
  if(button.detect(digitalRead(STTSTP))){
    if(run) noTone(2);                //  if run == true, we're stopping all sound
    run = !run;                       //  if run, then not run, else not run becomes run
    count = 1;                        //  reset beat count
  }
  //  if run, we might make "bleep, blip, blip, blip"
  if(run){
    uint32_t rightNow = micros();     //  measure time this instant
    if(!state && rightNow - backThen >= period){    //  if !state and a beat has passed
      state = true;                   //  we make another bleep or blip"
      if(count > 1){
        pitch = 440;                  //  for 2, 3 or 4, etc we blip
      } else {
        pitch = 880;                  //  on the 1, we bleep
      }
      tone(2,pitch);                  //  and this makes the bleeps and blips
      if(count >= 4){                 //  plus, for each bleep and blip we count beats
        count = 1;                    //  if it's beat 4, we reset count to 1
      } else {
        count++;                      //  otherwise we increment the count
      }
      backThen = rightNow;
    }
    //  if the current blip is long enough, we stop it
    if(state && micros() - backThen >= blipPrd){
      state = false;
      noTone(2);
    }
  }

  // read the tempo pot and set the tempo between 30 and 285 (255 steps)
  int pot = (analogRead(A0) + 1) / 4 - 1 + 30;  // read pot value & calculate tempo
  if(pot != tempo) tempo = pot;       //  set new tempo,
  if(tempo > 285) tempo = 285;        //  keep tempo below 285 and
  if(tempo < 30) tempo = 30;          //  keep tempo above 30
  period = 60000000 / tempo;          //  calculate beat period      uS
  blipPrd = period / 48;              //  calculate tone pulse width uS
}
