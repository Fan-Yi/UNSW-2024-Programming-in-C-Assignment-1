// Program Name
// Written by YOUR-NAME (YOUR-ZID),
// on TODAYS-DATE
// TODO: Program Description

#include <stdio.h>
#include <string.h>

#define ROWS 10
#define COLS 10

// TODO: You #defines go there

// Every tile on the map has to be one of the following values.
enum base { 
    NONE,
    WALL,
    STORAGE
};

// A single tile of our board.
// box should only contain the value:
// - true (1): there exists a box here
// - false (0): there doesn't exist a box here
struct tile {
    enum base base;
    int box;
};

// Function Prototypes
void init_board(struct tile board[ROWS][COLS]);
void print_line(void);
void print_title(void);
void print_board(struct tile board[ROWS][COLS], int player_row, int player_col);

// TODO: Your function prototypes go here

int main(void) {
    struct tile board[ROWS][COLS];
    init_board(board);

    // TODO: add your code (and remove this todo)

    // prints the board with no player, you might want to delete this...
    print_board(board, -1, -1);

    return 0;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// YOUR FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Your function implementations go here

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// PROVIDED FUNCTIONS //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// initialises the board to default values.
void init_board(struct tile board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j].base = NONE;
            board[i][j].box = 0;
        }
    }
}

// Helper function for print_board().
// Prints a line the width of the sokoban board.
void print_line(void) {
    for (int i = 0; i < COLS * 4 + 1; i++) {
        printf("-");
    }
    printf("\n");
}

// Helper function for print_board().
// Prints out the title for above the sokoban board.
void print_title(void) {
    print_line();
    char *title = "S O K O B A N";
    int len = COLS * 4 + 1;
    int n_white = len - strlen(title) - 2;
    printf("|");
    for (int i = 0; i < n_white / 2; i++) {
        printf(" ");
    }
    printf("%s", title);
    for (int i = 0; i < (n_white + 1) / 2; i++) {
        printf(" ");
    }
    printf("|\n");
}

// Prints out the current state of the sokoban board.
// It will place the player on the board at position player_row, player_col.
// If player position is out of bounds, it won't place a player anywhere.
void print_board(
    struct tile board[ROWS][COLS], int player_row, int player_col) {
    print_title();
    for (int i = 0; i < ROWS; i++) {
        print_line();
        for (int j = 0; j < COLS; j++) {
            printf("|");

            struct tile curr = board[i][j];
            if (i == player_row && j == player_col) {
                printf("^_^");
            } else if (curr.base == WALL) {
                printf("===");
            } else if (curr.box && curr.base == STORAGE) {
                printf("[o]");
            } else if (curr.box) {
                printf("[ ]");
            } else if (curr.base == STORAGE) {
                printf(" o ");
            } else {
                printf("   ");
            }
        }
        printf("|\n");
    }
    print_line();
    printf("\n");
}
