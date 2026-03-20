#include "../Headers/calc.h"

Token evaluate_tokens(Token op, Token lhs, Token rhs)
{
	if(op.l_bp == 0 && op.r_bp > 0) // prefix operators
	{
		switch(op.charValue)
		{
			case '+': // unary +
				return rhs;
			case '-': // unary -
				rhs.numberValue *= -1;
				return rhs;
		}
	}
	else if(op.l_bp > 0 && op.r_bp == 0) // postfix operators
	{
		// switch(op.charValue)
		// {
		//           case '!':
		// 	lhs.numberValue = my_power()
		// }
	}
	else // infix operators
	{
		switch(op.charValue)
		{
			case '+':
				lhs.numberValue += rhs.numberValue;
				return lhs;
			case '-':
				lhs.numberValue -= rhs.numberValue;
				return lhs;
			case '*':
				lhs.numberValue *= rhs.numberValue;
				return lhs;
			case '/':
				lhs.numberValue /= rhs.numberValue;
				return lhs;
			case '^':
				lhs.numberValue =
				    my_power(lhs.numberValue, (int)rhs.numberValue);
				return lhs;
				// fix this (modulo operation cannot be applied on real numbers)
				//  case '%':
				//      lhs.numberValue %= rhs.numberValue;
				//      return lhs;
		}
	}
}
