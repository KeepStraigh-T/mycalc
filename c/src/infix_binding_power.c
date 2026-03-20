#include "../Headers/calc.h"

void infix_binding_power(Token* op)
{
	switch(op->charValue)
	{
		case '+':
			op->l_bp = 1;
			op->r_bp = 2;
			break;
		case '-':
			op->l_bp = 1;
			op->r_bp = 2;
			break;
		case '*':
			op->l_bp = 3;
			op->r_bp = 4;
			break;
		case '/':
			op->l_bp = 3;
			op->r_bp = 4;
			break;
		case '^':
			op->l_bp = 7;
			op->r_bp = 6;
			break;
			// case '%':
			// 	op->l_bp = 3;
			// 	op->r_bp = 4;
			// 	break;
	}

	return;
}
