#include <MODI.h>

const unsigned int ENV_ID = 0x5A6; // please modify id to your module's id

/* Environment module */
Environment env1;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);
  Serial.println("welcome to MODI");
  MODI.begin();

  env1.begin(ENV_ID);

  /* add request */
  env1.addRequest(2);
  env1.addRequest(3);
  env1.addRequest(4);
  env1.addRequest(5);
  env1.addRequest(6);
  env1.addRequest(7);
}

void loop() {
  Serial.println("===============");
  Serial.print("Illuminance");
  Serial.println(env1.readIlluminance());
  Serial.print("red");
  Serial.println(env1.readRed());
  Serial.print("green");
  Serial.println(env1.readGreen());
  Serial.print("blue");
  Serial.println(env1.readBlue());
  Serial.print("temp");
  Serial.println(env1.readTemperature());
  Serial.print("humidity");
  Serial.println(env1.readHumidity()); 
  delay(100);
}