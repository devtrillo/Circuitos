#include <stdio.h>
#include <wiringPi.h>

void Initialice();
int SwitchNumberInput();

int inputPins[] = {7, 0, 1};

int main(int argc, char const *argv[])
{

	if (wiringPiSetup() == -1) {
		printf("ERROR wiring pi\n");
		return -1;
	}
	Initialice();
	while (1) {

		SwitchNumberInput();
		delay(100);
	}

	return 0;
}

void Initialice() {
	int i = 0;
	printf("Number of input pins: %d\n", sizeof(inputPins) / sizeof(*inputPins));
	while (i < sizeof(inputPins) / sizeof(*inputPins))
	{
		pinMode(inputPins[i], INPUT);
		pullUpDnControl(inputPins[i], PUD_UP);
		printf("input pin %d set as INPUT\n", inputPins[i]);
		i++;
	}
}
int SwitchNumberInput() {
	int index = 999;
	while (index == 999) {
		
		for (int i = 0; i <  sizeof(inputPins) / sizeof(*inputPins); ++i)
		{
			delay(50);
			if (digitalRead(inputPins[i]) == 1) {
				index = i;
				printf("Pressed Button #%d, Pin #%d\n", i, inputPins[i] );
				while (digitalRead(inputPins[i]) == 1) {
					printf("Waiting\n");
					delay(100);
				}
				break;
			}
		}
	}
	return index;
}