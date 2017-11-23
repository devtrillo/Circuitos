#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <unistd.h>
//#include <termios.h>
#include <conio.h>

void delay(int milli_seconds)
{
	clock_t start_time = clock();
	while (clock() < start_time + milli_seconds)
		;
}

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
			input = _getch() - '0';
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
