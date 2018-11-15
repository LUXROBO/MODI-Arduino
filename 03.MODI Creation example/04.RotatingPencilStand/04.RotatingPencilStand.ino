#include <MODI.h>

const unsigned int BUTTON_ID    = 0xF55; // please modify id to your module's id
const unsigned int MOTOR_ID     = 0xB5;
const unsigned int LED_ID       = 0xB73;

/* module */
Button button1;
Motor  motor1;
LED    led1;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);
  Serial.println("welcome to MODI");
  MODI.begin();

  button1.begin(BUTTON_ID); 
  motor1.begin(MOTOR_ID);
  led1.begin(LED_ID);

  /* add request */
  button1.addRequest(4);
}

void loop() {
 Serial.print("PushState:");
 Serial.println(button1.readPushState());
 motor1.writeTorque(0,0);
 
 while(button1.readPushState() >= 10)
 {
   motor1.writeTorque(20,0);
   led1.writeRGB(0,100,0);
   delay(200);
   led1.writeRGB(0,0,0);
   delay(200);
 }
}