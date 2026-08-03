#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int array_equals(int a[], int b[], int sizea, int sizeb);
void print_array(int *a, int size);
int matrix_equals(int **a, int **b, int a_rows, int a_cols, int b_rows, int b_cols);
void free_matrix(int **a, int a_rows);
void print_matrix(int **a, int a_rows, int a_cols);
int **make_matrix(int rows, int cols, int elem);
int **build_matrix(int rows, int cols, int *elems);
int check(char* name, int** input, int N, int M, int** exp, int exp_count);

/*
Implementare una funzione `saddle_points(matrix, N, M, count)` che:

- accetta in ingresso una matrice N x M di interi
- accetta un puntatore a intero count, passato per riferimento
- restituisce una nuova matrice N x M di interi
- nella nuova matrice:
    * ogni cella contiene 1 se la cella corrispondente nella matrice originale
      e' un punto di sella per righe
    * ogni altra cella contiene 0
- scrive in count il numero totale di punti di sella trovati

Una cella in posizione (i, j) e' un punto di sella per righe se il suo valore e':

- massimo nella propria riga, cioe' maggiore o uguale a tutti gli elementi
  della riga i
- minimo nella propria colonna, cioe' minore o uguale a tutti gli elementi
  della colonna j

I confronti non sono stretti: se lo stesso valore massimo o minimo compare piu'
volte, tutte le celle che soddisfano entrambe le proprieta' sono punti di sella.

In altre parole, un'invocazione saddle_points(matrix, 3, 3, &count) con

             | 3, 1, 2 |
    matrix = | 4, 2, 5 |
             | 6, 3, 7 |

deve restituire una nuova matrice:

             | 1, 0, 0 |
    result = | 0, 0, 0 |
             | 0, 0, 0 |

e deve scrivere in count il valore 1.

La cella in posizione (0, 0), che contiene 3, e' infatti il massimo della prima
riga ed e' contemporaneamente il minimo della prima colonna.

Osservazioni e consigli:

* SUGGERIMENTO: Si faccia riferimento alle funzioni di test/verifica per esempi di funzionamento.
* SUGGERIMENTO: La funzione non deve modificare la matrice originale, ma deve restituire una nuova matrice.
* SUGGERIMENTO: Si suggerisce di compilare con opzione -Wall per ottenere tutti i warning del compilatore: gcc -Wall source.c

NOTE GENERALI:

*) ATTENZIONE: la propria soluzione va inserita nella porzione del sorgente inclusa tra i commenti single-line
`// STUDENT-SOLUTION-START` e  `// STUDENT-SOLUTION-END`.
Codice scritto al di fuori di tali commenti non sara' considerato durante la valutazione.
*) E' possibile definire piu' funzioni ausiliarie qualora lo si ritenga opportuno.
Ma lo si faccia all'interno dei commenti, come indicato nel punto precedente.
*) ATTENZIONE: la soluzione verra' confrontata con quella dei colleghi mediante strumenti automatici al fine
di rilevare potenziali copiature. Il controllo e' resistente a rename di variabili, spezzamento di espressioni etc.
Qualora vengano riscontrate similarita' importanti, e' possibile che la prova possa venire annullata, e che ulteriori
modalita' di verifica di competenze, ad es. prove orali, siano attuate.
*/
// STUDENT-SOLUTION-START

int check_biggest_in_row(int **matrix, int my_index, int row_index, int n){
    int elem = matrix[row_index][my_index];
    for(int i = 0; i < n; i++){
        if(matrix[row_index][i] > elem){
            return 0;
        }
    }
    return 1;
}

int check_smallest_in_column(int **matrix, int my_index, int column_index, int n){
    int elem = matrix[my_index][column_index];
    for(int i = 0; i < n; i++){
        if(matrix[i][column_index] < elem){
            return 0;
        }
    }
    return 1;
}

int count_saddle_points(int **matrix,int N, int M){
    int count = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(matrix[i][j]){
                count++;
            }
        }
    }
    return count;
}

int **saddle_points(int **matrix, int N, int M, int *count) {
    if(N == 0 && M == 0){
        *count = 0;
        return build_matrix(0, 0, NULL);
    }

    int **result = make_matrix(N, M, 0);

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            int biggest_in_row = check_biggest_in_row(matrix, j, i, M);
            int smallest_in_column = check_smallest_in_column(matrix, i, j, N);
            if (biggest_in_row && smallest_in_column){
                result[i][j] = 1;
            }
        }
    }

    *count = count_saddle_points(result, N, M);
    return result;

}
// STUDENT-SOLUTION-END

