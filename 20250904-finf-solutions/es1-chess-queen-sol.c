#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/* chess: constants */

#define EMPTY 0
#define PAWN 2
#define KNIGHT 4
#define BISHOP 8
#define ROOK 16
#define QUEEN 32
#define KING 64

#define WHITE 0
#define BLACK 1

#define MASK_COLOR 1
#define MASK_PIECE 254
#define MASK_ROWCOL 7
#define MASK_COL_OFFSET 3

/* chess: boards */

char **create_initial_board(); // Crea una scacchiera per una partita iniziale
char **create_board_from_fen(const char *fen);
char **create_empty_board();
void free_board(char **board); // libera la memoria associata a una scacchiera
void print_board(char **board);

/* chess: pieces */

int is_white(char piece);
int is_queen(char piece);
char get_piece(char **board, char r, char c); // ottiene il pezzo alla riga `r` e colonna `c` (rappr. esterna)

/* chess: positions */

int valid_pos_e(char r, char c); // Restituisce il booleano che indica se la posizione data in rappr. esterna è corretta
char* pos_ic_es(char c);
char pos_es_ic(char *spos);
void pos_i_es(char row, char col, char* c);
char pos_e_ic(char r, char c); // converte riga e colonna in una posizione compatta su 1 byte
void pos_ic_e(char pos, char *r, char *c); // converte una posizione in riga e colonna
#define P(p_es) pos_es_ic(p_es) // syntactic sugar for pos_es_ic
void print_pos(char c);

/* chess: moves */

char* moves_queen(char** board, char row, char col, char *num_moves); // posizioni raggiungibili da regina in una mossa
char **make_move_new_board(char **board, char from, char to); // esegue una mossa sulla scacchiera, restituendone una nuova
void make_move(char **board, char from, char to); // esegue una mossa sulla scacchiera, modificandola in-place

/* arrays */

void print_array_of_positions(char *a, int size);
void print_array(char *a, int size);
void iter_array(char *a, int size, void (*f)(char));
void print_char(char c);
void print_array(char *a, int size);
int array_equals_char(char a[], char b[], int sizea, int sizeb);

/* matrices */

char** make_matrix(int rows, int cols, int elem); // crea una matrice con valori iniziali
void free_matrix(char **a, int a_rows); // libera la memoria associata a una matrice
void print_matrix(char **a, int a_rows, int a_cols); // stampa in stdout una matrice

int ntests = 0, ntests_passed = 0; // global vars for testing

