#include "../Headers/calc.h"
#include <math.h>

TokenArray* tokenizer(Buffer* buffer)
{
	if(!buffer || !buffer->ptr)
	{
		ERR("buffer or buff->ptr is NULL")
		return NULL;
	}

	TokenArray* tokenArr =
	    calloc(1, sizeof(TokenArray)); // allocate tokens container
	if(!tokenArr)
	{
		ERR("Memory allocation failed");
		return NULL;
	}

	int tokenArrayCap = 64;

	tokenArr->items =
	    calloc(tokenArrayCap, sizeof(Token*)); // allocater pointer to tokens
	if(!tokenArr->items)
	{
		ERR("Memory allocation failed");
		free(tokenArr);
		return NULL;
	}

	tokenArr->capacity = tokenArrayCap;

	int idx = 0;
	while(true)
	{
		if(tokenArr->size ==
		   tokenArr->capacity) // reallocate pointer if capacity full
		{
			Token** temp = realloc(tokenArr->items,
			                       2 * tokenArr->capacity * sizeof(Token*));
			if(!temp)
			{
				ERR("Memory allocation failed");
				destructArray(tokenArr);
				return NULL;
			}

			tokenArr->items     = temp;
			tokenArr->capacity *= 2;
		}

		tokenArr->items[idx] =
		    calloc(1, sizeof(Token)); // allocate pointer to new token

		if(!tokenArr->items[idx])
		{
			ERR("Memory allocation failed");
			destructArray(tokenArr);
			return NULL;
		}

		// Parse operator
		if(is_operator(buffer->ptr[buffer->currentIdx]))
			*tokenArr->items[idx] = parse_op(buffer->ptr[buffer->currentIdx++]);

		// Parse number
		else if(is_digit(buffer->ptr[buffer->currentIdx]))
		{

			long double val =
			    parse_num(buffer); // Here increments buffer->currentIdx
			if(isnan(val))
			{
				ERR("Error parsing number")
				destructArray(tokenArr);
				return NULL;
			}

			tokenArr->items[idx]->type        = numberType;
			tokenArr->items[idx]->numberValue = val;
			tokenArr->items[idx]->l_bp        = -1;
			tokenArr->items[idx]->r_bp        = -1;
		}
		// EOF
		else if(buffer->ptr[buffer->currentIdx] == '\n')
		{
			tokenArr->items[idx]->type = eof;
			tokenArr->size++;
			break;
		}
		else // Parsing failed
		{
			ERR("Error parsing input, incorrect expression");
			destructArray(tokenArr);
			return NULL;
		}

		tokenArr->size++;
		idx++;
	}

	return tokenArr;
}
