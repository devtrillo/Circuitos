#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <termios.h>

int mygetch(void);

int main(int argc, char const *argv[]) {
  int motor1=90,motor2=90;
	int c = 'x';
	while (c!='q'){
		printf("\nPress WASD to move the motors (Q to quit)\n");
		c=mygetch();
		switch(c){
			case 'A': case 'a':
				motor1=(motor1>10)?motor1-10:0;
				break;
			case 'D':case 'd':
				motor1=(motor1<=170)?motor1+10:180;
				break;
			case 'W': case 'w':
				motor2=(motor2<=170)?motor2+10:180;
				break;
			case 'S':case 's':
				motor2=(motor2>10)?motor2-10:0;
				break;
		}
		printf("Motor 1: %d\nMotor 2: %d",motor1,motor2);
	}
  return 0;
}
int mygetch(void) {
	struct termios oldt, newt;
	int ch;
	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return ch;
}
