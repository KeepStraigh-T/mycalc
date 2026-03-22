#include "../Headers/calc.h"

int mainloop()
{
  while (true)
    {
      Buffer* buffer = calloc(1, sizeof(Buffer));
      if (!buffer)
        {
          ERR("Buffer allocation failed");
          return ALLOC_FAILED;
        }

      // read line with editing possible
      buffer->ptr = readline("> ");
      if (!buffer->ptr)
        perror("readline returns NULL");

      buffer->size = strlen(buffer->ptr);
      if (buffer->size == 0)
        {
          free(buffer->ptr);
          free(buffer);
          continue;
        }

      if (!strcmp(buffer->ptr, "quit") || !strcmp(buffer->ptr, "q") || !strcmp(buffer->ptr, "exit"))
        return QUIT;

#ifdef DEBUG
      printf("Input buffer: %s\n", buffer->ptr); // print buffer
#endif
      TokenArray* tokenArray = tokenizer(buffer);
      if (!tokenArray)
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
