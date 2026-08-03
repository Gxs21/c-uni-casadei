#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int array_equals(int a[], int b[], int sizea, int sizeb);
int check(int* input, int input_len, int* expected, int expected_len);
void print_array(int *a, int size);

/*
Realizzare una funzione `h(spec,n,lenPtr)` che accetta in input 

    1. un puntatore ad intero `spec` (corrispondente ad un array)
    2. la lunghezza `n` dell'array `spec` in input
    3. un puntatore ad intero `lenPtr`

e che deve restituire in output il puntatore ad un nuovo array (la cui lunghezza sarà da depositare nella cella di memoria puntata da `lenPtr`)
generato seguendo le istruzioni contenute in `spec`.
In particolare, `spec` avrà lunghezza pari `n`, e sarà formato da una successione di `n/2` coppie (N_i,K_i)
stanti ad indicare che il numero `N_i` va inserito per `K_i` occorrenze nell'array risultante.

Ad esempio, `h([7,3, 5,2, 1,0, 7,1], 8, lenPtr) dovrà restituire il puntatore ad un nuovo array di contenuto [7,7,7,5,5,7], di lunghezza 3 + 2 + 0 + 1 = 6,
ovvero dove il numero 7 (`spec[0]`) compare 3 (`spec[1]`) volte, il numero 5 (`spec[2]`) compare 2  (`spec[3]`) volte, e così via.

Si faccia riferimento ad ulteriori esempi nella funzione di test (in particolare, si noti il comportamento atteso se un certo `K_i` non è positivo).

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
int* h(int* a, int length, int* new_length) {
    *new_length = 0;
    for(int i = 1; i < length; i += 2) *new_length += a[i] > 0 ? a[i] : 0;
    int* result = (int*) malloc(sizeof(int) * (*new_length));
    for(int i = 0, k = 0; i < length; i += 2) {
        for(int j = 0; j < a[i+1]; j++) result[k++] = a[i];
    }
    return result;
}
// STUDENT-SOLUTION-END

void test(){
    check((int[]) { }, 0, (int[]) {  }, 0);
    check((int[]) { 1, 0 }, 2, (int[]) {  }, 0);
    check((int[]) { 1, 0, 2, 0, 3, -1 }, 6, (int[]) {  }, 0);
    check((int[]) { 1, 1 }, 2, (int[]) { 1 }, 1);
    check((int[]) { 1, 1, 1, 1 }, 4, (int[]) { 1, 1 }, 2);
    check((int[]) { 1, 5 }, 2, (int[]) { 1, 1, 1, 1, 1 }, 5);
    check((int[]) { 1, 1, 0, 3, -1, -1}, 6, (int[]) { 1, 0, 0, 0 }, 4);
    check((int[]) { 7,3, 5,2, 1,0, 7,1 }, 8, (int[]) { 7, 7, 7, 5, 5, 7 }, 6);
}

int main(){
    test();
    return 0;
}

int check(int* input, int input_len, int* expected, int expected_len) {
    int actual_len;
    int* actual = h(input, input_len, &actual_len);
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
