#include "../Headers/calc.h"

extern Buffer buffer;

token parse_int()
{
	token temp = {0};

	long long num   = 0;
	int digits      = 0;
	bool isNegative = false;

	if(peek(0) == '-')
	{
		isNegative = true;
		buffer.currentIdx++;
	}

	for(int i = 0; is_number(peek(i)); i++)
		digits++;

	for(int i = digits - 1; i >= 0; i--)
		num += (buffer.ptr[buffer.currentIdx++] - '0') * my_power(10, i);

	if(isNegative)
		num *= -1;

	temp.numberValue = num;
	temp.type        = number;

	return temp;
}
