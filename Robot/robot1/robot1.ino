
//SCREEN
unsigned char happy2[16] = {0x00,0x00,0x00,0x00,0x02,0x07,0x22,0x40,0x40,0x22,0x07,0x02,0x00,0x00,0x00,0x00};
unsigned char serious[16] = {0x00,0x00,0x00,0x00,0x02,0x07,0x22,0x20,0x20,0x22,0x07,0x02,0x00,0x00,0x00,0x00};
unsigned char fear[16] = {0x00,0x00,0x00,0x00,0x02,0x07,0x22,0x50,0x50,0x22,0x07,0x02,0x00,0x00,0x00,0x00};
unsigned char sad[16] = {0x00,0x00,0x00,0x00,0x02,0x07,0x42,0x20,0x20,0x42,0x07,0x02,0x00,0x00,0x00,0x00};
unsigned char happy2_cligne[16] = {0x00,0x00,0x00,0x00,0x02,0x02,0x22,0x40,0x40,0x22,0x02,0x02,0x00,0x00,0x00,0x00};
unsigned char clear[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
//							1	2	  3		4	5	6	  7		8	9	10	 11	  12	13	14	 15	  16
unsigned char right[16] = {0x00,0x00,0x00,0x00,0x00,0x08,0x14,0x22,0x41,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char fullright[16] = {0x00,0x00,0x00,0x00,0x08,0x14,0x22,0x41,0x08,0x14,0x22,0x41,0x00,0x00,0x00};
unsigned char left[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x41,0x22,0x14,0x08,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char fullleft[16] = {0x00,0x00,0x00,0x41,0x22,0x14,0x08,0x41,0x22,0x14,0x08,0x00,0x00,0x00,0x00,0x00};
unsigned char lookleft[16] = {0x00,0x00,0x00,0x00,0x02,0x02,0x27,0x20,0x20,0x22,0x02,0x07,0x00,0x00,0x00,0x00};
unsigned char lookright[16] = {0x00,0x00,0x00,0x00,0x07,0x02,0x22,0x20,0x20,0x27,0x02,0x02,0x00,0x00,0x00,0x00};

unsigned char STOP[16] = {0x2E,0x2A,0x3A,0x00,0x02,0x3E,0x02,0x00,0x3E,0x22,0x3E,0x00,0x3E,0x0A,0x0E,0x00};
unsigned char back[16] = {0x00,0x00,0x00,0x00,0x00,0x24,0x48,0x90,0x48,0x24,0x00,0x00,0x00,0x00,0x00,0x00};


void showMatrix(unsigned char matrix[16])
{
	IIC_start();
	IIC_send(0xc0);
	for(char i = 0;i < 16;i++)
		IIC_send(matrix[i]);
	IIC_end();
	IIC_start();
	IIC_send(0x8A);
	IIC_end();
}


//IIC_FUNCTIONS------------------------------
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
			digitalWrite(IIC_SDA,HIGH);
		else
			digitalWrite(IIC_SDA,LOW);
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
	delayMicroseconds(3);
}
//------------------------------------------------------------------

//ULTRASONIC FUNCTION --------------------------------------------
float checkdistance() {
	digitalWrite(5, LOW);
	delayMicroseconds(2);
	digitalWrite(5, HIGH);
	delayMicroseconds(10);
	digitalWrite(5, LOW);
	float distance = pulseIn(4, HIGH) / 58.00;
	delay(10);
	return distance;
}
//-------------------------------------------------------------


//SERVO FUNCTION-------------------------------------------------------
volatile int pulsewidth;
int servopin;
enum e_angle {droite90 = 0, droite45 = 50, avant = 100, gauche45 = 150, gauche90 = 200};

void servoTurn(int myangle) 
{
	for (int i = 0; i <= 50; i = i + (1))
	{
		pulsewidth = myangle * 11 + 500;
		pinMode(servopin, OUTPUT);
		digitalWrite(servopin,HIGH);
		delayMicroseconds(pulsewidth);
		pinMode(servopin, OUTPUT);
		digitalWrite(servopin,LOW);
		delay((20 - pulsewidth / 1000));
	}
}
//---------------------------------------------------------------------

//MOTEURS FUNCTIONS-----------------------------------------------

int moyen[2] = {150, 100};
int vite[2] = {255, 195};

void avance(int speed[2])
{
	digitalWrite(12,LOW);
	analogWrite(3,speed[0]);
	digitalWrite(13,LOW);
	analogWrite(11,speed[1]);
}

void recule(int speed[2])
{
	digitalWrite(12,HIGH);
	analogWrite(3,speed[0]);
	digitalWrite(13,HIGH);
	analogWrite(11,speed[1]);
}

void droite(int speed[2])
{
	digitalWrite(12,HIGH);
	analogWrite(3,speed[0]);
	digitalWrite(13,LOW);
	analogWrite(11,speed[1]);
}

void gauche(int speed[2])
{
	digitalWrite(12,LOW);
	analogWrite(3,speed[0]);
	digitalWrite(13,HIGH);
	analogWrite(11,speed[1]);
}

void stop(void)
{
	digitalWrite(12,LOW);
	analogWrite(3,0);
	digitalWrite(13,LOW);
	analogWrite(11,0);
}
//-----------------------------------------------------------------------

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

	//ultrasonic
	Serial.begin(9600);
	pinMode(5, OUTPUT);
	pinMode(4, INPUT);	

	//moteurs
	pinMode(12, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(13, OUTPUT);
	pinMode(11, OUTPUT);

	//SERVO
	pulsewidth = 0;
	servopin = 9;
	servoTurn(avant);

	//Matrix
	showMatrix(happy2);

	//for randoming stuff
	randomSeed(analogRead(0));
}


int farSide()
{
	float	distScan[2] = {0, 0};
	int direction;
	int	servoAngle = 0;
	
	for (int i = 0; i < 4; i++)
	{
		servoTurn(servoAngle);
		distScan[0] = checkdistance();
		if (distScan[0] > distScan[1])
		{
			distScan[1] = distScan[0];
			direction = i;
			switch (i)
			{
				case 0:
					showMatrix(fullright);
					break;
				case 1:
					showMatrix(right);
					break;
				case 2:
					showMatrix(left);
					break;
				case 3:
					showMatrix(fullleft);
					break;
			}
		}
		servoAngle += 50;
		if (servoAngle == 100)
			servoAngle += 40;
	}
	servoTurn(avant);
	return direction;
}

void	directionTurn(int direction)
{
	int turnTime;

	if (direction == 0 || direction == 3)
		turnTime = 1000;
	else
		turnTime = 650;
	if (direction <= 1)
	{
		showMatrix(lookright);
		droite(moyen);
	}
	else
	{
		showMatrix(lookleft);
		gauche(moyen);
	}
	delay(turnTime);
	stop();
}

void tooNear()
{
	int dist;
		
	delay(400);
	dist = checkdistance();
	if (dist < 15 || dist > 100)//trop proche ou capteur vraiment trop proche
	{
		showMatrix(sad);
		recule(moyen);
		delay(700);
		stop();
		delay(200);
		showMatrix(fear);
	}
}

void	turnBestWay()
{
	tooNear();
	while (checkdistance() < 50)
	{
		tooNear();
		showMatrix(fear);
		directionTurn(farSide());
		delay(300);
	}
	delay(200);
}


float distance;
float preDistance;
int nbLoop = 0;
int stade = 0;

int	inRange(float ref, float actual, float range)
{
	if (actual >= ref - range && actual <= ref + range)
		return 1;
	return 0;
}

int jamCheck(float distance)
{
	if (inRange(preDistance, distance, 3) == 1)
	{
		showMatrix(back);
		stop();
		delay(500);
		recule(vite);
		delay(750);
		stop();
		if (inRange(distance, checkdistance(), 5) == 1)
		{
			directionTurn(farSide());
			delay(300);
			if (inRange(distance, checkdistance(), 10) == 1)
			{
				showMatrix(STOP);
				return 1;
			}
		}
	}
	else
		preDistance = distance;
	return 0;
}


void loop()
{
	distance = checkdistance();
	if (nbLoop == 50)
	{
		if (jamCheck(distance) == 1)
			exit(0);
		else
			nbLoop = 0;
	}
	nbLoop++;
	if (distance > 100)
	{
		if (stade != 1)
		{
			avance(vite);
			showMatrix(happy2);
			stade = 1;
		}
	}
	else if (distance > 30)
	{
		if (stade != 2)
		{
			showMatrix(serious);
			avance(moyen);
			stade = 2;
		}
	}
	else
	{	
		showMatrix(fear);
		stop();
		turnBestWay();
		stade = 0;
	}
}
