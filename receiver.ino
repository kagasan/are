#include <IRremote.hpp>

// 緑色led
// V側: 5pin
// GND側: GND

// OSRB38C9AA
// 足を下にして膨らんだセンサ部を手前に見て
// 右: 5V
// 中: GND
// 左: 2pin


const int IR_SENSOR = 2;
const int LED_GREEN = 5;
// 変数の宣言
uint16_t receivedAddress;
uint16_t receivedCommand;
uint32_t receivedRawData;
void setup() {
  pinMode(LED_GREEN, OUTPUT);
    Serial.begin(9600);   
    IrReceiver.begin(IR_SENSOR);
}
void loop() {
    if (IrReceiver.decode()) {
        // 受信データを変数に格納
        receivedAddress = IrReceiver.decodedIRData.address;
        receivedCommand = IrReceiver.decodedIRData.command;
        receivedRawData = IrReceiver.decodedIRData.decodedRawData;
        // シリアルモニタに結果を表示
        Serial.print("Address: ");
        Serial.println(receivedAddress, HEX);
        Serial.print("Command: ");
        Serial.println(receivedCommand, HEX);
        Serial.print("RawData: ");
        Serial.println(receivedRawData, HEX);
        if (receivedAddress == 0x4086 && receivedCommand == 0x001A) {
            Serial.println("center");
          for (int i = 0; i < 5; i++) {
              digitalWrite(LED_GREEN, HIGH);
            delay(100);
            digitalWrite(LED_GREEN, LOW);
              delay(100);
          }
        }
        if (receivedAddress == 0x4086 && receivedCommand == 0x001C) {
            Serial.println("right");
            digitalWrite(LED_GREEN, HIGH);
            
        }
        if (receivedAddress == 0x4086 && receivedCommand == 0x001D) {
            Serial.println("left");
            digitalWrite(LED_GREEN, LOW);
            
        }
        IrReceiver.resume(); // 受信を再開                            
    }
}
