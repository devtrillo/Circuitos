#include <stdio.h>
#include <conio.h>

int main(){
	int motor1=90,motor2=90;
	char c = 'x';
	while (c!='q'){
		printf("\nPress WASD to move the motors (Q to quit)\n");
		c=getch();
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
