#include "../Headers/calc.h"

extern Buffer buffer;

void destructor()
{
  free(buffer.ptr);
  buffer.currentIdx = 0;
  buffer.size = 0;
  buffer.capacity = INITIAL_CAPACITY;
}
