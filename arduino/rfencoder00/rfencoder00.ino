#define ENCODER_STEP_RESOLUTION 800
#define INTERRUPT_A_PIN 2
#define INTERRUPT_B_PIN 3

long encoder_pulses = 0;
long encoder_last_pulses = 0;
bool encoder_changed = false;
bool encoder_a = true;
bool encoder_b = false;

// void attachInterrupt(uint8_t IRQn, callback_t callback)
// {
//   // callbacks[IRQn] = callback;
//   rfduino_nvic_enableirq(IRQn);
// }

// void detachInterrupt(uint8_t IRQn)
// {
//   rfduino_nvic_disableirq(IRQn);
//   // callbacks[IRQn] = NULL;
// }

// void attachInterrupt(uint32_t pin, int callback, uint32_t mode)
// {
//   RFduino_pinWakeCallback(pin, mode, callback);
// }

// void detachInterrupt(uint32_t pin)
// {
//   RFduino_pinWakeCallback(pin, DISABLE, NULL);
// }

int encoder_a_rise(uint32_t ulPin) {
  // detachInterrupt(INTERRUPT_A_PIN);
  RFduino_pinWakeCallback(INTERRUPT_A_PIN, DISABLE, NULL);

  if (encoder_b) {
    encoder_pulses--;
  } else {
    encoder_pulses++;
  }

  encoder_a = true;
  encoder_changed = true;

  // attachInterrupt(INTERRUPT_A_PIN, encoder_a_fall, FALLING);
  RFduino_pinWakeCallback(INTERRUPT_A_PIN, FALLING, encoder_a_fall);
  return 0;
}

int encoder_a_fall(uint32_t ulPin) {
  // detachInterrupt(INTERRUPT_A_PIN);
  RFduino_pinWakeCallback(INTERRUPT_A_PIN, DISABLE, NULL);

  if (encoder_b) {
    encoder_pulses++;
  } else {
    encoder_pulses--;
  }

  encoder_a = false;
  encoder_changed = true;

  // attachInterrupt(INTERRUPT_A_PIN, encoder_a_rise, RISING);
  RFduino_pinWakeCallback(INTERRUPT_A_PIN, RISING, encoder_a_rise);
  return 0;
}

int encoder_b_rise(uint32_t ulPin) {
  // detachInterrupt(INTERRUPT_B_PIN);
  RFduino_pinWakeCallback(INTERRUPT_B_PIN, DISABLE, NULL);

  if (encoder_a) {
    encoder_pulses++;
  } else {
    encoder_pulses--;
  }

  encoder_b = true;
  encoder_changed = true;

  // attachInterrupt(INTERRUPT_B_PIN, encoder_b_fall, FALLING);
  RFduino_pinWakeCallback(INTERRUPT_A_PIN, FALLING, encoder_b_fall);
  return 0;
}

int encoder_b_fall(uint32_t ulPin) {
  // detachInterrupt(INTERRUPT_B_PIN);
  RFduino_pinWakeCallback(INTERRUPT_B_PIN, DISABLE, NULL);

  if (encoder_a) {
    encoder_pulses--;
  } else {
    encoder_pulses++;
  }

  encoder_b = false;
  encoder_changed = true;

  // attachInterrupt(INTERRUPT_B_PIN, encoder_b_rise, RISING);
  RFduino_pinWakeCallback(INTERRUPT_A_PIN, RISING, encoder_b_rise);
  return 0;
}




void setup() {

  // setup interrupts for encoder
  // attachInterrupt(INTERRUPT_A_PIN, encoder_a_rise, RISING);
  // attachInterrupt(INTERRUPT_B_PIN, encoder_b_rise, RISING);
  RFduino_pinWakeCallback(INTERRUPT_A_PIN, RISING, encoder_a_rise);
  RFduino_pinWakeCallback(INTERRUPT_A_PIN, RISING, encoder_b_rise);

  // start serial, only if not using midi
  Serial.begin(115200);
  Serial.println("Hello");

}

void loop() {

  if (encoder_changed) {
    encoder_changed = false;

    long delta_pulses = encoder_pulses - encoder_last_pulses;
    float delta = (float)delta_pulses / ENCODER_STEP_RESOLUTION;

    encoder_last_pulses = encoder_pulses;

    Serial.print("delta :: ");
    Serial.print(delta_pulses);
    Serial.print(" pulses :: ");
    Serial.print(encoder_pulses);
    Serial.println("");

  }
}

