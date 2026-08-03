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
int check(char* name, int** input, int N, int M,  int** exp); // funzione di test

/*
Implementare una funzione f(matrix, N, M) che 

- accetta in ingresso una matrice N x M di interi  e
- modifica sul posto la matrice in modo che le righe siano ordinate sulla base del totale della somma dei loro elementi

In altre parole, un'invocazione f(matrix, 4, 3) con 
             | 0, 1, 0 |
    matrix = | 3, 7, 8 |
             | 0, 5, 0 |
             | 1, 1, 1 |
deve modificare sul posto la matrice affinché
             | 3, 7, 8 |    <-- questa riga infatti ha somma 18
    matrix = | 0, 5, 0 |    <-- questa ha somma 5
             | 1, 1, 1 |    <-- questa ha somma 3
             | 0, 1, 0 |    <-- questa ha somma 1


Osservazioni e consigli:

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
int array_sum(int *array, int N) {
    int sum = 0;
    for(int i=0; i<N; i++) {
        sum += array[i];
    }
    return sum;
}

void f(int **matrix, int N, int M) {
    int sums[N];
    for(int i = 0; i<N; i++) sums[i] = array_sum(matrix[i], M);
    for(int i=0; i<N-1; i++) {
        int max_row = i;
        int j=i;
        for(; j<N; j++) {
            if(sums[j] > sums[max_row]) max_row = j;
        }
        int *temp = matrix[i];
        matrix[i] = matrix[max_row];
        matrix[max_row] = temp;
        int sum_temp = sums[i];
        sums[i] = sums[max_row];
        sums[max_row] = sum_temp;
    }
}
// STUDENT-SOLUTION-END

void test() {
    // Caso 0: esempio base (già presente)
    int** m0 = build_matrix(4, 3, (int[]) {
        0, 1, 0,
        3, 7, 8,
        0, 5, 0,
        1, 1, 1
    });
    int** exp0 = build_matrix(4, 3, (int[]) {
        3, 7, 8,
        0, 5, 0,
        1, 1, 1,
        0, 1, 0
    });
    check("Example from instructions", m0, 4, 3, exp0);

    // Caso 1: righe con somma uguale
    int** m1 = build_matrix(3, 4, (int[]) {
        1, 1, 1, 1,
        2, 2, 0, 0,
        0, 0, 2, 2
    });
    int** exp1 = build_matrix(3, 4, (int[]) {
        1, 1, 1, 1,
        2, 2, 0, 0,
        0, 0, 2, 2
    });
    check("Equal row sums", m1, 3, 4, exp1);

    // Caso 2: riga di soli zeri
    int** m2 = build_matrix(3, 3, (int[]) {
        5, 5, 5,
        0, 0, 0,
        2, 2, 2
    });
    int** exp2 = build_matrix(3, 3, (int[]) {
        5, 5, 5,
        2, 2, 2,
        0, 0, 0
    });
    check("One zero row", m2, 3, 3, exp2);

    // Caso 3: matrice 1xN
    int** m3 = build_matrix(1, 5, (int[]) {
        4, 3, 2, 1, 0
    });
    int** exp3 = build_matrix(1, 5, (int[]) {
        4, 3, 2, 1, 0
    });
    check("Single row matrix", m3, 1, 5, exp3);

    // Caso 4: matrice vuota
    int** m4 = build_matrix(0, 0, NULL);
    int** exp4 = build_matrix(0, 0, NULL);
    check("Empty matrix (0x0)", m4, 0, 0, exp4);

    // Caso 5: tutte le righe con somme decrescenti già ordinate
    int** m5 = build_matrix(3, 2, (int[]) {
        9, 0,
        5, 1,
        0, 0
    });
    int** exp5 = build_matrix(3, 2, (int[]) {
        9, 0,
        5, 1,
        0, 0
    });
    check("Already sorted matrix", m5, 3, 2, exp5);

    // Caso 6: righe in ordine inverso
    int** m6 = build_matrix(3, 1, (int[]) {
        0, 
        1,
        5
    });
    int** exp6 = build_matrix(3, 1, (int[]) {
        5,
        1,
        0
    });
    check("Reverse sorted input", m6, 3, 1, exp6);
}


int n_tests = 0, n_succ_tests = 0;

int main(){
    test();
    printf("=== SUCCESS %d OUT OF %d TESTS ===\n", n_succ_tests , n_tests);
    return 0;
}


int check(char* name, int** input, int N, int M, int** exp) {
    printf("\n-----------------\nTEST %d: %s\n-----------------\n", n_tests++, name);
    f(input, N, M);
    int success = matrix_equals(input, exp, N, M, N, M);
    print_matrix(input, N, M);
    puts("");
    if(!success){
        printf("Result: FAIL\n");
        printf("Actual:\n");
        print_matrix(input, N, M);
        printf("\nExpected:\n");
        print_matrix(exp, N, M);
    } else {
        n_succ_tests++;
        printf("Result: OK\n");
    }
    printf("\n");
    free_matrix(input, N);
    free_matrix(exp, N);
    return success;
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
    if(a == NULL || b == NULL) return a==b;
    for (int i=0; i<a_rows && i<b_rows; i++) {
        for(int j=0; j<a_cols && j<b_cols; j++) {
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