void test() {
    // Caso 0: esempio delle istruzioni
    int** m0 = build_matrix(3, 3, (int[]) {
        3, 1, 2,
        4, 2, 5,
        6, 3, 7
    });
    int** exp0 = build_matrix(3, 3, (int[]) {
        1, 0, 0,
        0, 0, 0,
        0, 0, 0
    });
    check("Example from instructions", m0, 3, 3, exp0, 1);

    // Caso 1: nessun punto di sella
    int** m1 = build_matrix(3, 3, (int[]) {
        1, 3, 2,
        2, 1, 3,
        3, 2, 1
    });
    int** exp1 = build_matrix(3, 3, (int[]) {
        0, 0, 0,
        0, 0, 0,
        0, 0, 0
    });
    check("No saddle points", m1, 3, 3, exp1, 0);

    // Caso 2: piu' punti di sella
    int** m2 = build_matrix(3, 4, (int[]) {
        4, 4, 1, 0,
        5, 5, 2, 1,
        6, 6, 3, 2
    });
    int** exp2 = build_matrix(3, 4, (int[]) {
        1, 1, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    });
    check("Several saddle points", m2, 3, 4, exp2, 2);

    // Caso 3: matrice con una sola riga
    int** m3 = build_matrix(1, 5, (int[]) {
        1, 7, 3, 7, 2
    });
    int** exp3 = build_matrix(1, 5, (int[]) {
        0, 1, 0, 1, 0
    });
    check("Single row matrix", m3, 1, 5, exp3, 2);

    // Caso 4: matrice con una sola colonna
    int** m4 = build_matrix(5, 1, (int[]) {
        2,
        5,
        1,
        4,
        3
    });
    int** exp4 = build_matrix(5, 1, (int[]) {
        0,
        0,
        1,
        0,
        0
    });
    check("Single column matrix", m4, 5, 1, exp4, 1);

    // Caso 5: tutti gli elementi uguali
    int** m5 = build_matrix(2, 3, (int[]) {
        4, 4, 4,
        4, 4, 4
    });
    int** exp5 = build_matrix(2, 3, (int[]) {
        1, 1, 1,
        1, 1, 1
    });
    check("All equal values", m5, 2, 3, exp5, 6);

    // Caso 6: matrice 1x1
    int** m6 = build_matrix(1, 1, (int[]) {
        7
    });
    int** exp6 = build_matrix(1, 1, (int[]) {
        1
    });
    check("Single cell matrix", m6, 1, 1, exp6, 1);

    // Caso 7: matrice vuota
    int** m7 = build_matrix(0, 0, NULL);
    int** exp7 = build_matrix(0, 0, NULL);
    check("Empty matrix 0x0", m7, 0, 0, exp7, 0);
}

int n_tests = 0, n_succ_tests = 0;

int main(){
    test();
    printf("=== SUCCESS %d OUT OF %d TESTS ===\n", n_succ_tests , n_tests);
    return 0;
}

int check(char* name, int** input, int N, int M, int** exp, int exp_count) {
    printf("\n-----------------\nTEST %d: %s\n-----------------\n", n_tests++, name);

    int actual_count = 0;
    int** actual = saddle_points(input, N, M, &actual_count);

    int success_matrix = matrix_equals(actual, exp, N, M, N, M);
    int success_count = actual_count == exp_count;
    int success = success_matrix && success_count;

    printf("Input:\n");
    print_matrix(input, N, M);

    printf("\nActual:\n");
    print_matrix(actual, N, M);

    printf("\nExpected count: %d, actual count: %d\n", exp_count, actual_count);

    puts("");

    if(!success){
        printf("Result: FAIL\n");
        printf("Expected matrix:\n");
        print_matrix(exp, N, M);
    } else {
        n_succ_tests++;
        printf("Result: OK\n");
    }

    printf("\n");

    free_matrix(input, N);
    free_matrix(exp, N);
    free_matrix(actual, N);

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
    if(a == NULL || b == NULL) return a == b;
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
    if(a == NULL) {
        printf("NULL\n");
        return;
    }
    for (int i=0; i<a_rows; i++) {
        printf("| ");
        for(int j=0; j<a_cols; j++) {
            printf("%2d ", a[i][j]);
        }
        printf(" |\n");
    }
}

int array_equals(int a[], int b[], int sizea, int sizeb){
    if(a == b) return FALSE;
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
