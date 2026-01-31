#include "../Headers/calc.h"

extern Buffer buffer;

int mainloop()
{
	while(true)
	{
		buffer.ptr = malloc(sizeof(char) * INITIAL_CAPACITY);
		if(buffer.ptr == NULL)
		{
			ERR("Memory allocation failed");
			continue;
		}
		buffer.capacity = INITIAL_CAPACITY;

		int getLine = get_line();

#ifdef DEBUG
		printf("%s\n", buffer.ptr); // print buffer
#endif

		if(getLine == QUIT)
		{
			destructor();
			printf("Quiting...\n");
			return 0;
		}
		else if(getLine == INVALID_INPUT)
		{
			printf("Syntax error\n");
			destructor();
			continue;
		}
		else
		{
			token result = pratt_parser(0);
			// if(result.flag == err)
			//   printf("Syntax error\n");
			// else
			printf("result: %lld\n", result.numberValue);

			puts("---------------------");
			destructor();
		}
	}
}
