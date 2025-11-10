# To enable debug symbols, uncomment this
# CFLAGS = -g

alloc_test: test.c alloc.o
	cc $(CFLAGS) -o alloc_test test.c alloc.o

clean:
	rm -f *.o alloc_test alloc_test_solution

# Ignore this for now
alloc_test_solution: test.c alloc_solution.o
	cc $(CFLAGS) -o alloc_test_solution test.c alloc_solution.o
