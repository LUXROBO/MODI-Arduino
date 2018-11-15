#include <MODI.h>

const unsigned int DIAL_ID    = 0xA18; // please modify id to your module's id
const unsigned int LED_ID     = 0xB73;

/* module */
Button button1;
Dial dial1;
LED led1;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);
  Serial.println("welcome to MODI");
  MODI.begin();

  dial1.begin(DIAL_ID);
  led1.begin(LED_ID);

  /* add request */
  dial1.addRequest(2);
}

void loop() {
  Serial.print("Degree:");
  Serial.println(dial1.readDegree());
 if(dial1.readDegree() <= 50)
 {
   Serial.println("UNUSE");
   led1.writeRGB(0,100,0);
 }
 else
 {
   Serial.println("USE");
   led1.writeRGB(100,0,0);
 }
  delay(200);
}