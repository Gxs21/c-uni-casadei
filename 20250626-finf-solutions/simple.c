#include <stdio.h>
#include <stdlib.h>

void f(char *p) {
    *p = 88;
}

int k = 0;
void ff(char **a) {
    char *narray = (char*)malloc(3);
    *a = narray;
    (*a)[0] = k++;
    (*a)[1] = k++;
    (*a)[2] = k++;
}

int main(){
    char x = 0;
    f(&x);
    printf("x = %d.\n", x);

    char *a = NULL;
    ff(&a);
    printf("%d %d %d\n", a[0], a[1], a[2]);

    char **aa = &a;
    ff(aa);
    printf("%d %d %d\n", a[0], a[1], a[2]);
}