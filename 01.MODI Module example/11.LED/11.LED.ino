#include <MODI.h>

const unsigned int LED_ID = 0xB73; // please modify id to your module's id

/* LED module */
LED led1;

uint8_t R =random(random(0,101));
uint8_t G =random(random(0,101));
uint8_t B =random(random(0,101));

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);
  Serial.println("welcome to MODI");
  MODI.begin();

  led1.begin(LED_ID);

  /* add request */
  led1.addRequest(2);
  led1.addRequest(3);
  led1.addRequest(4);
}

void loop() {
  Serial.println("===============");
 
  Serial.print("R :");
  Serial.println(led1.readRed());
  Serial.print("G :");
  Serial.println(led1.readGreen());
  Serial.print("B :");
  Serial.println(led1.readBlue());
  delay(1000);
  
  R =random(random(0,101));
  G =random(random(0,101));
  B =random(random(0,101));
  
  led1.writeRGB(R,G,B);
}