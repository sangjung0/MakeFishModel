#include <DFRobotDFPlayerMini.h>
#include "SoftwareSerial.h"
#include "Arduino.h"

SoftwareSerial mySoftwareSerial(10, 11); // 소프트웨어 시리얼 용 핀 지정
DFRobotDFPlayerMini myDFPlayer;              // 객체 생성
void printDetail(uint8_t type, int value);

void setup() {
  // put your setup code here, to run once:
  mySoftwareSerial.begin(9600);          // 소프트웨어 시리얼 통신 개시
  Serial.begin(9600);
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial), false) {  //객체 초기화
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.setTimeOut(500); //시리얼 통신용 타임아웃 시간 지정

  myDFPlayer.volume(100);  //0-30사이의 값을 인수로 입력.
  delay(1000);
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);    // 일반모드
  delay(1000);
  myDFPlayer.play(1); 

  myDFPlayer.enableLoop(); //현재 재생 중인 트랙을 반복 재생 모드로 지정
  delay(1000);

  Serial.println(myDFPlayer.readState()); //mp3 모듈 상태 읽어오기
  Serial.println(myDFPlayer.readVolume()); //현재 볼륨값 읽어오기
  Serial.println(myDFPlayer.readEQ()); //EQ세팅 읽어오기
  Serial.println(myDFPlayer.readFileCounts()); //SD카드내의 전체 음악파일 개수 얻어오기
  Serial.println(myDFPlayer.readCurrentFileNumber()); //현재 재생중인 폴더의 파일번호 얻어오기
  Serial.println(myDFPlayer.readFileCountsInFolder(3)); 
}

void loop() {
  // put your main code here, to run repeatedly:

  static unsigned long timer = millis();
  
  if (millis() - timer > 3000) {
    timer = millis();
    myDFPlayer.next();  //다음 곡 재생
  }
  
  if (myDFPlayer.available()) {
    Serial.println(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }

}
