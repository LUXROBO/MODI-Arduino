#include <MODI.h>

const unsigned int SPEAKER_ID = 0xB36; // please modify id to your module's id

/* Speaker module */
Speaker speaker1;

uint8_t vol = 0;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);
  Serial.println("welcome to MODI");
  MODI.begin();

  speaker1.begin(SPEAKER_ID);

  /* add request */
  speaker1.addRequest(2);
  speaker1.addRequest(3);
}

void loop() {
  Serial.println("===============");
  speaker1.readVolume();
  speaker1.readFreq();

  speaker1.writeTune(F_MI_6,vol);

  vol = (vol+1)%101;
  Serial.println(vol);
  delay(100);
}