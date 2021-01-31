#ifndef MULTI_SERVO_H
#define MULTI_SERVO_H
#include <Servo.h>

class Sweep : public Servo
{
  public:
  Sweep(int pin, int min_time, int max_time, int con, int val)
  {
    servoPin = pin;
    minTime = min_time;
    maxTime = max_time;
    conTime = con;
    servoControl = val;
  }

  void begin()
  {
    attach(servoPin);
  }

  void SetRange(int smin, int smax)
  {
    servoMin = smin;
    servoMax = smax;
  }
  
  void Update()
  {
    currentMillis = millis();
    if(servoState < servoMax && servoState > servoMin && currentMillis - previousMillis > conTime)
    {
      previousMillis = currentMillis;
      servoState += servoControl * dir;
      if(servoState > servoMax) servoState = servoMax;
      else if(servoState < servoMin) servoState = servoMin;
      write(servoState);
    }
    else if(servoState >= servoMax && currentMillis - previousMillis > minTime)
    {
      previousMillis = currentMillis;
      dir = -1;
      servoState += servoControl * dir;
      if(servoState > servoMax) servoState = servoMax;
      else if(servoState < servoMin) servoState = servoMin;
      write(servoState);
    }
    else if(servoState <= servoMin && currentMillis - previousMillis > maxTime)
    {
      previousMillis = currentMillis;
      dir = 1;
      servoState += servoControl * dir;
      if(servoState > servoMax) servoState = servoMax;
      else if(servoState < servoMin) servoState = servoMin;
      write(servoState);
    }
  }
  private:
  int minTime = 0, maxTime = 0, conTime = 0, dir = 1;
  int servoPin = 0, servoState = 0, servoControl = 0, servoMin = 0, servoMax = 180;
  unsigned long currentMillis = 0, previousMillis = 0;
};

#endif
