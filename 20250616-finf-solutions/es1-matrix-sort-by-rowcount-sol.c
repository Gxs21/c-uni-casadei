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
int **clone_matrix(int **m, int rows, int cols);
int check(char* name, int** input, int N, int M,  int** exp); // funzione di test

/*
Implementare una funzione f(matrix, N, M) che 

- accetta in ingresso una matrice N x M di interi  e
- crea una nuova matrice della stessa dimensione di M, con le stesse righe di M
  ma dove queste sono ordinate sulla base di quanto sono dense (ovvero, in base al numero di elementi diversi da zero)

In altre parole, un'invocazione f(matrix, 4, 3) con 
             | 0, 1, 0 |
    matrix = | 3, 7, 8 |
             | 0, 5, 0 |
             | 1, 1, 1 |
deve restituire una matrice
                 | 3, 7, 8 |    <-- questa riga infatti 0 elementi uguali a 0
    new_matrix = | 1, 1, 1 |    <-- anche questa riga non ha nessuno zero
                 | 1, 5, 0 |    <-- questa ha una occorrenza di 0
                 | 0, 1, 0 |    <-- questa ha 2 occorrenze di 0


Osservazioni e consigli:

* Per la creazione di nuove matrici, si osservino make_matrix() o build_matrix(), oppure anche clone_matrix() che crea una copia di matrice esistente
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
int count_different(int *array, int N, int K) {
    int count = 0;
    for(int i=0; i<N; i++) {
        if(array[i] != K) count++;
    }
    return count;
}

int** f(int **original_matrix, int N, int M) {
    int **matrix = clone_matrix(original_matrix, N, M);
    int counts[N];
    for(int i = 0; i<N; i++) counts[i] = 0;
    for(int i = 0; i<N; i++) counts[i] = count_different(matrix[i], M, 0);
    for(int i=0; i<N-1; i++) {
        int max_row = i;
        int j=i;
        for(; j<N; j++) {
            if(counts[j] > counts[max_row]) max_row = j;
        }
        int *temp = matrix[i];
        matrix[i] = matrix[max_row];
        matrix[max_row] = temp;
        int sum_temp = counts[i];
        counts[i] = counts[max_row];
        counts[max_row] = sum_temp;
    }
    return matrix;
}
// STUDENT-SOLUTION-END

void test() {
    // Caso 0: esempio base (già presente)
    int** m0 = build_matrix(4, 3, (int[]) {
        0, 1, 0,
        3, 7, 8,
        1, 5, 0,
        1, 1, 1
    });
    int** exp0 = build_matrix(4, 3, (int[]) {
        3, 7, 8,
        1, 1, 1,
        1, 5, 0,
        0, 1, 0
    });
    check("Example from instructions", m0, 4, 3, exp0);

    // Caso 1: tutte le righe con stessa densità
    int** m1 = build_matrix(3, 4, (int[]) {
        1, 0, 1, 0,
        0, 2, 0, 2,
        3, 0, 3, 0
    });
    int** exp1 = build_matrix(3, 4, (int[]) {
        1, 0, 1, 0,
        0, 2, 0, 2,
        3, 0, 3, 0
    });
    check("Equal density rows (no reorder)", m1, 3, 4, exp1);

    // Caso 2: riga tutta di zeri
    int** m2 = build_matrix(3, 3, (int[]) {
        0, 0, 0,
        1, 0, 1,
        1, 1, 1
    });
    int** exp2 = build_matrix(3, 3, (int[]) {
        1, 1, 1,
        1, 0, 1,
        0, 0, 0
    });
    check("One all-zero row", m2, 3, 3, exp2);

    // Caso 3: matrice 1xN (nessun ordinamento)
    int** m3 = build_matrix(1, 5, (int[]) {
        0, 1, 2, 0, 3
    });
    int** exp3 = build_matrix(1, 5, (int[]) {
        0, 1, 2, 0, 3
    });
    check("Single row matrix", m3, 1, 5, exp3);

    // Caso 4: tutte righe già ordinate per densità decrescente
    int** m4 = build_matrix(3, 3, (int[]) {
        1, 2, 3,
        1, 0, 1,
        0, 0, 0
    });
    int** exp4 = build_matrix(3, 3, (int[]) {
        1, 2, 3,
        1, 0, 1,
        0, 0, 0
    });
    check("Already sorted by density", m4, 3, 3, exp4);

    // Caso 5: ordine inverso
    int** m5 = build_matrix(3, 3, (int[]) {
        0, 0, 0,
        0, 1, 0,
        2, 2, 2
    });
    int** exp5 = build_matrix(3, 3, (int[]) {
        2, 2, 2,
        0, 1, 0,
        0, 0, 0
    });
    check("Reverse sorted input", m5, 3, 3, exp5);

    // Caso 6: tutte righe a densità massima
    int** m6 = build_matrix(2, 3, (int[]) {
        1, 1, 1,
        -1, 2, 3
    });
    int** exp6 = build_matrix(2, 3, (int[]) {
        1, 1, 1,
        -1, 2, 3
    });
    check("All dense rows", m6, 2, 3, exp6);

    // Caso 7: matrice 0x0
    int** m7 = build_matrix(0, 0, NULL);
    int** exp7 = build_matrix(0, 0, NULL);
    check("Empty matrix (0x0)", m7, 0, 0, exp7);
}

int n_tests = 0, n_succ_tests = 0;

int main(){
    test();
    printf("=== SUCCESS %d OUT OF %d TESTS ===\n", n_succ_tests , n_tests);
    return 0;
}


int check(char* name, int** input, int N, int M, int** exp) {
    printf("\n-----------------\nTEST %d: %s\n-----------------\n", n_tests++, name);
    int** result = f(input, N, M);
    int success = matrix_equals(result, exp, N, M, N, M);
    //print_matrix(input, N, M);
    puts("");
    if(!success){
        printf("Result: FAIL\n");
        printf("Actual:\n");
        print_matrix(result, N, M);
        printf("\nExpected:\n");
        print_matrix(exp, N, M);
    } else {
        n_succ_tests++;
        printf("Result: OK\n");
    }
    printf("\n");
    free_matrix(input, N);
    free_matrix(result, N);
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

int **clone_matrix(int **m, int rows, int cols) {
    // Allocazione array di puntatori a riga
    int **copy = malloc(rows * sizeof(int *));
    if (!copy) return NULL; // allocazione fallita

    for (int i = 0; i < rows; i++) {
        copy[i] = malloc(cols * sizeof(int));
        if (!copy[i]) {
            // In caso di errore, dealloca righe precedenti
            for (int k = 0; k < i; k++) free(copy[k]);
            free(copy);
            return NULL;
        }

        for (int j = 0; j < cols; j++) {
            copy[i][j] = m[i][j]; // copia effettiva dei dati
        }
    }

    return copy;
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
