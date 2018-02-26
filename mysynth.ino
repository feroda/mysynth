const int LEDS_PIN[] = {6, 7};
const int SWITCH_PIN = 3;
const int POT_PIN = A0;
const int BUZZER_PIN = 9;

int led_active = 0;
int switch_value = 0;
int old_switch_value = 0;
int pot_value = 0;

int frequency = 2500;
int duration = 100;

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


int my_map_buzzer(int value) {
    /* My custom `map` implementation */
    // Serial.print("value*4900 = ");
    // Serial.println(value*4900);
    // Serial.print("value*4900/1023 = ");
    // Serial.println(value*4900/1023);
    return (value*4900/1023) + 100;
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

  Serial.print("pot_value = ");
  Serial.println(pot_value);

  if (led_active == 0) {
    frequency = map(pot_value,0,1023,100,5000);
    Serial.println(frequency);
    frequency = my_map_buzzer(pot_value);
    Serial.println(frequency);

  } else {
    duration = map(pot_value,0, 1023, 50, 100);
  }
  tone(BUZZER_PIN, frequency, duration);
  delay(50);

}
