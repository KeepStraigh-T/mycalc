#include "../Headers/calc.h"

Token next_token(TokenArray* tokenArr)
{
  Token temp = { 0 };
  if (!tokenArr || !tokenArr->items)
    return temp;

  temp = tokenArr->items[tokenArr->size - 1];

  if (tokenArr->size > 1)
    pop_back(tokenArr);

  return temp;
}
