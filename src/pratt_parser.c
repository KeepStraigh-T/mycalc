#include "../Headers/calc.h"

extern Buffer buffer;

token pratt_parser(int min_preced)
{
	static int preced_raise = 0;

	while(peek(0) == '(')
	{
		buffer.currentIdx++;
		preced_raise += PRECED_RAISE;
	}

	token lhs = next_token();

	while(true)
	{
		while(peek(0) == ')')
		{
			if(preced_raise > 0)
				preced_raise -= PRECED_RAISE;
			buffer.currentIdx++;
		}

		token op = next_token();

		op.preced += preced_raise;

		if(op.state == err)
		{
			lhs.state = err;
			return lhs;
		}
		else if(op.preced <= min_preced)
		{
			buffer.currentIdx--;
			break;
		}

		token rhs = pratt_parser(op.preced);
		if(rhs.state == err)
		{
			lhs.state = err;
			return lhs;
		}
		lhs = evaluate(lhs, rhs, op.charValue);
	}

	return lhs;
}
