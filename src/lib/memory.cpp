/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2008 Soeren Sonnenburg
 * Copyright (C) 2008 Fraunhofer Institute FIRST and Max-Planck-Society
 */

#include "lib/ShogunException.h"
#include "lib/memory.h"
#include <stdio.h>

//void* operator new(size_t size)
void* operator new(size_t size) throw (std::bad_alloc)
{
	//void *p=malloc(900000000*size);
	void *p=malloc(size);
	if (!p)
	{
		size_t buf_len=128;
		char buf[buf_len];
		size_t written=snprintf(buf, buf_len,
			"Out of memory error, tried to allocate %d bytes.\n", size);
		if (written==buf_len)
			throw ShogunException(buf);
		else
			throw ShogunException("Out of memory error.\n");
	}

	//printf("Overloaded new, created object of size %d at %p.\n", size, p);
	return p;
}

void operator delete(void *p)
{
	//printf("Free in overloaded delete at %p.\n", p);
	free(p);
}

/*
void* operator new[](size_t size)
{
	void *p=malloc(size);
	if (!p)
		throw ShogunException("Assertion failed for new.\n");

	printf("Overloaded new[], created object of size %d at %p.\n", size, p);
	return p;
}

void operator delete[](void *p)
{
	printf("Free in overloaded delete[] at %p.\n", p);
	free(p);
}
*/
