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

		buffer->ptr = calloc(INITIAL_CAPACITY, sizeof(char));
		if(!(buffer->ptr))
		{
			free(buffer);
			ERR("Buffer pointer allocation failed");
			return ALLOC_FAILED;
		}
		buffer->capacity = INITIAL_CAPACITY;

		printf("> ");
		int input = get_input(buffer);

#ifdef DEBUG
		printf("Input buffer: %s\n", buffer->ptr); // print buffer
#endif
		if(input == QUIT)
		{
			free(buffer->ptr);
			free(buffer);
			printf("Quiting...\n");
			return 0;
		}
		else if(input == INVALID_INPUT)
		{
			printf("Error: unexpected character\n");
			free(buffer->ptr);
			free(buffer);
			continue;
		}
		else
		{
			TokenArray* tokenArray = tokenizer(buffer);
			if(!tokenArray)
			{
				ERR("Allocation failed");
				free(buffer->ptr);
				free(buffer);
				return ALLOC_FAILED;
			}

			reverseArray(tokenArray);

			Token result = pratt_parser(tokenArray, 0);
			printf("Result: %Lf\n", result.numberValue);

			puts("---------------------");

#ifdef DEBUG
			printArray(tokenArray);
#endif

			destructArray(tokenArray);
			free(buffer->ptr);
			free(buffer);
		}
	}
}
