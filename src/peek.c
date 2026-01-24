#include "../Headers/calc.h"

extern Buffer buffer;

char peek(int offset)
{
  return buffer.ptr[buffer.currentIdx + offset];
}
