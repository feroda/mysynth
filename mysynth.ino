const int LEDS_PIN[] = {6, 7};
const int SWITCH_PIN = 4;
const int POT_PIN = A0;
const int BUZZER_PIN = 9;

const int SWITCH_COUNT_CONFIRM_STATE_CHANGE = 10;
int switch_partial_count = 0;
int switch_value = 0;
int old_switch_value = 0;

int led_active = 0;
int pot_value = 0;

const int MAX_SOUND_DURATION = 200;
int tone_start = 0;
int frequency = 2500;
int duration = 100;

void led_initialize() {
  // Initialize 2 leds, and check them
  // by make them blinking
  int led_init;
  for (int i=0; i<=1; i++) {
    led_init = LEDS_PIN[i];
    pinMode(led_init, OUTPUT);
    digitalWrite(led_init, HIGH);
    delay(100);
    digitalWrite(led_init, LOW);
  }
}

void setup() {
  
  Serial.begin(9600);
  pinMode(SWITCH_PIN, INPUT);
  pinMode(POT_PIN, INPUT);
  led_initialize();
  tone_start = 0;
  Serial.println("setup() ends.");
  
}

int debounce(int switch_instant_value) {
    // Read repeteadly the swith instant state,
    // and confirm the value read if repeatedly the same value

    int switch_real_value = old_switch_value;

    if (switch_instant_value != old_switch_value) {
        // If value instant value changes -> start counter
        switch_partial_count++;
        if (switch_partial_count >= SWITCH_COUNT_CONFIRM_STATE_CHANGE) {
            // If the new state is confirmed for SWITCH_COUNT_CONFIRM_STATE_CHANGE times
            // -> set the new real state
            switch_real_value = switch_instant_value;
        }
    } else {
        // Otherwise reset the counter
        switch_partial_count = 0;
    }
    Serial.print("switch old state = ");
    Serial.println(old_switch_value);
    Serial.print("switch real value = ");
    Serial.println(switch_real_value);
    Serial.print("switch partial count = ");
    Serial.println(switch_partial_count);

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

// DEBUG
void loop1() {
  
  switch_value = digitalRead(SWITCH_PIN);
  
  Serial.print("switch = ");
  Serial.println(switch_value);
  //switch_value = debounce(switch_value);
  //Serial.print("switch real = ");
  //Serial.println(switch_value);
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

      old_switch_value = switch_value;
      
      if (switch_value) {
        // If the button is pressed
        digitalWrite(LEDS_PIN[led_active], LOW);
        led_active = (led_active + 1) % 2;
        Serial.print("led_active = ");
        Serial.println(led_active);
        digitalWrite(LEDS_PIN[led_active], HIGH);
      }
  }

  Serial.print("pot_value = ");
  Serial.println(pot_value);

  if (led_active == 0) {
    // LED 0 control frequency
    frequency = map(pot_value,0,1023,100,5000);
    Serial.println(frequency);
    frequency = my_map_buzzer(pot_value);
    Serial.println(frequency);

  } else {
    // LED 1 control duration
    duration = map(pot_value,0, 1023, 50, MAX_SOUND_DURATION);
  }

  if (millis() > tone_start + MAX_SOUND_DURATION) { 
    tone_start = millis();
    tone(BUZZER_PIN, frequency, duration);
  }

}
