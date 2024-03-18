#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BOARD_LENGTH 10

typedef struct Cell { //struct of cells
    int isRevealed;
    int isBomb;
    int isFlag;
}Cell;

typedef struct Grid { //struc of grid
    int x;
    int y;
    Cell** pCells;
}Grid;

int ask_int(const char* prompt, int min, int max) {
    int value;
    char ch;

    // Print the prompt message
    printf("%s", prompt);

    // Loop until a valid integer within the valid range is entered
    while (1) {
        // Attempt to read an integer from input
        if (scanf_s("%d%c", &value, &ch, 1) == 2 && ch == '\n') {
            // Check if the input is within the valid range
            if (value >= min && value < max) {
                // If the input is a valid integer within the valid range, break out of the loop
                break;
            }
        }
        // If the input is not a valid integer or not within the valid range, print an error message
        printf("Invalid input. Please enter a number between %d and %d.\n", min, max - 1);

        // Consume the invalid input
        while ((ch = getchar()) != '\n' && ch != EOF) {}

        // Print the prompt message again
        printf("%s", prompt);
    }

    return value;
}

void bombPlacement(Cell** board) {
    int numBombs = 0;
    while (numBombs < BOARD_LENGTH) {
        srand(time(NULL));
        int x = rand() % BOARD_LENGTH;
        int y = rand() % BOARD_LENGTH;
        if (!board[x][y].isBomb) {
            board[x][y].isBomb = 1;
            numBombs++;
        }
    }
    printf("\n%d\n", numBombs);
}


Cell** createBoard()
{
    //#TODO function
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
            grid.pCells[i][j].isFlag = 0;
        }
    }

    return grid.pCells;
}


void showBoard(Cell** board, int choiceCellX, int choiceCellY) {
    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            if (i == choiceCellX && j == choiceCellY) {
                // Reveal the selected cell
                board[i][j].isRevealed = 1;
                if (board[i][j].isBomb) {
                    printf(" %-5c ",'B');
                } else {
                    printf(" %-5c ",'.');
                }
            } else {
                if (board[i][j].isRevealed) {
                    if (board[i][j].isBomb) {
                        printf(" %-5c ",'B');
                    } else {
                        printf(" %-5c ",'.');
                    }
                } else {
                    printf(" %-5c ", '*');
                }
            }
        }
        printf("\n");
    }
}



int main()
{

    Grid grid;
    int start = 0;
    int choiceCellX;
    int choiceCellY;
    Cell** board = createBoard();
    bombPlacement(board);
    showBoard(board, choiceCellX, choiceCellY);

    while(start == 0){
            printf("Pendant");
        int errorCase = 0;
        while(errorCase == 0){
                choiceCellX = ask_int("Enter X coordinate (0-9): ", 0, BOARD_LENGTH);
                choiceCellY = ask_int("Enter Y coordinate (0-9): ", 0, BOARD_LENGTH);

            if (choiceCellX >= 0 && choiceCellX < BOARD_LENGTH && choiceCellY >= 0 && choiceCellY < BOARD_LENGTH) {
                errorCase = 1;
            }else {
                // If the input is not a valid coordinate, print an error message
                printf("Invalid coordinate. Please enter a number between 0 and %d.\n", BOARD_LENGTH - 1);
            }
        }
        showBoard(board, choiceCellX, choiceCellY);
    }


    return 0;
}
