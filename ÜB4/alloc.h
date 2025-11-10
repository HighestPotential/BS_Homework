#include <stddef.h>

#define KB 1024
#define MB (1024 * KB)
#define MEMSIZE (2 * MB)

/**
 * Allocates memory of given size.
 * (Note that unlinke the real malloc implementation,
 * this implementation does not handle alignment)
 *
 * \param size - Size of allocated memory.
 * \return Pointer to allocated memory if succeeds or NULL otherwise.
 */
void *malloc_ptr(size_t size);

/**
 * Deallocate previously allocated memory.
 *
 * \param ptr - Pointer to deallocated memory.
 */
void free_ptr(void *ptr);

