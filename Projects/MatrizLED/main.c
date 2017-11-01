#include <stdio.h>
#include <wiringPi.h>
void turnLED(int led);
int main(int argc, char const *argv[])
{
	printf("Turn on LED\n");
	wiringPiSetup();
	pinMode(0,OUTPUT);
	pinMode(1,OUTPUT);
	pinMode(2,OUTPUT);
	pinMode(3,OUTPUT);
	pinMode(7,INPUT);
	int index=0;
	int del=500;
	pullUpDnControl(7,PUD_UP);
	while(1)
	{			
		
		if(digitalRead(7)==1){
			index=(index+1)%4;
		}else{
			index=(index-1<0)?3:index-1;
		}
		turnLED(index); 
		delay(del);
	} 
	turnLED(10);
	return 0;
}
void turnLED(int led){
	int i=0;
	while(i<4)
	{
		if(i==led){
			digitalWrite(i,HIGH);
		}else{
			digitalWrite(i,LOW);
		}
		i++;
	}
}
