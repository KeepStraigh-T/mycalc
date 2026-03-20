#include "../Headers/calc.h"

void printArray(const TokenArray* tokens)
{
	if(!tokens || !tokens->items || tokens->size == 0)
		return;

	printf("Tokens: ");
	for(int i = 0; i < tokens->size; i++)
	{
		if(tokens->items[i]->type == operatorType)
			printf("%c ", tokens->items[i]->charValue);
		else if(tokens->items[i]->type == numberType)
			printf("%Lf ", tokens->items[i]->numberValue);
	}
	puts(" ");

	return;
}
