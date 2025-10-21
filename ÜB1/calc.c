#include <stdio.h>
#include <stdlib.h>

int main() {
    int n = 0;
    int sum = 0;
    int remainder = 0;	 
    puts("Enter an integer");
    if (scanf("%d", &n)==1){
        while (n != 0) {
        remainder = n % 10;
        sum = sum + remainder;
        n = n / 10;
        }
        printf("Sum = %d\n", sum);
        exit(EXIT_SUCCESS);
    }else{
        printf("Error, wrong Input");
        exit(EXIT_FAILURE);
    }

}
//3 b) -quesrsumme
//-
