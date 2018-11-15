#include <MODI.h>

const unsigned int MIC_ID = 0xCEE; // please modify id to your module's id

/* Mic module */
Mic mic1;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);
  Serial.println("welcome to MODI");
  MODI.begin();

  mic1.begin(MIC_ID);

  /* add request */
  mic1.addRequest(2);
  mic1.addRequest(3);

}

void loop() {
  Serial.println("===============");
  Serial.print("Volume:");
  Serial.println(mic1.readVolume());
  Serial.print("Freq:");
  Serial.println(mic1.readFreq());
  delay(100);
}