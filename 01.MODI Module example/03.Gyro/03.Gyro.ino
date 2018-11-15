#include <MODI.h>

const unsigned int GYRO_ID = 0xE51; // please modify id to your module's id

/* Gyro module */
Gyro gyro1;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);
  Serial.println("welcome to MODI");
  MODI.begin();

  gyro1.begin(GYRO_ID);

  /* add request */
  gyro1.addRequest(2);
  gyro1.addRequest(3);
  gyro1.addRequest(4);
  gyro1.addRequest(5);
  gyro1.addRequest(6);
  gyro1.addRequest(7);
  gyro1.addRequest(8);
  gyro1.addRequest(9);
  gyro1.addRequest(10);
  gyro1.addRequest(11);
}

void loop() {
  Serial.println("===============");
  Serial.print("Roll:");
  Serial.println(gyro1.readRoll());
  Serial.print("Pitch:");
  Serial.println(gyro1.readPitch());
  Serial.print("Yaw:");
  Serial.println(gyro1.readYaw());
  Serial.print("Gyro_X axis:");
  Serial.println(gyro1.readGyro_X());
  Serial.print("Gyro_Y axis:");
  Serial.println(gyro1.readGyro_Y());
  Serial.print("Gyro_Z axis:");
  Serial.println(gyro1.readGyro_Z()); 
  Serial.print("Accel_X axis:");
  Serial.println(gyro1.readAccel_X()); 
  Serial.print("Accel_Y axis:");
  Serial.println(gyro1.readAccel_Y()); 
  Serial.print("Accel_Z axis:");
  Serial.println(gyro1.readAccel_Z()); 
  Serial.print("Vibration:");
  Serial.println(gyro1.readVibration()); 
  delay(100);
}