#include <MODI.h>

const unsigned int IR_ID = 0xE; // please modify id to your module's id

/* Infrared module */
Ir ir1;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);
  Serial.println("welcome to MODI");
  MODI.begin();

  ir1.begin(IR_ID);

  /* add request */
  ir1.addRequest(2);
}

void loop() {
  Serial.println("===============");
 
  Serial.print("Proximity :");
  Serial.println(ir1.readProximity());
  delay(100);
}