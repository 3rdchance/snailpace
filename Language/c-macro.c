/* 1. can # define a const string 
 *    1.1 MACRO will use multiple times, macro name should __str__##name, for
 *    name redefinition
 * */

#include <stdio.h>
#include <stdlib.h>


#define PRINT(name)              \
    const char* __str__##name = #name; \
    printf("name in macro %s\n", __str__##name);



int main()
{
	/* test1: macro to string */
	PRINT(hello);
	int a = 2;
	PRINT(a);



	return 0;
}
