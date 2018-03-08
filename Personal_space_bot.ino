/***********************************************************
Personal space bot
Author: Onion Ring Studios
Date: 03.08.2018
***********************************************************/

const int latchPin = 12; //Pin connected to ST_CP of 74HC595
const int clockPin = 8;//Pin connected to SH_CP of 74HC595
const int dataPin = 11; //Pin connected to DS of 74HC595
#define trigPin 6
#define echoPin 5



unsigned char  tab[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};

int expression[] = {0, 0, 0, 0, 0, 0, 0, 0};
long duration, distance;
int t = 0;

// Expressions
int happy[]=        {0x00, 0x34, 0x32, 0x02, 0x02, 0x32, 0x34, 0x00};
int neutral[] =     {0x00, 0x30, 0x32, 0x02, 0x02, 0x32, 0x30, 0x00};
int frightened[] =  {0x00, 0x42, 0x24, 0x66, 0x00, 0x18, 0x3C, 0x00};
int sad[] =         {0x00, 0x12, 0x34, 0x04, 0x04, 0x34, 0x12, 0x00};
int angry[] =       {0x00, 0x32, 0x16, 0x06, 0x06, 0x16, 0x32, 0x00};




void setup ()
{
  //set pins to output
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  //set trigPin to output and echoPin to input for the distance sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{

 /* Ultrasonic distance sensor */
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 7000);

if(duration > 0){   // Calculates the distance
  distance = (((duration) / 2) / 29.1);
}
else if(duration == 0){
  distance = 100;
}

// sets the different facial expressions based on distance
if(distance < 15){
  for(int i=0; i<8; i++){expression[i] = angry[i];}
  t = 0;
}
else if(distance < 65){
  for(int i=0; i<8; i++){expression[i] = happy[i];}
  t = 0;
}
else if(t > 1000){ // He becomes sad after a few seconds of being alone
  for(int i=0; i<8; i++){expression[i] = sad[i];}
}
else {
  for(int i=0; i<8; i++){expression[i] = neutral[i];}
  t += 1;
}

  // Sends the data to the two 74HC595 chips
  for(int n=0; n<8; n++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,MSBFIRST, expression[n]);
    shiftOut(dataPin,clockPin,MSBFIRST,tab[n]);
    digitalWrite(latchPin,HIGH);
  }
}
