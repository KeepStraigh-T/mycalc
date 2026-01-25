#include "../Headers/calc.h"

extern Buffer buffer;

token next_token()
{
	token temp = {0};

	if(buffer.currentIdx == 0 && peek(0) == '-') // the very first number
		temp = parse_int();
	else if(is_number(peek(0)))
		temp = parse_int();
	else if(is_operator(peek(0)))
		temp = parse_op();
	// else if(peek(0) == '(')
	// {
	//   buffer.currentIdx++;
	//   temp = parse_int();
	// }
	// else if(peek(0) == ')')
	// {
	//   buffer.currentIdx++;
	//   temp.charValue = ')';
	// }
	else if(peek(0) == '\0')
		temp.state = eof;
	else
		temp.state = err;

	return temp;
}
