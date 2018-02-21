const int LEDS_PIN[] = {6, 7};


void setup() {
  
  Serial.begin(9600);
  
  for (int i=0; i<=1; i++) {
    pinMode(LEDS_PIN[i], OUTPUT);
  }
  
  Serial.println("setup() ends.");
  
}


void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i< 2; i++) {
    Serial.print("switch on led ");
    Serial.println(LEDS_PIN[i]);
    digitalWrite(LEDS_PIN[i], HIGH);
    delay(200);
    digitalWrite(LEDS_PIN[i], LOW);
  }

  delay(1);

}