/*
Si implementi la funzione `char* moves_queen(char** board, char row, char col, char *num_moves)` che

* data una scacchiera iniziale `board` e la posizione di riga `row` e colonna `col` di una regina (QUEEN),
* restituisca in output, nel caso la posizione sia valida ed individui effettivamente una regina (bianca o nera),
  un nuovo array contenente le posizioni valide raggiungibili da tale regina **in una singola mossa**, 
  scrivendo nel parametro `num_moves` il numero di posizioni valide raggiungibili (ovvero la dimensione di tale array di output).

DETTAGLI:

- Se gli input non sono corretti (ad esempio, la posizione non è valida, o non c'è una regina in quella posizione), 
  si restituisca un array vuoto e 0 (zero) come numero di posizioni raggiungibili valide.
  Per semplicità, si può dimensionare la memoria dell'array restituito alla dimensione massima possibile (28 posizioni).

- La scacchiera è rappresentata mediante una matrice 8x8 di interi in rappresentazione 8-bit (char). 
  Se `b` è la scacchiera, `b[7][7]` rappresenta il contenuto della cella nell'angolo in alto a destra (H8),
  e b[0][0] il contenuto della cella in basso a sinistra (A1):
- La posizione matriciale [riga][colonna] della matrice (0-indexed e assunta orientata dal basso all'alto come in figura) è nota come **rappresentazione interna**.
- Il programma internamente fa uso di altre rappresentazioni. 

    A B C D E F G H
    ---------------
8 |             X   | 8
7 |                 | 7
6 |                 | 6
5 |                 | 5
4 |                 | 4
3 |                 | 3
2 |                 | 2
1 |                 | 1     
    ---------------
    A B C D E F G H

  Ad esempio, la posizione della "X" nella scacchiera mostrata sopra ha queste rappresentazioni:
    - rappr. interna: due valori 7,6 (riga e colonna, 0-indexed)
    - rappr. interna compatta: singolo valore ottale 067 (in binario, 00 110 111 = 00 <3 bit colonna> <3 bit riga>)
    - rappr. esterna: due valori 8,7 (riga e colonna, ma 1-indexed)
    - rappr. esterna stringa: stringa di due caratteri "G8" (colonna come lettera, riga come numero 1-indexed)
  Si noti che la rappr. interna compatta è è l'unica che consente di memorizzare una posizione in un singolo byte (char).
  Sono implementate funzioni per convertire tra queste rappresentazioni, ad esempio:
    - void pos_i_es(char row, char col, char* c); // converte da rappr. interna a rappr. interna stringa
    - char pos_e_ic(char r, char c); // converte da rappr. esterna a rappr. interna compatta
    - si noti la convenzione dei nomi "pos_<rappr. di partenza>_<rappr. di arrivo>" dove "i" = interna, "e" = esterna, "ic" = interna compatta, "es" = esterna stringa

- Rappresentazione del contenuto delle celle.
    * ogni cella b[r][c] ha associato un numero intero (tipo char) che ne denota il contenuto (ovvero quale pezzo è ivi localizzato)
    * Il valore EMPTY = 0 denota una cella vuota, altrimenti il contenuto sarà un valore che codificherà pezzo e colore
    * Il bit meno significativo denota se il pezzo è bianco (WHITE = 0) o nero (BLACK = 1).
    * Le tipologie di pezzi sono rappresentate da potenze di 2 crescenti (a partire da 2^1 per il pedone), come da 
      costanti simboliche definite sopra: PAWN=2, KNIGHT=4, BISHOP=8, ROOK=16, QUEEN=32, KING=64.
    * Quindi, ad esempio,    b[0][0] = ROCK | WHITE    denota il piazzamento di una torre bianca in A1 (OR bitwise tra ROCK=16 e WHITE=0)

Per chi non conoscesse gli scacchi, ecco le informazioni essenziali per questo esercizio:

- La regina (QUEEN - Q) si può muovere di un numero qualsiasi di caselle in orizzontale, verticale e diagonale;
- La regina non può saltare sopra altri pezzi (propri o avversari), dunque questi, se presenti, bloccheranno l'avanzamento. 
- I pezzi avversari possono essere "catturati": la regina occuperà il loro posto.
- Si osservi i test ("EXPECTED MOVES") per esempi di output atteso

NOTE GENERALI:
*) ATTENZIONE: la propria soluzione va inserita nella porzione del sorgente inclusa tra i commenti single-line
`// STUDENT-SOLUTION-START` e `// STUDENT-SOLUTION-END`.
Codice scritto al di fuori di tali commenti non sarà considerato durante la valutazione.
*) E' possibile definire più funzioni ausiliarie qualora lo si ritenga opportuno.
Ma lo si faccia all'interno dei commenti, come indicato nel punto precedente.
*) ATTENZIONE: la soluzione verrà confrontata con quella dei colleghi mediante strumenti automatici al fine
di rilevare potenziali copiature. Il controllo è resistente a rename di variabili, spezzamento di espressioni etc.
Qualora vengano riscontrate similarità importanti, è possibile che la prova possa venire annullata, e che ulteriori
modalità di verifica di competenze (ad es., prove orali) siano attuate.
*/

