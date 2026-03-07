#include "../Headers/calc.h"

int mainloop()
{
	while(true)
	{
		Buffer* buffer = calloc(1, sizeof(Buffer));
		if(!buffer)
		{
			ERR("Buffer allocation failed");
			return ALLOC_FAILED;
		}

		buffer->ptr = malloc(sizeof(char) * INITIAL_CAPACITY);
		if(!(buffer->ptr))
		{
			free(buffer);
			ERR("Buffer pointer allocation failed");
			return ALLOC_FAILED;
		}
		buffer->capacity = INITIAL_CAPACITY;

		int input = get_input(buffer);

#ifdef DEBUG
		printf("%s\n", buffer->ptr); // print buffer
#endif

		if(input == QUIT)
		{
			// destructor(buffer);
			free(buffer->ptr);
			free(buffer);
			printf("Quiting...\n");
			return 0;
		}
		else if(input == INVALID_INPUT)
		{
			printf("Error: unexpected character\n");
			// destructor(buffer);
			free(buffer->ptr);
			free(buffer);
			continue;
		}
		else
		{
			TokenArray* tokens = tokenizer(buffer);
			if(!tokens)
			{
				ERR("Allocation failed");
				free(buffer->ptr);
				free(buffer);
				return ALLOC_FAILED;
			}

			// logic part

			// token result = pratt_parser(0);
			// if(result.flag == err)
			//   printf("Syntax error\n");
			// else
			// printf("result: %lld\n", result.numberValue);

			// puts("---------------------");
			// destructor(buffer);
			free(tokens->items);
			free(tokens);
			free(buffer->ptr);
			free(buffer);
		}
	}
}
