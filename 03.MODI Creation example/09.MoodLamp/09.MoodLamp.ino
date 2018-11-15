#include <MODI.h>

const unsigned int NETWORK_ID   = 0xF9; // please modify id to your module's id
const unsigned int LED_ID       = 0xB72;

/* module */
Network network1;
LED led1;

int mode = 0;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);
  Serial.println("welcome to MODI");
  MODI.begin();

  network1.begin(NETWORK_ID);
  led1.begin(LED_ID);

  /* add request */
  network1.addRequest(2);
}

void loop() {
  Serial.print("Event:");
  Serial.println(network1.readEvent());
  if(network1.readEvent() == 1) // button pressed
  {
    mode = mode + 1;
    if(mode == 0)
    {
      led1.writeRGB(20,20,20);
    }
    else if(mode == 1)
    {
      led1.writeRGB(60,60,60);
    }
    else if(mode == 2)
    {
      led1.writeRGB(100,100,100);
    }
    else if(mode == 4)
    {
      led1.writeRGB(0,0,0);
      mode = 0;
    }
    delay(500);
  }
  delay(100);
}