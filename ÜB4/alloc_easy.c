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
		if (node->size < size) {
			// TODO
		}

		// Node is too small to split, using the whole node
		if (// TODO) {
			// TODO
		} else {
			// Node is large enough to split into this node (now used) and another one
			struct free_block* new_node = (struct free_block*) (node->data + size);

			// Insert the new_node into the list
			// TODO

			// Note that the new node might have a size of zero, but we don't need to care for our exercise.
			// In reality we would define a smallest free block size and handle that case appropriately,
			// But for simplicity, this implementation may allow zero-size free blocks to exist.
			// TODO

			// Since we need to know the actual size of this node when calling free(),
			// we need to set the size of the node we will use now.
			// TODO
		}
	}
	// Could not find any free block :(
	// TODO
}

void free_ptr(void *ptr) {
	if (!initialized) {
		init_mem();
	}

	// We assume that the pointer we received is correct.
	// This means there should be a free_block struct at ptr - sizeof(struct freeblock)
	// By converting the pointer to a "struct free_block *" and decrementing it,
	// We receive that pointer. Look up "pointer arithmetics" to learn more.
	struct free_block *orig_node = (struct free_block *)ptr - 1;

	// There is a little explanation of the prev_next_ptr approach at the end of this file
	struct free_block *node;
	struct free_block **prev_next_ptr;
	for (prev_next_ptr = &head, node = head; ; prev_next_ptr = &(node->next), node = node->next) {
		if (*prev_next_ptr == NULL) {  // We are at the end of the list
			// Insert our node at the tail
			// TODO
		} else if (node > orig_node) {  // This node comes after the one we want to free
			// Insert our node
			// TODO

			// merge with next node, if possible
			if (// TODO) {
				// TODO
			}
		} else {
			// No insertion happens this loop
			continue;
		}

		// We inserted our original node back into the freelist
		// Now try to merge with previous node
		if (// TODO) {  // Cannot merge previous, if we're the first
			// The next field is the first field of the struct.
			// This means that the pointer to its next field is the same as the pointer to the
			// struct itself, so we can just cast our pointer.
			struct free_block *prev = (struct free_block*) prev_next_ptr;
			if (// TODO) { // Check if the previous node is adjacent
				// Merge the nodes
				// TODO
			}
		}
		// We freed the memory (inserted a node), so we're done
		return;
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
