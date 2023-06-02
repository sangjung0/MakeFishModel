#include <Servo.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

//mp3모듈
#define MP3_RXD 2
#define MP3_TXD 3

//블루투스 모듈
#define BT_RXD 4
#define BT_TXD 5

//모터드라이버
#define MD_in3 6
#define MD_in4 7
#define ENB 8

//초음파 모듈
#define Trig_Pin 9
#define Echo_Pin 10

//서보모터 핀 번호
#define TAIL1_PIN 11
#define TAIL2_PIN 12
#define BODY1_PIN 13
#define BODY2_PIN A0
#define BODY3_PIN A1
#define MOUTH1_PIN A2
#define MOUTH2_PIN A3
#define BODY4_PIN A4
Servo tail1;
Servo tail2;
Servo body1;
Servo body2;
Servo body3;
Servo mouth1;
Servo mouth2;
Servo body4;

// 소포트웨어 시리얼 설정
SoftwareSerial MP3(MP3_TXD, MP3_RXD);
SoftwareSerial BT(BT_TXD, BT_RXD);

//mp3모듈 객체 생성
DFRobotDFPlayerMini mp3Player; 

// 움직임 모드
short movement = -1;
short sound = -1;
double time = 0;
short mode = -1;
short nose = 0;

// 서보모터 변수
short tail1_angle;
short tail2_angle;
short body1_angle;
short body2_angle;
short body3_angle;
short mouth1_angle;
short mouth2_angle;
short body4_angle;
const short init_tail1_angle = 90;
const short init_tail2_angle = 90;
const short init_body1_angle = 90;
const short init_body2_angle = 90;
const short init_body3_angle = 90;
const short init_mouth1_angle = 135;
const short init_mouth2_angle = 135;
const short init_body4_angle = 90;

//서보모터 배열
#define len_servo 8
const Servo* servo[len_servo] = {&tail1, &tail2, &body1, &body2, &body3, &mouth1, &mouth2, &body4};
const short servo_pin[len_servo] = {TAIL1_PIN, TAIL2_PIN, BODY1_PIN, BODY2_PIN, BODY3_PIN, MOUTH1_PIN, MOUTH2_PIN, BODY4_PIN};
const short* init_angle[len_servo] = {&init_tail1_angle, &init_tail2_angle, &init_body1_angle, &init_body2_angle, &init_body3_angle, &init_mouth1_angle, &init_mouth2_angle, &init_body4_angle};
const short* angle[len_servo] = {&tail1_angle, &tail2_angle, &body1_angle, &body2_angle, &body3_angle, &mouth1_angle, &mouth2_angle, &body4_angle};

//함수 정의
void swim();
void move_servo(Servo* servo, int value,int pDelay);
void line_up(Servo* servo[len_servo]);
void tail_move(short v, short* movement);
void move(Servo* s, short angle);

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
  for(int i=0; i < len_servo; i++){
    (*servo[i]).attach(servo_pin[i]);
  }
  
  // if (!mp3Player.begin(MP3), false) {  //객체 초기화
  //   Serial.println(F("Unable to begin:"));
  //   Serial.println(F("1.Please recheck the connection!"));
  //   Serial.println(F("2.Please insert the SD card!"));
  //   while(true);
  // }
  // mp3Player.volume(0);
  // mp3Player.EQ(DFPLAYER_EQ_NORMAL); 
  delay(3000);
  for(int i=0; i < len_servo; i++){
    (*servo[i]).write(*init_angle[i]);
  }
}

