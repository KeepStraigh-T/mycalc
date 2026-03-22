#include "../Headers/calc.h"

void destructArray(TokenArray* tokens)
{
  free(tokens->items);
  free(tokens);
}
