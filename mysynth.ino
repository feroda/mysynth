int leds_pin[] = {6, 7};

void setup() {
  // put your setup code here, to run once:
  for (int i=0; i<=1; i++) {
    pinMode(leds_pin[i], OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(leds_pin[0], HIGH);
  delay(100);
  digitalWrite(leds_pin[0], LOW);
  digitalWrite(leds_pin[1], HIGH);
  delay(200);
  digitalWrite(leds_pin[1], LOW);

}