// STUDENT-SOLUTION-START
/* 
  Restituisce un array con le posizioni (rappr. interna compatta) valide raggiungibili in una singola mossa
  da una regina in posizione di riga `row` e colonna `col` (rappr. ESTERNA). 
  NOTA: si può anche allocare un array di dimensione pari al numero massimo di posizioni raggiungibili da una regina (27),
  ma si restituisca in `num_moves` solo il numero delle posizioni valide (dentro i limiti della scacchiera, con eventuale cattura di nemici). 
  NOTA: funzioni potenzialmente utili includono:
    - get_piece(b, r,c) per ottenere il pezzo in posizione [r][c] (rappr. esterna) nella scacchiera b
    - is_queen(piece) per verificare se un pezzo è una regina
    - is_white(piece) per verificare se un pezzo è bianco
    - piece(b, r,c) per ottenere la rappr. del pezzo in posizione di rappr. esterna data da riga r e colonna c nella scacchiera b
    - pos_e_ic(r, c) restituisce la rappr. interna compatta della posizione data in rappr. esterna da riga r e colonna c
    - valid_pos_e(r, c) restituisce il booleano che indica se la posizione data in rappr. esterna è valida (entro i limiti della scacchiera)
*/
char* moves_queen(char **board, char row, char col, char *num_moves) {
    char piece = get_piece(board, row, col);
    if(!is_queen(piece)) {
        *num_moves = 0;
        return (char*)malloc(0);
    }
    int enemy = is_white(piece) ? BLACK : WHITE;
    char* moves = (char*) malloc(27 * sizeof(char)); // massimo 27 posizioni per una regina
    unsigned char n = 0;
    
    for (int dir = 0; dir < 8; ++dir) { // 0 = NO, 1 = NE, 2 = SE, 3 = SO, 4 = N, 5 = E, 6 = S, 7 = O
        for (int i = 1; i < 8; ++i) {
            char r = row, c = col;
            switch (dir) {
                case 0: r += i; c -= i; break;
                case 1: r += i; c += i; break;
                case 2: r -= i; c += i; break;
                case 3: r -= i; c -= i; break;
                case 4: r += i; break;
                case 5: c += i; break;
                case 6: r -= i; break;
                case 7: c -= i; break;
            }
            if (!valid_pos_e(r, c)) break;
            char p = pos_e_ic(r, c);
            if (get_piece(board, r, c) == EMPTY) {
                moves[n++] = p;
            } else if((get_piece(board, r, c) & MASK_COLOR) == enemy) {
                moves[n++] = p;
                break;
            } else {
                break;
            }
        }
    }
    *num_moves = n;
    return moves;
}
// STUDENT-SOLUTION-END

char get_piece(char **board, char r, char c) {
    if (!valid_pos_e(r, c)) return 0;
    return board[r-1][c-1];
}

/* Converte riga e colonna in rappr. esterna (1-indexed), in una posizione interna (0-indexed) compatta su 1 byte. */
char pos_e_ic(char r, char c) {
    return (char) (((r-1) & MASK_ROWCOL) | (((c-1) & MASK_ROWCOL) << MASK_COL_OFFSET));
}

/* Converte da rappr. interna compatta a rappr. esterna delle posizioni della scacchiera */
void pos_ic_e(char pos, char *r, char *c) {
    *r = (pos & MASK_ROWCOL) + 1;
    *c = ((pos >> MASK_COL_OFFSET) & MASK_ROWCOL) + 1;
}

/* converte da rappr. esterna stringa a interna compatta */
char pos_es_ic(char *spos) {
    if(spos == NULL || spos[0] < 'A' || spos[0] > 'H' || spos[1] < '1' || spos[1] > '8') return -1;
    return pos_e_ic(spos[1]-'0', spos[0]-'A'+1);
}

/* converte da rappr. esterna a interna*/
void pos_e_i(char r, char c, char *ir, char *ic) {
    *ir = r - 1;
    *ic = c - 1;
}

/* Predicato che restituisce il Booleano indicante se il pezzo è bianco */
int is_white(char piece) {
    return (piece & 1) == WHITE;
}

/* Predicato che restituisce il Booleano indicante se il pezzo è una regina (bianca o nera) */
int is_queen(char piece) {
    return piece & QUEEN;
}

/* Predicato che restituisce il Booleano indicante se la posizione in rappr. esterna fornita è valida */
int valid_pos_e(char r, char c) { return r >= 1 && r <= 8 && c >= 1 && c <= 8; }

char **create_initial_board() {
    char **board = make_matrix(8, 8, EMPTY);
    // Setup pieces for both sides
    int piece_order[] = {ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK};
    for (int i = 0; i < 8; i++) {
        board[0][i] = piece_order[i] | BLACK;
        board[1][i] = PAWN | BLACK;
        board[6][i] = PAWN | WHITE;
        board[7][i] = piece_order[i] | WHITE;
    }
    return board;
}

