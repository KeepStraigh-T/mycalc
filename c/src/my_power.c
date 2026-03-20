#include "../Headers/calc.h"

long double my_power(long double base, int exponent)
{
	if(exponent == 0.0)
		return 1.0;

	long double num = base;

	for(int exp = 1; exp < exponent; exp++)
		num *= base;

	return num;
}
