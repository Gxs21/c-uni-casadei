#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define NELEMS(x) (sizeof(x)>0 ? sizeof(x) / sizeof((x)[0]) : 0)

int array_equals(int a[], int b[], int sizea, int sizeb);
int check(int a[], int b[], int sizea, int sizeb, char *lbl);
void print_array(int *a, int size);

/*
Realizzare una funzione `f` con l'obiettivo di generare array corrispondenti a un "range" con passo dato.
Gli input sono:
1. l'intero `from` indicante il valore iniziale del range (inclusivo)
2. l'intero `to` indicante il valore finale del range (inclusivo)
3. l'intero `step` indicante il passo tra un valore del range e il successivo
4. il puntatore all'intero che descrive la dimensione dell'array risultante
L'output è l'array di interi risultante.
Ad esempio, f(1,5,2,p) deve assegnare il valore 3 al puntatore p, e restituire un nuovo array di contenuto [1,3,5]. 
f(3,-5,-5) deve restituire un array di contenuto [3,-2] e settare il puntatore a 2.
Si consideri la funzione `test` sottostante per ulteriori esempi e casi particolari.

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
int* f(int from, int to, int step, int *result_size) {
    return NULL; // TODO
}
// STUDENT-SOLUTION-END

void test(){
    // Test simple sequence
    int sz1; int *o1 = f(1, 10, 1, &sz1);
    check(o1, (int[]) { 1,2,3,4,5,6,7,8,9,10 }, sz1, 10, "Simple sequence");

    int sz2; int *o2 = f(1, 5, 10, &sz2);
    check(o2, (int[]) { 1 }, sz2, 1, "Large step");

    int sz3; int *o3 = f(1, 5, 2, &sz3);
    check(o3, (int[]) { 1, 3, 5 }, sz3, 3, "End is exclusive");

    int sz4; int *o4 = f(9, -11, -4, &sz4);
    check(o4, (int[]) { 9, 5, 1, -3, -7, -11 }, sz4, 6, "Negative step");

    int sz5; int *o5 = f(9, 1, 1, &sz5);
    check(o5, (int[]) { 0 }, sz5, 0, "Inverted ends with positive step");

    int sz6; int *o6 = f(1, 10, 0, &sz6);
    check(o6, (int[]) { 1 }, sz6, 1, "Zero step");

    int sz7; int *o7 = f(3, -5, -5, &sz7);
    check(o7, (int[]) { 3, -2 }, sz7, 2, "Negative step with non-divisible range");

    free(o1); free(o2); free(o3); free(o4); free(o5); free(o6); free(o7);
}

int main(){
    test();
    return 0;
}

int check(int a[], int b[], int sizea, int sizeb, char *lbl){
    int equals = array_equals(a, b, sizea, sizeb);
    printf("%s%s", equals ? "OK: " : "FAIL: ", lbl);
    if(!equals){
        printf(" - Expected: ");
        print_array(b, sizeb);
        printf(" - Actual: ");
        print_array(a, sizea);
    }
    puts("");
    return equals;
}

int array_equals(int a[], int b[], int sizea, int sizeb){
    if(a == b) return FALSE; // shouldn't pass the same array
    if(sizea != sizeb) return FALSE;
    for (; sizea--;)
        if (a[sizea] != b[sizea])
            return FALSE;
    return TRUE;
}

void print_array(int *a, int size){
    if (a == NULL) {
        printf("(NULL)");
        return;
    }
    if(size == 0) {
        printf("(empty)");
        return;
    }
    int i;
    for (i=0; i<size; i++) printf("%d ", a[i]);
} 
