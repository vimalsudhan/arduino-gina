#include <Arduino.h>


void head_cooldown()
{
  delay(50);
}

void head_left()
{
  head.write(HEAD_LEFT_ANGLE);
  head_cooldown();
}

void head_right()
{
  head.write(HEAD_RIGHT_ANGLE);
  head_cooldown();
}

void head_forward()
{
  head.write(84);
  head_cooldown();
}

void head_wakeup()
{
  int init=head.read();
  int i;
  for(i=init;i>=0;i-=11)
  {
    if(init%2==0)
      digitalWrite(ledPin,HIGH);
    else
      digitalWrite(ledPin,LOW);
    head.write(i);
    delay(15);
  }
//  for(i=0;i<=180;i+=11)
//  {
//    if(i%2==0)
//      digitalWrite(ledPin,HIGH);
//    else
//      digitalWrite(ledPin,LOW);
//    head.write(i);
//    delay(15);
//  }
//  for(i=180;i>=90;i-=11)
//  {
//    if(i%2==0)
//      digitalWrite(ledPin,HIGH);
//    else
//      digitalWrite(ledPin,LOW);
//    head.write(i);
//    delay(15);
//  }
  digitalWrite(ledPin,LOW);
  head_forward();
}

void glowLED()
{
  digitalWrite(ledPin,HIGH);
}

void offLED()
{
  digitalWrite(ledPin,LOW);
}