void loop() {

  // //초음파 센서로 거리 구하기
  // digitalWrite(Trig_Pin, LOW);
  // delayMicroseconds(2);
  // digitalWrite(Trig_Pin, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(Trig_Pin, LOW);
  // long duration = pulseIn(Echo_Pin, HIGH);
  // float distance = duration * 0.0343 / 2;
  // Serial.println(distance);

  if (BT.available()){
    mode = BT.read() - 48;
    Serial.println(mode);
  }

  // if(mode != 0){
  //   Serial.write(mode);
  //   Serial.write("\n");
  // }

  switch(mode){
    case 0:
      //정렬
      movement = 0;
      break;
    case 1:
      //물결움직임
      movement = 1;
      break;
    case 2:
      //좌로 굴러
      movement = 2;
      break;
    case 3:
      //우로 굴러
      movement = 3;
      break;
    case 4:
      //상승
      movement = 4;
      break;
    case 5:
      //하강
      movement = 5;
      break;
    case 6:
      //꼬리 원위치
      movement = 6;
      break;
    case 7:
      //꼬리 원위치
      movement = 7;
      break;
    case 8:
      //꼬리 원위치
      movement = 8;
      break;
    case 9:
      // 울음소리 1
      sound = 0;
      break;
    case 10:
      // 울음소리 2
      sound = 1;
      break;
    default:
      break;
  }
  mode = -1;

  //움직임
  switch(movement){
    case 0:
      //정렬
      line_up(servo);
      break;
    case 1:
      //물결움직임
      swim(init_tail1_angle);
      break;
    case 2:
      //좌로 굴러
      swim(init_tail1_angle);
      tail_move( -1 , &movement);
      break;
    case 3:
      //우로 굴러
      swim(init_tail1_angle);
      tail_move( 1, &movement);
      break;
    case 4:
      //상승
      swim(init_tail1_angle-20);
      move(&body4, init_body4_angle-30);
      break;
    case 5:
      //하강
      swim(init_tail1_angle+20);
      move(&body4, init_body4_angle+30);
      break;
    case 6:
      //꼬리 원위치
      swim(init_tail1_angle);
      move(&body4, init_body4_angle);
      move(&tail2, init_tail2_angle);
      break;
    case 7:
      //입벌리기
      //swim(init_tail1_angle);
      move(&mouth1, 90);
      move(&mouth2, 90);
    case 8:
      //입닫기
      //swim(init_tail1_angle);
      move(&mouth1, init_mouth1_angle);
      move(&mouth2, init_mouth2_angle);
      break;
    default:
      break;
  }


  //울음소리
  // switch(sound){
  //   case -1:
  //     break;
  //   case 0:
  //     mp3Player.volume(30);
  //     mp3Player.play(1);
  //     sound = -1;
  //     break;
  //   case 1:
  //     mp3Player.volume(30);
  //     mp3Player.play(2);
  //     sound = -1;
  //     break;
  //   default:
  //     break;
  // }

  //움직임 속도
  Serial.print("movement: ");
  Serial.print(movement);
  Serial.print(" time: ");
  Serial.println(time);
  delay(100);
}

void swim(short tail_angle){
  // 물결 모양 생성
  tail1_angle = sin(time + 0) * 30 + tail_angle;
  body1_angle = sin(time + 0.25) * 15 + init_body1_angle;
  body2_angle = sin(time + 0.5) * 15 + init_body2_angle;
  body3_angle = sin(time + 0.75) * 15 + init_body3_angle;

  // 서보모터 각도 설정
  tail1.write(tail1_angle);
  body1.write(body1_angle);
  body2.write(body2_angle);
  body3.write(body3_angle);

  // 시간 증가
  time += 0.4;
}

void move(Servo* s, short angle){
  Servo& a = *s;
  int corrent_angle = a.read();
  int value = corrent_angle - angle;
  if(abs(value) < 5){
    a.write(angle);
    return 0;
  }
  if(value < 0){
    a.write(corrent_angle+5);
  }else{
    a.write(corrent_angle-5);
  }

}

void tail_move(short v, short* movement){
  int angle = tail2.read();
  int value = init_tail2_angle;
  if(v == 1){
    value = value+30 - angle;
    if(abs(value) < 5){
      tail2.write(init_tail2_angle+30);
      *movement = 1;
      return 0;
    }
  }else if(v == -1){
    value = value-30 - angle;
    if(abs(value) < 5){
      tail2.write(init_tail2_angle-30);
      *movement = 1;
      return 0;
    }
  }else{
    value = value - angle;
    if(abs(value) < 5){
      tail2.write(init_tail2_angle);
      *movement = 1;
      return 0;
    }
  }
  if(value > 0){
    tail2.write(angle+5);
  }else{
    tail2.write(angle-5);
  }
}

void line_up(Servo* servo[len_servo]){
  for(int i= 0 ; i < len_servo; i++){
    Servo& s = *servo[i];
    short a = *init_angle[i];
    short corrent_angle = s.read();
    if(abs(corrent_angle - a) < 5){
      s.write(a);
    }else{
      if(corrent_angle - a < 0){
        s.write(corrent_angle + 5);
      }else{
        s.write(corrent_angle - 5);
      }
    }
  }
}

void move_servo(Servo* servo, int value,int pDelay){
  (*servo).write(value);
  delay(pDelay);
}