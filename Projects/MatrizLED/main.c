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
	int left=1;
	pullUpDnControl(7,PUD_UP);
	for (int i = 0; i < 100; ++i)
	{			
		for (int j = 0; j < 4&&left==1; j++)
		{
			printf("Going left\n");
			left = digitalRead(7);
			turnLED(j);
			delay(500);
		}
		for(int k=3;k>=0 && left==0;k--){
			printf("Going right\n");
			left = digitalRead(7);
			turnLED(k);
			delay(500);		
		}
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