/* dupneg.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list {
    int val;
    struct list *next;
} list;

list *f(list *L);
list *g(list *L, int increasing);
void test(list *input, list *expected);

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

    Realizzare la funzione f() che accetta come parametro una lista L di interi:

    - la funzione restituisce una NUOVA lista L' che contiene una copia degli elementi di L;

    - inoltre, vanno inseriti elementi per indicare il passaggio da una progressione crescente 
        ad una decrescente (elemento `-1`) e viceversa (elemento `+1`).

    Si consideri le seguenti corrispondenze di input e output:
    
    * Input: L = (0, 1, 9). Output: L' = (0, 1, 9).
        Qui, nessun elemento viene inserito, perché la lista L è monotona crescente.
    * Input: L = (4, 7, 5). Output: L' = (4, 7, -1, 5)
        Qui, viene inserito l'elemento -1 per indicare il passaggio dalla progressione crescente [4,7]
        alla progressione decrescente [7,5].
    * Input: L = (7, 4, 5). Output: L' = (7, 5, 1, 5)
        Qui, viene inserito l'elemento +1 per indicare il passaggio dalla progressione decrescente [7,4]
        alla progressione crescente [4,5].
    * Input: L = (7, 4, 2, 4, 7, 9, 8, 6). Output: L' = (7, 4, 2, 1, 4, 7, 9, -1, 8, 6)

    Consiglio: si definisca funzione ausiliaria che accetti come ulteriore parametro l'indicazione 
    della crescenza/decrescenza dei numeri.

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
list *f(list *L) {
    if (L == NULL) {
        return L;
    } else if (L->next == NULL) {
        return list_create(L->val, NULL);
    } else {
        return g(L, L->val == L->next->val ? 0 : (L->val > L->next->val ? -1 : 1));
    }
}

list *g(list *L, int increasing) {
    if (L == NULL) {
        return L;
    } else if (L->next == NULL) {
        return list_create(L->val, NULL);
    } else {
        if (increasing>0 && L->val > L->next->val) {
            return list_create(L->val, list_create(-1, g(L->next, -increasing)));
        } else if (increasing<0 && L->val < L->next->val) {
            return list_create(L->val, list_create(+1, g(L->next, -increasing)));
        } else {
            return list_create(L->val, 
                g(L->next, increasing==0 ? (L->val == L->next->val ? 0 : (L->val > L->next->val ? -1 : 1)) : increasing));
        }
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

void test(list *input, list *expected) {
    list *out = f(input);
    printf("---------\nInput: ");
    list_print(input);
    printf("\nOutput: ");
    list_print(out);
    printf("\nRisultato atteso: ");
    list_print(expected);
    printf("\n");
    if (list_equal(out, expected)) {
        printf("Test OK\n");
    } else {
        printf("Test fallito\n");
    }
    list_destroy(out);
}

int main(void) {
    test(list_from_array((int[]) {  }, 0), list_from_array((int[]) { }, 0));
    test(list_from_array((int[]) { 77 }, 1), list_from_array((int[]) { 77 }, 1));
    test(list_from_array((int[]) { 0, 1, 9 }, 3), list_from_array((int[]) { 0, 1, 9 }, 3));
    test(list_from_array((int[]) { 4, 7, 5 }, 3), list_from_array((int[]) { 4, 7, -1, 5 }, 4));
    test(list_from_array((int[]) { 4, 4, 7, 5 }, 4), list_from_array((int[]) { 4, 4, 7, -1, 5 }, 5));
    test(list_from_array((int[]) { 7, 4, 5 }, 3), list_from_array((int[]) { 7, 4, 1, 5 }, 4));
    test(list_from_array((int[]) { 7, 7, 4, 5 }, 4), list_from_array((int[]) { 7, 7, 4, 1, 5 }, 5));
    test(list_from_array((int[]) { 0, 1, 9 }, 3), list_from_array((int[]) { 0, 1, 9 }, 3));
    test(list_from_array((int[]) { 7, 4, 2, 4, 7, 9, 8, 6 }, 8), 
         list_from_array((int[]) { 7, 4, 2, 1, 4, 7, 9, -1, 8, 6 }, 10));
    return 0;
}
