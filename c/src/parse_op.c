#include "../Headers/calc.h"

char parse_op(Buffer* buffer)
{

	if(is_operator(peek(0)))
	{
		switch(peek(0))
		{
			case '+':
				temp.charValue = '+';
				temp.preced    = 1;
				break;
			case '-':
				temp.charValue = '-';
				temp.preced    = 1;
				break;
			case '*':
				temp.charValue = '*';
				temp.preced    = 2;
				break;
			case '/':
				temp.charValue = '/';
				temp.preced    = 2;
				break;
			case '%':
				temp.charValue = '%';
				temp.preced    = 2;
				break;
			case '^':
				temp.charValue = '^';
				temp.preced    = 3;
				break;
			case '(':
				temp.charValue = '(';
				temp.preced    = 0;
				break;
			case ')':
				temp.charValue = ')';
				temp.preced    = 0;
				break;
			default:
				break;
		}
		buffer.currentIdx++;
		temp.type = operator;
		return temp;
	}

	return temp;
}
