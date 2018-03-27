const int LEDS_PIN = 13;
const int SWITCH_PIN = 4;

const int SWITCH_COUNT_CONFIRM_STATE_CHANGE = 10;
int switch_partial_count = 0;
int switch_value = 0;
int old_switch_value = 0;


void setup() {
  Serial.begin(9600);
  pinMode(SWITCH_PIN, INPUT);
}


int debounce(int switch_instant_value) {
    // Read repeteadly the switch instant state,
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

    return switch_real_value;
}


void loop() {
  
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
        digitalWrite(LED_PIN, HIGH);
      } else {
        digitalWrite(LED_PIN, LOW);
      }
}

