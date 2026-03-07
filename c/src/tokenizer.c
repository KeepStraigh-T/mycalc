#include "../Headers/calc.h"

TokenArray* tokenizer(Buffer* buffer)
{
	if(!buffer || !buffer->ptr)
	{
		ERR("_In_ buffer or buff->ptr is NULL")
		return NULL;
	}

	TokenArray* tokens = calloc(1, sizeof(TokenArray));
	if(!tokens)
	{
		ERR("Memory allocation failed");
		return NULL;
	}

	int tokenArrayCap = 64;

	tokens->items = calloc(tokenArrayCap, sizeof(Token));
	if(!tokens->items)
	{
		ERR("Memory allocation failed");
		free(tokens);
		return NULL;
	}

	tokens->capacity = tokenArrayCap;

	for(int idx = 0; buffer->ptr[buffer->currentIdx] != '\0'; idx++)
	{
		if(tokens->size == tokens->capacity)
		{
			tokens->items =
			    realloc(tokens->items, 2 * tokens->capacity * sizeof(Token));
			if(!tokens->items)
			{
				ERR("Memory allocation failed");
				free(tokens);
				return NULL;
			}
		}

		Token* temp = calloc(1, sizeof(Token));
		if(!temp)
		{
			ERR("Memory allocation failed");
			free(tokens->items);
			free(tokens);
		}

		if(is_operator(buffer->ptr[buffer->currentIdx]))
		{
			tokens->items[idx].type      = operatorType;
			tokens->items[idx].charValue = buffer->ptr[buffer->currentIdx++];
			tokens->items[idx].state     = ok;
			tokens->items[idx].preced    = 4;
		}

		else if(is_digit(buffer->ptr[buffer->currentIdx]))
		{
			long double val = parse_num(buffer);
			if(isnan(val))
			{
				ERR("Error parsing number")
				free(tokens->items);
				free(tokens);
				return NULL;
			}

			tokens->items[idx].type        = numberType;
			tokens->items[idx].numberValue = val;
			tokens->items[idx].state       = ok;
			tokens->items[idx].preced      = -1;
		}

		else
		{
			ERR("Error parsing input, incorrect expression");
			free(tokens->items);
			free(tokens);
			return NULL;
		}

#ifdef DEBUG
		if(tokens->items[idx].type == numberType)
			printf("%Lf", tokens->items[idx].numberValue);
		else
			printf("%c", tokens->items[idx].charValue);
#endif
	}

#ifdef DEBUG
	puts("");
#endif

	tokens->size++;

	return tokens;
}
