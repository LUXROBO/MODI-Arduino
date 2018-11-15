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
  button1.addRequest(2);
}

void loop() {
 Serial.print("ClickState:");
 Serial.println(button1.readClick());

 motor1.writeAngle(50,50);
 if(button1.readClick() >= 10)
 {
   int random0 = random(1,3+1);

   if(random0 == 1)
   {
    Serial.println("Bite!!");
    motor1.writeAngle(40,60);
    delay(2000);
   }
   else
   {
    motor1.writeAngle(60,40);
    delay(500);
   }
 }
 delay(100);
}