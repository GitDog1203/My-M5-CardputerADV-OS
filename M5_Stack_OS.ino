#include <M5Cardputer.h>
const char* ITEMS[] = { "Notes", "Games", "Clock", "Settings" };
const int COUNT = sizeof(ITEMS) / sizeof(ITEMS[0]);
int sel = 0;
bool dirty = true;
const char K_UP=1, K_DOWN=2, K_LEFT=3, K_RIGHT=4, K_ENTER=5, K_BACK=6;

char readKey() {
  if(!M5Cardputer.Keyboard.isChange()) return 0;
  if(!M5Cardputer.Keyboard.isPressed()) return 0;
  auto st = M5Cardputer.Keyboard.keysState();
  if (st.enter) return K_ENTER;
  for (auto c : st.word) {
    if (c == ';') return K_UP;
    if (c == '.') return K_DOWN;
    if (c == ',') return K_LEFT;
    if (c == '/') return K_RIGHT;
    if (c == '`') return K_BACK;
    return c;
  }
  return 0;
}

void drawMenu() {
  auto& d = M5Cardputer.Display;
  d.fillScreen(TFT_BLACK);
  d.setTextColor(TFT_CYAN, TFT_BLACK);
  d.setTextSize(2); d.setCursor(8, 6); d.print("MENU");
  d.setTextSize(2);
  for (int i = 0; i < COUNT; i++) {
    int y = 34 + i * 22;
    if (i == sel) d.setTextColor(TFT_BLACK, TFT_CYAN);
    else          d.setTextColor(TFT_WHITE, TFT_BLACK);
    d.setCursor(12, y);
    d.printf(" %s ", ITEMS[i]);
  }
}
void setup() {
  auto cfg = M5.config();
  M5Cardputer.begin(cfg, true);
  M5Cardputer.Display.setRotation(1);
}
void loop() {
   M5Cardputer.update();
  if (dirty) { drawMenu(); dirty = false; }
  char k = readKey();
  if (k == K_DOWN) { sel = (sel + 1) % COUNT;         dirty = true; }
  if (k == K_UP)   { sel = (sel - 1 + COUNT) % COUNT; dirty = true; }
  if (k == K_ENTER) {
    auto& d = M5Cardputer.Display;
    d.fillScreen(TFT_BLACK); d.setTextColor(TFT_CYAN);
    d.setTextSize(2); d.setCursor(8, 55);
    d.printf("-> %s", ITEMS[sel]);
    delay(600); dirty = true;
  }
  delay(10);
}




