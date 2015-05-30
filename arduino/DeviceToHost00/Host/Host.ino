#include <RFduinoGZLL.h>

device_t role = HOST;

// pin for the Green Led
int green_led = 3;

void setup()
{
  pinMode(green_led, OUTPUT);

  Serial.begin(115200);

  Serial.print("char :: ");
  Serial.println(sizeof(char));

  Serial.print("int :: ");
  Serial.println(sizeof(int));

  Serial.print("long :: ");
  Serial.println(sizeof(long));

  // start the GZLL stack
  RFduinoGZLL.begin(role);
}

void loop()
{
}

void RFduinoGZLL_onReceive(device_t device, int rssi, char *data, int len)
{
  int accread = (int)data[0];

  // this test is not needed for a single device
  // if (device == DEVICE0)
  //   digitalWrite(green_led, accread);

  Serial.println( accread );

  // no data to piggyback on the acknowledgement sent back to the Device
  // RFduinoGZLL.sendToDevice(device, "OK");
}
