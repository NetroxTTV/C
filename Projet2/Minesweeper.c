#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BOARD_LENGTH 10

typedef struct Cell { // Structure representing cells on the board
    int isRevealed; // Indicating if the cell is revealed
    int isBomb; // Indicating if the cell contains a bomb
    int bombCount; // Count bombs around the cell
} Cell;

typedef struct Grid { // Structure representing the grid
    int x; // Width of the grid
    int y; // Height of the grid
    Cell** pCells; // Pointer to Cell
} Grid;

// Function to ask the user for an integer input within a given range
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
// Function to place bombs on the board, ensuring the first chosen cell and its neighbors are non-bomb cell
void bombPlacement(Cell** board, int firstMoveX, int firstMoveY) {
    int numBombs = 0;
    while (numBombs < (BOARD_LENGTH * BOARD_LENGTH) / 10 + 1) {
        int x = rand() % BOARD_LENGTH;
        int y = rand() % BOARD_LENGTH;
        if (board[x][y].isBomb == 0) {
            if (abs(firstMoveX - x) > 1 || abs(firstMoveY - y) > 1) {// Ensure that the first chosen cell and its neighbors are not bombs
                board[x][y].isBomb = 1;
                numBombs++;
            }
        }
    }
    printf("\nThere are %d bombs!\n", numBombs);
}

// Function to create the board
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

// Function to reveal adjacent cells
void revealAdjacentCells(Cell** board, int x, int y) {
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i >= 0 && i < BOARD_LENGTH && j >= 0 && j < BOARD_LENGTH) {
                if (!board[i][j].isBomb && !board[i][j].isRevealed) {
                    board[i][j].isRevealed = 1;
                    if (countBombsAround(board, i, j) == 0) {
                        revealAdjacentCells(board, i, j);
                    }
                }
            }
        }
    }
}

// Function to count the number of bombs around a cell
int countBombsAround(Cell** board, int x, int y) {
    int bombCount = 0;

    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i >= 0 && i < BOARD_LENGTH && j >= 0 && j < BOARD_LENGTH) {
                if (board[i][j].isBomb) {
                    bombCount++;

                }
            }
        }
    }
    return bombCount;
}

// Function to Show the current state of the board
void showBoard(Cell** board, int choiceCellX, int choiceCellY) {
    int bombCount;
    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            if (i == choiceCellX && j == choiceCellY) {
                if (board[i][j].isBomb) {
                    printf(" %-1c ", 'B');
                }
                else {
                    bombCount = countBombsAround(board, i, j);
                    printf(" %-1d ", bombCount);
                }
            }
            else {
                bombCount = countBombsAround(board, i, j);
                if (board[i][j].isRevealed) {
                    if (board[i][j].isBomb) {
                        printf(" %-1c ", 'B');
                    }
                    else {
                        printf(" %-1d ", bombCount);
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

// Function to ask the user for coordinates of a cell to reveal
void ask_Coord(Cell** board, int* choiceCellX, int* choiceCellY) {
    int errorCase = 0;
    while (errorCase == 0) {
        *choiceCellX = ask_int("Enter X coordinate : ", 0, BOARD_LENGTH);
        *choiceCellY = ask_int("Enter Y coordinate : ", 0, BOARD_LENGTH);

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

// Function to check if the game is won
int checkWin(Cell** board) {// Returns 1 if all non-bomb cells have been revealed, otherwise returns 0
    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            if (!board[i][j].isBomb && !board[i][j].isRevealed) {
                return 0; // There is any unrevealed non-bomb cell
            }
        }
    }
    return 1; // All non-bomb cells have been revealed
}

// Function to free memory allocated
void freeBoard(Cell** board) {
    for (int i = 0; i < BOARD_LENGTH; i++) {
        free(board[i]);
    }
    free(board);
}

int main() {
    srand(time(NULL)); // Seed for random number generation
    Grid grid;
    int win = 0;
    int start = 0;
    int choiceCellX;
    int choiceCellY;
    Cell** board = createBoard(); // Create the game board
    ask_Coord(board, &choiceCellX, &choiceCellY); // Ask the user for the first cell to reveal
    bombPlacement(board, choiceCellX, choiceCellY); // Place bombs on the board
    revealAdjacentCells(board, choiceCellX, choiceCellY); // Reveal adjacent cells to the first cell
    showBoard(board, choiceCellX, choiceCellY); // Show the board

    // Main game loop
    while (start == 0) {
        ask_Coord(board, &choiceCellX, &choiceCellY); // Ask the user for the next cell to reveal
        if (board[choiceCellX][choiceCellY].isBomb) { // Check if the cell contains a bomb
            start = 1; // End the game if the cell is a bomb
            win = 0;
            break;
        }
        revealAdjacentCells(board, choiceCellX, choiceCellY); // Reveal adjacent cells to the chosen cell
        showBoard(board, choiceCellX, choiceCellY); // Updated board
        checkWin(board); // Check if the game is won
        if (checkWin(board) == 1) { // If all non-bomb cells are revealed, the game is won
            win = 1;
            start = 1; // End the game
        }
    }

    // Print game result
    showBoard(board, choiceCellX, choiceCellY);
    if (win == 0) {
        printf("You lose !");
    }
    else {
        printf("You win !");
    }

    freeBoard(board); // Free memory allocated for the board
    return 0;
}
