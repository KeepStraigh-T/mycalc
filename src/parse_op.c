#include "../Headers/calc.h"

extern Buffer buffer;

token parse_op()
{
  token temp = {0};

  if(is_operator(peek(0)))
  {
    switch (peek(0)) 
    {
      case '+':
        temp.charValue = '+';
        temp.preced = 1;
        break;
      case '-':   
        temp.charValue = '-';
        temp.preced = 1;
        break;
      case '*':
        temp.charValue = '*';
        temp.preced = 2;
        break;
      case '/':
        temp.charValue = '/';
        temp.preced = 2;
        break;
      case '%':
        temp.charValue = '%'; 
        temp.preced = 2;
        break;
      case '(':
        temp.charValue = '(';
        temp.preced = 0;
        break;
      case ')':
        temp.charValue = ')';
        temp.preced = 0;
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
