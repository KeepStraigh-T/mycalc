#include "../Headers/calc.h"

void destructor(Buffer* buffer)
{
	free(buffer->ptr);
	free(buffer);
}
