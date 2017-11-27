#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
//Output PINS
//INPUT pins
//7,0,2,3
void Initialice();
int main(int argc, char const *argv[])
{
	srand(time(NULL));
	int sequence[100] = { 0 };
	int size = 0;
	int input = 0;
	while (size < 10)
	{
		int i = 0;
		//Set sequence
		while (i <= size) {
			if (sequence[i] == 0)
				sequence[i] = rand() % 4 + 1;
			printf("%d\n", sequence[i]);
			i++;
			delay(1000);
		}
		i = 0;
		//Recive input
		while (i <= size) {
			input = SwitchNumberInput() - '0';
			if (input != sequence[i]) {
				printf("Secuencia incorrecta\n");
				return -1;
			}
			i++;
		}
		system("CLS");
		printf("Next loop\n");
		size++;
	}
	printf("Congratulations you finished");
	return 0;
}
void Initialice() {
	pinMode(7, INPUT);
	pinMode(0, INPUT);
	pinMode(2, INPUT);
	pinMode(3, INPUT); 
	pullUpDnControl(7, PUD_UP);
	pullUpDnControl(0, PUD_UP);
	pullUpDnControl(2, PUD_UP);
	pullUpDnControl(3, PUD_UP);
}
int SwitchNumberInput() {
	int index = 999;
	while (index==999){
		if(digitalRead(7)==1)
			index=1;
		if(digitalRead(0)==1)
			index=2;
		if(digitalRead(2)==1)
			index=3;
		if(digitalRead(3)==1)
			index=4;
	}
}