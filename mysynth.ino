const int LEDS_PIN[] = {6, 7};
const int SWITCH_PIN = 3;
const int POT_PIN = A0;

int led_active = 0;
int switch_value = 0;
int old_switch_value = 0;
int pot_value = 0;

void setup() {
  int led_init;
  Serial.begin(9600);
  
  pinMode(SWITCH_PIN, INPUT);
  pinMode(POT_PIN, INPUT);
  for (int i=0; i<=1; i++) {
    led_init = LEDS_PIN[i];
    pinMode(led_init, OUTPUT);
    digitalWrite(led_init, HIGH);
    delay(100);
    digitalWrite(led_init, LOW);
  }
  
  Serial.println("setup() ends.");
  
}


void loop() {
  // put your main code here, to run repeatedly:
  switch_value = digitalRead(SWITCH_PIN);
  pot_value = analogRead(POT_PIN);
  
  Serial.print("button = ");
  Serial.println(switch_value);

  if (switch_value != old_switch_value) {

      if (switch_value) {
        digitalWrite(LEDS_PIN[led_active], LOW);
        led_active = (led_active + 1) % 2;
        Serial.print("led_active = ");
        Serial.println(led_active);
        digitalWrite(LEDS_PIN[led_active], HIGH);
      }
      old_switch_value = switch_value;
  }

  if (pot_value < 512) {
    digitalWrite(LEDS_PIN[1], LOW);
    Serial.print("pot_value = ");
    Serial.println(pot_value);
    Serial.println("led_active = 0");
    digitalWrite(LEDS_PIN[0], HIGH);
  } else {
    Serial.print("pot_value = ");
    Serial.println(pot_value);
    digitalWrite(LEDS_PIN[0], LOW);
    Serial.print("led_active = 1");
    digitalWrite(LEDS_PIN[1], HIGH);
  }

  delay(100);

}
