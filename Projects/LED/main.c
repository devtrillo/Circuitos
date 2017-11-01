#include <stdio.h>
#include <wiringPi.h>

int main(int argc, char const *argv[])
{
	printf("Turn on LED\n");
	wiringPiSetup();
	pinMode(7,OUTPUT);
	while(1){	
		digitalWrite(7,HIGH);
		delay(10);
		digitalWrite(7,LOW);
		delay(100);

	}
	return 0;
}