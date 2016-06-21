#pragma once
#include <common.h>
#include <typeinfo>


#define honew		new(__FILE__, __LINE__)
#define hodelete	delete

void* operator new(size_t size);
HO_API void* operator new(size_t size, const char* file, uint line);
void* operator new[](size_t size);
HO_API void* operator new[](size_t size, const char* file, uint line);
	
void operator delete(void* block);
HO_API void operator delete(void* block, const char* file, uint line);
void operator delete[](void* block);
HO_API void operator delete[](void* block, const char* file, uint line);

