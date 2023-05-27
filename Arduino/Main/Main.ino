// #include <Servo.h>

// // 서보모터 핀 번호
// #define TAIL1_PIN 3
// #define TAIL2_PIN 4
// #define FIN1_PIN 5
// #define FIN2_PIN 6
// #define FIN3_PIN 7
// #define FIN4_PIN 8

// #define Trig_Pin 9
// #define Echo_Pin 10

// #define MD_in3 13
// #define MD_in4 12
// #define ENB 11

// short check = 0;
// int time_delay = 0;

// // 물결 모양 생성에 사용되는 변수
// float time = 0;
// float tail_angle = 0;
// float tail2_angle = 0;
// float fin1_angle = 0;
// float fin2_angle = 0;
// float fin3_angle = 0;
// float fin4_angle = 0;

// // 서보모터 객체 생성
// Servo tail1;
// Servo tail2;
// Servo fin1;
// Servo fin2;
// Servo fin3;
// Servo fin4;

// void swim();

// void setup() {
//   Serial.begin(9600);

//   // 서보모터 핀 초기화
//   tail1.attach(TAIL1_PIN);
//   tail2.attach(TAIL2_PIN);
//   fin1.attach(FIN1_PIN);
//   fin2.attach(FIN2_PIN);
//   fin3.attach(FIN3_PIN);
//   fin4.attach(FIN4_PIN);

//   pinMode(Trig_Pin, OUTPUT);
//   pinMode(Echo_Pin, INPUT);
//   pinMode(MD_in3, OUTPUT);
//   pinMode(MD_in4, OUTPUT);

//   delay(1000);
// }

// void loop() {
  
//   digitalWrite(Trig_Pin, LOW);
//   delayMicroseconds(2);
//   digitalWrite(Trig_Pin, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(Trig_Pin, LOW);

//   long duration = pulseIn(Echo_Pin, HIGH);
//   float distance = duration * 0.0343 / 2;

//   //Serial.print("Distance: ");
//   //Serial.print(distance);
//   //Serial.println(" cm");

//   if(distance < 100 && check != 2){
//     swim();
//     check = 1;
//     time_delay += 25;
//   }else{
//     if (check == 1 && time_delay >= 1000){
//       check = 2;
//       digitalWrite(MD_in3, HIGH);
//       digitalWrite(MD_in4, LOW);
//       analogWrite(ENB, 255);
//       Serial.println("check");
//       delay(1000);
//     }else if (check == 2){
//       digitalWrite(MD_in3, LOW);
//       digitalWrite(MD_in4, HIGH);
//       analogWrite(ENB, 255);
//       delay(500);
//       analogWrite(ENB, 0);
//       check = 0;
//     }
//     time_delay = 0;
//   }

//   delay(25);
// }

// void swim(){
//   // 물결 모양 생성
//   tail_angle = sin(time) * 30;
//   tail2_angle = sin(time + 0.25) * 30;
//   fin1_angle = sin(time + 0.5) * 30;
//   fin2_angle = sin(time + 0.75) * 30;
//   fin3_angle = sin(time + 1) * 35;
//   fin4_angle = sin(time + 1) * 35;

//   // 서보모터 각도 설정
//   tail1.write(tail_angle + 90);
//   tail2.write(tail2_angle + 90);
//   fin1.write(fin1_angle + 90);
//   fin2.write(fin1_angle + 90);
//   fin3.write(-fin2_angle + 90);
//   fin4.write(fin2_angle + 90);

//   // 시간 증가
//   time += 0.4;
// }