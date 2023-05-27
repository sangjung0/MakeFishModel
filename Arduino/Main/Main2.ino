#include <Servo.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

//mp3모듈
#define MP3_RXD 0
#define MP3_TXD 1

//블루투스 모듈
#define BT_RXD 2
#define BT_TXD 3

//모터드라이버
#define MD_in3 4
#define MD_in4 5
#define ENB 6

//초음파 모듈
#define Trig_Pin 7
#define Echo_Pin 8

//서보모터 핀 번호
#define TAIL1_PIN 9
#define TAIL2_PIN 10
#define TAIL3_PIN 11
#define TAIL4_PIN 12
#define BODY1_PIN 13
#define BODY2_PIN A0
#define BODY3_PIN A1
#define BODY4_PIN A2
#define MOUTH1_PIN A3
#define MOUTH2_PIN A4
#define MOUTH3_PIN A5
#define BODY5_PIN A6
Servo tail1;
Servo tail2;
Servo tail3;
Servo tail4;
Servo body1;
Servo body2;
Servo body3;
Servo body4;
Servo mouth1;
Servo mouth2;
Servo mouth3;
Servo body5;
Servo* servo[12] = {&tail1, &tail2, &tail3, &tail4, &body1, &body2, &body3, &body4, &mouth1, &mouth2, &mouth3, &body5};
short len_servo = 12;

// 소포트웨어 시리얼 설정
SoftwareSerial MP3(MP3_RXD, MP3_TXD);
SoftwareSerial BT(BT_RXD, BT_TXD);

//mp3모듈 객체 생성
DFRobotDFPlayerMini mp3Player; 

// 움직임 모드
short movement = 0;
short sound = 0;
int time = 0;
short mode = 0;

// 서보모터 변수
short tail1_angle;
short tail2_angle;
short tail3_angle;
short tail4_angle;
short body1_angle;
short body2_angle;
short body3_angle;
short body4_angle;
short mouth1_angle;
short mouth2_angle;
short mouth3_angle;
short body5_angle;

//함수 정의
void swim();
void move_servo(Servo* servo, int value,int pDelay);

void setup() {
  //시리얼 설정
  Serial.begin(9600);
  MP3.begin(9600);
  BT.begin(9600);

  //모터드라이
  pinMode(MD_in3, OUTPUT);
  pinMode(MD_in4, OUTPUT);
  
  //초음파
  pinMode(Trig_Pin, OUTPUT);
  pinMode(Echo_Pin, INPUT);

  // 서보모터 핀 초기화
  tail1.attach(TAIL1_PIN);
  tail2.attach(TAIL2_PIN);
  tail3.attach(TAIL3_PIN);
  tail4.attach(TAIL4_PIN);
  body1.attach(BODY1_PIN);
  body2.attach(BODY2_PIN);
  body3.attach(BODY3_PIN);
  body4.attach(BODY4_PIN);
  mouth1.attach(MOUTH1_PIN);
  mouth2.attach(MOUTH2_PIN);
  mouth3.attach(MOUTH3_PIN);
  body5.attach(BODY5_PIN);
  
  // if (!mp3Player.begin(MP3), false) {  //객체 초기화
  //   Serial.println(F("Unable to begin:"));
  //   Serial.println(F("1.Please recheck the connection!"));
  //   Serial.println(F("2.Please insert the SD card!"));
  //   while(true);
  // }
  // mp3Player.setTimeOut(500);
  // mp3Player.volume(30);
  // mp3Player.EQ(DFPLAYER_EQ_NORMAL); 
  // delay(1000);
  delay(3000);
}

void loop() {

  for(int i= 0 ; i < len_servo; i++){
    move_servo(servo[i],90,0);
  }
  delay(1000);

  return;

  //초음파 센서로 거리 구하기
  digitalWrite(Trig_Pin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_Pin, LOW);
  long duration = pulseIn(Echo_Pin, HIGH);
  float distance = duration * 0.0343 / 2;

  if (BT.available()){
    mode = BT.read();
  }
  if(mode != 0){
    Serial.write(mode);
    Serial.write("\n");
  }
  if(sound == 1){
    //울음소리
    mp3Player.play(1);
  }

  if(mode == 1){
    //물결움직임
  }else if(mode == 2){
    
  }else if(mode == 3){
    
  }
}

void swim(){
  // 물결 모양 생성
  tail1_angle = sin(time + 1) * 30 + 90;;
  tail2_angle = sin(time + 0.8) * 30 + 90;;
  tail3_angle = sin(time + 0.6) * 30 + 90;;
  tail4_angle = sin(time + 0.4) * 30 + 90;;
  body1_angle = sin(time + 0.3) * 30 + 90;;
  body2_angle = sin(time + 0.2) * 30 + 90;;
  body3_angle = sin(time + 0.1) * 30 + 90;;
  body4_angle = sin(time + 0) * 30 + 90;;

  // 서보모터 각도 설정
  tail1.write(tail1_angle);
  tail2.write(tail2_angle);
  tail3.write(tail3_angle);
  tail4.write(tail4_angle);
  body1.write(body1_angle);
  body2.write(body2_angle);
  body3.write(body3_angle);
  body4.write(body4_angle);

  // 시간 증가
  time += 0.4;
}

void move_servo(Servo* servo, int value,int pDelay){
  (*servo).write(value);
  delay(pDelay);
}