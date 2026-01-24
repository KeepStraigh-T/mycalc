#include "../Headers/calc.h"

token evaluate(token lhs, token rhs, int op_value)
{
  token temp = {0};

  switch (op_value) 
  {
    case add:
      temp.numberValue = lhs.numberValue + rhs.numberValue;
      break;
    case substruct:
      temp.numberValue = lhs.numberValue - rhs.numberValue;
      break;
    case multiply:
      temp.numberValue = lhs.numberValue * rhs.numberValue;
      break;
    case divide:
      if(rhs.numberValue != 0)
        temp.numberValue = lhs.numberValue / rhs.numberValue;
      else
      {
        temp.state = err;
        ERR("Division by 0");
      }
      break;
    case modulo:
      if(rhs.numberValue != 0)
        temp.numberValue = lhs.numberValue % rhs.numberValue;
      else
      {
        temp.state = err;
        ERR("Division (modulo) by 0");
      }
      break;
  }
  
  temp.type = number;
  return temp;
}
