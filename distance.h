#include <Arduino.h>


long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

int getdistance()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
 delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  delay(10);
  return inches;
}

boolean is_movable()
{
  int gap=getdistance();
  preDistanceAhead=gap;
  if(gap>frontGap)
    return true;
  return false;
}

boolean is_movable_left()
{
  boolean movable=false;
  head_left();
  if(is_movable()==true)
    movable=true;
//  
//  int c=constrain(preDistanceAhead,0,480);
//  int f=map(c,0,480,2000,4000);
//  tone(speakerPin,f,speakerDelay);
    
  head_forward();
  return movable;
}

boolean is_movable_right()
{
  boolean movable=false;
  head_right();
  if(is_movable()==true)
    movable=true;
//  
//  int c=constrain(preDistanceAhead,0,480);
//  int f=map(c,0,480,2000,4000);
//  tone(speakerPin,f,speakerDelay);

  head_forward();
  return movable;
}

int seek_mode()
{
  boolean left_movable=is_movable_left();
  int left_distance=preDistanceAhead;
  boolean right_movable=is_movable_right();
  int right_distance=preDistanceAhead;
  int turn=3;
  if(left_movable==true && left_distance>right_distance)
    turn=1;
  else if(right_movable==true && right_distance>left_distance)
    turn=2;
  return turn;
}

int calc_speed()
{
  Serial.print("Distance :");
  Serial.println(distanceAhead);
  int vsp=distanceAhead/MAX_SPEED_GAP*100;
  if(vsp>100)
    vsp=100;
  if(vsp<MIN_SPEED)
    return MIN_SPEED;
  int actual=(vsp/100*(100-MIN_SPEED))+MIN_SPEED;
  return actual;
}
