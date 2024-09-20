#include <stdlib.h>

void fun() {
	char *leak = malloc(sizeof(int) * 100);

}

int main()
{
	fun();

	return 0;
}
