#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BOARD_LENGTH 10

typedef struct Cell { //struct of cells
    int isRevealed;
    int isBomb;
    int bombCount;
}Cell;

typedef struct Grid { //struc of grid
    int x;
    int y;
    Cell** pCells;
}Grid;

int ask_int(const char* prompt, int min, int max) {
    int value;
    char ch;


    printf("%s", prompt);


    while (1) {

        if (scanf_s("%d%c", &value, &ch, 1) == 2 && ch == '\n') {

            if (value >= min && value < max) {

                break;
            }
        }

        printf("Invalid input. Please enter a number between %d and %d.\n", min, max - 1);


        while ((ch = getchar()) != '\n') {}


        printf("%s", prompt);
    }

    return value;
}

//#TODO Better algo, uniform & no random complexity 

void bombPlacement(Cell** board) {
    int numBombs = 0;
    while (numBombs < BOARD_LENGTH) {
        int x = rand() % BOARD_LENGTH;
        int y = rand() % BOARD_LENGTH;
        if (board[x][y].isBomb == 0) {
            if (!board[x][y].isBomb) {
                board[x][y].isBomb = 1;
                numBombs++;
            }
        }

    }
    printf("\nIl y a %d bombes !\n", numBombs);
}


Cell** createBoard()
{
    Grid grid;
    grid.x = BOARD_LENGTH;
    grid.y = BOARD_LENGTH;

    grid.pCells = (Cell**)malloc(sizeof(Cell*) * grid.x);
    if (grid.pCells == NULL)
    {
        exit(1);
    }

    for (int i = 0; i < grid.x; i++) {
        grid.pCells[i] = (Cell*)malloc(sizeof(Cell) * grid.y);
        if (grid.pCells[i] == NULL)
        {
            exit(1);
        }

        for (int j = 0; j < grid.y; j++) {
            grid.pCells[i][j].isBomb = 0;
            grid.pCells[i][j].isRevealed = 0;
        }
    }

    return grid.pCells;
}

void showBoard(Cell** board, int choiceCellX, int choiceCellY) {
    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            if (i == choiceCellX && j == choiceCellY) {
                board[i][j].isRevealed = 1;
                if (board[i][j].isBomb) {
                    printf(" %-1c ", 'B');
                }
                else {
                    printf(" %-1c ", '0');
                }
            }
            else {
                if (board[i][j].isRevealed) {
                    if (board[i][j].isBomb) {
                        printf(" %-1c ", 'B');
                    }
                    else {
                        
                        if (board[i - 1][j - 1].isBomb || board[i - 1][j].isBomb || board[i - 1][j + 1].isBomb || board[i][j - 1].isBomb || board[i][j + 1].isBomb || board[i + 1][j + 1].isBomb || board[i + 1][j].isBomb || board[i + 1][j - 1].isBomb) {
                            printf(" %-1c ", '1');
                        }
                        else {
                            printf(" %-1c ", '0');
                        }
                    }
                }
                else {
                    printf(" %-1c ", '*');
                }
            }
        }
        printf("\n");
    }
}

void ask_Coord(Cell** board, int* choiceCellX, int* choiceCellY) {
    int errorCase = 0;
    while (errorCase == 0) {
        *choiceCellX = ask_int("Enter X coordinate (0-9): ", 0, BOARD_LENGTH);
        *choiceCellY = ask_int("Enter Y coordinate (0-9): ", 0, BOARD_LENGTH);

        if (*choiceCellX >= 0 && *choiceCellX < BOARD_LENGTH && *choiceCellY >= 0 && *choiceCellY < BOARD_LENGTH) {
            if (board[*choiceCellX][*choiceCellY].isRevealed == 0) {
                errorCase = 1;
            }
            else {
                printf("Please enter the coordinates of a cell that is not revealed!\n");
            }
        }
        else {
            printf("Invalid coordinate. Please enter a number between 0 and %d.\n", BOARD_LENGTH - 1);
        }
    }
}

void firstStrike() {

}

int main()
{
    srand(time(NULL));
    Grid grid;
    int start = 0;
    int choiceCellX;
    int choiceCellY;
    Cell** board = createBoard();
    ask_Coord(board, &choiceCellX, &choiceCellY);
    bombPlacement(board);
    showBoard(board, choiceCellX, choiceCellY);

    while (start == 0) {
        ask_Coord(board, &choiceCellX, &choiceCellY);
        showBoard(board, choiceCellX, choiceCellY);
        if (board[choiceCellX][choiceCellY].isRevealed == 1 && board[choiceCellX][choiceCellY].isBomb == 1) {
            start = 1;
        }
    }

    printf("Vous avez perdu !");
    return 0;
}
