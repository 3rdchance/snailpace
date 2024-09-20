#include <stdlib.h>

int main()
{
	int* stack = malloc(sizeof(int) * 100);

	stack[100] = -1;
	return 0;
}
