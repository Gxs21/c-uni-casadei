#include <stdio.h>
#define ARR_LEN 7
int main(void) {
  int a[ARR_LEN] = { 4, -1, 8, 9, 11, 9, 2 };
  int *p = &a[2];
  for (int i = 0; i <= ARR_LEN-1 && *p<20; i++) {
    *p += *(p+i) > 9 ? ++p[i] : p[i-1]++; // nota: prima dell'assegnamento, tutti i side effect sono applicati
    printf("%d\n", *p);
  }
  for (int i = 0; i < 2; i++) {
    a[0]++;
  }
  printf("a[0]=%d a[1]=%d a[2]=%d a[3]=%d a[4]=%d a[6]=%d", a[0], a[1], a[2], a[3], a[4], a[6]);
  return 0;
}

