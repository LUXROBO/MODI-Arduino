#include <MODI.h>

const unsigned int MOTOR_ID     = 0xB5; // please modify id to your module's id
const unsigned int NETWORK_ID   = 0xF9;

/* module */
Motor  motor1;
Network network1;

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
  motor1.writeSpeed(0,0);
  while(network1.readEvent == 2) // up
  {
    motor1.writeSpeed(100,-100);
  }
  while(network1.readEvent == 3) // down
  {
    motor1.writeSpeed(-100,100);
  }
  while(network1.readEvent == 4) // left
  {
    motor1.writeSpeed(50,25);
  }
  while(network1.readEvent == 5) // right
  {
    motor1.writeSpeed(-25,-50);
  }
  delay(100);
}