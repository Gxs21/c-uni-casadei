#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/**
 * Si realizzi una funzione `hex_to_long` che, data in ingresso una stringa reppresentante
 * un numero esadecimale con segno (senza prefisso "0x"), ne produca una conversione in long.
 * In particolare, la funzione restituisce un puntatore al valore di tipo long ottenuto 
 * interpretando la stringa in ingresso come valore esadecimale, oppure NULL nel caso in cui 
 * detta conversione non sia possibile.
 * 
 * La funzione deve prendere in considerazione il segno, accettando stringhe che inizino 
 * col prefisso "-". Non è previsto alcun prefisso per i numeri positivi.
 * Quanto al segno, il numero 0 viene trattato come un numero positivo.
 * La funzione si occupa di alloacare la *minima* quantità di memoria necessaria a 
 * rappresentare il long in uscita (cioè, non va allocata memoria nel caso in cui la 
 * conversione non sia possibile).
 * La funzione considera la cifre esadecimali maiuscole uguali alle minuscole, quindi:
 * - A == a == 10
 * - B == b == 11
 * - C == c == 12
 * - D == d == 13
 * - E == e == 14
 * - F == f == 15
 * 
 * Si considera la stringa in ingresso NON-convertibile in long quando si verifica una qualsiasi delle seguenti condizioni:
 * - la stringa è vuota, oppure non contiene cifre esadecimali
 * - la stringa contiene un qualunque carattere diverso da '-', '0', '1', '2', '3', '4', '5', '7', '8', '9', 
 *   'A', 'B', 'C', 'D', 'E', 'F', 'a', 'b', 'c', 'd', 'e', 'f'
 * - il numero rappresentato sfora il range dei long ammissibili: [LONG_MIN, LONG_MAX]
 * 
 * Ad esempio:
 * - la stringa "12A" deve esser convertita nel long 0x12AL (il cui valore decimale è 298 = 1*16^2 + 2*16 + 10)
 *      (viene allocato spazio per 1 long)
 * - la stringa "-12A" deve esser convertita nel long -0x12AL (il cui valore decimale è -298 = -1*16^2 - 2*16 - 10)
 *      (viene allocato spazio per 1 long)
 * - la stringa "-12X" non può esser convertita in long a causa del carattere 'X', motivo per cui la funzione restituisce NULL
 *      (NON viene allocato alcuno spazio)
 * Si faccia riferimento alla funzione main per altri esempi.
 * 
 * Suggerimenti e vincoli:
 * - è vietato usare la funzione di libreria `atoi`, e qualunque variante di `sscanf` 
 * 
 * - è possibile usare altre funzioni di libreria, ad esempio `strlen`
 * 
 * - la propria soluzione va inserita nella porzione del sorgente inclusa tra i commenti single-line
 *   `// STUDENT-SOLUTION-START` e  `// STUDENT-SOLUTION-END`.
 *   Codice scritto al di fuori di tali commenti non sarà considerato durante la valutazione.
 * 
 * - è possibile ed anche consigliato avvantaggiarsi con l'impiego delle funzioni `long_sum_overflow` e `long_mult_overflow` definite sotto
 * 
 * - è possibile ed anche consigliato realizzare funzioni ausiliarie, purche comprese tra la coppia di commenti suddetti
 * 
 * - ATTENZIONE: la soluzione verrà confrontata con quella dei colleghi mediante strumenti automatici al fine 
 *   di rilevare potenziali copiature. Il controllo è resistente a rename di variabili, spezzamento di espressioni etc.
 *   Qualora vengano riscontrate similarità importanti, è possibile che la prova possa venire annullata, e che ulteriori
 *   modalità di verifica di competenze (ad es., prove orali) siano attuate. 
 */
long *hex_to_long(char *hex);

/**
 * (Funzione NON da realizzare, ma da usare se lo si ritiene utile/necessario. Codice fornito sotto.)
 * Somma due numeri interi di tipo long (a e b), disponendo il risultato nella cella di memoria puntata da result.
 * Restituisce 1 (vero) se l'operazione è andata a buon fine, oppure 0 (falso) se l'operazione ha sforato i limiti dei long (overflow od underflow).
 */
int long_sum_overflow(long a, long b, long* result);

/**
 * (Funzione NON da realizzare, ma da usare se lo si ritiene utile/necessario. Codice fornito sotto.)
 * Moltiplica due numeri interi di tipo long (a e b), disponendo il risultato nella cella di memoria puntata da result.
 * Restituisce 1 (vero) se l'operazione è andata a buon fine, oppure 0 (falso) se l'operazione ha sforato i limiti dei long (overflow od underflow).
 */