char **create_empty_board() {
    return make_matrix(8, 8, EMPTY);
}

char **create_board_from_fen(const char *fen) {
    char **board = make_matrix(8, 8, EMPTY);
    int row = 0, col = 0;
    while (*fen) {
        if (*fen == '/') {
            row++;
            col = 0;
        } else if (*fen >= '1' && *fen <= '8') {
            col += *fen - '0';
        } else {
            int piece = EMPTY;
            switch (*fen) {
                case 'p': piece = PAWN | BLACK; break;
                case 'r': piece = ROOK | BLACK; break;
                case 'n': piece = KNIGHT | BLACK; break;
                case 'b': piece = BISHOP | BLACK; break;
                case 'q': piece = QUEEN | BLACK; break;
                case 'k': piece = KING | BLACK; break;
                case 'P': piece = PAWN | WHITE; break;
                case 'R': piece = ROOK | WHITE; break;
                case 'N': piece = KNIGHT | WHITE; break;
                case 'B': piece = BISHOP | WHITE; break;
                case 'Q': piece = QUEEN | WHITE; break;
                case 'K': piece = KING | WHITE; break;
            }
            board[row][col++] = piece;
        }
        fen++;
    }
    return board;
}

char** copy_board(char **board) {
    char **new_board = make_matrix(8, 8, EMPTY);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            new_board[i][j] = board[i][j];
        }
    }
    return new_board;
}

char** make_move_new_board(char **board, char from, char to) {
    char **new_board = copy_board(board);
    char from_r, from_c, to_r, to_c;
    pos_ic_e(from, &from_r, &from_c);
    pos_ic_e(to, &to_r, &to_c);
    printf("Moving from (%d,%c) to (%d,%c)\n", from_r, 'A'+from_c-1, to_r, 'A'+to_c-1);
    new_board[to_r-1][to_c-1] = new_board[from_r-1][from_c-1];
    new_board[from_r-1][from_c-1] = EMPTY;
    return new_board;
}

void make_move(char **board, char from, char to) {
    char from_r, from_c, to_r, to_c;
    pos_ic_e(from, &from_r, &from_c);
    pos_ic_e(to, &to_r, &to_c);
    board[to_r-1][to_c-1] = board[from_r-1][from_c-1];
    board[from_r-1][from_c-1] = EMPTY;
}

char **make_matrix(int rows, int cols, int elem) {
    char** m = (char **) malloc(rows * sizeof(char*));
    for(int i=0; i<rows; i++){
        m[i] = (char *) malloc(cols * sizeof(char));
        for(int j=0; j<cols; j++){
            m[i][j] = elem;
        }
    }
    return m;
}

char get_piece_char_repr(int e) {
    switch (e & 254) {
        case EMPTY: return ' '; break;
        case PAWN : return (e%2==WHITE ? 'P' : 'p'); ;
        case KNIGHT : return (e%2==WHITE ? 'N' : 'n'); ;
        case BISHOP : return (e%2==WHITE ? 'B' : 'b'); ;
        case ROOK : return (e%2==WHITE ? 'R' : 'r'); ;
        case QUEEN : return (e%2==WHITE ? 'Q' : 'q'); ;
        case KING : return (e%2==WHITE ? 'K' : 'k'); ;
        default: return '?';
    }
}

void print_board(char **board) {
    printf("\n    A B C D E F G H\n");
    printf("    ---------------\n");
    for (int i = 7; i >= 0; i--) {
        printf("%d | ", i+1);
        for (int j = 0; j < 8; j++) {
            char piece = ' ';
            int e = board[i][j];
            piece = get_piece_char_repr(e);
            printf("%c ", piece);
        }
        printf("| %d\n", i+1);
    }
    printf("    ---------------\n");
    printf("    A B C D E F G H\n");
}

