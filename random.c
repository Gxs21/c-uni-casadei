#include <stdio.h>

int main(void){
    int a = -5;
     int b = a++; 
     int c = b--; 
     int d = ++c; 
     int e = --d; 
    printf("a=%d b=%d c=%d d=%d e=%d\n", a, b, c, d, e);


return 0;
}