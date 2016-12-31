#include <Arduino.h>

void set_speed(int m,int s)
{
  if(s>100)
    s=100;
  int sp=255*s/100;
  analogWrite(m,sp);
}

void set_speed_all(int s)
{
  set_speed(EA,s);
  set_speed(EB,s);
}

void backward()
{
  digitalWrite(A_I1,LOW); 
  digitalWrite(A_I2,HIGH); 
  digitalWrite(B_I1,LOW); 
  digitalWrite(B_I2,HIGH); 
}

void forward()
{
  digitalWrite(A_I1,HIGH); 
  digitalWrite(A_I2,LOW); 
  digitalWrite(B_I1,HIGH); 
  digitalWrite(B_I2,LOW);
}

void stop()
{
  digitalWrite(A_I1,LOW); 
  digitalWrite(A_I2,LOW); 
  digitalWrite(B_I1,LOW); 
  digitalWrite(B_I2,LOW); 
}

void brake()
{
  backward();
  delay(80);
  forward();
  delay(50);
  stop();
}

void engines_on()
{
  set_speed(EA,100);
  set_speed(EB,100);
}

void engines_off()
{
  set_speed(EA,0);
  set_speed(EB,0);
}

void turn_left()
{
  digitalWrite(A_I1,LOW); 
  digitalWrite(A_I2,LOW); 
  digitalWrite(B_I1,HIGH); 
  digitalWrite(B_I2,LOW);   
}

void left()
{
  turn_left();
  delay(1800);
  brake();
}

void turn_right()
{
  digitalWrite(A_I1,HIGH); 
  digitalWrite(A_I2,LOW); 
  digitalWrite(B_I1,LOW); 
  digitalWrite(B_I2,LOW); 
}  

void right()
{
  turn_right();
  delay(1800);
  brake();
}

void turn_about()
{
  digitalWrite(A_I1,LOW); 
  digitalWrite(A_I2,HIGH); 
  digitalWrite(B_I1,HIGH); 
  digitalWrite(B_I2,LOW); 
}

void about()
{
  brake();
  digitalWrite(A_I1,LOW); 
  digitalWrite(A_I2,HIGH); 
  digitalWrite(B_I1,HIGH); 
  digitalWrite(B_I2,LOW); 
  delay(1500);
}

void stuck_sense(int prev,int cur,int threshold,int off_threshold)
{
  if(prev==cur)
    stuck_count++;
  else
    stuck_count=0;
  if(stuck_count>threshold)
  {
    movable=true;
    set_speed_all(100);
    for(int f=3000;f<4000;f+=10)
      tone(speakerPin,f,300);
    about();
    brake();
  }
  if(stuck_count>off_threshold)
  {
    glowLED();
    tone(speakerPin,3000,5000);
    exit(0);
  }
}

void turn_until()
{
  int prevdistance;
  while(1)
  {
    if(is_movable()==true)
    {
      stuck_count=0;
      return;
    }
    stuck_sense(prevdistance,preDistanceAhead,20,30);
    prevdistance=preDistanceAhead;
    delay(30);
  }
}

