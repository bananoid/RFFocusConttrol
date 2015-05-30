// quadrature detector test
// Thomas Olson
// teo20150310.01
// Not interested in interrupts in this example.
// Just need to read the position value from ACC (-1024 to +1024).
// Ole Kristensen added pinModes, TASKS_READCLRACC, and updating a pos integer.

int phaseApin = 3;
int phaseBpin = 4;

long lastPos = 0;
long pos = 0;

void setup() {
  delay(1500); // give me time to start serial monitor
  Serial.begin(115200);
  Serial.println("quadrature detector test");

  // setup Quadrature Pins
  pinMode(phaseApin, INPUT_PULLUP);
  pinMode(phaseBpin, INPUT_PULLUP);
  NRF_QDEC->PSELA = phaseApin;
  NRF_QDEC->PSELB = phaseBpin;

  // LED drive not used PSELLED default is off.
  NRF_QDEC->PSELLED = 0xFFFFFFFF; // Make sure it is OFF
  // LEDPRE is don't care if not using LED.
  // LEDPOL don't care about LED Polarity.
  // DBFEN default debounce disabled.
  NRF_QDEC->DBFEN = 0; // 0=disabled, 1=enabled
  // The SAMPLEPER default is 128 us.
  NRF_QDEC->SAMPLEPER = 3; // 0=128us, 3=1024us
  NRF_QDEC->REPORTPER = 4; //Not sure I need this if not using interrupts
  // Clear the accumulators with READCLRACC .. init I don't care
  NRF_QDEC->TASKS_READCLRACC = 1;
  NRF_QDEC->ACCREAD;
  NRF_QDEC->ACCDBLREAD;

  // Turn on QDEC - ENABLE bit 1 - 0=DISABLE, 1=ENABLE
  NRF_QDEC->ENABLE = 1;

  // Start the QDEC
  NRF_QDEC->TASKS_START = 1;

}

void loop() {

  // delay(100);

  NRF_QDEC->TASKS_READCLRACC = 1;  // the QDEC is double buffered, we tell it to swap here.
                                   // this allows it to update the encoder in a clear ACC 'in the background'
  int accread = NRF_QDEC->ACCREAD; // while we muddle around with the values from ACCREAD
  pos += accread;                  // ie. by upating our position variable.

  if( lastPos == pos ) return;
  lastPos = pos;

  Serial.print("POS: ");
  Serial.println(pos);

  Serial.print("ACC: ");
  Serial.println(NRF_QDEC->ACC);

  Serial.print("ACCREAD: ");
  Serial.println(accread);

  Serial.print("ACCDBL: ");
  Serial.println(NRF_QDEC->ACCDBL);

  Serial.print("ACCDBLREAD: ");
  Serial.println(NRF_QDEC->ACCDBLREAD);

  Serial.print("SAMPLE: ");
  Serial.println(NRF_QDEC->SAMPLE);

  Serial.print("ACCOF: ");
  Serial.println(NRF_QDEC->EVENTS_ACCOF, HEX);

  Serial.println("");

}
