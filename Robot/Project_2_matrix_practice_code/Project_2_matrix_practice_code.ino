
unsigned char start01[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};

unsigned char front[] = {0x00,0x00,0x00,0x00,0x00,0x24,0x12,0x09,0x12,0x24,0x00,0x00,0x00,0x00,0x00,0x00};

unsigned char back[] = {0x00,0x00,0x00,0x00,0x00,0x24,0x48,0x90,0x48,0x24,0x00,0x00,0x00,0x00,0x00,0x00};

unsigned char left[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x44,0x28,0x10,0x44,0x28,0x10,0x44,0x28,0x10,0x00};

unsigned char right[] = {0x00,0x10,0x28,0x44,0x10,0x28,0x44,0x10,0x28,0x44,0x00,0x00,0x00,0x00,0x00,0x00};

unsigned char STOP01[] = {0x2E,0x2A,0x3A,0x00,0x02,0x3E,0x02,0x00,0x3E,0x22,0x3E,0x00,0x3E,0x0A,0x0E,0x00};

unsigned char clear[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

//                        1     2    3    4   5     6    7    8    9    10  11   12   13   14   15   16
unsigned char happy[] = {0x00,0x00,0x00,0x00,0x24,0x4E,0x84,0x80,0x80,0x84,0x4E,0x24,0x00,0x00,0x00,0x00};
unsigned char happy2[] = {0x00,0x00,0x00,0x00,0x02,0x07,0x22,0x40,0x40,0x22,0x07,0x02,0x00,0x00,0x00,0x00};
unsigned char happy2_cligne[] = {0x00,0x00,0x00,0x00,0x02,0x02,0x22,0x40,0x40,0x22,0x02,0x02,0x00,0x00,0x00,0x00};

#define IIC_SCL  A5

#define IIC_SDA  A4

unsigned char data_line = 0;

unsigned char delay_count = 0;

void IIC_start()
{
  digitalWrite(IIC_SCL,LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SCL,HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,LOW);
  delayMicroseconds(3);}

void IIC_send(unsigned char send_data)
{
  for(char i = 0;i < 8;i++)
  {
      digitalWrite(IIC_SCL,LOW);
      delayMicroseconds(3);
      if(send_data & 0x01)
      {
        digitalWrite(IIC_SDA,HIGH);
      }
      else
      {
        digitalWrite(IIC_SDA,LOW);
      }
      delayMicroseconds(3);
      digitalWrite(IIC_SCL,HIGH);
      delayMicroseconds(3);
      send_data = send_data >> 1;
  }
}

void IIC_end()
{
  digitalWrite(IIC_SCL,LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SCL,HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,HIGH);
  delayMicroseconds(3);}

void setup(){
    pinMode(IIC_SCL,OUTPUT);
  pinMode(IIC_SDA,OUTPUT);
  digitalWrite(IIC_SCL,LOW);
  digitalWrite(IIC_SDA,LOW);
  IIC_start();
    IIC_send(0x40);
    IIC_end();
    IIC_start();
    IIC_send(0xc0);
  IIC_start();
      IIC_send(0xc0);
      for(char i = 0;i < 16;i++)
      {
         IIC_send(clear[i]);
      }
      if(++delay_count >= 10)
      {
        delay_count = 0;
        data_line++;
        if(data_line >= 4)
        {
          data_line = 0;
        }
      }
      IIC_end();
      IIC_start();
      IIC_send(0x8A);
      IIC_end();

      randomSeed(analogRead(0));
      
}

void loop(){
  IIC_start();
  IIC_send(0xc0);
  for(char i = 0;i < 16;i++)
  {
     IIC_send(happy2[i]);
  }
  if(++delay_count >= 10)
  {
    delay_count = 0;
    data_line++;
    if(data_line >= 4)
    {
      data_line = 0;
    }
  }
  IIC_end();
  IIC_start();
  IIC_send(0x8A);
  IIC_end();
  delay(random(500, 5000));
    IIC_start();
  IIC_send(0xc0);
  for(char i = 0;i < 16;i++)
  {
     IIC_send(happy2_cligne[i]);
  }
  if(++delay_count >= 10)
  {
    delay_count = 0;
    data_line++;
    if(data_line >= 4)
    {
      data_line = 0;
    }
  }
  IIC_end();
  IIC_start();
  IIC_send(0x8A);
  IIC_end();
  delay(200);

}
