#include "../Headers/calc.h"

extern Buffer buffer;

int get_line()
{
	printf("> ");
	int idx             = 0;
	bool unassess_input = false;
	char c;

	while(true)
	{
		c = getchar();

		if(buffer.size >= buffer.capacity)
		{
			buffer.capacity *= 2;
			buffer.ptr = realloc(buffer.ptr, sizeof(char) * buffer.capacity);
			if(buffer.ptr == NULL)
				exit(ALLOC_FAILED);
		}

		// add here upcoming operators
		if((c >= '0' && c <= '9') ||
		   (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' ||
		    c == '^' || c == '(' || c == ')'))
		{
			buffer.ptr[idx++] = c;
			buffer.size++;
		}
		else
		{
			if(c == 32 || c == 9) // space or hor. tab
				continue;
			else if(c == '\n')
			{
				buffer.ptr[idx] = '\0';
				buffer.size++;
				break;
			}
			else
			{
				buffer.ptr[idx++] = c;
				buffer.size++;
				unassess_input = true;
				continue;
			}
		}
	}

	if(!strcmp(buffer.ptr, "quit"))
		return QUIT;
	else if(unassess_input)
		return INVALID_INPUT;

	return 0;
}
