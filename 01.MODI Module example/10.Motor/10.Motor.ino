#include <MODI.h>

const unsigned int MOTOR_ID = 0xB5;
; // please modify id to your module's id

/* Motor module */
Motor motor1;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);
  Serial.println("welcome to MODI");
  MODI.begin();

  motor1.begin(MOTOR_ID);

  /* add request */
  motor1.addRequest(2);
  motor1.addRequest(3);
  motor1.addRequest(4);
  motor1.addRequest(5);
  motor1.addRequest(6);
  motor1.addRequest(7);
  motor1.addRequest(8);
  motor1.addRequest(9);
  motor1.addRequest(10);
  motor1.addRequest(11);
  motor1.addRequest(12);
  motor1.addRequest(13);
  motor1.addRequest(14);
}

void loop() {
  Serial.println("===============");
  Serial.print("Upper Motor Torque:");
  Serial.println(motor1.readTorque_Upper());
  Serial.print("Bottom Motor Torque:");
  Serial.println(motor1.readTorque_Bottom());
  Serial.print("Upper Motor Speed:");
  Serial.println(motor1.readSpeed_Upper());
  Serial.print("Bottom Motor Speed:");
  Serial.println(motor1.readSpeed_Bottom());
  Serial.print("Upper Motor Angle:");
  Serial.println(motor1.readAngle_Upper());
  Serial.print("Bottom Motor Angle:");
  Serial.println(motor1.readAngle_Bottom());
  Serial.print("Upper Motor Sense Speed:");
  Serial.println(motor1.readSenseSpeed_Upper());
  Serial.print("Bottom Motor Sense Speed:");
  Serial.println(motor1.readSenseSpeed_Bottom());
  Serial.print("Upper Motor Sense Angle:");
  Serial.println(motor1.readSenseAngle_Upper());
  Serial.print("Bottom Motor Sense Angle:");
  Serial.println(motor1.readSenseAngle_Bottom());

  
  /* Speed */
  motor1.writeSpeed(75,20);
  //motor1.writeSpeed_Upper(100);
  //motor1.writeSpeed_Bottom(100);
  
  /* Torque */
  //motor1.writeTorque(60,-95);
  //motor1.writeTorque_Upper(25);
  //motor1.writeTorque_Bottom(30);
   
  /* Angle */
  //motor1.writeAngle(50,35);
  // motor1.writeAngle_Upper(60);
  // motor1.writeAngle_Bottom(0);
  
  delay(500);
}