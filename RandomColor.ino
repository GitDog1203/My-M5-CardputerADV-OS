#include <M5Cardputer.h>

void setup() {  //start page
  auto cfg = M5.config();
  M5Cardputer.begin(cfg, true);
  M5Cardputer.Display.setRotation(1);
  M5Cardputer.Display.fillScreen(TFT_BLACK);
  M5Cardputer.Display.setTextSize(2);
  M5Cardputer.Display.setCursor(6, 55);
  M5Cardputer.Display.print("press any key!");
}

void loop() {
  M5Cardputer.update();
  if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
    uint16_t color = M5Cardputer.Display.color565(   
      random(255), random(255), random(255));     // generates random color   
    M5Cardputer.Display.fillScreen(color);           
 }
}