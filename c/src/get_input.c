#include "../Headers/calc.h"

int get_input(Buffer* const buffer)
{
	printf("> ");

	int idx             = 0;
	bool unassess_input = false;
	char c;

	while(true)
	{
		c = getchar();

		if(buffer->size >= buffer->capacity)
		{
			buffer->capacity *= 2;
			buffer->ptr = realloc(buffer->ptr, sizeof(char) * buffer->capacity);
			if(buffer->ptr == NULL)
			{
				destructor(buffer);
				exit(ALLOC_FAILED);
			}
		}

		// add here upcoming operators
		if((c >= '0' && c <= '9') ||
		   (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' ||
		    c == '^' || c == '(' || c == ')') ||
		   c == '.')
		{
			buffer->ptr[idx++] = c;
			buffer->size++;
		}
		else
		{
			if(c == ' ' || c == '\t') // space or hor. tab
				continue;
			else if(c == '\n')
			{
				buffer->ptr[idx] = '\0';
				break;
			}
			else
			{ // could be implemented better (not to continue reading input)
				buffer->ptr[idx++] = c;
				buffer->size++;
				unassess_input = true;
				continue;
			}
		}
	}

	if(!strcmp(buffer->ptr, "quit") || !strcmp(buffer->ptr, "q") ||
	   !strcmp(buffer->ptr, "exit"))
		return QUIT;
	else if(unassess_input)
		return INVALID_INPUT;

	return 0;
}
