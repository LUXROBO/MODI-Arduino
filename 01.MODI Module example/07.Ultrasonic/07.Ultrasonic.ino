#include <MODI.h>

const unsigned int ULTRA_ID = 0x577; // please modify id to your module's id

/* Ultrasonic module */
Ultrasonic ultra1;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);
  Serial.println("welcome to MODI");
  MODI.begin();

  ultra1.begin(ULTRA_ID);

  /* add request */
  ultra1.addRequest(2);
}

void loop() {
  Serial.println("===============");
 
  Serial.print("Dial :");
  Serial.println(ultra1.readDistance());
  delay(100);
}