#include <stdio.h>
int main()
{
	float a = 0.15 + 0.15;
	float b = 0.1 + 0.2;
	if(a == b) {
		printf( "0.15 + 0.15 == 0.1 + 0.2\n");
	} else {
		printf( "0.15 + 0.15 == 0.1 + 0.2 false\n");
	}
	if(a >= b) {
		printf("0.15 + 0.15 >= 0.1 + 0.2\n");
	} else {
		printf("0.15 + 0.15 >= 0.1 + 0.2 false\n");
	}
	return 0;
}
