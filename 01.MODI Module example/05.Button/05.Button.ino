#include <MODI.h>

const unsigned int BUTTON_ID = 0xF55; // please modify id to your module's id

/* Button module */
Button button1;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);
  Serial.println("welcome to MODI");
  MODI.begin();

  button1.begin(BUTTON_ID);

  /* add request */
  button1.addRequest(2);
  button1.addRequest(3);
  button1.addRequest(4);
  button1.addRequest(5);

}

void loop() {
  Serial.println("===============");
 
  if(button1.readClick() > 1.0)
  {
    Serial.println("Button is clicked"); 
  }
  else
  {
    Serial.println("Button is unclicked");
  }
  if(button1.readDoubleClick() > 1.0)
  {
    Serial.println("Button is double clicked");
  }
  else
  {
    Serial.println("Button is not double clicked");
  }
  if(button1.readPushState() > 1.0)
  {
    Serial.println("Button is pressed");
  }
  else
  {
    Serial.println("Button is unpressed");
  }

  Serial.println("Button is toggle State:");
  Serial.println(button1.readToggle());

  delay(100);
}