#include "../Headers/calc.h"

TokenArray* lexer(Buffer* buffer)
{
	if(buffer == NULL || buffer->ptr == NULL)
		return NULL;

	TokenArray* tokens = malloc(sizeof(TokenArray));
	if(!tokens)
		return NULL;

	Token* newToken = tokenizer(buffer);

	return tokens;
}
