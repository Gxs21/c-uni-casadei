#include <stdio.h>
#define ARR_LEN 7
int main(void) {
  int a[ARR_LEN] = { 4, -1, 8, 9, 11, 9, 2 };
  int *p = &a[0] + 4;
  for (; --(*p) > 7; ) {
    printf("*");
    p = p - 1;
  }
  for (int i = 0; i < 2; i++) {
    a[i]--;
    a[ARR_LEN-1-i]++;
  }
  printf("a[1]=%d a[3]=%d a[4]=%d a[5]=%d", a[1], a[3], a[4], a[5]);
  return 0;
}

