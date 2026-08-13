#include <stdio.h>

int main (void) {
    char letter = 1, vocal=2, uppercase = 4, number = 8;
    char c; 
    printf ("inserire un numero o una lettera");
    scanf("%c", &c);
    char data = c>='A' && c<='Z' ? uppercase : 0;
    data |= c=='a' || c=='A' || c=='b' /*...*/ ? vocal :0;
    data |= c>='0' && c<='9' ? number : 0;
    data |= c>='a' && c<='z' ? letter : 0;
    printf ("maschera: %d", data);
return 0;
}