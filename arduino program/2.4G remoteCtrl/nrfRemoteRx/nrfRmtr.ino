#include <arduino.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <Servo.h>


RF24  radio(5, 6);


const byte address[6] = "00001";

const int channelLib[8] = {21, 20, 19, 18, 17, 16, 15, 14};
const int outputPin[7] = {2, 3, 4, 7, 8, 9, 10};
const int powerLib[7] = {1, 2, 4, 8, 16, 32, 64};

const char getText[17][5] = {"0001", "0010", "0011", 
                             "0100", "0101", "0110", "0111", 
                             "1000", "1001", "1010", "1011", 
                             "1100", "1101", "1110", "1111", "0000"};
                             
char text[32] = "";


int channelRead(void);
bool radioPower(void);

void setup()
{
  Serial.begin(115200);
  Serial.println("Ready to reveive!");
  for(int i = 0; i < 7; i++)
  {
    pinMode(outputPin[i], OUTPUT);
    digitalWrite(outputPin[i], 0);
  }
  
  for(int i = 0; i < 8; i++)
    pinMode(channelLib[i], INPUT_PULLUP);

  radio.begin();
  radio.setChannel(channelRead());
  radio.openReadingPipe(0, address);
  
  if(!radioPower())
  {
    radio.setPALevel(RF24_PA_MIN);
    radio.setDataRate(RF24_250KBPS);
  }
  else
  {
    radio.setPALevel(RF24_PA_MAX);
    radio.setDataRate(RF24_2MBPS);
  }
  radio.startListening();
}

void loop()
{
  while(1)
  {
    if(radio.available())
    {
      radio.read(&text, sizeof(text));
      if(strcmp(text, getText[0]) == 0)
      {
        Serial.println("前进");
        digitalWrite(7, 1);
        digitalWrite(8, 0);
        digitalWrite(9, 0);
        digitalWrite(10, 0);
        delay(1200);
      }
      if(strcmp(text, getText[1]) == 0)
      {
        Serial.println("后退");
        digitalWrite(7, 0);
        digitalWrite(8, 1);
        digitalWrite(9, 0);
        digitalWrite(10, 0);
        delay(1200);
      }
      if(strcmp(text, getText[2]) == 0)
      {
        Serial.println("左转");
        digitalWrite(7, 1);
        digitalWrite(8, 1);
        digitalWrite(9, 0);
        digitalWrite(10, 0);
        delay(1200);
      }
      if(strcmp(text, getText[3]) == 0)
      {
        Serial.println("右转");
        digitalWrite(7, 0);
        digitalWrite(8, 0);
        digitalWrite(9, 1);
        digitalWrite(10, 0);
        delay(1200);
      }
      if(strcmp(text, getText[4]) == 0)
      {
        Serial.println("功能1");
        digitalWrite(7, 1);
        digitalWrite(8, 0);
        digitalWrite(9, 1);
        digitalWrite(10, 0);
        delay(1200);
      }
      if(strcmp(text, getText[5]) == 0)
      {
        Serial.println("功能2");
        digitalWrite(7, 0);
        digitalWrite(8, 1);
        digitalWrite(9, 1);
        digitalWrite(10, 0);
        delay(1200);
      }
      if(strcmp(text, getText[6]) == 0)
      {
        Serial.println("其他1");
        digitalWrite(7, 1);
        digitalWrite(8, 1);
        digitalWrite(9, 1);
        digitalWrite(10, 0);
        delay(1200);
      }
      if(strcmp(text, getText[7]) == 0)
      {
        Serial.println("其他2");
        digitalWrite(7, 0);
        digitalWrite(8, 0);
        digitalWrite(9, 0);
        digitalWrite(10, 1);
        delay(1200);
      }
      if(strcmp(text, getText[8]) == 0)
      {
        Serial.println("其他3");
        digitalWrite(7, 1);
        digitalWrite(8, 0);
        digitalWrite(9, 0);
        digitalWrite(10, 1);
        delay(1200);
      }
      if(strcmp(text, getText[9]) == 0)
      {
        Serial.println("其他4");
        digitalWrite(7, 0);
        digitalWrite(8, 1);
        digitalWrite(9, 0);
        digitalWrite(10, 1);
        delay(1200);
      }
    }
    digitalWrite(7, 0);
    digitalWrite(8, 0);
    digitalWrite(9, 0);
    digitalWrite(10, 0);
    delay(80);
  }
}

int channelRead(void)
{
  int channelNum = 0;

  if(analogRead(A7) < 70)
    channelNum = channelNum + powerLib[0];

  if(analogRead(A6) < 70)
    channelNum = channelNum + powerLib[1];

  if(!digitalRead(A5))
    channelNum = channelNum + powerLib[2];

  if(!digitalRead(A4))
    channelNum = channelNum + powerLib[3];

  if(!digitalRead(A3))
    channelNum = channelNum + powerLib[4];

  if(!digitalRead(A2))
    channelNum = channelNum + powerLib[5];

  if(!digitalRead(A1))
    channelNum = channelNum + powerLib[6];

  Serial.println(channelNum);
  return channelNum;
}

bool radioPower(void)
{
  if(digitalRead(channelLib[7]))
    return false;

  return true;
}
/*
void onTimer()
{
  radio.setChannel(channelRead());
}
*/
