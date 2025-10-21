# include <stdio.h>

int main(void) {
    // NOTE: the lines above the TODO: tell you what the line below the TODO: (the one you need to add) should print.
    printf("If you see this message, the compilation and execution worked.\n");
    printf("For readability, make sure that each print you add is terminated with a newline!\n");
    printf("This program prints a couple of things. For example:\n");
    printf("An integer: \n", 2);
    // TODO:

    printf("\n");
    printf("Pi as a floating point number to the 10th decimal place: %.10f \n", 3.14159265359);
    // TODO:

    // TODO:
    printf("A string!': %s \n", "String");

    // TODO:
    printf("16 * 16 as a hexadecimal number: %x \n", 16*16);

    // TODO:
    printf("The word ..onkey, completed by adding a letter via a format string:\n");

    // TODO:
    printf("A percentage sign: %% \n");

    // TODO:
    printf("A number in scientific notation: %e \n", 123.0);

    int a[3] = {1, 2, 3};
    int *b = &a[1];
    printf("The second element of the array a[3] = {1, 2, 3} is: %d \n", *b);
    //TODO: Try not to use a[1] here!
    
    printf("The address of the second element is: %p \n", b);
    // TODO:
}
