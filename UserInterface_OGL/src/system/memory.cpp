#include "memory.h"

void* operator new(size_t size)
{
	return malloc(size);
}

void* operator new(size_t size, const char* file, uint line)
{
	return malloc(size);
}

void* operator new[](size_t size)
{
	return malloc(size);
}

void* operator new[](size_t size, const char* file, uint line)
{
	return malloc(size);
}

void operator delete(void* block)
{
	free(block);
}

void operator delete(void* block, const char* file, uint line)
{
	free(block);
}

void operator delete[](void* block)
{
	free(block);
}

void operator delete[](void* block, const char* file, uint line)
{
	free(block);
}


