#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

#define RED 0
#define GREEN 1
#define BLUE 2

void setColor(int r,int g, int b){
	softPwmWrite(RED,r);
	softPwmWrite(GREEN,g);
	softPwmWrite(BLUE,b);
	printf("R: %d G: %d B: %d\n",r,g,b);
	delay(25);
}

int main(int argc, char const *argv[])
{
	wiringPiSetup();
	softPwmCreate(RED, 0, 100);
	softPwmCreate(GREEN, 0, 100);
	softPwmCreate(BLUE, 0, 100);
	while(1){
		int i=0;
		while(i<255){
			setColor(255-i,i,(125+i)%255);			
			i++;
		}
		while(i>0){
			setColor(255-i,i,(125+i)%255);			
			i--;
		}
		
	}
}
