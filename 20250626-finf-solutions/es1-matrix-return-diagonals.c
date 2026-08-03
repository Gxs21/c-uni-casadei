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
int check(char* name, char** input, int N, int is_diag, char *main_diag, char *second_diag, int exp_is_diag, char* exp_main_diag, char* exp_second_diag); // funzione di test

/*
Implementare una funzione f(matrix, N) che 

- accetta in ingresso una matrice quadrata N x N  di char (numeri interi su 8 bit di rappresentazione), e
- restituisce in uscita 
a) il valore Booleano (vero/falso) corrispondente al fatto che la matrice sia diagonale 
   (una matrice diagonale è una matrice quadrata dove solo i valori nella diagonale principale sono diversi da zero)
b) nuovi array corrispondenti alle due diagonali della matrice (principale e secondaria) 

In altre parole, un'invocazione f(matrix, 3, main_diag, second_diag) con 
             | 1, 0, 0 |
    matrix = | 0, 5, 0 |
             | 0, 0, 0 |
deve restituire in output:
    a) 1 (true) come valore di ritorno, in quanto solo la diagonale principale [1, 5, 0] ha valori diversi da zero
    b) due array nuovi, nell'ordine: [1,5,0] (diagonale principale) e [0,5,0] (diagonale secondaria)
    (ATTENZIONE: ordinare gli elementi dalla riga più in alto -- ovvero quella di indice 0)

ATTENZIONE: ogni diagonale sarà rappresentata come parametro "puntatore di puntatore". Si ricorda che:

- occorre allocare dinamicamente la memoria degli array per le due diagonali (affinché sopravvivano alla funzione)
- il valore va assegnato all'oggetto puntatore (di tipo char*) puntato dal parametro (di tipo char**)
- si può operare direttamente sul parametro, o creare una variabile apposita che alla fine verrà assegnata al parametro
- si ricorda che *pptr[i], per le regole di priorità degli operatori, equivale a *(pptr[i]): potrebbe non essere ciò che si intende

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
int f(char **matrix, int N, char **main_diag, char **second_diag) {
    return FALSE; // TODO
}
// STUDENT-SOLUTION-END

void test(){
    char** m0 = build_matrix(3, 3, (char[]) 
        { 1, 0, 0,
          0, 5, 0,
          0, 0, 0 }
    );
    char *main_diag = NULL, *second_diag = NULL;
    int is_diag = f(m0, 3, &main_diag, &second_diag);
    check("a 3x3 diagonal matrix (see instructions)", m0, 3, is_diag, main_diag, second_diag, TRUE, (char[]){ 1, 5, 0 }, (char[]){ 0, 5, 0 });

    main_diag = NULL; second_diag = NULL;
    char** m1 = build_matrix(3, 3, (char[]) 
        { 3, 0, 0,
          0, 5, 0,
          1, 0, 0 }
    );
    is_diag = f(m1, 3, &main_diag, &second_diag);
    check("a 3 x 3 non-diagonal matrix", m1, 3, is_diag, main_diag, second_diag, FALSE, (char[]){ 3, 5, 0 }, (char[]){ 0, 5, 1 });

    main_diag = NULL; second_diag = NULL;
    char** m2 = build_matrix(2, 2, (char[]) 
        { 0, 0,
          0, 0  }
    );
    is_diag = f(m2, 2, &main_diag, &second_diag);
    check("a null-matrix is diagonal", m2, 2, is_diag, main_diag, second_diag, TRUE, (char[]){ 0, 0 }, (char[]){ 0, 0 });


    main_diag = NULL; second_diag = NULL;
    char** m3 = build_matrix(4, 4, (char[]) 
        { 0, 0, 0, 7, 
          0, 0, 6, 0,
          1, 1, 1, 1,
          -3,0, 2, -3  }
    );
    is_diag = f(m3, 4, &main_diag, &second_diag);
    check("a 4x4 non-diagonal matrix", m3, 4, is_diag, main_diag, second_diag, FALSE, (char[]){ 0, 0, 1, -3 }, (char[]){ 7, 6, 1, -3 });

    main_diag = NULL; second_diag = NULL;
    char** m4 = build_matrix(1, 1, (char[]) 
        { 0 }
    );
    is_diag = f(m4, 1, &main_diag, &second_diag);
    check("a singleton matrix is always diagonal", m4, 1, is_diag, main_diag, second_diag, TRUE, (char[]){ 0 }, (char[]){ 0 });
}

int n_tests = 0, n_succ_tests = 0;

int main(){
    test();
    printf("=== SUCCESS %d OUT OF %d TESTS ===\n", n_succ_tests , n_tests);
    return 0;
}


int check(char* name, char** input, int N, int is_diag, char *main_diag, char *second_diag, int exp_is_diag, char* exp_main_diag, char* exp_second_diag) {
    printf("\n-----------------\nTEST %d: %s\n-----------------\n", n_tests++, name);
    int success = is_diag==exp_is_diag && array_equals(main_diag, exp_main_diag, N, N) && array_equals(second_diag, exp_second_diag, N, N);
    print_matrix(input, N, N);
    puts("");
    if(!success){
        printf("Result: FAIL\n");
        printf("Actual: %s - diagonals: ", is_diag ? "IS diagonal" : "IS NOT diagonal");
        print_array(main_diag, N);
        print_array(second_diag, N);
        printf("\nExpected: %s - diagonals: ", exp_is_diag ? "IS diagonal" : "IS NOT diagonal");
        print_array(exp_main_diag, N);
        print_array(exp_second_diag, N);
    } else {
        n_succ_tests++;
        printf("Result: OK\n");
    }
    printf("\n");
    free(main_diag); free(second_diag);
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
