#include "../Headers/calc.h"
#include <math.h>

static int64_t strtolng(Buffer* buffer)
{
  int64_t num = 0;
  int digits = 0;

  for (int i = 0; is_digit(buffer->ptr[buffer->currentIdx + i]); i++)
    digits++;

  for (int i = digits - 1; i >= 0; i--)
    num += (buffer->ptr[buffer->currentIdx++] - '0') * my_power(10, i);

  return num;
}

static long double double_fraction(Buffer* buffer)
{
  int64_t num = 0;
  int digits = 0;

  for (int i = 0; is_digit(buffer->ptr[buffer->currentIdx + i]); i++)
    digits++;

  for (int i = digits - 1; i >= 0; i--)
    num += (buffer->ptr[buffer->currentIdx++] - '0') * my_power(10, i);

  return num / (long double)my_power(10, digits);
}

long double parse_num(Buffer* buffer)
{
  long double num = (long double)strtolng(buffer);

  if (buffer->ptr[buffer->currentIdx] != '.')
    return num;
  else if (!is_digit(buffer->ptr[++buffer->currentIdx])) // next token after
                                                         // '.' is not a digit
    {

      ERR("Error parsing input, incorrect expression");
      return NAN;
    }

  num += double_fraction(buffer);

  return num;
}
