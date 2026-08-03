#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_protein2rna(char* protein, char *expected);
char *protein2rna(char *protein);
char *peptite2codon(char peptide);
int put_codon_into_protein(char *protein, int i, char *rna);


/**
 * Si realizzi una funzione `protein2rna` che, data una sequenza di aminoacidi `protein`, restituisca una possibile sequenza di mRNA che la codifichi.
 * La funzione deve restituire NULL se la sequenza di aminoacidi non è valida.
 * Il carattere di terminazione della stringa `protein` deve essere tradotto nel codone di terminazione `UAA`.
 * La stringa restituita in uscita deve essere allocata dinamicamente e terminare a sua volta col carattere di terminazione `\0`.
 * È possibile ed anche consigliato sfruttare la funzione `peptite2codon` che, data una lettera dell'alfabeto degli aminoacidi, restituisce un possibile codone corrispondente.
 * 
 * Ad esempio, la sequenza di caratteri `ALICE\0` deve essere convertita in `GCUUUAAUUUGUGAAUAA\0`.
 * 
 * Si noti che la sequenza di aminoacidi `ABBA` non è valida (poiché B non è un amminoacido valido), quindi la funzione deve restituire NULL.
 *   NOTE GENERALI:
 *) ATTENZIONE: la propria soluzione va inserita nella porzione del sorgente inclusa tra i commenti single-line `// STUDENT-SOLUTION-START` e  `// STUDENT-SOLUTION-END`. Codice scritto al di fuori di tali commenti non sarà considerato durante la valutazione.
 *) E' possibile definire più funzioni ausiliarie qualora lo si ritenga opportuno. Ma lo si faccia all'interno dei commenti, come indicato nel punto precedente.
 *) ATTENZIONE: la soluzione verrà confrontata con quella dei colleghi mediante strumenti automatici al fine di rilevare potenziali copiature. Il controllo è resistente a rename di variabili, spezzamento di espressioni etc. Qualora vengano riscontrate similarità importanti, è possibile che la prova possa venire annullata, e che ulteriori modalità di verifica di competenze (ad es., prove orali) siano attuate.
 */
// STUDENT-SOLUTION-START
char *protein2rna(char *protein) {
    char *rna = malloc(((strlen(protein) + 1) * 3 + 1) * sizeof(char));
    int i = 0;
    for (; protein[i] != '\0'; i++) {
        if (!put_codon_into_protein(protein, i, rna)) {
            free(rna);
            return NULL;
        }
    }
    if (!put_codon_into_protein(protein, i++, rna)) {
        free(rna);
        return NULL;
    }
    rna[i * 3] = '\0';
    return rna;
}

int put_codon_into_protein(char *protein, int i, char *rna) {
    char *codon = peptite2codon(protein[i]);
    if (codon == NULL) {
        return 0; // failure
    }
    strcpy(rna + i * 3, codon);
    return 1; // success
}
// STUDENT-SOLUTION-END

char *peptite2codon(char peptide) {
    char *result;
    if (peptide == 'A') {
        result = "GCU";
    } else if (peptide == 'C') {
        result = "UGU";
    } else if (peptide == 'D') {
        result = "GAU";
    } else if (peptide == 'E') {
        result = "GAA";
    } else if (peptide == 'F') {
        result = "UUU";
    } else if (peptide == 'G') {
        result = "GGU";
    } else if (peptide == 'H') {
        result = "CAU";
    } else if (peptide == 'I') {
        result = "AUU";
    } else if (peptide == 'K') {
        result = "AAA";
    } else if (peptide == 'L') {
        result = "UUA";
    } else if (peptide == 'M') {
        result = "AUG";
    } else if (peptide == 'N') {
        result = "AAU";
    } else if (peptide == 'P') {
        result = "CCU";
    } else if (peptide == 'Q') {
        result = "CAA";
    } else if (peptide == 'R') {
        result = "CGU";
    } else if (peptide == 'S') {
        result = "UCU";
    } else if (peptide == 'T') {
        result = "ACU";
    } else if (peptide == 'V') {
        result = "GUU";
    } else if (peptide == 'W') {
        result = "UGG";
    } else if (peptide == 'Y') {
        result = "UAU";
    } else if (peptide == '\0') {
        result = "UAA";
    } else {
        result = NULL;
    }
    // printf("%c -> %s\n", peptide, result);
    return result;
}

int main(void) {
    int status = 0;

    status |= check_protein2rna("A", "GCUUAA");
    status |= check_protein2rna("C", "UGUUAA");
    status |= check_protein2rna("D", "GAUUAA");
    status |= check_protein2rna("E", "GAAUAA");
    status |= check_protein2rna("F", "UUUUAA");
    status |= check_protein2rna("G", "GGUUAA");
    status |= check_protein2rna("H", "CAUUAA");
    status |= check_protein2rna("I", "AUUUAA");
    status |= check_protein2rna("K", "AAAUAA");
    status |= check_protein2rna("L", "UUAUAA");
    status |= check_protein2rna("M", "AUGUAA");
    status |= check_protein2rna("N", "AAUUAA");
    status |= check_protein2rna("P", "CCUUAA");
    status |= check_protein2rna("Q", "CAAUAA");
    status |= check_protein2rna("R", "CGUUAA");
    status |= check_protein2rna("S", "UCUUAA");
    status |= check_protein2rna("T", "ACUUAA");
    status |= check_protein2rna("V", "GUUUAA");
    status |= check_protein2rna("W", "UGGUAA");
    status |= check_protein2rna("Y", "UAUUAA");
    status |= check_protein2rna("ALICE", "GCUUUAAUUUGUGAAUAA");
    status |= check_protein2rna("CARL", "UGUGCUCGUUUAUAA");
    status |= check_protein2rna("DAN", "GAUGCUAAUUAA");
    status |= check_protein2rna("EVE", "GAAGUUGAAUAA");
    status |= check_protein2rna("ACDEFGHIKLMNPQRSTVWY", "GCUUGUGAUGAAUUUGGUCAUAUUAAAUUAAUGAAUCCUCAACGUUCUACUGUUUGGUAUUAA");

    return status;
}

int check_protein2rna(char* protein, char *expected) {
    printf("Here's one possible mRNA sequence encoding the protein `%s`:\n", protein == NULL ? "NULL" : protein);
    printf("\texpected: `%s`\n", expected);
    char *actual = protein2rna(protein);
    printf("\tactual:   `%s`\n", actual == NULL ? "NULL" : actual);
    if (strcmp(expected, actual) == 0) {
        printf("\tOK!\n");
        return 0;
    } else {
        printf("\tERROR: unexpected result!\n");
        return 1;
    }
}
