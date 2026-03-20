#include "../Headers/calc.h"

void destructArray(TokenArray* tokens)
{
	for(int idx = 0; idx < tokens->size; idx++)
		free(tokens->items[idx]);

	free(tokens->items);
	free(tokens);
}
