#include <stdio.h>
#include <wiringPi.h>

int main(int argc, char const *argv[])
{
	printf("Turn on LED\n");
	wiringPiSetup();
	pinMode(25, OUTPUT);
	pinMode(29, OUTPUT);
	for (int i = 0; i < 1; ++i)
	{
		digitalWrite(29, LOW);
		delay(100);
		digitalWrite(29, HIGH);
		delay(1000);

	}
	return 0;
}