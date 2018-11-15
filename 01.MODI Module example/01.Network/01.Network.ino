#include <MODI.h>

const unsigned int NETWORK_ID = 0xF9; // please modify id to your module's id

/* Network module */
Network network1;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);
  Serial.println("welcome to MODI");
  MODI.begin();

  network1.begin(NETWORK_ID);

  /* add request */
  network1.addRequest(2);
  network1.addRequest(3);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(network1.readEvent() == 1)
  {
    Serial.println("Button Pressed");
    network1.writeEvent(1); // buzzer on
  }
  else if(network1.readEvent() == 2) // joystick up
  {
    Serial.println("Joystick Up Pressed");
  }
  else if(network1.readEvent() == 3) // joystick down
  {
    Serial.println("Joystick Down Pressed");
  }
  else if(network1.readEvent() == 4) // joystick right
  {
    Serial.println("Joystick Right Pressed");
  }
  else if(network1.readEvent() == 5) // joystick left
  {
    Serial.println("Joystick Left Pressed");
  }
  else
  {
    network1.writeEvent(0); // buzzer off
  }
  delay(100);
}