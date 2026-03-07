#include "../Headers/calc.h"

token* next_token(Buffer* buffer)
{
	token* temp = {0};

	if(is_digit(peek(0)))
		temp = parse_num(buffer);
	else if(is_operator(peek(0)))
		temp = parse_op();
	else if(peek(0) == '\0')
		temp.state = eof;
	else
		temp.state = err;

	return temp;
}
