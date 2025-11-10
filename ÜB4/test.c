#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "alloc.h"

void basic_alloc_checks(void) {
	int *ptr = malloc_ptr(sizeof(int) * 128);
	assert(ptr != NULL);
	memset(ptr, 0x42, sizeof(int) * 128);
	free_ptr(ptr);
	assert(malloc_ptr(MEMSIZE) == NULL);
}

void test_alloc_free_reuse() {
    void *a = malloc_ptr(32);
    free_ptr(a);
    void *b = malloc_ptr(32);
    assert(a == b);  // allocator should ideally reuse the freed block
}

void test_multiple_allocs() {
    void *a = malloc_ptr(8);
    void *b = malloc_ptr(8);
    assert(a != NULL && b != NULL);
    assert(a != b);
    memset(a, 0x11, 8);
    memset(b, 0x22, 8);
    free_ptr(a);
    free_ptr(b);
}

void test_no_overlap() {
    uint8_t *a = malloc_ptr(64);
    uint8_t *b = malloc_ptr(64);
    for (int i = 0; i < 64; i++) a[i] = 0xAA;
    for (int i = 0; i < 64; i++) b[i] = 0xBB;

    for (int i = 0; i < 64; i++) assert(a[i] == 0xAA);
    for (int i = 0; i < 64; i++) assert(b[i] == 0xBB);

    free_ptr(a);
    free_ptr(b);
}

void test_fragmentation() {
    void *ptrs[1000];
    for (int i = 0; i < 1000; i++) {
        ptrs[i] = malloc_ptr((i % 64) + 1);
        assert(ptrs[i] != NULL);
    }
    for (int i = 0; i < 1000; i += 2) free_ptr(ptrs[i]);
    for (int i = 0; i < 1000; i += 3) {
        void *p = malloc_ptr(32);
        assert(p != NULL);
        free_ptr(p);
    }
    for (int i = 1; i < 1000; i += 2) free_ptr(ptrs[i]);
}

int main(void) {
	basic_alloc_checks();
	test_alloc_free_reuse();
	test_multiple_allocs();
	test_no_overlap();
	test_fragmentation();

	puts("Successfully passed all tests. Nice!");
	puts("Maybe you can think of some tests yourself?");

	return 0;
}
