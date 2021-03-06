#include <MODI.h>

const unsigned int DISPLAY_ID = 0x3F4;

const unsigned char image [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xFF, 0xFF, 0x00, 0x7E, 0x00, 0xFF, 0x80, 0x3E, 0xFF, 0xFF, 0x01, 0xFF, 0x80, 0xFF, 0xE0, 0x3E,
0xFF, 0xFF, 0x03, 0xFF, 0xC0, 0xFF, 0xF0, 0x3E, 0xFF, 0xFF, 0x07, 0xFF, 0xE0, 0xFF, 0xF8, 0x3E,
0xFF, 0xFF, 0x0F, 0xFF, 0xF0, 0xFF, 0xFC, 0x3E, 0xFF, 0xFF, 0x0F, 0xFF, 0xF0, 0xFF, 0xFC, 0x3E,
0xFF, 0xFF, 0x0F, 0xFF, 0xF8, 0xFF, 0xFE, 0x3E, 0xFF, 0xFF, 0x0F, 0xFF, 0xF8, 0xFF, 0xFE, 0x3E,
0xFF, 0xFF, 0x0F, 0xFF, 0xF8, 0xFF, 0xFE, 0x3E, 0xFF, 0xFF, 0x0F, 0xFF, 0xF8, 0xFF, 0xFE, 0x3E,
0xFF, 0xFF, 0x0F, 0xFF, 0xF8, 0xFF, 0xFE, 0x3E, 0xF3, 0xDF, 0x0F, 0xFF, 0xF0, 0xFF, 0xFC, 0x3E,
0xF1, 0x9F, 0x0F, 0xFF, 0xF0, 0xFF, 0xFC, 0x3E, 0xF0, 0x1F, 0x07, 0xFF, 0xE0, 0xFF, 0xF8, 0x3E,
0xF0, 0x1F, 0x03, 0xFF, 0xC0, 0xFF, 0xF0, 0x3E, 0xF0, 0x1F, 0x01, 0xFF, 0x80, 0xFF, 0xE0, 0x3E,
0xF0, 0x1F, 0x00, 0xFF, 0x00, 0xFF, 0x80, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};



/* Display module */
Display display1;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);
  Serial.println("welcome to MODI");
  MODI.begin();

  display1.begin(DISPLAY_ID);
  delay(1000);
  display1.writeDots(image);
}

void loop() {

  

}