#include <SoftwareSerial.h>

#define BT_RXD 2
#define BT_TXD 3

SoftwareSerial hc06(BT_RXD, BT_TXD);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  hc06.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int mode = 0;
  if (hc06.available()){
    mode = hc06.read();
  }
  if(mode != 0){
    Serial.write(mode);
    Serial.write("\n");
  }
}
