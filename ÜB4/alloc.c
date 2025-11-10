#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "alloc.h"

uint8_t MEM[MEMSIZE];
bool initialized = false;

// The type for the nodes of the freelist
// Neat little hack: data points to the memory region after the free_block struct,
// but does not use any space itself.
struct free_block {
	struct free_block* next;
	size_t size;
	uint8_t data[];
};

// The freelist (the head of it)
struct free_block* head = NULL;

void init_mem(void) {
	head = (struct free_block *) MEM;
	head->next = NULL;
	head->size = MEMSIZE - sizeof(struct free_block);
	initialized = true;
}

void *malloc_ptr(size_t size) {
	if (!initialized) {
		init_mem();
	}
	// TODO
	
}

void free_ptr(void *ptr) {
	if (!initialized) {
		init_mem();
	}
	// TODO

}
