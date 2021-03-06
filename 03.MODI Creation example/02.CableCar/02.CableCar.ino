#include <MODI.h>

const unsigned int BUTTON_ID    = 0xF55; // please modify id to your module's id
const unsigned int MOTOR_ID     = 0xB5;

/* module */
Button button1;
Motor  motor1;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);
  Serial.println("welcome to MODI");
  MODI.begin();

  button1.begin(BUTTON_ID); 
  motor1.begin(MOTOR_ID);

  /* add request */
  button1.addRequest(5);
}

void loop() {
 if(button1.readToggle() >= 10)
 {
   motor1.writeSpeed(30,30);
 }
 else
 {
   motor1.writeSpeed(0,0);
 }
  delay(200);
}