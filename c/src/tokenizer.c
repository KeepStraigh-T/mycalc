#include "../Headers/calc.h"
#include <ctype.h>
#include <math.h>

TokenArray* tokenizer(Buffer* buffer)
{
  if (!buffer || !buffer->ptr)
    {
      ERR("buffer or buff->ptr is NULL")
      return NULL;
    }

  TokenArray* tokenArr = calloc(1, sizeof(TokenArray)); // allocate tokens container
  if (!tokenArr)
    {
      ERR("Memory allocation failed");
      return NULL;
    }

  int tokenArrayCap = 64;

  tokenArr->items = calloc(tokenArrayCap,
                           sizeof(Token)); // allocate pointer to tokens
  if (!tokenArr->items)
    {
      ERR("Memory allocation failed");
      free(tokenArr);
      return NULL;
    }

  tokenArr->capacity = tokenArrayCap;

  int idx = 0;
  while (buffer->currentIdx < buffer->size)
    {
      if (tokenArr->size == tokenArr->capacity)
        {
          Token* temp = realloc(tokenArr->items, 2 * tokenArr->capacity * sizeof(Token*));
          if (!temp)
            {
              ERR("Memory allocation failed");
              destructArray(tokenArr);
              return NULL;
            }
          tokenArr->items = temp;
          tokenArr->capacity *= 2;
        }

      // Parse operator
      if (is_operator(buffer->ptr[buffer->currentIdx]))
        {
          tokenArr->items[idx] = parse_op(buffer->ptr[buffer->currentIdx]);
          buffer->currentIdx++;
        }

      // Parse number
      else if (is_digit(buffer->ptr[buffer->currentIdx]))
        {
          long double val = parse_num(buffer); // Here increments buffer->currentIdx
          if (isnan(val))
            {
              ERR("Error parsing number")
              destructArray(tokenArr);
              return NULL;
            }

          tokenArr->items[idx].type = numberType;
          tokenArr->items[idx].numberValue = val;
          tokenArr->items[idx].l_bp = -1;
          tokenArr->items[idx].r_bp = -1;
        }
      // blank character (space or tab)
      else if (isblank(buffer->ptr[buffer->currentIdx]))
        {
          buffer->currentIdx++;
          continue;
        }
      else // Parsing failed
        {
          ERR("Error: unexpected character");
          destructArray(tokenArr);
          return NULL;
        }

      tokenArr->size++;
      idx++;
    }
  // add EOF token
  if (tokenArr->size == tokenArr->capacity)
    {
      Token* temp = realloc(tokenArr->items, (tokenArr->capacity + 5) * sizeof(Token*));
      if (!temp)
        {
          ERR("Memory allocation failed");
          destructArray(tokenArr);
          return NULL;
        }
      tokenArr->items = temp;
      tokenArr->capacity += 5;
    }

  tokenArr->items[tokenArr->size].type = eof;
  tokenArr->size++;

  return tokenArr;
}
