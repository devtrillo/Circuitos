#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>

int Initialice();
int SwitchNumberInput();
void ShowSequence();

int inputPins[] = {7, 0, 2, 3};
int outputPins[] = {29, 28, 27, 25};
int sequence[10] = { 0 };

int main(int argc, char const * argv[])
{

	if (wiringPiSetup() == -1) {
		printf("ERROR wiring pi\n");
		return -1;
	}
	if (Initialice() == -1) {
		printf("ERROR in array sizes\n");
		return -2;
	}
	for (int i = 0; i < sizeof(sequence) / sizeof(*sequence); ++i)
	{
		ShowSequence(i);
		for (int j = 0; j <= i; ++j)
		{
			int  index = SwitchNumberInput();
			if (index != sequence[i]) {
				printf("Secuencia incorrecta\n");
				printf("index = %d | sequence[i] = %d\n", index, sequence[i]);
				return -1;
			}
		}
	}
	return 0;
}
int Initialice() {
	int outputSize = sizeof(outputPins) / sizeof(*outputPins);
	int inputSize = sizeof(inputPins) / sizeof(*inputPins);
	if (inputSize != outputSize)
		return -1;
	srand(time(NULL));
	for (int i = 0; i <  inputSize; ++i)
	{
		pinMode(inputPins[i], INPUT);
		pullUpDnControl(inputPins[i], PUD_UP);
		printf("Pin %d set as INPUT\n", inputPins[i]);
	}
	for (int i = 0; i <  outputSize; ++i) {
		pinMode(outputPins[i], OUTPUT);
		digitalWrite(outputPins[i], HIGH);
		printf("Pin %d set as OUTPUT\n", outputPins[i]);
	}
	return 0;
}
int SwitchNumberInput() {
	int index = 999;
	while (index == 999) {
		for (int i = 0; i <  sizeof(inputPins) / sizeof(*inputPins); ++i)
		{
			printf("checking  button %d\n", i);
			delay(200);
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
void ShowSequence(int size) {
	for (int i = 0; i <= size; ++i)
	{
		if (sequence[i] == 0)
			sequence[i] = i % sizeof(outputPins) / sizeof(*outputPins);
		//sequence[i] =  sizeof(outputPins) / sizeof(*outputPins);
		printf("%d\n", sequence[i]);
		digitalWrite(outputPins[sequence[i]], LOW);
		delay(2000);
		digitalWrite(outputPins[sequence[i]], HIGH);

	}
}