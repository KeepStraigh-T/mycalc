#include "../Headers/calc.h"

Token peek_last(const TokenArray* tokenArr)
{
  return tokenArr->items[tokenArr->size - 1];
}
