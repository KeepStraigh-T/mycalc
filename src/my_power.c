#include "../Headers/calc.h"

long long my_power(int base, int exponent)
{
	if(exponent == 0)
		return 1;

	long long num = base;

	for(int exp = 1; exp < exponent; exp++)
		num *= base;

	return num;
}
