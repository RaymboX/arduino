void setup(){
  pinMode(12, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
}

enum e_vitesse {moyen = 150, vite = 255};

void avance(int speed)
{
  digitalWrite(12,LOW);
  analogWrite(3,speed);
  digitalWrite(13,LOW);
  analogWrite(11,speed);
}

void recule(int speed)
{
  digitalWrite(12,HIGH);
  analogWrite(3,speed);
  digitalWrite(13,HIGH);
  analogWrite(11,speed);
}

void droite(int speed)
{
  digitalWrite(12,HIGH);
  analogWrite(3,speed);
  digitalWrite(13,LOW);
  analogWrite(11,speed);
}

void gauche(int speed)
{
  digitalWrite(12,LOW);
  analogWrite(3,speed);
  digitalWrite(13,HIGH);
  analogWrite(11,speed);
}

void stop(void)
{
  digitalWrite(12,LOW);
  analogWrite(3,0);
  digitalWrite(13,LOW);
  analogWrite(11,0);
}

void loop()
{
  avance(moyen);
  delay(1000);
  recule(moyen);
  delay(1000);
  droite(moyen);
  delay(1000);
  gauche(moyen);
  delay(1000);
  stop();
  delay(1000);
}
