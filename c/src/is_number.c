#include "../Headers/calc.h"

bool is_number(char input)
{
  if(input >= '0' && input <= '9')
    return true;

  return false;
}
