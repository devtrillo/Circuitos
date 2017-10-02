#include <stdio.h>
#include <wiringPi.h>

int main(int argc, char const *argv[])
{
	printf("Turn on LED\n");
	wiringPiSetup();
	pinMode(0,OUTPUT);
	while(1){	
		digitalWrite(0,HIGH);
		delay(150);
		digitalWrite(0,LOW);
		delay(50);

	}
	return 0;
}