#include <stdio.h>

// Function to swap two integers using pointers
void swap(int *a, int *b) {
    // Your code here
    int c = *a;
    *a=*b;
    *b=c;
}

// Function to calculate the sum of two integers using pointers
int sum(int *a, int *b) {
    int sumOf2= *a+*b;
    return sumOf2;
    // Your code here
}

// Function to "swap" two integers using pointers
void swap_wrong(int *a, int *b) {
    int *c = a;
    a = b;
    b = c;
}

int main() {
    int num1, num2;

    // Prompt the user for input
    printf("Enter two integers: ");
    scanf("%d %d", &num1, &num2);

    // Print the original values
    printf("Original values: num1 = %d, num2 = %d\n", num1, num2);

    // Swap the values using pointers
    swap(&num1, &num2);
    printf("Swapped values: num1 = %d, num2 = %d\n", num1, num2);

    // Calculate and print the sum using pointers
    int result = sum(&num1, &num2);
    printf("Sum of swapped values: %d\n", result);

    swap_wrong(&num1, &num2);
    return 0;
}
