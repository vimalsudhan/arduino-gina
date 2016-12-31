
#include <Servo.h>

const int pingPin=7;
const int headServoPin=10;
const int ledPin=13;
const int speakerPin=4;

int distanceAhead=0;
int prevDistanceAhead=0;
int preDistanceAhead=0;
int stuck_count=0;
boolean movable;

const int frontGap=12;  //front gap in inches
const int MAX_SPEED_GAP=30;
const int MIN_SPEED=90;
const boolean SEEK=true;
const int STUCK_THRESHOLD=20;
const int STUCK_OFF_THRESHOLD=35;
const int HEAD_LEFT_ANGLE=135;
const int HEAD_RIGHT_ANGLE=45;
const int speakerDelay=300;

const int turn_delay=500;

const int A_I1=2;
const int A_I2=3;
const int B_I1=8;
const int B_I2=9;
const int EA=5;
const int EB=6;

Servo head;

#include "head.h"
#include "distance.h"
#include "driver.h"

void setup()
{
  pinMode(A_I1,OUTPUT);
  pinMode(A_I2,OUTPUT);
  pinMode(B_I1,OUTPUT);
  pinMode(B_I2,OUTPUT);
  pinMode(EA,OUTPUT);
  pinMode(EB,OUTPUT);
  head.attach(headServoPin);
  wakeup();
  Serial.begin(9600);
}

void wakeup()
{
  set_speed_all(100);
  head_wakeup();
  forward();
}

void sdasdloop()
{
  int i;
  i=getdistance();
  Serial.println(i);
}

void loop()
{
  movable=is_movable();
  distanceAhead=preDistanceAhead;
  stuck_sense(prevDistanceAhead,distanceAhead,STUCK_THRESHOLD,STUCK_OFF_THRESHOLD);
  prevDistanceAhead=distanceAhead;
  if(distanceAhead<4)
  {
    backward();
    delay(100);
  }
  if(movable==false)
  {
    glowLED();
    brake();
    int turn=3;
    set_speed_all(100);
    if(SEEK)
      turn=seek_mode();
    else
    {
      if(is_movable_left())
        turn=1;
      else if(is_movable_right())
        turn=2;
    }
    if(turn==1)
      turn_left();
    else if(turn==2)
      turn_right();
    else
      turn_about();
    delay(turn_delay);
//    turn_until();
    offLED();
    is_movable();
    distanceAhead=preDistanceAhead;
    forward();
  }
  int speedvalue=calc_speed();  
  set_speed_all(speedvalue);
  forward();
}

