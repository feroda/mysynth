const int LEDS_PIN[] = {6, 7};
const int SWITCH_PIN = 4;
const int POT_PIN = A0;
const int BUZZER_PIN = 9;

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

void loop() {
  
  pot_value = analogRead(POT_PIN);

  // ATTENZIONE: problema dei rimbalzi (disturbi). 
  // Nell'implmentazione completa e' stata realizzata una funzione
  // debounce proprio per pulire i disturbi di questo tipo.
  // La tecnica: si considera valido un nuovo valore solo se lo si e'
  //             letto per N volter consecutivamente. Ad esempio 10.
  switch_value = digitalRead(SWITCH_PIN);
  
  // Serial.print("switch = ");
  // Serial.println(switch_value);

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
  } else {
    // LED 1 control duration
    duration = map(pot_value,0, 1023, 50, MAX_SOUND_DURATION);
  }

  if (millis() > tone_start + MAX_SOUND_DURATION) { 
    tone_start = millis();
    tone(BUZZER_PIN, frequency, duration);
  }

}
