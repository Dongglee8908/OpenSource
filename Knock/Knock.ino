unsigned long currentMillis = 0, previousMillis = 0;
byte Knock = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  currentMillis = millis();
  if(analogRead(A0) > 20)
  {
    if(currentMillis - previousMillis > 100)
    {
      previousMillis = currentMillis;
      Knock++;
      Serial.println(Knock);
    }
  }
  else if(currentMillis - previousMillis > 450 && Knock)
  {
    previousMillis = millis();
    Knock = 0;
  }
}
