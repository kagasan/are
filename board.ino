#include <IRremote.hpp>

const int LED_GREEN = 11;
const int BUTTON = 13;
const int IR_SENSOR = 8;
const int LED_IR = 7;

// 変数の宣言
uint16_t receivedAddress;
uint16_t receivedCommand;
uint32_t receivedRawData;

int last_status = 0;

void setup() {
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);   
  IrReceiver.begin(IR_SENSOR);
  IrSender.begin(LED_IR);
}
void loop() {
  if (digitalRead(BUTTON) == LOW) {
    digitalWrite(LED_GREEN, HIGH);
    IrSender.sendNEC(0x4086, 0x1A, 0);
    delay(500);
    digitalWrite(LED_GREEN, LOW);
  }
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
