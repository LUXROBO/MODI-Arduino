#include <MODI.h>

const unsigned int BUTTON_ID    = 0xF55; // please modify id to your module's id
const unsigned int MOTOR_ID     = 0xB5;
int random0 = 0;
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
  button1.addRequest(2);
}

void loop() {
 Serial.print("ClickState:");
 Serial.println(button1.readClick());
 
 if(button1.readClick() >= 10)
 {
   random0 = random(2000,5000+1);

   motor1.writeTorque(100,0);
   Serial.print("Random Time:");
   Serial.println(randome0);
   delay(random0);
   motor1.writeTorque(0,0);
 }
}