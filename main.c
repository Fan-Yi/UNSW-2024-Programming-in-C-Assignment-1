// Program Name
// Written by Yi Fan,
// on TODAYS-DATE
// TODO: Program Description

#include <stdio.h>
#include <string.h>

// #define NDBUG
#include <assert.h>

#define ROWS 10
#define COLS 10

// TODO: You #defines go there

// Every tile on the map has to be one of the following values.
enum Base { 
    NONE,
    WALL,
    STORAGE
};

// A single tile of our board.
// box should only contain the value:
// - true (1): there exists a box here
// - false (0): there doesn't exist a box here
struct Tile {
    enum Base base;
    int box;
};

// Function Prototypes
void init_board(struct Tile board[ROWS][COLS]);
void print_line(void);
void print_title(void);
void print_board(struct Tile board[ROWS][COLS], int player_row, int player_col);

// TODO: Your function prototypes go here
inline static int row_or_col_out_of_bound(int, int);


int main(void) {
    struct Tile board[ROWS][COLS];
    init_board(board);

    // TODO: add your code (and remove this todo)
    printf("=== Level Setup ===\n");
    char ch;
    do
    {
        scanf(" %c", &ch);
        if(ch == 'w' || ch == 's' || ch == 'b')
        {
            unsigned int row, col;
            scanf("%d%d", &row, &col);
            // if((ch == 'w' || ch == 's') && row_or_col_out_of_bound(row, col))
            if(row_or_col_out_of_bound(row, col))
            {
                printf("%c %d %d\n", ch, row, col);
                printf("Location out of bounds\n");
                // prints the board with no player
                print_board(board, -1, -1);
                continue;
            }

            switch (ch)
            {
            case 'w':
                board[row][col].base = WALL;
                board[row][col].box = 0;
                break;
            case 's':
                board[row][col].base = STORAGE;
                break;
            default:
                board[row][col].base = board[row][col].base == STORAGE ?  STORAGE : NONE;
                board[row][col].box = 1;
            }

            printf("%c %d %d\n", ch, row, col);
            // prints the board with no player
            print_board(board, -1, -1);
        }
        else if(ch == 'W')
        {
            unsigned int r1, c1, r2, c2;
            scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
            assert(r1 == r2 || c1 == c2);
            if(r1 == r2)
            {
                //
                for(unsigned int c = c1; c <= c2; c++)
                {
                    if(c < 0) continue;
                    if(c >= COLS) break;
                    board[r1][c].box = 0;
                    board[r1][c].base = WALL;
                }
            }
            else // c1==c2
            {
                //
                for(unsigned int r = r1; r <= r2; r++)
                {
                    if(r < 0) continue;
                    if(r >= ROWS) break;
                    board[r][c1].box = 0;
                    board[r][c1].base = WALL;
                }
            }

            printf("%c %d %d %d %d\n", ch, r1, c1, r2, c2);
            // prints the board with no player
            print_board(board, -1, -1);
        }
        else // should be [ctrl-d]
        {
            assert(ch == '[');
            char str[1024];
            scanf("%s", str);
            assert(!strcmp(str, "ctrl-d]"));
            printf("%c%s\n", ch, str);
            break;
        }
    } while (1);

    return 0;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// YOUR FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Your function implementations go here
inline static int row_or_col_out_of_bound(int row, int col)
{
    return row < 0 || row >= ROWS || col < 0 || col >= COLS;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// PROVIDED FUNCTIONS //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// initialises the board to default values.
void init_board(struct Tile board[ROWS][COLS]) {
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
    struct Tile board[ROWS][COLS], int player_row, int player_col) {
    print_title();
    for (int i = 0; i < ROWS; i++) {
        print_line();
        for (int j = 0; j < COLS; j++) {
            printf("|");

            struct Tile curr = board[i][j];
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