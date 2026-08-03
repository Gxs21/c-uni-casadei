#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int array_equals(unsigned char a[], unsigned char b[], int sizea, int sizeb);
int check(unsigned char* input, int input_len, unsigned char* expected, int expected_len);
void print_array(unsigned char *a, int size);

/*
Supponiamo di voler rappresentare delle configurazioni binarie mediante un array di interi, come segue:

    [1, 0, 1, 0, 1, 1, 1]

Utilizzando un singolo array, se vogliamo specificare più configurazioni, avremmo bisogno o di assumere una lunghezza per tali configurazioni, 
o di utilizzare dei "separatori" per le configurazioni, che ad esempio è un qualunque valore diverso da 0 o 1.
Allora, potremo indicare due configurazioni come segue:

    [1, 0, 1, 0, 5, 0, 1]
                 ^
dove il 5 funge da separatore delle due configurazioni "0101" e "10" (si noti che nell'array i bit meno significativi vengono prima).

Allora, realizzare una funzione `f(numbers,length,new_length)` che 

1. accetta in ingresso un array `numbers` di `length` valori unsigned char (interi senza segno su 8 bit)
  che indicano delle configurazioni di bit e dove ogni valore diverso da 0 e 1 può fungere da "separatore"; e

2. restituisce un nuovo array di valori unsigned char, di lunghezza `*new_length` da impostare, contenente i valori interi identificati da tali
  configurazioni di bit.

Per esempio, dato in ingresso un array `[88,1,1,5,1,0,1,1,77]` il risultato dovrà essere un array `[3,13]`, 
 in quanto la prima configurazione è "11" e la seconda è "1101" (dove i bit sono indicati dal più significativo al meno significativo,
 mentre -- si noti -- la configurazione specificata nell'array li riporta dal meno significativo al più significativo).

Si noti che si assume le configurazioni abbiano al più 8 bit, per cui eventuali bit in eccesso specificati dalle configurazioni vanno tralasciati.

Si osservi la funzione `test` per ulteriori esempi e input "malformati" da gestire.

SUGGERIMENTO: Sia data una variabile intera `x`: si ricorda che i suoi bit possono essere impostati come segue.

    x += 1 << 0;  // imposta il bit meno significativo a 1 (assumendo inizialmente tale bit sia zero)
    x |= 0 << 2;  // imposta il terzo bit meno significativo a 0  (assumendo inizialmente tale bit sia zero)

dove `z << n` rappresenta l'operazione di shift dei bit della rappresentazione della variabile intera `z` a sinistra di `n` posizioni.

SUGGERIMENTO: si consiglia di usare una variabile per tenere traccia dello "stato"

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

unsigned char* f(unsigned char* a, int length, int* new_length) {
    *new_length = 0;
    char parsing_conf = 0;
    for(int i = 0; i < length; i++){
        if(!parsing_conf && (a[i]==0 || a[i]==1)) {
            parsing_conf = 1;
            (*new_length)++;
        } else if(parsing_conf && !(a[i]==0 || a[i]==1)) {
            parsing_conf = 0;
        }
    }

    unsigned char *result = (unsigned char*) malloc(sizeof(unsigned char) * (*new_length));
    parsing_conf = 0;
    for(int i = 0, j = 0, k = 0; i < length; i++) { 
        if(!parsing_conf && (a[i]==0 || a[i]==1)) {
            // printf("Starting new conf result[%d] at a[%d] = %d\n", j, i, a[i]);
            parsing_conf = 1;
            result[j] = a[i];
            k = 1;
        } else if(parsing_conf && !(a[i]==0 || a[i]==1)) {
            // printf("Stop writing conf at a[%d] = %d\n", i, a[i]);
            parsing_conf = 0;
            k = 0;
            j++;
        } else if(parsing_conf) {
            // printf("Continuing conf at a[%d] = %d\n", i, a[i]);
            result[j] |= a[i] << k; // result[j] += a[i] << k;
            k++;
        }
    }
    return result;
}
// STUDENT-SOLUTION-END

void test(){
    check((unsigned char[]) { 0 }, 1, (unsigned char[]) { 0 }, 1); // simplest configuration #1
    check((unsigned char[]) { 1 }, 1, (unsigned char[]) { 1 }, 1); // simplest configuration #2
    check((unsigned char[]) { 2 }, 1, (unsigned char[]) {  }, 0); // simplest invalid configuration
    check((unsigned char[]) { 88, 5, 77 }, 3, (unsigned char[]) {  }, 0); // no configurations, only boundary values
    check((unsigned char[]) { 0, 1, 1, 1 }, 4, (unsigned char[]) { 14 }, 1); // a single configuration
    check((unsigned char[]) { 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1 }, 13, (unsigned char[]) { 4 }, 1); // a configuration with exceeding length
    check((unsigned char[]) { 88, 1, 1, 5, 1, 0, 1, 1, 77 }, 9, (unsigned char[]) { 3, 13 }, 2); // example in problem description comment
    check((unsigned char[]) { 3, 
                              1, 
                              5, 
                              0, 0, 1, 
                              77, 55, 
                              0, 0, 0, 0,   0, 0, 0, 1, 
                              3, 
                              0, 0, 0, 0,   0, 0, 0, 0,     1, 1 
                            }, 27, (unsigned char[]) { 1, 4, 128, 0 }, 4); // an additional, full example

}

int main(){
    test();
    return 0;
}

int check(unsigned char* input, int input_len, unsigned char* expected, int expected_len) {
    int actual_len = 0;
    unsigned char *actual = f(input, input_len, &actual_len);
    int equals = actual==expected || array_equals(actual, expected, actual_len, expected_len);
    printf("TEST on input ");
    print_array(input, input_len);
    printf("\n\tGOT: ");
    print_array(actual, actual_len);
    puts("");
    if(!equals){
        printf("FAIL");
        printf("\n\tActual: ");
        actual!=NULL ? print_array(actual, actual_len) : printf("NULL");        
        printf("\n\tExpected: ");
        print_array(expected, expected_len);
    } else {
        printf("OK");
    }
    printf("\n---\n");
    free(actual);
    return equals;
}

void print_array(unsigned char *a, int size){
    int i;
    printf("[");
    for (i=0; i<size; i++) printf("%d%s", a[i], i<size-1 ? "," : "");
    printf("]");
} 

int array_equals(unsigned char a[], unsigned char b[], int sizea, int sizeb){
    if(a == b) return FALSE;  // shouldn't pass the same array
    if(sizea != sizeb) return FALSE;
    for (; sizea--;)
        if (a[sizea] != b[sizea])
            return FALSE;
    return TRUE;
}
