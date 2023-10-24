#include "windows.h"
#include "mem_manager.h"

const DWORD MEM_HEAP = 0;
const DWORD MEM_VIRTUAL = 1;
LPVOID g_heap = NULL;

void Copy_Memory(PVOID Dest, PVOID Source, int count) {
	PCHAR	  S, D;
	int  I;

	S = PCHAR(Source);
	D = PCHAR(Dest);
	if (S == D)return;

	if (DWORD_PTR(D) > DWORD_PTR(S)) {
		for (I = count - 1; I >= 0; I--) {
			D[I] = S[I];
		}
	}
	else {
		for (I = 0; I < count; I++) {
			D[I] = S[I];
		}
	}
}

mem_alloc mem_get(DWORD size, Pmem_alloc old_alloc)
{
	LPVOID p = NULL;
	mem_alloc res{};
	res.pointer = NULL;
	res.size = 4096 * ((size / 4096) + 1);
	res.type = 0;
	if (size > 0) {
		if (old_alloc != NULL) {
			if (size <= old_alloc->size) {
				res.pointer = old_alloc->pointer;
				res.size = old_alloc->size;
				res.type = old_alloc->type;
				return res;
			}
			else {
				mem_free(*old_alloc);
			}
		}

		if (g_heap == NULL) {
			g_heap = GetProcessHeap();
		}
		size = res.size;
		if (g_heap != NULL) {
			p = HeapAlloc(g_heap, 0, size);
			if (p != NULL) {
				res.pointer = (PCHAR)p;
				res.type = MEM_HEAP;
			}
		}
		if (res.pointer == NULL) {
			p = VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			if (p != NULL) {
				res.pointer = (PCHAR)p;
				res.type = MEM_VIRTUAL;
			}
		}
	}
	return res;
}

void mem_free(mem_alloc p)
{
	if (p.type == MEM_HEAP) {
		if (p.pointer != NULL) {
			HeapFree(g_heap, 0, p.pointer);
		}
	}
	if (p.type == MEM_VIRTUAL) {
		if (p.pointer != NULL) {
			VirtualFree(p.pointer, 0, MEM_RELEASE);
		}
	}
}
