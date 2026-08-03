#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Si realizzi una funzione `int_to_string` che, dato in ingresso un numero intero
 * ne produca una rappresentazione del valore in base 10 sotto forma di stringa.
 * La funzione deve prendere in considerazione il segno, rappresentando in uscita i numeri
 * negativi col prefisso "-". Non è previsto alcun prefisso per i numeri positivi.
 * Quanto al segno, il numero 0 viene trattato come un numero positivo.
 * La funzione si occupa di alloacare la *minima* quantità di memoria necessaria a 
 * rappresentare la stringa in uscita
 * 
 * Ad esempio:
 * - il numero decimale 123 dovrebbe essere sappresentato dalla stringa "123" 
 *      (viene allocato spazio per 4 caratteri)
 * - il numero decimale -1 dovrebbe essere rappesentato come "-1"
 *      (viene allocato spazio per 3 caratteri)
 * - il numero esadecimale 0xA dovrebbe essere rappresentato come "10"
 *      (viene allocato spazio per 3 caratteri)
 * - il numero ottale 010 dovrebbe essere rappresentato come "8"
 *      (viene allocato spazio per 2 caratteri)
 * - il numero binario 0b11 dovrebbe essere rappresentato come "3"
 *      (viene allocato spazio per 2 caratteri)
 * Si faccia riferimento alla funzione main per altri esempi.
 * 
 * Suggerimenti e vincoli:
 * - è vietato usare la funzione di libreria `itoa`
 * - è possibile usare altre funzioni di libreria
 * - la propria soluzione va inserita nella porzione del sorgente inclusa tra i commenti single-line
 *   `// STUDENT-SOLUTION-START` e  `// STUDENT-SOLUTION-END`.
 *   Codice scritto al di fuori di tali commenti non sarà considerato durante la valutazione.
 * - è possibile ed anche consigliato realizzare funzioni ausiliarie, purche comprese tra 
 *   la coppia di commenti suddetti
 * - ATTENZIONE: la soluzione verrà confrontata con quella dei colleghi mediante strumenti automatici al fine 
 *   di rilevare potenziali copiature. Il controllo è resistente a rename di variabili, spezzamento di espressioni etc.
 *   Qualora vengano riscontrate similarità importanti, è possibile che la prova possa venire annullata, e che ulteriori
 *   modalità di verifica di competenze (ad es., prove orali) siano attuate. 
 */
char *int_to_string(int number);
int count_decimal_digits(int number);
int test_int_to_string(int number, char *representation);


// STUDENT-SOLUTION-START
int count_decimal_digits(int number) {
    int count = 0;
    while (number > 0) {
        count++;
        number /= 10;
    }
    return count == 0 ? 1 : count;
}

char *int_to_string(int number) {
    int negative = 0;
    if (number < 0) {
        negative = 1;
        number = -number;
    }
    int digits = count_decimal_digits(number);
    int length = 1 + negative + digits;
    char *result = (char *) malloc(length * sizeof(char));
    int i = length - 1;
    result[i--] = '\0';
    if (number == 0) {
        result[0] = '0';
    }
    for (; number > 0; i--) {
        result[i] = '0' + (number % 10);
        number /= 10;
    }
    if (negative) {
        result[0] = '-';
    }
    return result;
}
// STUDENT-SOLUTION-END

int main() {
    int status = 0;

    status |= test_int_to_string(0, "0");
    status |= test_int_to_string(1234567890, "1234567890");
    status |= test_int_to_string(-1234567890, "-1234567890");
    status |= test_int_to_string(-1, "-1");
    status |= test_int_to_string(0xff, "255");
    status |= test_int_to_string(-017, "-15");
    status |= test_int_to_string(-0b111, "-7");

    return status;
}


int test_int_to_string(int number, char *representation) {
    printf("Representing number `%d`:\n", number);
    printf("\texpected: `%s`\n", representation);
    char *actual = int_to_string(number);
    printf("\tactual:   `%s`\n", actual == NULL ? "NULL" : actual);
    if (strcmp(representation, actual) == 0) {
        printf("\tOK!\n");
        return 0;
    } else {
        printf("\tERROR: unexpected result!\n");
        return 1;
    }
}
