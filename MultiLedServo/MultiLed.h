#ifndef MULTI_LED_H
#define MULTI_LED_H

class Flash
{
  public:
  Flash(int pin, int on, int off)
  {
    ledPin = pin;
    onTime = on;
    offTime = off;
    pinMode(ledPin, OUTPUT);
  }

  void Update()
  {
    currentMillis = millis();
    if(ledState == HIGH && currentMillis - previousMillis > onTime)
    {
      ledState = LOW;
      previousMillis = currentMillis;
      digitalWrite(ledPin, ledState);
    }
    else if(ledState == LOW && currentMillis - previousMillis > offTime)
    {
      ledState = HIGH;
      previousMillis = currentMillis;
      digitalWrite(ledPin, ledState);
    }
  }
  
  private:
  bool ledState = 0;
  int onTime = 0, offTime = 0, ledPin = 0;
  unsigned long currentMillis = 0, previousMillis = 0;
};

class FlashCount
{
  public:
  FlashCount(int pin, int cycle, int on, int off, int count)
  {
    ledPin = pin;
    ledCycle = cycle;
    onTime = on;
    offTime = off;
    ledSetCount = count;
    pinMode(ledPin, OUTPUT);
  }

  void Update()
  {
    currentMillis = millis();
    if(cycleState == LOW && currentMillis - previousMillis > ledCycle)
    {
      previousMillis = currentMillis;
      cycleState = HIGH;
    }
    else if(cycleState)
    {
      if(ledState == HIGH && currentMillis - previousMillis > onTime)
      {
        ledCount++;
        ledState = LOW;
        previousMillis = currentMillis;
        digitalWrite(ledPin, ledState);
        if(ledCount >= ledSetCount)
        {
          cycleState = ledState = ledCount = 0;
        }
      }
      else if(ledState == LOW && currentMillis - previousMillis > offTime)
      {
        ledState = HIGH;
        previousMillis = currentMillis;
        digitalWrite(ledPin, ledState);
      }
    }
  }
  
  private:
  bool ledState = 0, cycleState = 0;
  unsigned long currentMillis = 0, previousMillis = 0;
  int onTime = 0, offTime = 0, ledPin = 0, ledCount = 0, ledSetCount = 0, ledCycle = 0;
};

class Smooth
{
  public:
  Smooth(int pin, int on, int off, int con, int val)
  {
    ledPin = pin;
    onTime = on;
    offTime = off;
    conTime = con;
    ledControl = val;
    pinMode(ledPin, OUTPUT);
  }

  void SetRange(int smin, int smax)
  {
    ledMin = smin;
    ledMax = smax;
  }
  
  void Update()
  {
    currentMillis = millis();
    if(ledState < ledMax && ledState > ledMin && currentMillis - previousMillis > conTime)
    {
      previousMillis = currentMillis;
      ledState += ledControl * dir;
      if(ledState > ledMax) ledState = ledMax;
      else if(ledState < ledMin) ledState = ledMin;
      analogWrite(ledPin, ledState);
    }
    else if(ledState >= ledMax && currentMillis - previousMillis > onTime)
    {
      previousMillis = currentMillis;
      dir = -1;
      ledState += ledControl * dir;
      if(ledState > ledMax) ledState = ledMax;
      else if(ledState < ledMin) ledState = ledMin;
      analogWrite(ledPin, ledState);
    }
    else if(ledState <= ledMin && currentMillis - previousMillis > offTime)
    {
      previousMillis = currentMillis;
      dir = 1;
      ledState += ledControl * dir;
      if(ledState > ledMax) ledState = ledMax;
      else if(ledState < ledMin) ledState = ledMin;
      analogWrite(ledPin, ledState);
    }
  }
  
  private:
  int onTime = 0, offTime = 0, conTime = 0, dir = 1;
  int ledPin = 0, ledState = 0, ledControl = 0, ledMin = 0, ledMax = 250;
  unsigned long currentMillis = 0, previousMillis = 0;
};

#endif
