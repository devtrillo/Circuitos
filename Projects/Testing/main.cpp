#include <stdio.h>

int main(int argc, char const *argv[])
{
	if(argc==1)
		printf("Hello World\n");
	else
		printf("Hello %s\n",argv[1]);
printf("Goodbye\n\n");
	return 0;
}