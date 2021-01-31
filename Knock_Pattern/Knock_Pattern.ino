#define Thresold 30

byte Knock = 0, Open = 0;
int Pattern[] = {460, 300, 155, 410};
unsigned long currentMillis = 0, previousMillis = 0;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(2, OUTPUT);
}

void loop() {
  //readPattern();
  checkPattern();
  digitalWrite(2, Open);
}

void readPattern()
{
  currentMillis = millis();
  if(analogRead(A0) > Thresold)
  {
    if(!Knock) previousMillis = currentMillis;
    Serial.println(currentMillis - previousMillis);
    previousMillis = currentMillis;
    delay(100);
    while(analogRead(A0) > Thresold / 100);
    Knock++;
  }
  else if(currentMillis - previousMillis > 1000 && Knock)
  {
    previousMillis = currentMillis;
    Knock = 0;
  }
}

void checkPattern()
{
  currentMillis = millis();
  if(analogRead(A0) > Thresold)
  {
    if(!Knock)
    { // First
      previousMillis = currentMillis;
      Knock++;
    }
    else if(abs(currentMillis - previousMillis - Pattern[Knock-1]) < 80
    && Knock <= (sizeof(Pattern) / sizeof(int))+1) // check
    { // Yes
      previousMillis = currentMillis;
      Knock++;
    }
    else // No
    {
      previousMillis = currentMillis;
      Knock = 0;
    }
    delay(100);
    while(analogRead(A0) > Thresold / 100);
    if(Knock == (sizeof(Pattern) / sizeof(int))+1)
    { // Open
      Open = !Open; Knock = 0;
      Serial.println("Do you want to build a snowman~?");
    }
  }
  else if(currentMillis - previousMillis > 1000 && Knock)
  {
    previousMillis = currentMillis;
    Knock = 0;
  }
}
