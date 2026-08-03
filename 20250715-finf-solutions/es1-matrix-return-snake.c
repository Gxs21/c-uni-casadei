#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define LTR 0 // LEFT-to-RIGHT
#define UTD 1 // UP-to-DOWN

int array_equals(int a[], int b[], int sizea, int sizeb);
void print_array(int *a, int size);
int matrix_equals(int **a, int **b, int a_rows, int a_cols, int b_rows, int b_cols); // controlla l'uguaglianza di due matrici
void free_matrix(int **a, int a_rows); // libera la memoria associata a una matrice
void print_matrix(int **a, int a_rows, int a_cols); // stampa in stdout una matrice
int **make_matrix(int rows, int cols, int elem); // costruisce una matrice di `rows` righe e `cols` colonne, con ogni cella inizializzata a `elem`
int **build_matrix(int rows, int cols, int *elems); // costruisce una matrice di `rows` righe e `cols` colonne, con contenuto fornito sequenzialmente dall'array `elems`

/*
Implementare una funzione f(N, M, K, D) che 

- presi in ingresso quattro interi N, M, K, D
- restituisca in uscita una nuova matrice NxM "a serpentina", ovvero
  riempita con i valori della successione intera K, K+1, K+2, ..., K+N*M-1, 
  piazzati nella matrice seguendo una serpentina nella direzione determinata da D)

Ad esempio, un'invocazione f(3, 4, 0, 0) deve produrre una matrice 3x4 fatta come segue 
             | 0, 5, 6, 11 |
             | 1, 4, 7, 10 |
             | 2, 3, 8, 9  |
dove abbiamo N=3 righe, M=4 colonne, il valore di partenza nella cella (0,0) è K=0, e D=0 significa un riempimento Left-to-Right.
In esempio astratto, f(N=4, M=3, K, D=1) compilerebbe la matrice come segue:
             | K,    K+1,  K+2, |
             | K+5,  K+4,  K+3, |
             | K+6,  K+7,  K+8, |
             | K+11, K+10, K+9  |

Nota:

* Il parametro `D` definisce la direzione principale della "serpentina". 
  Nota che puoi usare le costanti simboliche definite sopra LTR (vuol dire Left-To-Right, e vale 0) e UTD (Up-To-Down, vale 1).
  Una serpentina Left-To-Right riempie scorrendo le colonne della matrice alternando passate verso il basso a passate verso l'alto (come nel primo esempio).
  Una serpentina Up-to-Down riempie scorrendo le righe della matrice alternando passate verso destra a passate verso sinistra (come nel secondo esempio).

Osservazioni e consigli:

* occorre restituire un "puntatore di puntatore", e allocare dinamicamente la matrice (che, ricordiamo, è concettualizzabile come array di puntatori 
  agli array corrispondenti alle righe); si prenda spunto dalle funzioni make_matrix e build_matrix incluse in questo sorgente
* si valuti di risolvere il problema in prima battuta battezzando una direzione (ovvero ignorando `D`), 
  cercando poi di generalizzare una volta che questa è funzionante; 
* SUGGERIMENTO: Si faccia riferimento alle funzioni di test/verifica per esempi di funzionamento
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
int** f(int N, int M, int K, int D) {
    return NULL;
}
// STUDENT-SOLUTION-END

// GLOBAL VARS FOR TESTS
int n_tests = 0, n_succ_tests = 0;

int check(char* name, int N, int M, int K, int D, int** exp_matrix) {
    printf("\n-----------------\nTEST %d: %s\n-----------------\n", n_tests++, name);
    int **res = f(N, M, K, D);
    int success = matrix_equals(res, exp_matrix, N, M, N, M);
    puts("");
    if(!success){
        printf("Result: FAIL\n");
        printf("Actual:\n");
        print_matrix(res, N, M);
        printf("\nExpected:\n");
        print_matrix(exp_matrix, N, M);
    } else {
        n_succ_tests++;
        printf("Result: OK\n");
        printf("Actual matrix equals expected matrix:\n");
        print_matrix(exp_matrix, N, M);
    }
    printf("\n");
    free_matrix(res, N);
    free_matrix(exp_matrix, N);
    return success;
}


void test(){
    check("3x4 L-t-R snake starting at K=0", 3, 4, 0, LTR, build_matrix(3, 4, (int[]) {
        0, 5, 6, 11, 
        1, 4, 7, 10, 
        2, 3, 8, 9  
    }));

    
    check("1x1 L-t-R snake starting at K=7", 1, 1, 7, LTR, build_matrix(1, 1, (int[]) {
        7
    }));

    check("1x1 U-t-D snake starting at K=-5", 1, 1, -5, UTD, build_matrix(1, 1, (int[]) {
        -5
    }));

    check("4x3 U-t-D snake starting at K=-9", 4, 3, -9, UTD, build_matrix(4, 3, (int[]) {
        -9, -8, -7,
        -4, -5, -6,
        -3, -2, -1,
         2,  1,  0 
    }));

    check("5x1 U-t-D snake starting at K=3", 5, 1, 3, UTD, build_matrix(5, 1, (int[]) {
        3,
        4,
        5,
        6,
        7,
    }));

    check("1x6 L-t-R snake starting at K=3", 1, 6, 3, LTR, build_matrix(1, 6, (int[]) {
        3,4,5,6,7,8
    }));
}

int main(){
    test();
    printf("=== SUCCESS %d OUT OF %d TESTS ===\n", n_succ_tests , n_tests);
    return 0;
}


int **make_matrix(int rows, int cols, int elem) {
    int** m = (int **) malloc(rows * sizeof(int*));
    for(int i=0; i<rows; i++){
        m[i] = (int *) malloc(cols * sizeof(int));
        for(int j=0; j<cols; j++){
            m[i][j] = elem;
        }
    }
    return m;
}

int **build_matrix(int rows, int cols, int *elems) {
    int** m = (int **) malloc(rows * sizeof(int*));
    for(int i=0; i<rows; i++){
        m[i] = (int *) malloc(cols * sizeof(int));
        for(int j=0; j<cols; j++){
            m[i][j] = elems[i * cols + j];
        }
    }
    return m;
}

int matrix_equals(int **a, int **b, int a_rows, int a_cols, int b_rows, int b_cols) {
    if(a_rows != b_rows || a_cols != b_cols) return FALSE;
    if(a == NULL) return b == NULL;
    for (int i=0; i<a_rows; i++) {
        for(int j=0; j<a_cols; j++) {
            if(a[i][j] != b[i][j]) return FALSE;
        }
    }
    return TRUE;
}


void free_matrix(int **a, int a_rows) { 
    if(a == NULL) return;
    for (int i=0; i<a_rows; i++) {
        free(a[i]);
    }
    free(a);
}

void print_matrix(int **a, int a_rows, int a_cols) { 
    if(a == NULL) return;
    for (int i=0; i<a_rows; i++) {
        printf("| ");
        for(int j=0; j<a_cols; j++) {
            printf("%2d ", a[i][j]);
        }
        printf(" |\n");
    }
}

int array_equals(int a[], int b[], int sizea, int sizeb){
    if(a == b) return FALSE;  // shouldn't pass the same array
    if(a == NULL || b == NULL) return FALSE;
    if(sizea != sizeb) return FALSE;
    for (; sizea--;)
        if (a[sizea] != b[sizea])
            return FALSE;
    return TRUE;
}

void print_array(int *a, int size){
    if(a == NULL) {
        printf("NULL");
        return;
    }
    int i;
    printf("[");
    for (i=0; i<size; i++) printf("%d%s", a[i], i<size-1 ? "," : "");
    printf("]");
} 
