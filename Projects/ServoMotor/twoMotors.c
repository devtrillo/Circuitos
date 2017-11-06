#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <unistd.h>
#include <termios.h>
#define LED 24

void Servo(void);
void MoveServo(int,int);
int mygetch(void);

int main(int argc, char const *argv[]) {
  wiringPiSetup();
  Servo();
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
				mo,or1=(motor1<=170)?motor1+10:180;
				break;
			case 'W': case 'w':
				motor2=(motor2<=170)?motor2+10:180;
				break;
			case 'S':case 's':
				motor2=(motor2>10)?motor2-10:0;
				break;
		}
		MoveServo(motor1,motor2);
		printf("Motor 1: %d\nMotor 2: %d",motor1,motor2);
	}
  return 0;
}
void Servo(void){
  pinMode(24,PWM_OUTPUT);
	pinMode(26,PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(384);//cloak at 50kHz
	pwmSetRange(1000);//Range at 1000 ticks (20ms)
  MoveServo(90,90);
}
void MoveServo(int motor1,int motor2){
	unsigned int value1=35+(motor1/2.25)	;
  unsigned int value2=35+(motor2/2.25)	;
	pwmWrite(24,value1);
  pwmWrite(26,value2);
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
