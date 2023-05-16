#include <Servo.h>

// 서보모터 핀 번호
#define TAIL1_PIN 3
#define TAIL2_PIN 4
#define FIN1_PIN 5
#define FIN2_PIN 6
#define FIN3_PIN 7
#define FIN4_PIN 8

// 물결 모양 생성에 사용되는 변수
float time = 0;
float tail_angle = 0;
float fin1_angle = 0;
float fin2_angle = 0;
float fin3_angle = 0;
float fin4_angle = 0;

// 서보모터 객체 생성
Servo tail1;
Servo tail2;
Servo fin1;
Servo fin2;
Servo fin3;
Servo fin4;

void setup() {
  // 서보모터 핀 초기화
  tail1.attach(TAIL1_PIN);
  tail2.attach(TAIL2_PIN);
  fin1.attach(FIN1_PIN);
  fin2.attach(FIN2_PIN);
  fin3.attach(FIN3_PIN);
  fin4.attach(FIN4_PIN);
  delay(10000);
}

void loop() {
  // 물결 모양 생성
  tail_angle = sin(time) * 30;
  fin1_angle = sin(time + 0.25) * 30;
  fin2_angle = sin(time + 0.5) * 30;
  fin3_angle = sin(time + 0.75) * 30;
  fin4_angle = sin(time + 1) * 30;

  // 서보모터 각도 설정
  tail1.write(tail_angle + 90);
  tail2.write(-tail_angle + 90);
  fin1.write(fin1_angle + 90);
  fin2.write(-fin1_angle + 90);
  fin3.write(fin2_angle + 90);
  fin4.write(-fin2_angle + 90);

  // 시간 증가
  time += 0.1;
  delay(25);
}