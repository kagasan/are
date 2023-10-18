#include <IRremote.hpp>

// push button
// 片方: 10pin
// 片方: GND

// 緑LED
// V側: 7pin
// GND側: GND

// 赤LED
// V側: 8pin
// GND側: GND

// フォトインタラプタ
// Tの字になるようにうえから見て
// 右上: 「100kΩを経由してGND」と「5pin」を並列
// 右下: 100Ωを経由してGND
// 左上: 5V
// 左下: 5V

// BC547L
// osi5fu5111c-40
// 上が平, 下が曲面になる視点で見て
// 左: 5V - 47Ω - IR - トランジスタ
// 中: 1kΩを経由して8pin
// 右: GND

const int LED_IR = 12;
const int PHOTO_IT = 5;
const int LED_RED = 8;
const int LED_GREEN = 7;
const int BUTTON = 10;
int last_status = 0;
void setup() {
  pinMode(LED_IR, OUTPUT);
  pinMode(PHOTO_IT, INPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  IrSender.begin(LED_IR);
  digitalWrite(LED_RED, HIGH);
}
void lightTurn(int num = 1) {
  for (int i = 0; i < num; i++) {
    IrSender.sendNEC(0x4086, 0x1A, 0);
    delay(500);
  }
}
void loop() {
  // 手動操作
  if (digitalRead(BUTTON) == LOW) {
    lightTurn(1);
  }
  // カード操作(out)
  if (digitalRead(PHOTO_IT) == HIGH && last_status == 1){ 
    last_status = 0;
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);
    lightTurn(3);
  }
  // カード操作(in)
  else if (digitalRead(PHOTO_IT) == LOW && last_status == 0){
    last_status = 1;
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
    lightTurn(1);
  }
}
