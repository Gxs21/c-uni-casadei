#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int array_equals(char a[], char b[], int sizea, int sizeb);
void print_array(char *a, int size);
int matrix_equals(char **a, char **b, int a_rows, int a_cols, int b_rows, int b_cols); // controlla l'uguaglianza di due matrici
void free_matrix(char **a, int a_rows); // libera la memoria associata a una matrice
void print_matrix(char **a, int a_rows, int a_cols); // stampa in stdout una matrice
char **make_matrix(int rows, int cols, char elem); // costruisce una matrice di `rows` righe e `cols` colonne, con ogni cella inizializzata a `elem`
char **build_matrix(int rows, int cols, char *elems); // costruisce una matrice di `rows` righe e `cols` colonne, con contenuto fornito sequenzialmente dall'array `elems`
int check(char* name, char** input, int N, int is_cross, char *central_row, char *central_col, int exp_is_cross, char* exp_central_row, char* exp_central_col); // funzione di test

/*
Implementare una funzione f(matrix, N) che 

- accetta in ingresso una matrice quadrata N x N (con N dispari),  di char (numeri interi su 8 bit di rappresentazione), e
- restituisce in uscita 
a) due nuovi array corrispondenti alla riga e la colonna centrale
b) un flag booleano che vada ad indicare se la matrice rappresenta un "croce pulita" 
  (tutti gli elementi al di fuori della riga e la colonna centrale sono uguali a zero) 

In altre parole, un'invocazione f(matrix, 3, &is_cross) con 
             | 0, 1, 0 |
    matrix = | 3, 7, 8 |
             | 0, 5, 0 |
deve restituire in output:
    a) una coppia di array: [[3,7,8], [1,7,5]] (ovvero un array che include una copia della riga centrale [3,7,8] e la colonna centrale [1,7,5])
    b) l'assegnamento del puntatore a Booleano is_cross a 1 (true), in quanto tutti i valori al di fuori della riga/colonna centrale sono nulli

ATTENZIONE: occorrerà restituire un "puntatore di puntatore". Si ricorda che:

- occorre allocare dinamicamente la memoria degli array per creare una copia della riga/colonna centrale che "sopravviva" alla funzione
- occorre allocare dinamicamente la memoria dell'array dei puntatori (tipo char**) a tali righe/colonne
- si può osservare il funzionamento di make_matrix o build_matrix fornite in questo sorgente per capire come restituire array di array (matrici) da funzioni

Osservazioni e consigli:

* SUGGERIMENTO: si cerchi prima di tutto di impostare il codice corretto per la restituzione del risultato dalla funzione
* SUGGERIMENTO: si faccia riferimento alle funzioni di test/verifica per esempi di funzionamento
* SUGGERIMENTO: si suggerisce di compilare con opzione -Wall per ottenere tutti i warning del compilatore: gcc -Wall source.c

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
char** f(char **matrix, int N, int *is_cross_matrix) {
    *is_cross_matrix = TRUE; // TODO
    return NULL; // TODO
}
// STUDENT-SOLUTION-END

void test(){
    char** m0 = build_matrix(3, 3, (char[]) 
        { 0, 1, 0,
          3, 7, 8,
          0, 5, 0 }
    );
    int is_cross = FALSE;
    char **outs = NULL;
    outs = f(m0, 3, &is_cross);
    if(outs != NULL) check("a 3x3 cross-like matrix (see instructions)", m0, 3, is_cross, outs[0], outs[1], TRUE, (char[]){ 1, 7, 5 }, (char[]){ 3, 7, 8 });

    outs = NULL; is_cross = FALSE;
    char** m1 = build_matrix(3, 3, (char[]) 
        { 3, 0, 0,
          0, 5, 0,
          1, 0, 0 }
    );
    outs = f(m1, 3, &is_cross);
    if(outs != NULL) check("a 3 x 3 non-cross-like matrix", m1, 3, is_cross, outs[0], outs[1], FALSE, (char[]){ 0, 5, 0 }, (char[]){ 0, 5, 0 });

    outs = NULL; is_cross = FALSE;
    char** m2 = build_matrix(5, 5, (char[]) 
        { 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0,
          0, 0, 0, 0, 0,
          0, 0, 0, 0, 0,
          0, 0, 0, 0, 0 }
    );
    outs = f(m2, 5, &is_cross);
    if(outs != NULL) check("a null-matrix is always cross-like", m2, 5, is_cross, outs[0], outs[1], TRUE, (char[]){ 0, 0, 0, 0, 0 }, (char[]){ 0, 0, 0, 0, 0, });

    outs = NULL; is_cross = FALSE;
    char** m4 = build_matrix(1, 1, (char[]) 
        { 0 }
    );
    outs = f(m4, 1, &is_cross);
    if(outs != NULL) check("a singleton matrix is always cross-like", m4, 1, is_cross, outs[0], outs[1], TRUE, (char[]){ 0 }, (char[]){ 0 });
}

int n_tests = 0, n_succ_tests = 0;

int main(){
    test();
    printf("=== SUCCESS %d OUT OF %d TESTS ===\n", n_succ_tests , n_tests);
    return 0;
}


int check(char* name, char** input, int N, int is_cross, char *central_row, char *central_col, int exp_is_cross, char* exp_central_row, char* exp_central_col) {
    printf("\n-----------------\nTEST %d: %s\n-----------------\n", n_tests++, name);
    int success = is_cross==exp_is_cross && array_equals(central_row, exp_central_row, N, N) && array_equals(central_col, exp_central_col, N, N);
    print_matrix(input, N, N);
    puts("");
    if(!success){
        printf("Result: FAIL\n");
        printf("Actual: %s - cross: ", is_cross ? "IS cross" : "IS NOT cross");
        print_array(central_row, N);
        print_array(central_col, N);
        printf("\nExpected: %s - cross: ", exp_is_cross ? "IS cross" : "IS NOT cross");
        print_array(exp_central_row, N);
        print_array(exp_central_col, N);
    } else {
        n_succ_tests++;
        printf("Result: OK\n");
    }
    printf("\n");
    free(central_row); free(central_col);
    free_matrix(input, N);
    return success;
}

char **make_matrix(int rows, int cols, char elem) {
    char** m = (char **) malloc(rows * sizeof(char*));
    for(int i=0; i<rows; i++){
        m[i] = (char *) malloc(cols * sizeof(char));
        for(int j=0; j<cols; j++){
            m[i][j] = elem;
        }
    }
    return m;
}

char **build_matrix(int rows, int cols, char *elems) {
    char** m = (char **) malloc(rows * sizeof(char*));
    for(int i=0; i<rows; i++){
        m[i] = (char *) malloc(cols * sizeof(char));
        for(int j=0; j<cols; j++){
            m[i][j] = elems[i * cols + j];
        }
    }
    return m;
}

int matrix_equals(char **a, char **b, int a_rows, int a_cols, int b_rows, int b_cols) {
    if(a_rows != b_rows || a_cols != b_cols) return FALSE;
    if(a == NULL) return b == NULL;
    for (int i=0; i<a_rows; i++) {
        for(int j=0; j<a_cols; j++) {
            if(a[i][j] != b[i][j]) return FALSE;
        }
    }
    return TRUE;
}


void free_matrix(char **a, int a_rows) { 
    if(a == NULL) return;
    for (int i=0; i<a_rows; i++) {
        free(a[i]);
    }
    free(a);
}

void print_matrix(char **a, int a_rows, int a_cols) { 
    if(a == NULL) return;
    for (int i=0; i<a_rows; i++) {
        printf("| ");
        for(int j=0; j<a_cols; j++) {
            printf("%2d ", a[i][j]);
        }
        printf(" |\n");
    }
}

int array_equals(char a[], char b[], int sizea, int sizeb){
    if(a == b) return FALSE;  // shouldn't pass the same array
    if(a == NULL || b == NULL) return FALSE;
    if(sizea != sizeb) return FALSE;
    for (; sizea--;)
        if (a[sizea] != b[sizea])
            return FALSE;
    return TRUE;
}

void print_array(char *a, int size){
    if(a == NULL) {
        printf("NULL");
        return;
    }
    int i;
    printf("[");
    for (i=0; i<size; i++) printf("%d%s", a[i], i<size-1 ? "," : "");
    printf("]");
} 
