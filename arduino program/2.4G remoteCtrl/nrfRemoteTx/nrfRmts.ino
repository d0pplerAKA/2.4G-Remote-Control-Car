#include <arduino.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>


RF24  radio(2, 3);

const byte address[6] = "00001";

const int channelLib[8] = {4, 5, 6, 7 ,8 ,9, 20, 21};
const int buttonLib[6] = {14, 15, 16, 17, 18, 19};
const int powerLib[7] = {1, 2, 4, 8, 16, 32, 64};

const char text[17][5] = {"0010", "0001", "0011", 
                          "0100", "0101", "0110", "0111", 
                          "1000", "1001", "1010", "1011", 
                          "1100", "1101", "1110", "1111", "0000"};
                          
const int led = 10;


int channelRead(void);
bool radioPower(void);

void setup()
{  
  pinMode(led, OUTPUT);
  digitalWrite(led, 1);

  for(int i = 0; i < 8; i++)
    pinMode(channelLib[i], INPUT_PULLUP);
    
  for(int i = 0; i < 6; i++)
    pinMode(buttonLib[i], INPUT_PULLUP);

  radio.begin();
  radio.setChannel(channelRead());
  radio.openWritingPipe(address);
  
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
  
  for(int i = 0; i < 4; i++)
  {
    digitalWrite(led, 0);
    delay(50);
    digitalWrite(led, 1);
    delay(50); 
  }

  radio.stopListening();
}

void loop()
{
  int temp;
  digitalWrite(led, 1);
   
  while(1)
  {
    for(temp = 0; temp < 6; temp++)
    { 
      if(digitalRead(buttonLib[temp]) == 0)
      {
        delay(3);
        digitalWrite(led, 0);
        radio.write(&text[temp], sizeof(text[temp]));
      }
    }
    /*
    if(digitalRead(buttonLib[0]) == 0 && digitalRead(buttonLib[2]) == 0)
    {
      delay(5);
      radio.write(&text[6], sizeof(text[6]));
      digitalWrite(led, 0); 
      delay(500);
    }
    if(digitalRead(buttonLib[0]) == 0 && digitalRead(buttonLib[3]) == 0)
    {
      delay(5);
      radio.write(&text[7], sizeof(text[7]));
      digitalWrite(led, 0);
      delay(500);
    }
    if(digitalRead(buttonLib[0]) == 0 && digitalRead(buttonLib[4]) == 0)
    {
      delay(5);
      radio.write(&text[8], sizeof(text[8]));
      digitalWrite(led, 0);
      delay(500);
    }
    if(digitalRead(buttonLib[0]) == 0 && digitalRead(buttonLib[5]) == 0)
    {
      delay(5);
      radio.write(&text[9], sizeof(text[9]));
      digitalWrite(led, 0);
      delay(500);
    }


    if(digitalRead(buttonLib[1]) == 0 && digitalRead(buttonLib[2]) == 0)
    {
      delay(5);
      radio.write(&text[6], sizeof(text[6]));
      digitalWrite(led, 0);
      delay(500);
    }
    if(digitalRead(buttonLib[1]) == 0 && digitalRead(buttonLib[3]) == 0)
    {
      delay(5);
      radio.write(&text[7], sizeof(text[7]));
      digitalWrite(led, 0);
      delay(500);
    }
    if(digitalRead(buttonLib[1]) == 0 && digitalRead(buttonLib[4]) == 0)
    {
      delay(5);
      radio.write(&text[8], sizeof(text[8]));
      digitalWrite(led, 0);
      delay(500);
    }
    if(digitalRead(buttonLib[1]) == 0 && digitalRead(buttonLib[5]) == 0)
    {
      delay(5);
      radio.write(&text[9], sizeof(text[9]));
      digitalWrite(led, 0);
      delay(500);
    }
    */
    digitalWrite(led, 1); 
  }
}

int channelRead(void)
{
  int channelNum = 0;

  for(int i = 0; i < 6; i++)
  {
    if(!digitalRead(channelLib[i]))
    channelNum = channelNum + powerLib[i];
  }
  
  if(analogRead(channelLib[6]) < 70)
  {
    channelNum = channelNum + powerLib[6];
  }

  return channelNum;
}

bool radioPower(void)
{
  if(analogRead(channelLib[7]) > 900)
    return false;

  return true;
}

void onTimer()
{
  radio.setChannel(channelRead());
}