int check_same_moves_set(char actual_moves[], char exp_moves[], int actual_sz, int exp_sz) {
    if(actual_sz != exp_sz) return 0;
    for(int i=0; i<exp_sz; i++) {
        int found = 0;
        for(int j=0; j<actual_sz; j++) {
            if(exp_moves[i] == actual_moves[j]) {
                found = 1;
                break;
            }
        }
        if(!found) {
            printf("Missing move: ");
            print_pos(exp_moves[i]);
            return 0;
        }
    }
    return 1;
}

void sort_moves(char *moves, int num_moves) {
    for(int i=0; i<num_moves-1; i++) {
        for(int j=i+1; j<num_moves; j++) {
            if(moves[i] > moves[j]) {
                char tmp = moves[i];
                moves[i] = moves[j];
                moves[j] = tmp;
            }
        }
    }
}

void test_moves(char** board, char piece, char pos, char *expected_moves, int num_expected_moves) {
    ntests++;
    char *s = "SUCCESS", *f = "FAILURE";
    char num_moves;
    char *moves;
    char row, col;
    pos_ic_e(pos, &row, &col);
    if(piece & QUEEN) moves = moves_queen(board, row, col, &num_moves);
    int outcome = 0;
    printf("\n%s] %c moves from ", (outcome = check_same_moves_set(moves, expected_moves, num_moves, num_expected_moves)) ? s : f, get_piece_char_repr(piece));
    print_pos(pos);
    // sort_moves(moves, num_moves);
    // sort_moves(expected_moves, num_expected_moves);
    ntests_passed += outcome;
    if(!outcome || outcome) {
        printf("\n\tACTUAL MOVES  : ");
        print_array_of_positions(moves, num_moves);
        printf("\n\tEXPECTED MOVES: ");
        print_array_of_positions(expected_moves, num_expected_moves);
        print_board(board);
        puts("");
    }
}

char get_pos_ic(char piece, char **board) {
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            if(board[i][j] == piece) return pos_e_ic(i+1, j+1);
        }
    }
    return -1;
}

void test_queen_moves(){
    printf("\n*** TESTING moves_queen ***\n");

    // constrained in the corner
    char** board0 = create_board_from_fen("8/8/8/8/8/8/6BP/6KQ");
    char expected_moves0[] = {  };
    test_moves(board0, QUEEN, get_pos_ic(QUEEN | WHITE, board0), expected_moves0, 0);

    // almost constrained in the corner
    char** board0b = create_board_from_fen("8/8/8/8/8/8/6BP/6qQ");
    char expected_moves0b[] = { P("G8") };
    test_moves(board0b, QUEEN, get_pos_ic(QUEEN | WHITE, board0b), expected_moves0b, 1);

    // queen present but wrong position
    test_moves(board0b, QUEEN, get_pos_ic(BISHOP | WHITE, board0b), (char[0]){ }, 0);


    // no queen
    char** board_e0 = create_board_from_fen("K/8/k/8/8/8/6BP/6rR");
    char expected_moves_e0[] = {  };
    test_moves(board_e0, QUEEN, get_pos_ic(QUEEN | WHITE, board_e0), expected_moves_e0, 0);

    // unconstrained from the middle
    char** board1 = create_board_from_fen("8/8/8/8/4Q3/8/8/8");
    char expected_moves1[] = {
        // mosse stile alfiere 
        P("F6"), P("G7"), P("H8"),
        P("F4"), P("G3"), P("H2"),
        P("D4"), P("C3"), P("B2"), P("A1"),
        P("D6"), P("C7"), P("B8"),
        // mosse stile torre
        P("A5"), P("B5"), P("C5"), P("D5"), P("F5"), P("G5"), P("H5"),
        P("E1"), P("E2"), P("E3"), P("E4"), P("E6"), P("E7"), P("E8")
     };
    test_moves(board1, QUEEN, get_pos_ic(QUEEN | WHITE, board1), expected_moves1, 27);

    // constrained by own and enemy pieces
    char** board2 = create_board_from_fen("8/1PrP4/2Q4K/8/4p3/p7/2R/8/8");
    char expected_moves2[] = {
        // mosse stile alfiere 
        P("B4"), P("A5"), P("D4"), P("E5") /* cattura*/, /* stop */
        // mosse stile torre
        P("A3"), P("B3"), P("D3"), P("E3"), P("F3"), P("G3"), /* stop */
        P("C2") /* cattura */, P("C4"), P("C5"), P("C6") /* stop */
    };
    test_moves(board2, QUEEN, get_pos_ic(QUEEN | WHITE, board2), expected_moves2, 14);

    char ***boards = (char**[]) { board0, board0b, board_e0, board1, board2 };
    for(int i=0; i<2; i++) free_board(boards[i]);
}

