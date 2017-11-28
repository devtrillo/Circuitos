#include <stdio.h>
#include <wiringPi.h>

int Initialice();
int SwitchNumberInput();

int inputPins[] = {7, 0, 2, 3};
int outputPins[] = {29, 28, 27, 26};
int powerPins[] = {25, 24, 23, 22};

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

int Initialice() {
	int outputSize = sizeof(outputPins) / sizeof(*outputPins);
	int inputSize = sizeof(inputPins) / sizeof(*inputPins);
	if (inputSize != outputSize)
		return -1;
	for (int i = 0; i <  inputSize; ++i)
	{
		pinMode(inputPins[i], INPUT);
		pullUpDnControl(inputPins[i], PUD_DOWN);
		printf("Pin %d set as INPUT\n", inputPins[i]);
	}
	for (int i = 0; i <  outputSize; ++i) {
		pinMode(outputPins[i], OUTPUT);
		digitalWrite(outputPins[i], LOW);
		printf("Pin %d set as OUTPUT\n", outputPins[i]);
	}
	for (int i = 0; i <  outputSize; ++i) {
		pinMode(powerPins[i], OUTPUT);
		digitalWrite(powerPins[i], HIGH);
		printf("Pin %d set as POWER\n", powerPins[i]);
	}
	return 0;
}
int SwitchNumberInput() {
	int index = 999;
	while (index == 999) {

		for (int i = 0; i <  sizeof(inputPins) / sizeof(*inputPins); ++i)
		{
			//printf("checking  button %d\n", i);
			if (digitalRead(inputPins[i]) == 1) {
				index = i;
				printf("Pressed Button #%d, Pin #%d\n", i + 1, inputPins[i] );
				while (digitalRead(inputPins[i]) == 1) {
					;
				}
				break;
			}
		}
	}
	return index;
}