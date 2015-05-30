long encoder_pulses = 0;
long encoder_last_pulses = 0;
bool encoder_changed = false;
bool encoder_a = true;
bool encoder_b = false;

#define ENCODER_STEP_RESOLUTION 800

void setup() {

  // setup interrupts for encoder
  attachInterrupt(0, encoder_a_rise, RISING);
  attachInterrupt(1, encoder_b_rise, RISING);

  // start serial, only if not using midi
  Serial.begin(115400);
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

void encoder_a_rise() {
  detachInterrupt(0);

  if (encoder_b) {
    encoder_pulses--;
  } else {
    encoder_pulses++;
  }

  encoder_a = true;
  encoder_changed = true;

  attachInterrupt(0, encoder_a_fall, FALLING);
}

void encoder_a_fall() {
  detachInterrupt(0);

  if (encoder_b) {
    encoder_pulses++;
  } else {
    encoder_pulses--;
  }

  encoder_a = false;
  encoder_changed = true;

  attachInterrupt(0, encoder_a_rise, RISING);
}

void encoder_b_rise() {
  detachInterrupt(1);

  if (encoder_a) {
    encoder_pulses++;
  } else {
    encoder_pulses--;
  }

  encoder_b = true;
  encoder_changed = true;

  attachInterrupt(1, encoder_b_fall, FALLING);
}

void encoder_b_fall() {
  detachInterrupt(1);

  if (encoder_a) {
    encoder_pulses--;
  } else {
    encoder_pulses++;
  }

  encoder_b = false;
  encoder_changed = true;

  attachInterrupt(1, encoder_b_rise, RISING);
}
