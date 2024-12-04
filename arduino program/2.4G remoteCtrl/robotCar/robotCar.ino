#include <Arduino.h>
#include <Servo.h>


const int outputPin[] = {4, 5, 6, 7, 8, 9, 10, 11};
const int inputPin[] = {14, 15, 16, 17};

Servo servo;


void mForward(void);
void mBakcward(void);
void mLeft(void);
void mRight(void);
void mStop(void);
void mVoid(void);
void servoUp(void);
void servoDown(void);
void mShiftLeft(void);
void mShiftRight(void);
int readStatus(void);


void setup()
{ 
  Serial.begin(115200);
  
  servo.attach(3, 500, 2550);
  servo.write(140);

  for(int i = 0; i < 8; i++)
  {
    pinMode(outputPin[i], OUTPUT);
    digitalWrite(outputPin[i], 0);
  }

  for(int i = 0; i < 4; i++)
  {
    pinMode(inputPin[i], INPUT_PULLUP);
  }
}

void loop()
{
  int rs = 0;
  while(1)
  {
    rs = readStatus();
    Serial.println(rs);
    if(rs == 0)
      //mStop();
      mVoid();
    if(rs == 1)
      mForward();
    if(rs == 2)
      mBackward();
    if(rs == 3)
      mLeft();
    if(rs == 4)
      mRight();
    if(rs == 5)
      //servoUp();
      mShiftLeft();
    if(rs == 6)
      //servoDown();
      mShiftRight();
    if(rs == 7)
      mShiftLeft();
    if(rs == 8)
      mShiftRight();
    mStop();
    //mVoid();
  }
}

void mForward(void)
{
  digitalWrite(4, 0);
  digitalWrite(5, 1);
  digitalWrite(6, 0);
  digitalWrite(7, 1);
  digitalWrite(8, 0);
  digitalWrite(9, 1);
  digitalWrite(10, 0);
  digitalWrite(11, 1);
  delay(1200);
}

void mBackward(void)
{
  digitalWrite(4, 1);
  digitalWrite(5, 0);
  digitalWrite(6, 1);
  digitalWrite(7, 0);
  digitalWrite(8, 1);
  digitalWrite(9, 0);
  digitalWrite(10, 1);
  digitalWrite(11, 0);
  delay(1200);
}

void mLeft(void)
{
  digitalWrite(4, 1);
  digitalWrite(5, 0);
  digitalWrite(6, 1);
  digitalWrite(7, 0);
  digitalWrite(8, 0);
  digitalWrite(9, 1);
  digitalWrite(10, 0);
  digitalWrite(11, 1);
  delay(1200);
}

void mRight(void)
{
  digitalWrite(4, 0);
  digitalWrite(5, 1);
  digitalWrite(6, 0);
  digitalWrite(7, 1);
  digitalWrite(8, 1);
  digitalWrite(9, 0);
  digitalWrite(10, 1);
  digitalWrite(11, 0);
  delay(1200);
}

void mStop(void)
{
  digitalWrite(4, 1);
  digitalWrite(5, 1);
  digitalWrite(6, 1);
  digitalWrite(7, 1);
  digitalWrite(8, 1);
  digitalWrite(9, 1);
  digitalWrite(10, 1);
  digitalWrite(11, 1);
  delay(85);
}
void mVoid(void)
{
  digitalWrite(4, 0);
  digitalWrite(5, 0);
  digitalWrite(6, 0);
  digitalWrite(7, 0);
  digitalWrite(8, 0);
  digitalWrite(9, 0);
  digitalWrite(10, 0);
  digitalWrite(11, 0);
  delay(80);
}

void servoUp(void)
{
  servo.write(140);
  delay(2000);
}

void servoDown(void)
{
  servo.write(125);
  delay(2000);
}

void mShiftLeft(void)
{
  digitalWrite(4, 0);
  digitalWrite(5, 1);
  digitalWrite(6, 1);
  digitalWrite(7, 0);
  digitalWrite(8, 0);
  digitalWrite(9, 1);
  digitalWrite(10, 1);
  digitalWrite(11, 0);
  delay(1000);
}

void mShiftRight(void)
{
  digitalWrite(4, 1);
  digitalWrite(5, 0);
  digitalWrite(6, 0);
  digitalWrite(7, 1);
  digitalWrite(8, 1);
  digitalWrite(9, 0);
  digitalWrite(10, 0);
  digitalWrite(11, 1);
  delay(1000);
}

int readStatus(void)
{
  int aBit, bBit, cBit, dBit, rStatus;

  aBit = digitalRead(A0);
  bBit = digitalRead(A1);
  cBit = digitalRead(A2);
  dBit = digitalRead(A3);

  rStatus = aBit*1 + bBit*2 + cBit*4 + dBit*8;

  return rStatus;
}
