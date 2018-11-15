#include <MODI.h>

const unsigned int DIAL_ID = 0xA18; // please modify id to your module's id

/* Dial module */
Dial dial1;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);
  Serial.println("welcome to MODI");
  MODI.begin();

  dial1.begin(DIAL_ID);

  /* add request */
  dial1.addRequest(2);
  dial1.addRequest(3);
}

void loop() {
  Serial.println("===============");
 
  Serial.print("Dial :");
  Serial.println(dial1.readDegree());
  Serial.print("Dial Turn Speed :");
  Serial.println(dial1.readTurnSpeed());
  delay(100);
}