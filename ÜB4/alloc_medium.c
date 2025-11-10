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

	// There is a little explanation of the prev_next_ptr approach at the end of this file
	struct free_block *node;
	struct free_block **prev_next_ptr;
	for (prev_next_ptr = &head, node = head; node != NULL; prev_next_ptr = &(node->next), node = node->next) {
		// TODO
	}
	// Could not find any free block :(
	// TODO
}

void free_ptr(void *ptr) {
	if (!initialized) {
		init_mem();
	}

	struct free_block *orig_node = (struct free_block *)ptr - 1;

	struct free_block *node;
	struct free_block **prev_next_ptr;
	// There is a little explanation of the prev_next_ptr approach at the end of this file
	for (prev_next_ptr = &head, node = head; ; prev_next_ptr = &(node->next), node = node->next) {
		// TODO
	}
}

// The prev_next_ptr Pattern - Why We Use a Pointer to a Pointer
// ==============================================================
// 
// Traditional approach (what you might try first):
// -----------------------------------------------------
// We need TWO pointers: one for current node, one for previous node
// 
//     prev          node
//      |             |
//      v             v
//   +-----+       +-----+       +-----+
//   | blk |------>| blk |------>| blk |----> NULL
//   +-----+       +-----+       +-----+
//   
// Problem: Special case for head! If we remove the first node, we need
// different code than removing a middle node.
// 
// 
// Our approach (pointer to the next pointer):
// -------------------------------------------
// prev_next_ptr points to WHERE the pointer to current node is stored
// 
// Iteration 1: At head
//     prev_next_ptr = &head
//          |
//          v
//     [head variable] node = head
//          |
//          v                           v
//       +-----+       +-----+       +-----+
//       | blk |------>| blk |------>| blk |----> NULL
//       +-----+       +-----+       +-----+
//       
// Iteration 2: At second node
//                          prev_next_ptr = &(node->next)
//                               |
//             +-----------------+
//             |
//             |
//       +-----v       +-----+       +-----+
//       | blk x------>| blk |------>| blk |----> NULL
//       +-----+ .next +-----+ .next +-----+
//                        ^
//                        |
//                      node = node->next
// 
// 
// The Magic: To remove or insert, we always do:
//     *prev_next_ptr = new_value;
//     
// This works whether we're modifying:
// - The head variable itself (first iteration)
// - The 'next' field of a free_block (later iterations)
// 
// NO SPECIAL CASES! Same code for head and middle nodes.

