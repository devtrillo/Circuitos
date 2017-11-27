#include <stdio.h>
#include <wiringPi.h>

void Initialice();
int SwitchNumberInput();

int inputPins[] = {7, 0, 2, 3};
int outputPins[] = {26, 27, 28, 29};

int main(int argc, char const *argv[])
{

	if (wiringPiSetup() == -1) {
		printf("ERROR wiring pi\n");
		return -1;
	}
	Initialice();
	for (int i = 0; i < 10; ++i)
	{
		SwitchNumberInput();
	}
}
void Initialice() {
	for (int i = 0; i <  sizeof(inputPins) / sizeof(*inputPins); ++i)
	{
		pinMode(inputPins[i], INPUT);
		pullUpDnControl(inputPins[i], PUD_UP);
		printf("input pin %d set as INPUT\n", inputPins[i]);
	}
}
int SwitchNumberInput() {
	int index = 999;
	while (index == 999) {
		for (int i = 0; i <  sizeof(inputPins) / sizeof(*inputPins); ++i)
		{
			delay(1000);
			printf("checking button %d\n", i);
			if (digitalRead(inputPins[i]) == 1) {
				index = inputPins[i];
				printf("Pressed Button #%d, Pin #%d\n", i + 1, inputPins[i] );
				while (digitalRead(inputPins[i]) == 1) {
					delay(200);
				}
				break;
			}
		}
	}
	return index;
}