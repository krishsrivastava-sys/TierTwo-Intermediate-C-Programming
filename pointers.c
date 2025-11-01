#include <stdio.h>

int main(void) {
    int x = 42;          // A regular integer variable
    int *p = &x;         // p points to x
    int **pp = &p;       // pp points to p

    printf("x   = %d\n", x);
    printf("&x  = %p (address of x)\n", (void*)&x);

    printf("p   = %p (value of p -> address of x)\n", (void*)p);
    printf("&p  = %p (address of p itself)\n", (void*)&p);
    printf("*p  = %d (value stored at address p → x)\n", *p);

    printf("\n--- Now with double pointer ---\n");
    printf("pp  = %p (value of pp -> address of p)\n", (void*)pp);
    printf("&pp = %p (address of pp itself)\n", (void*)&pp);
    printf("*pp = %p (value stored at address pp -> p)\n", (void*)*pp);
    printf("**pp = %d (value stored at address p -> x)\n", **pp);

    return 0;
}
