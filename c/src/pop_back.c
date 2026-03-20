
#include "../Headers/calc.h"

void pop_back(TokenArray* tokenArr)
{
	if(!tokenArr || !tokenArr->items || tokenArr->size == 0)
		return;

	int lastToken = tokenArr->size - 1;

	free(tokenArr->items[lastToken]);

	if(--tokenArr->size == 0)
		tokenArr->items = NULL;
}
