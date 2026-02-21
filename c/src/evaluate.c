#include "../Headers/calc.h"

token evaluate(token lhs, token rhs, int op_value)
{
	token temp = {0};

	switch(op_value)
	{
		case '+':
			temp.numberValue = lhs.numberValue + rhs.numberValue;
			break;
		case '-':
			temp.numberValue = lhs.numberValue - rhs.numberValue;
			break;
		case '*':
			temp.numberValue = lhs.numberValue * rhs.numberValue;
			break;
		case '/':
			if(rhs.numberValue != 0)
				temp.numberValue = lhs.numberValue / rhs.numberValue;
			else
			{
				temp.state = err;
				ERR("Division by 0");
			}
			break;
		case '%':
			if(rhs.numberValue != 0)
				temp.numberValue = lhs.numberValue % rhs.numberValue;
			else
			{
				temp.state = err;
				ERR("Division (modulo) by 0");
			}
			break;
		case '^':
			temp.numberValue = my_power(lhs.numberValue, rhs.numberValue);
			break;
	}

	temp.type = number;
	return temp;
}
