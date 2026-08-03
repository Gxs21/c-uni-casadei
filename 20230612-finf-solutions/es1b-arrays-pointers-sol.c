#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int array_equals(int a[], int b[], int sizea, int sizeb);
int check(int* input, int input_len, int* expected, int expected_len);
void print_array(int *a, int size);

/*
Realizzare una funzione `g` che accetta un array di interi e restituisce un nuovo array SENZA DUPLICATI
 (ovvero mantenendo solo LA PRIMA OCCORRENZA di ogni intero contenuto).
Ad esempio, dato `g(x,4,ptr)` con `x` che punta all'array di lunghezza 4 con contenuto `[1,2,1,4]`, 
 il risultato dev'essere un puntatore al contenuto `[1,2,4]` (dove il secondo `1` dell'array in input 
 è stato tralasciato), dove si è inoltre assegnato il puntatore `ptr` alla lunghezza 3 del nuovo array.
Si osservi la funzione `test` sotto riportata per ulteriori esempi.

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
int has_duplicates_before(int *a, int length, int elem) {
    for(int i=elem-1; i >= 0; i--) {
        if(a[i] == a[elem]) return 1;
    }
    return 0;
}

int* g(int* a, int length, int* new_length) {
    int result_len = length;
    for(int i = 0; i < length; i++) {
        result_len -= has_duplicates_before(a, length, i);
    }
    int* result = (int*) malloc(sizeof(int) * result_len);
    for(int i = 0, j = 0; i < length; i++) {
        if(!has_duplicates_before(a, length, i)) {
            result[j++] = a[i];
        }
    }
    *new_length = result_len;
    return result;
}
// STUDENT-SOLUTION-END

void test(){
    check((int[]) { }, 0, (int[]) {  }, 0);
    check((int[]) { 1 }, 1, (int[]) { 1 }, 1);
    check((int[]) { 1, 1 }, 2, (int[]) { 1 }, 1);
    check((int[]) { 1, 1, 1 }, 3, (int[]) { 1 }, 1);
    check((int[]) { 1, 1, 1, 0, 1, 1, 1}, 7, (int[]) { 1, 0 }, 2);
    check((int[]) { 1, 2, 3 }, 3, (int[]) { 1, 2, 3 }, 3);
    check((int[]) { 1, 2, 1, 3 }, 4, (int[]) { 1, 2, 3 }, 3);    
    check((int[]) { 1, 2, 1, 3, 1, 3, 2 }, 7, (int[]) { 1, 2, 3 }, 3);    
}

int main(){
    test();
    return 0;
}

int check(int* input, int input_len, int* expected, int expected_len) {
    int actual_len;
    int* actual = g(input, input_len, &actual_len);
    int equals = actual==expected || array_equals(actual, expected, actual_len, expected_len);
    printf("TEST on input ");
    print_array(input, input_len);
    if(!equals){
        printf(": FAIL");
        printf("\n\tActual: ");
        actual!=NULL ? print_array(actual, actual_len) : printf("NULL");        
        printf("\n\tExpected: ");
        print_array(expected, expected_len);
    } else {
        printf(": OK");
    }
    puts("");
    free(actual);
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
