#include "../Headers/calc.h"

void reverseArray(TokenArray* tokens)
{
	if(!tokens || !tokens->items || tokens->size == 0)
		return;

	int i = 0;

	Token temp = *tokens->items[i];

	while(i < tokens->size / 2)
	{
		temp = *tokens->items[tokens->size - 1 - i];
		*tokens->items[tokens->size - 1 - i] = *tokens->items[i];
		*tokens->items[i]                    = temp;
		i++;
	}

	return;
}
