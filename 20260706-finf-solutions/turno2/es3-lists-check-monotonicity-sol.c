/* monotone.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list {
    int val;
    struct list *next;
} list;

int f(list *L);
void test(list *input, int expected);

/* Questi funzioni sono gia' definite, quindi e' possibile usarle direttamente */
list *list_create(int val, list *t);
int list_length(list *L);
void list_destroy(list *L);
void list_print(list *L);
int is_empty(list *L);
int list_equal(list *L1, list *L2);
list *list_from_array(int v[], int n);

/*
    FUNZIONE DA REALIZZARE
    ======================

    Realizzare la funzione f() che accetta come parametro una lista L di interi
    e restituisce:

    - -1 se la lista e' una progressione monotona non crescente;

    - +1 se la lista e' una progressione monotona non decrescente;

    - 0 altrimenti.

    Una lista vuota, una lista con un solo elemento, e una lista con tutti elementi uguali
    sono considerate monotone non decrescenti, quindi la funzione deve restituire +1.

    Si considerino le seguenti corrispondenze di input e output:
    
    * Input: L = (0, 1, 9). Output: +1.
        La lista L e' monotona non decrescente.
    * Input: L = (9, 1, 0). Output: -1.
        La lista L e' monotona non crescente.
    * Input: L = (4, 7, 5). Output: 0.
        La lista L prima cresce e poi decresce.
    * Input: L = (7, 4, 5). Output: 0.
        La lista L prima decresce e poi cresce.

    NB: una funzione che supera i test non e' necessariamente corretta.

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
int f(list *L) {
    int non_crescente = 1;
    int non_decrescente = 1;

    while (L != NULL && L->next != NULL) {
        if (L->val < L->next->val) {
            non_crescente = 0;
        } else if (L->val > L->next->val) {
            non_decrescente = 0;
        }
        L = L->next;
    }

    if (non_decrescente) {
        return +1;
    } else if (non_crescente) {
        return -1;
    } else {
        return 0;
    }
}
// STUDENT-SOLUTION-END

/**
 ** Non dovrebbe essere necessario modificare la parte seguente
 **/

/* Crea (mediante malloc() ) e restituisce un puntatore ad un nuovo
   nodo di una lista; il nodo contiene il valore v e punta a t come
   elemento successivo. Il chiamante e' responsabile per deallocare
   mediante free() o simili il blocco di memoria restituita da questa
   funzione, quando non piu' utilizzata */
list *list_create(int val, list *t) {
    list *r = (list *)malloc(sizeof(list));
    r->val = val;
    r->next = t;
    return r;
}

/* Restituisce la lunghezza (numero di nodi) della lista L; se L e' la
   lista vuota, restituisce 0 */
int list_length(list *L) {
    if (NULL == L) {
        return 0;
    } else {
        return (1 + list_length(L->next));
    }
}

/* Libera la memoria occupata da tutti i nodi della lista L */
void list_destroy(list *L) {
    if (L != NULL) {
        list_destroy(L->next);
        L->next = NULL; /* non necessario... */
        free(L);
    }
}

/* Stampa i valori contenuti nei nodi di L; si puo' avere L == NULL. */
void list_print(list *L) {
    printf("(");
    while (L != NULL) {
        printf("%d", L->val);
        if (L->next != NULL) {
            printf(" ");
        }
        L = L->next;
    }
    printf(")");
}

/* Restituisce 1 se e solo se L e' la lista vuota, 0 altrimenti */
int is_empty(list *L) { return (L == NULL); }

/* Restituisce 1 sse L1 e L2 contengono gli stessi valori */
int list_equal(list *L1, list *L2) {
    if (L1 == NULL || L2 == NULL) {
        return (L1 == NULL && L2 == NULL);
    } else {
        return (L1->val == L2->val && list_equal(L1->next, L2->next));
    }
}

/* Restituisce una lista con n nodi, in cui il nodo i-esimo contiene
   il valore v[i] (il nodo 0 è il primo nodo della lista). */
list *list_from_array(int v[], int n) {
    if (n > 0) {
        return list_create(v[0], list_from_array(v + 1, n - 1));
    } else {
        return NULL;
    }
}

int tests = 0, tests_success = 0;

void test(list *input, int expected) {
    int out = f(input);
    printf("---------\nInput: ");
    list_print(input);
    printf("\nOutput: %d", out);
    printf("\nRisultato atteso: %d", expected);
    printf("\n");
    if (out == expected) {
        printf("Test OK\n");
        tests_success++;
    } else {
        printf("Test fallito\n");
    }
    tests++;
    list_destroy(input);
}

int main(void) {
    test(NULL, +1);
    test(list_from_array((int[]) { 77 }, 1), +1);
    test(list_from_array((int[]) { 4, 4, 4 }, 3), +1);
    test(list_from_array((int[]) { 0, 1, 9 }, 3), +1);
    test(list_from_array((int[]) { 4, 4, 7, 7 }, 4), +1);
    test(list_from_array((int[]) { 9, 1, 0 }, 3), -1);
    test(list_from_array((int[]) { 7, 7, 4, 4 }, 4), -1);
    test(list_from_array((int[]) { 4, 7, 5 }, 3), 0);
    test(list_from_array((int[]) { 7, 4, 5 }, 3), 0);
    test(list_from_array((int[]) { 7, 4, 2, 4, 7, 9, 8, 6 }, 8), 0);
    printf("\n---\nTotal tests: %d, Success: %d, Failed: %d\n", tests, tests_success, tests - tests_success);
    return 0;
}
