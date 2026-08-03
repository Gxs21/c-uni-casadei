/* dupneg.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list {
    int val;
    struct list *next;
} list;

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

    Realizzare la funzione f() che accetta come parametro numero intero `l`:
    - la funzione restituisce una lista `L` di lunghezza `l`
    - gli elementi della lista contengono valori dispari consecutivi a partire da 1 
    - Esempio, f(5) = (1, 3, 5, 7, 9)
    - NB: Si faccia riferimento ai test per ulteriori esempi, ma una funzione che supera i test non e' necessariamente corretta.

    Note generali:
    - ATTENZIONE: la propria soluzione va inserita nella porzione del sorgente inclusa tra i commenti single-line `STUDENT-SOLUTION-START` e `STUDENT-SOLUTION-END`. Codice scritto al di fuori di tali commenti non sarà considerato durante la valutazione.
    - ATTENZIONE: la soluzione verrà confrontata con quella dei colleghi mediante strumenti automatici al fine di rilevare potenziali copiature. Il controllo è resistente a rename di variabili, spezzamento di espressioni etc. Qualora vengano riscontrate similarità importanti, è possibile che la prova possa venire annullata, e che ulteriori modalità di verifica di competenze (ad es., prove orali) siano attuate.
*/

// STUDENT-SOLUTION-START
list *f(int l) {
    if (l < 1) {
        return NULL;
    }
    list *L = list_create(1, NULL);
    list *cur = L;
    for (int i = 1; i < l; i++) {
        cur->next = list_create(i * 2 + 1, NULL);
        cur = cur->next;
    }
    return L;
}
// STUDENT-SOLUTION-END

/**
 ** Non dovrebbe essere necessario modificare la parte seguente
 **/

/* Crea (mediante malloc()) e restituisce un puntatore ad un nuovo
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

list *list_clone(list *list) {
    if (list == NULL) return NULL;
    return list_create(list->val, list_clone(list->next));
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

int test_i = 1;
void test(int l, list *expect) {
    list *out = f(l);
    printf("Test %d", test_i++);
    if (list_equal(out, expect)) {
        printf(" OK: ");
    } else {
        printf(" FAIL: ");
    }
    printf("l=%d, risultato atteso=", l);
    list_print(expect);
    printf(", risultato ottenuto=");
    list_print(out);
    printf("\n");
    list_destroy(out);
    list_destroy(expect);
}

int main(void) {
    int a1[] = {1, 3, 5, 7, 9};
    int a2[] = {1};
    
    list *B1 = list_from_array(a1, sizeof(a1) / sizeof(int)),
         *B2 = list_from_array(a2, sizeof(a2) / sizeof(int));


    test(5, B1);
    test(1, B2);
    test(0, NULL);
    test(-1, NULL);
    return 0;
}
