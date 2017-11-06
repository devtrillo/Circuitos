#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#define LED 24

void Servo(void);
void MoveServo(int);

int main(int argc, char const *argv[]) {
  wiringPiSetup();
  int number=35;
  Servo();
  while(number!=-1){
    MoveServo(number);
	  printf("Enter a value (-1 to exit)");
	  scanf("%d",&number);
  }
  return 0;
}
void Servo(void){
	pinMode(24,PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(384);//cloak at 50kHz
	pwmSetRange(1000);//Range at 1000 ticks (20ms)
	pwmWrite(24,35);
}
void MoveServo(int position){
	unsigned int value=35+(position/2.25)	;
	printf("Value: %d  |  Position: %d\n",value,position);
	pwmWrite(24,value);
}
