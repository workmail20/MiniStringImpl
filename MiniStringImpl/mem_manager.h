#include <winnt.h>
#include <Windows.h>
#ifndef MEMMANAG_H
#define MEMMANAG_H

typedef struct _mem_alloc {
	PCHAR pointer;
	DWORD type;
	DWORD size;
}mem_alloc, * Pmem_alloc;

mem_alloc mem_get(DWORD size, Pmem_alloc old_alloc = NULL);
void mem_free(mem_alloc p);
void Copy_Memory(PVOID Dest, PVOID Source, int count);

#endif