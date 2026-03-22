#include "../Headers/calc.h"

Token parse_op(char c)
{
  Token temp = { 0 };

  temp.type = operatorType;

  switch (c)
    {
      case '+':
        temp.charValue = '+';
        break;
      case '-':
        temp.charValue = '-';
        break;
      case '*':
        temp.charValue = '*';
        break;
      case '/':
        temp.charValue = '/';
        break;
      case '%':
        temp.charValue = '%';
        break;
      case '^':
        temp.charValue = '^';
        break;
      case '(':
        temp.charValue = '(';
        temp.type = parentheses;
        break;
      case ')':
        temp.charValue = ')';
        temp.type = parentheses;
        break;
      default:
        break;
    }

  return temp;
}
