#include "../Headers/calc.h"

extern Buffer buffer;

token next_token()
{
	token temp = {0};

	if(buffer.currentIdx == 0 && peek(0) == '-') // if '-' is a first token
		temp = parse_int();
	else if(peek(-1) == '(' && peek(0) == '-') // '-' token after '('
		temp = parse_int();
	else if(is_number(peek(0)))
		temp = parse_int();
	else if(is_operator(peek(0)))
		temp = parse_op();
	else if(peek(0) == '\0')
		temp.state = eof;
	else
		temp.state = err;

	return temp;
}
