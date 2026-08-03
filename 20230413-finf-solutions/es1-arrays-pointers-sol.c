#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int array_equals(int a[], int b[], int sizea, int sizeb);
int check(int* input, int len, int shift, int* expected);
void print_array(int *a, int size);

/*
Realizzare una funzione `f` con l'obiettivo di traslare (o shiftare) i valori, verso destra o verso sinistra, 
con traboccamento nella parte opposta.

Si consideri le seguenti corrispondenze di input/output:

* f([1,2,3,4,5], 5, N)
    * N = +1 => risultato [5,1,2,3,4]
    * N = -1 => risultato [2,3,4,5,1]
    * N = 0 => risultato [1,2,3,4,5]
    * N = 4 => risultato [2,3,4,5,1]
    * N = 5 => risultato [1,2,3,4,5]
    * N = -5 => risultato [1,2,3,4,5]

Si noti che espressioni `x % N` restituiscono valori modulo `N` (ovvero tra 0..`N`) in valore assoluto,
ma preservano il segno. Quindi `-1 % 5` dà `-1`, e `-7 % 5` dà `-2`.

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
int* f(int* a, int length, int shift) {
    int *result = (int*) malloc(sizeof(int) * length);
    for(int i = 0; i < length; i++) {
        int new_pos = (i+shift)%length;
        result[new_pos >= 0 ? new_pos : length+new_pos] = a[i];
    }
    return result;
}
// STUDENT-SOLUTION-END

void test(){
    check((int[]) { 1, 2, 3, 4, 5 }, 5, 0, (int[]) { 1, 2, 3, 4, 5 });
    check((int[]) { 1, 2, 3, 4, 5 }, 5, 1, (int[]) { 5, 1, 2, 3, 4 });
    check((int[]) { 1, 2, 3, 4, 5 }, 5, -1, (int[]) { 2, 3, 4, 5, 1 });
    check((int[]) { 1, 2, 3, 4, 5 }, 5, 4, (int[]) { 2, 3, 4, 5, 1 });
    check((int[]) { 1, 2, 3, 4, 5 }, 5, 5, (int[]) { 1, 2, 3, 4, 5 });
    check((int[]) { 1, 2, 3, 4, 5 }, 5, -5, (int[]) { 1, 2, 3, 4, 5 });
    check((int[]) { 1, 2, 3, 4, 5 }, 5, -7, (int[]) { 3, 4, 5, 1, 2 });
    check((int[]) {  }, 0, 1, (int[]) {  });
    check((int[]) {  }, 0, 99, (int[]) {  });
    check((int[]) { 77 }, 1, 0, (int[]) { 77 });
    check((int[]) { 77 }, 1, 99, (int[]) { 77 });
}

int main(){
    test();
    return 0;
}

int check(int* input, int len, int shift, int* expected){
    int *actual = f(input, len, shift);
    int equals = actual!=NULL && array_equals(actual, expected, len, len);
    printf("TEST on input ");
    print_array(input, len);
    printf(" with shift %+d: %s ", shift, equals ? "OK" : "FAIL");
    printf("\n\tActual: ");
    actual!=NULL ? print_array(actual, len) : printf("NULL");
    if(!equals){
        printf("\n\tExpected: ");
        print_array(expected, len);
    }
    puts("");
    return equals;
}

void print_array(int *a, int size){
    int i;
    printf("[");
    for (i=0; i<size; i++) printf("%d%s", a[i], i<size-1 ? "," : "");
    printf("]");
} 

int array_equals(int a[], int b[], int sizea, int sizeb){
    if(a == b) return FALSE;  // shouldn't pass the same array
    if(sizea != sizeb) return FALSE;
    for (; sizea--;)
        if (a[sizea] != b[sizea])
            return FALSE;
    return TRUE;
}
