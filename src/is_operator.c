#include "../Headers/calc.h"

bool is_operator(char input)
{
	if(input == '+' || input == '-' || input == '*' || input == '/' ||
	   input == '^' || input == '%' || input == '^')
		return true;
	return false;
}
