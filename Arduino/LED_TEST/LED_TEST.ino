int RED = 3;
int BLUE = 5;
int GREEN = 6;

void setup() {
  // put your setup code here, to run once:
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 256; i++){
    analogWrite(RED,i);
    for (int j = 0 ; j < 256; j++){
      analogWrite(GREEN,j);
      for (int l = 0 ; l < 256; l++){
        analogWrite(BLUE,l);
      }
    }
  }

}
