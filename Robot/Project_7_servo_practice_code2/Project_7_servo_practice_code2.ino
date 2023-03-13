volatile int pulsewidth;

void procedure(int servopin, int myangle) {
  for (int i = 0; i <= 50; i = i + (1)) {
    pulsewidth = myangle * 11 + 500;
    pinMode(servopin, OUTPUT);
    digitalWrite(servopin,HIGH);
    delayMicroseconds(pulsewidth);
    pinMode(servopin, OUTPUT);
    digitalWrite(servopin,LOW);
    delay((20 - pulsewidth / 1000));
  }
}

void setup(){
  pulsewidth = 0;
}

void loop(){

  procedure(9, 100);

}