int long_mult_overflow(long a, long b, long* result);


int test_hex_to_long(char *hex, long *expected);

/**
 * Restituisce 16^x, oppure -1 se il risultato sfora il limite dei long
 */
long pow16(long x);


// STUDENT-SOLUTION-START
long *hex_to_long(char *hex) {
    if (hex[0] == '\0') return NULL; 
    long sign = hex[0] == '-' ? -1L : 1L;
    if (sign < 0L) hex++;
    long length = (long) strlen(hex);
    if (length == 0L) return NULL;
    long result = 0L;
    for (long i = 0L; i < length; i++) {
        char hexDigit = hex[i];
        long hexDigitValue;
        if (hexDigit >= '0' && hexDigit <= '9') {
            hexDigitValue = hexDigit - '0';
        } else if (hexDigit >= 'a' && hexDigit <= 'f') {
            hexDigitValue = hexDigit - 'a' + 10;
        } else if (hexDigit >= 'A' && hexDigit <= 'F') {
            hexDigitValue = hexDigit - 'A' + 10;
        } else {
            return NULL;
        }
        long base = pow16(length - 1L - i);
        if (base < 0) {
            return NULL;
        }
        long delta;
        if (!long_mult_overflow(hexDigitValue, base, &delta)) {
            return NULL;
        }
        delta *= sign;
        if (!long_sum_overflow(result, delta, &result)) {
            return NULL;
        }
    }
    long *result_ptr = (long *) malloc(sizeof(long));
    *result_ptr = result;
    return result_ptr;
}
// STUDENT-SOLUTION-END

long pow16(long x) {
    long shifts = 4L * x;
    if (shifts >= sizeof(long) * 8L) {
        return -1;
    }
    return 1L << shifts;
}

int long_sum_overflow(long a, long b, long* result) {
    *result = a + b;
    if (a > 0 && b > 0 && *result < 0) return 0;
    if (a < 0 && b < 0 && *result > 0) return 0;
    return 1;
}

int long_mult_overflow(long a, long b, long* result) {
    *result = a * b;
    if (((a >= 0) == (b >= 0)) && *result < 0) return 0;
    if (((a >= 0) != (b >= 0)) && *result > 0) return 0;
    return 1;
}

int main() {
    int status = 0;
    long expected;

    expected = 0L;
    status |= test_hex_to_long("0", &expected);

    expected = 1L;
    status |= test_hex_to_long("1", &expected);

    expected = -2L;
    status |= test_hex_to_long("-2", &expected);

    expected = 0xAL;
    status |= test_hex_to_long("a", &expected);

    expected = -0xBL;
    status |= test_hex_to_long("-B", &expected);

    expected = 0xC3L;
    status |= test_hex_to_long("C3", &expected);

    expected = -0xF4L;
    status |= test_hex_to_long("-F4", &expected);

    expected = 0xABCDEFL;
    status |= test_hex_to_long("ABCDEF", &expected);

    expected = -0xFEDCBAL;
    status |= test_hex_to_long("-fedcba", &expected);

    expected = 0x7FFFFFFFFFFFFFFFL;
    status |= test_hex_to_long("7FFFFFFFFFFFFFFF", &expected);

    status |= test_hex_to_long("", NULL);

    status |= test_hex_to_long("-", NULL);

    status |= test_hex_to_long("not a number", NULL);

    status |= test_hex_to_long("8000000000000000", NULL);

    status |= test_hex_to_long("10000000000000000", NULL);

    status |= test_hex_to_long("-FFFFFFFFFFFFFFFF", NULL);

    return status;
}


int test_hex_to_long(char *hex, long *expected) {
    printf("Parsing string `%s` as an hexadecimal number:\n", hex);
    if (expected == NULL) {
        printf("\texpected: NULL\n");
    } else if (*expected >= 0) {
        printf("\texpected: `%ld` (0x%lX)\n", *expected, *expected);
    } else {
        printf("\texpected: `%ld` (-0x%lX)\n", *expected, -*expected);
    }
    long *actual = hex_to_long(hex);
    if (actual == NULL) {
        printf("\t  actual: NULL\n");
    } else if (*actual >= 0) {
        printf("\t  actual: `%ld` (0x%lX)\n", *actual, *actual);
    } else {
        printf("\t  actual: `%ld` (-0x%lX)\n", *actual, -*actual);
    }
    if ((expected == NULL && actual == NULL) || (expected != NULL && actual != NULL && *expected == *actual)) {
        printf("\tOK!\n");
        return 0;
    } else {
        printf("\tERROR: unexpected result!\n");
        return 1;
    }
}
