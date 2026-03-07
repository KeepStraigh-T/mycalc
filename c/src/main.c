#include "../Headers/calc.h"

Buffer buffer = {0};

int main()
{
	puts("Type a mathemetical expression");
	puts("or type \"quit\" to quit");
	// printf("%lu bytes\n", sizeof(long double));
	// printf("%lu bytes\n", sizeof(long long));
	return mainloop();
}
