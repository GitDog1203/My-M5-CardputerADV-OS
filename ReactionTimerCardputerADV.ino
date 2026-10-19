#include <M5Cardputer.h>

int state = 0;          
uint32_t goTime, startReact;
long best = 999999;

void msg(const char* t, uint16_t bg, uint16_t fg) {
  auto& d = M5Cardputer.Display;
  d.fillScreen(bg); d.setTextColor(fg, bg);
  d.setTextSize(3); d.setTextDatum(middle_center);
  d.drawString(t, 120, 67); d.setTextDatum(top_left);
}

void setup() {
  auto cfg = M5.config();
  M5Cardputer.begin(cfg, true);
  M5Cardputer.Display.setRotation(1);
  msg("press to start", TFT_BLACK, TFT_WHITE);
}

void loop() {
  M5Cardputer.update();
  bool pressed = M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed();

  if (state == 0) {                      
    if (pressed) { state = 1; goTime = millis() + random(1200, 4000);
                   msg("wait...", TFT_BLACK, TFT_WHITE); }
  }
  else if (state == 1) {                 
    if (pressed) { msg("too soon!", TFT_RED, TFT_WHITE); state = 3; }
    else if (millis() >= goTime) { state = 2; startReact = millis();
                                  msg("TAP!", TFT_GREEN, TFT_BLACK); }
  }
  else if (state == 2) {                 
    if (pressed) {
      long ms = millis() - startReact;    
      if (ms < best) best = ms;
      auto& d = M5Cardputer.Display;
      d.fillScreen(TFT_BLACK); d.setTextColor(TFT_WHITE, TFT_BLACK);
      d.setTextSize(2); d.setCursor(8, 30); d.printf("%ld ms", ms);
      d.setCursor(8, 60); d.printf("best %ld", best);
      d.setTextSize(1); d.setCursor(8, 110); d.print("press to retry");
      state = 3;
    }
  }
  else if (state == 3) {                    
    if (pressed) { state = 0; msg("press to start", TFT_BLACK, TFT_WHITE); }
  }
}