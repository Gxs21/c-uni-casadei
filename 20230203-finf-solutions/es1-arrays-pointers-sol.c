#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define NELEMS(x) (sizeof(x)>0 ? sizeof(x) / sizeof((x)[0]) : 0)

#define NOT_DECREASING 1
#define NOT_INCREASING 2
#define HAS_NEGATIVE 4
#define SUM_POSITIVE 8

int array_equals(int a[], int b[], int sizea, int sizeb);
int check(int expected, int actual, char *lbl);
void print_array(int *a, int size);

/*
Realizzare una funzione `f` con l'obiettivo di analizzare un array di interi `a`
indicando in output se quest'ultimo:

1) è una sequenza non-decrescente (ad es.: [1,2,2,5,7])
2) è una sequenza non-crescente (ad es.: [7,5,1,1])
3) include un numero negativo (ad es.: [4,7,-6,0])
4) la somma dei suoi elementi è positiva (ad es.: [-6,10,-4,1])

Si richiede di impacchettare queste informazioni nell'output, nell'ordine dato, a partire dal bit meno significativo.
Si faccia riferimento alle costanti simboliche definite sopra nel sorgente.
Ad esempio, `f(a,3)` (nota: il secondo parametro è la lunghezza dell'array) con `a`=[-5,2,4] deve restituire 13 (in base 10), ovvero 1101 in base 2 
(in quanto l'array di input è non-decrescente, include un numero negativo, ed ha somma positiva).

Si ricorda che gli operatori logici bitwise sono i seguenti:
    - `~` (bitwise negation)
    - `&` (bitwise AND)
    - `|` (bitwise OR)
    - `^` (bitwise XOR)

E si ricorda che essi si possono usare assieme alle cosiddette "maschere di bit" per manipolare 
numeri rappresentati in codice binario. Ad esempio: 
    
    int x = 0;
    x = x | 4; // assegna a 1 il terzo bit da destra (4 == 000.....0100)
    x = x | 3; // assegna a 1 i primi 2 bit da destra (3 == 00.....0111)
    printf("x = %d", x); // x = 7
    x = x & ~4; // spegne il terzo bit da destra
    printf("x = %d", x); // x = 3

NOTE GENERALI:
*) ATTENZIONE: la propria soluzione va inserita nella porzione del sorgente inclusa tra i commenti single-line
`// STUDENT-SOLUTION-START` e  `// STUDENT-SOLUTION-END`.
Codice scritto al di fuori di tali commenti non sarà considerato durante la valutazione.
*) E' possibile definire più funzioni ausiliarie qualora lo si ritenga opportuno. 
Ma lo si faccia all'interno dei commenti, come indicato nel punto precedente.
*) ATTENZIONE: la soluzione verrà confrontata con quella dei colleghi mediante strumenti automatici al fine
di rilevare potenziali copiature. Il controllo è resistente a rename di variabili, spezzamento di espressioni etc.
Qualora vengano riscontrate similarità importanti, è possibile che la prova possa venire annullata, e che ulteriori
modalità di verifica di competenze (ad es., prove orali) siano attuate.
*/
// STUDENT-SOLUTION-START
short f(int* a, int length) {
    if(!length) return 0;
    short not_decreasing = 1;
    short not_increasing = 1;
    short has_negative = a[0] < 0;
    long sum = a[0];
    for (int i=1; i<length; i++) {
        if(a[i] > a[i-1]) not_increasing = 0;
        if(a[i] < a[i-1]) not_decreasing = 0;
        if(a[i] < 0) has_negative = 1;
        sum += a[i];
    } 
    return 
        (not_decreasing ? 1 : 0) |
        (not_increasing ? 2 : 0) |
        (has_negative ? 4 : 0) |
        (sum > 0 ? 8 : 0);
}
// STUDENT-SOLUTION-END

void test(){
    check(HAS_NEGATIVE, f((int[]) { -2, -4, -3 }, 3), "no non-increasing, no non-decreasing, with negative value, no positive sum");
    check(HAS_NEGATIVE, f((int[]) { -5, 2, -8, 3 }, 4), "no non-increasing, no non-decreasing, with negative value, no positive sum");
    check(SUM_POSITIVE, f((int[]) { 0, 6, 1 }, 3), "no non-increasing, no non-decreasing, no negative value, with positive sum");
    check(NOT_INCREASING | NOT_DECREASING, f((int[]) { 0 }, 1), "non-increasing, non-decreasing, no negative value, no positive sum");
    check(NOT_INCREASING | NOT_DECREASING | SUM_POSITIVE, f((int[]) { 4 }, 1), "non-increasing, non-decreasing, no negative value, positive sum");
    check(NOT_INCREASING | NOT_DECREASING | HAS_NEGATIVE, f((int[]) { -4 }, 1), "non-increasing, non-decreasing, with negative value, no positive sum");
    check(NOT_INCREASING | SUM_POSITIVE, f((int[]) { 4, 3, 2 }, 3), "non-increasing, no non-decreasing, no negative value, positive sum");
    check(NOT_INCREASING | HAS_NEGATIVE, f((int[]) { 4, 3, -100 }, 3), "non-increasing, no non-decreasing, no negative value, no positive sum");
    check(NOT_INCREASING | HAS_NEGATIVE | SUM_POSITIVE, f((int[]) { 4, 3, -1 }, 3), "non-increasing, no non-decreasing, no negative value, positive sum");
    check(NOT_DECREASING | HAS_NEGATIVE, f((int[]) { -5, 2, 3 }, 3), "non-decreasing, negative value, no positive sum");
    check(NOT_DECREASING | HAS_NEGATIVE | SUM_POSITIVE, f((int[]) { -5, 2, 4 }, 3), "non-decreasing, negative value, positive sum");
}

int main(){
    test();
    return 0;
}

int check(int expected, int actual, char *lbl){
    int equals = expected == actual;
    printf("%s%s", equals ? "OK: " : "FAIL: ", lbl);
    if(!equals){
        printf(" - Expected: %d - Actual: %d", expected, actual);
    }
    puts("");
    return equals;
}

void print_array(int *a, int size){
    int i;
    for (i=0; i<size; i++) printf("%d ", a[i]);
} 
