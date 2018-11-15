#include <MODI.h>

const unsigned int MOTOR_ID     = 0xB5; // please modify id to your module's id
const unsigned int NETWORK_ID   = 0xF9;
/* module */
Motor  motor1;
Network network1;

int mode = 0;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);
  Serial.println("welcome to MODI");
  MODI.begin();

  motor1.begin(MOTOR_ID);
  network1.begin(NETWORK_ID);
  /* add request */
  network1.addRequest(2);
}

void loop() {
  Serial.print("Event:");
  Serial.println(network1.readEvent());
  motor1.writeSpeed(0,0);
  if(network1.readEvent() == 1) // button pressed
  {
    if(mode == 0)
    {
      mode = 1;
      motor1.writeAngle(0,0);
    }
    else if(mode == 1)
    {
      mode = 0;
      motor1.writeAngle(75,0);
    }
    delay(500);
  }
  delay(100);
}