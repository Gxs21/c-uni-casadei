#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * Si realizzi una funzione che converta un numero intero `x` in una stringa contenente la rappresentazione esadecimale del numero stesso, usando solo lettere minuscole.
 * 
 * La funzione si occupa di allocare la *minima* quantità di memoria necessaria per contenere la stringa risultato.
 * Si ricorda che detta quantità di byte ammonta al logaritmo intero in base 16 di `x`, maggiorato di 1 nel caso in cui il logaritmo sia 0, più 1 byte per il terminatore `\0`. 
 * 
 * Ad esempio `int2hex(987)` deve restituire la stringa `"3db"` (che, si ricorda, occupa 4 byte: 3 per i caratteri visibili e 1 per il terminatore `\0`).
 * 
 * È possibile, ed anche consigliato, sfruttare la funzione hex() fornita, che restituisce il carattere esadecimane corrispondente alla cifra passata come parametro.
 * 
 * È consigliato creare altre funzioni d'appoggio come ad esempio log16() che calcola il logaritmo intero in base 16 di un numero intero.
 * 
 * NOTE GENERALI:
 * - ATTENZIONE: la propria soluzione va inserita nella porzione del sorgente inclusa tra i commenti single-line `// STUDENT-SOLUTION-START` e  `// STUDENT-SOLUTION-END`. Codice scritto al di fuori di tali commenti non sarà considerato durante la valutazione.
 * - E' possibile definire più funzioni ausiliarie qualora lo si ritenga opportuno. Ma lo si faccia all'interno dei commenti, come indicato nel punto precedente.
 * - ATTENZIONE: la soluzione verrà confrontata con quella dei colleghi mediante strumenti automatici al fine di rilevare potenziali copiature. Il controllo è resistente a rename di variabili, spezzamento di espressioni etc. Qualora vengano riscontrate similarità importanti, è possibile che la prova possa venire annullata, e che ulteriori modalità di verifica di competenze (ad es., prove orali) siano attuate.
*/
char *int2hex(int x);

/**
 * Restituisce la cifra esadecimale corrispondente alla cifra decimale `digit` fornita in ingresso.
 * Il carattere restituito è sempre minuscolo.
 * La tabella di conversione è la seguente:
 * 0 -> '0'
 * 1 -> '1'
 * ...
 * 9 -> '9'
 * 10 -> 'a'
 * 11 -> 'b'
 * 12 -> 'c'
 * 13 -> 'd'
 * 14 -> 'e'
 * 15 -> 'f'
 */
char hex(int digit);

/**
 * Calcola il logaritmo intero in base 16 di `x`. 
 */
int log16(int x);

// STUDENT-SOLUTION-START
char *int2hex(int x) {
    int bit = log16(x);
    char *result = (char*)(malloc(sizeof(char)*bit+2));
    int *rest=(int*)(malloc(sizeof(int)*bit));
    int new_x=x;
    for (int i=1; i<bit; i++){
        
        rest[bit-i]=new_x%16;
        new_x=new_x/16;
        result[bit-i]= hex(rest[i]);
    }
    result[bit+1]='\0';
    return result;
}
// STUDENT-SOLUTION-END

char hex(int digit) {
    digit = digit % 16;
    if (digit < 10) {
        return '0' + digit;
    } else {
        return 'a' + digit - 10;
    }
}

int main(void) {
    char expected[10];
    int statusCode = 0;
    
    for (int i = 1000; i >= 0; i--) {
        char *actual = int2hex(i);
        sprintf(expected, "%x", i);
        printf("hex(%u). Expected: %s\n", i, expected);
        printf("           Actual: %s\n", actual);
        if (strcmp(expected, actual) != 0) {
            printf("    ERROR: the two strings do not match!\n");
            statusCode = 1;
        } else {
            printf("    OK!\n");
        }
        free(actual);
    }

    return statusCode;
}
