#include "U8glib.h"


U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);  // I2C / TWI 

char msg1[] = "Te luid";

char msg2[] = "Stop";
void draw(char* msg) {
  // graphic commands to redraw the complete screen should be placed here  
   
  // call procedure from base class, http://arduino.cc/en/Serial/Print
  u8g.setPrintPos(10, 44);
  u8g.print(msg);
}

void setup(void) {
  // flip screen, if required
  // u8g.setRot180();
  u8g.setFont(u8g_font_fur25);
  
}

void loop(void) {
  // picture loop
  u8g.firstPage();  
  do {
    draw(msg1);
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(2000);

  // picture loop
  u8g.firstPage();  
  do {
    draw(msg2);
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(500);
}

