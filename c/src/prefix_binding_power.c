#include "../Headers/calc.h"

Token prefix_binding_power(Token op)
{
  Token temp = op;
  temp.l_bp = 0;
  temp.r_bp = 5;

  return temp;
}
