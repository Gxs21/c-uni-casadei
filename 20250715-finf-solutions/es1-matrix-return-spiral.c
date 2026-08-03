#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int array_equals(int a[], int b[], int sizea, int sizeb);
void print_array(int *a, int size);
int matrix_equals(int **a, int **b, int a_rows, int a_cols, int b_rows, int b_cols); // controlla l'uguaglianza di due matrici
void free_matrix(int **a, int a_rows); // libera la memoria associata a una matrice
void print_matrix(int **a, int a_rows, int a_cols); // stampa in stdout una matrice
int **make_matrix(int rows, int cols, int elem); // costruisce una matrice di `rows` righe e `cols` colonne, con ogni cella inizializzata a `elem`
int **build_matrix(int rows, int cols, int *elems); // costruisce una matrice di `rows` righe e `cols` colonne, con contenuto fornito sequenzialmente dall'array `elems`

/*
Implementare una funzione f(N, K) che 

- presi in ingresso due interi N e K
- restituisca in uscita una nuova matrice quadrata NxN i cui elementi disegnano una spirale di valori crescenti a partire da K

Ad esempio, un'invocazione f(3, 0) deve produrre una matrice 3x3 fatta come segue 
             | 0, 7, 6 |
             | 1, 8, 5 |
             | 2, 3, 4 |
ovvero dove il valore K=0 è il valore iniziale alla cella (0,0), e i valori delle restanti celle sono dati dagli incrementi 
del valore delle celle precedenti nella "spirale". Si osservino le celle per gli interi successivi 0, 1, 2, 3, e così via:
tali valori sono disposti lungo i bordi (in senso antiorario) della matrice e, una volta riempito un perimetro, la successione
procede sempre in senso antiorario nei "bordi" delle sottomatrici interne. 
Geometricamente, la "spirale" è data proprio dalla disposizione ordinata dei valori della successione numerica con valore iniziale K.
In esempio astratto, f(N, K) con N=4 e K generico compilerebbe la matrice 4x4 come segue:
             | K,   K+11, K+10, K+9 |
             | K+1, K+12, K+15, K+8 |
             | K+2, K+13, K+14, K+7 |
             | K+3, K+4,  K+5,  K+6 |

Osservazioni e consigli:

* occorre restituire un "puntatore di puntatore", e allocare dinamicamente la matrice (che, ricordiamo, è concettualizzabile come array di puntatori 
  agli array corrispondenti alle righe); si prenda spunto dalle funzioni make_matrix e build_matrix incluse in questo sorgente
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
int** f(int N, int K) {
    return NULL;
}
// STUDENT-SOLUTION-END

// GLOBAL VARS FOR TESTS
int n_tests = 0, n_succ_tests = 0;

int check(char* name, int N, int K, int** exp_matrix) {
    printf("\n-----------------\nTEST %d: %s\n-----------------\n", n_tests++, name);
    int **res = f(N, K);
    int success = matrix_equals(res, exp_matrix, N, N, N, N);
    puts("");
    if(!success){
        printf("Result: FAIL\n");
        printf("Actual:\n");
        print_matrix(res, N, N);
        printf("\nExpected:\n");
        print_matrix(exp_matrix, N, N);
    } else {
        n_succ_tests++;
        printf("Result: OK\n");
        printf("Actual matrix equals expected matrix:\n");
        print_matrix(exp_matrix, N, N);
    }
    printf("\n");
    free_matrix(res, N);
    free_matrix(exp_matrix, N);
    return success;
}


void test(){
    check("3x3 spiral starting at K=0", 3, 0, build_matrix(3, 3, (int[]) {
        0, 7, 6,
        1, 8, 5,
        2, 3, 4
    }));

    check("1x1 spiral starting at K=7", 1, 7, build_matrix(1, 1, (int[]) {
        7
    }));

    check("2x2 spiral starting at K=2", 2, 2, build_matrix(2, 2, (int[]) {
        2, 5,
        3, 4
    }));

    check("4x4 spiral starting at K=-9", 4, -9, build_matrix(4, 4, (int[]) {
        -9,  2,  1,  0,
        -8,  3,  6, -1,
        -7,  4,  5, -2,
        -6, -5, -4, -3
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
