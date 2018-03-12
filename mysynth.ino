const int LEDS_PIN[] = {6, 7};
const int SWITCH_PIN = 3;
const int POT_PIN = A0;
const int BUZZER_PIN = 9;

const int LOOP_DELAY = 200;

const int SWITCH_COUNT_CONFIRM_STATE_CHANGE = 10;
int switch_partial_count = 0;
int switch_value = 0;
int old_switch_value = 0;

int led_active = 0;
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

int debounce(int switch_instant_value) {

    int switch_real_value = old_switch_value;

    if (switch_instant_value != old_switch_value) {
        switch_partial_count = 0;
    }

    if (!switch_partial_count) {
        switch_partial_count++;
        if (switch_partial_count > SWITCH_COUNT_CONFIRM_STATE_CHANGE) {
            switch_real_value = switch_real_value;
        }
    }
    
    return switch_real_value;
  
}


int my_map_buzzer(int value) {
    /* My custom `map` implementation */
    //Serial.print("value*4900 = ");
    //Serial.println(value*4900);
    //Serial.print("value*4900/1023 = ");
    //Serial.println(value*4900/1023);
    return (value*4900/1023) + 100;
}

void loop() {
  
  pot_value = analogRead(POT_PIN);
  
  switch_value = digitalRead(SWITCH_PIN);
  Serial.print("switch = ");
  Serial.println(switch_value);
  switch_value = debounce(switch_value);
  Serial.print("switch real = ");
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
    duration = map(pot_value,0, 1023, 50, LOOP_DELAY);
  }
  //tone(BUZZER_PIN, frequency, duration);
  delay(LOOP_DELAY);

}