void showcase() {
    printf("\n*** SHOWCASE moves_queen ***\n");

    char** a_board = create_board_from_fen("8/8/8/8/8/8/8/6Q1");
    print_board(a_board);

    char num_moves = 0;
    char row, col, irow, icol;
    pos_ic_e(get_pos_ic(QUEEN | WHITE, a_board), &row, &col);
    char *queen_positions = moves_queen(a_board, row, col, &num_moves);
    char pos_s[3];
    pos_e_i(row, col, &irow, &icol);
    pos_i_es(row, col, pos_s);
    printf("Rappr. interna compatta: %o (octal), %d (dec)\n", get_pos_ic(QUEEN | WHITE, a_board), get_pos_ic(QUEEN | WHITE, a_board));
    printf("Rappr. interna: (%d,%d)\n", irow, icol);
    printf("Rappr. esterna: (%d,%d)\n", row, col);
    printf("Rappr. esterna stringa: %s\n", pos_s);
    printf("Queen moves from %s: ", pos_s);    // more tests

    print_array_of_positions(queen_positions, num_moves);
    puts("");
    for(int i=0; i<num_moves; i++){
        char kr, kc;
        pos_ic_e(queen_positions[i], &kr, &kc);
        char **new_board = make_move_new_board(a_board, get_pos_ic(QUEEN | WHITE, a_board), queen_positions[i]);
        print_board(new_board);
        free_board(new_board);
        puts("");
    }

    free_board(a_board);
}

/* ENTRY POINT */
int main(){
    test_queen_moves();
    printf("\n*** TESTS SUMMARY: %d/%d tests passed ***\n", ntests_passed, ntests);
    // showcase();
    puts("");
    return 0;
}

void free_board(char **board) {
    free_matrix(board, 8);
}

void free_matrix(char **a, int a_rows) { 
    if(a == NULL) return;
    for (int i = 0; i < a_rows; i++) {
        free(a[i]);
    }
    free(a);
}

void print_matrix(char **a, int a_rows, int a_cols) { 
    if(a == NULL) return;
    for (int i = 0; i < a_rows; i++) {
        printf("| ");
        for (int j = 0; j < a_cols; j++) {
            printf("%2d ", a[i][j]);
        }
        printf(" |\n");
    }
}

void iter_array(char *a, int size, void (*f)(char)) {
    int i;
    printf("[");
    for (i=0; i<size; i++) {
        f(a[i]);
        printf("%s", i<size-1 ? "," : "");
    }
    printf("]");
} 
void print_char(char c) {
    printf("%c", c);
}
void print_array(char *a, int size) {
    iter_array(a, size, print_char);
}
void print_pos(char c) {
    char row, col;
    pos_ic_e(c, &row, &col);
    printf("(%c%d)", 'A'+col-1, row);
}
char* pos_ic_es(char c) {
    char row, col;
    pos_ic_e(c, &row, &col);
    char *repr = (char*) malloc(3 * sizeof(char));
    sprintf(repr, "%c%hu", 'A'+col-1, row);
    return repr;
}
void pos_i_es(char r, char c, char *s) {
    sprintf(s, "%c%d", 'A'+c-1, r);
}
void print_array_of_positions(char *a, int size) {
    iter_array(a, size, print_pos);
}

int array_equals_char(char a[], char b[], int sizea, int sizeb) {
    if(sizea==0 && sizeb==0) return TRUE;
    if((a == NULL && b != NULL) || (b == NULL && a != NULL)) return FALSE;
    if(a == b) return FALSE; // shouldn't pass the same array
    if(sizea != sizeb) return FALSE;
    for (; sizea--;)
        if (a[sizea] != b[sizea])
            return FALSE;
    return TRUE;
}