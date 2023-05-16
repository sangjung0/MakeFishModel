#include <Servo.h>

Servo servo[6];

const short servo_pin[6] ={3,4,5,6,7,8};
const short len_servo_pin = 6;

int servo_value[6] = {0};

const short motion_1[20][len_servo_pin]={
  {45,90,15,165,15,135},
  {45,90,15,165,15,135},
  {90,45,165,15,165,45},
  {90,45,165,15,165,45},
  {45,90,15,165,15,135},
  {45,90,15,165,15,135},
  {90,45,165,15,165,45},
  {90,45,165,15,165,45},
  {45,90,15,165,15,135},
  {45,90,15,165,15,135},
  {90,45,165,15,165,45},
  {90,45,165,15,165,45},
  {45,90,15,165,15,135},
  {45,90,15,165,15,135},
  {90,45,165,15,165,45},
  {90,45,165,15,165,45},
  {45,90,15,165,15,135},
  {45,90,15,165,15,135},
  {90,45,165,15,165,45},
  {90,45,165,15,165,45}
  };

const short motion_1_Time[20]={
  90,
  90,
  90,
  90,
  90,
  90,
  90,
  90,
  90,
  90,
  90,
  90,
  90,
  90,
  90,
  90,
  90,
  90,
  90,
  90
  };

void move_servo(Servo* servo, int value,int pDelay);
void move_motion(Servo servo[], short motion[][len_servo_pin], short motion_Time[]);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i=0; i<len_servo_pin;i++){
    servo[i].attach(servo_pin[i]);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
  for(int i=0;i<len_servo_pin;i++){
    move_servo(&servo[i],90,0);
  }
  delay(2000);
  move_motion(servo, motion_1, motion_1_Time);

}

void move_servo(Servo* servo, int value,int pDelay){
  (*servo).write(value);
  delay(pDelay);
}

void move_motion(Servo servo[], short motion[][len_servo_pin], short motion_Time[]){
  int len = 20;
  for(int i=0; i<len;i++){
    for(int j=0;j<len_servo_pin;j++){
      servo[j].write(motion[i][j]);
    }
    delay(motion_Time[i]);
  }
}