                                                                 /* Minesweeper by Duperray Lucas and Rosselet Thomas
                                                                               V 0.17 on 03/27/24 
                                                                    Last update : 
                                                                               Adjusting revealAdjacentCells function */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BOARD_LENGTH 25

typedef struct Cell { // Structure representing cells on the board
    int isRevealed; // Indicating if the cell is revealed
    int isBomb; // Indicating if the cell contains a bomb
    int bombCount; // Count bombs around the cell
    int isFlag;
} Cell;

typedef struct Grid { // Structure representing the grid
    int x; // Width of the grid
    int y; // Height of the grid
    Cell** pCells; // Pointer to Cell
} Grid;

// Function to ask the user for an integer input within a given range
int ask(const char* prompt, int min, int max) {
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

// Function to place bombs on the board, ensuring the first chosen cell and its neighbors are non-bomb cell
void bombPlacement(Cell** board, int firstMoveX, int firstMoveY, int bombCount) {
    int numBombs = 0;
    int totalCells = BOARD_LENGTH * BOARD_LENGTH;
    int* unbombedCells = (int*)malloc(totalCells * sizeof(int));
    int count = 0;

    // Initialize the list of unbombed cells
    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            if (board[i][j].isBomb == 0) {
                unbombedCells[count] = i * BOARD_LENGTH + j;
                count++;
            }
        }
    }

    while (numBombs < (BOARD_LENGTH * BOARD_LENGTH) / 10 + 1) {
        int randomCount = rand() % count;
        int cellIndex = unbombedCells[randomCount];
        int x = cellIndex / BOARD_LENGTH;
        int y = cellIndex % BOARD_LENGTH;

        if (abs(firstMoveX - x) > 1 || abs(firstMoveY - y) > 1) { //bombCreation with absolute value
            board[x][y].isBomb = 1;
            for (int row = -1; row <= 1; row++) { //give cell a number of bomb around
                for (int col = -1; col <= 1; col++) {
                    if (x + row >= 0 && x + row < BOARD_LENGTH && y + col >= 0 && y + col < BOARD_LENGTH) {
                        board[x + row][y + col].bombCount++;
                    }
                }
            }
            numBombs++;
        }

        // Remove the bomb cell from the list of unbombed cells
        unbombedCells[randomCount] = unbombedCells[count - 1];
        count--;
    }

    free(unbombedCells);
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
            grid.pCells[i][j].bombCount = 0;
        }
    }

    return grid.pCells;
}

// Function to reveal adjacent cells
void revealAdjacentCells(Cell** board, int x, int y) {

    board[x][y].isRevealed = 1;
    
    if (board[x][y].bombCount != 0)
    {
        return;
    }
    
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i >= 0 && i < BOARD_LENGTH && j >= 0 && j < BOARD_LENGTH) {
                if (!board[i][j].isRevealed) {
                    revealAdjacentCells(board, i, j);
                }
            }
        }
    }
}

//Place flag
void flagPlacement(Cell** board, int x, int y){
    if (board[x][y].isFlag == 0){
        board[x][y].isFlag = "F";
    }
    else{
        printf("There's already a Flag Here.");
    }
}

//Set color to numbers
void colorGrid(int bombC) {
    if (bombC == 0) {
        printf("\033[1;37m %-2d \033[0m", bombC);
    }
    else if (bombC == 1) {
        printf("\033[1;34m %-2d \033[0m", bombC);
    }
    else if (bombC == 2) {
        printf("\033[1;32m %-2d \033[0m", bombC);
    }
    else {
        printf("\033[1;31m %-2d \033[0m", bombC);
    }
}

// Function to Show the current state of the board
void showBoard(Cell** board, int choiceCellX, int choiceCellY) {
    int bombCount;
    for (int i = 0; i < BOARD_LENGTH; i++) {
        printf("%-2d | ", i);
        for (int j = 0; j < BOARD_LENGTH; j++) {
            if (i == choiceCellX && j == choiceCellY) {
                if (board[i][j].isBomb) {
                    printf("\033[1;35m %-2c \033[0m", 'B');
                }
                else {
                    bombCount = board[i][j].bombCount;
                    colorGrid(bombCount);
                }
            }
            else {
                bombCount = board[i][j].bombCount;
                if (board[i][j].isRevealed) {
                    if (board[i][j].isBomb) {
                        printf("\033[1;35m %-2c \033[0m", 'B');
                    }
                    else {
                        colorGrid(bombCount);
                    }
                }
                else {
                    printf(" %-2c ", '*');
                }
            }
        }
        printf("\n");
    }
}

// Function to ask the user for coordinates of a cell to reveal
void askCoord(Cell** board, int* choiceCellX, int* choiceCellY) {
    int errorCase = 0;
    while (errorCase == 0) {
        *choiceCellX = ask("Enter X coordinate : ", 0, BOARD_LENGTH);
        *choiceCellY = ask("Enter Y coordinate : ", 0, BOARD_LENGTH);

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

void revealGrid(Cell** board) {
    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            board[i][j].isRevealed = 1;
        }
    }
}

int main() {
    srand(time(NULL)); // Seed for random number generation
    Grid grid;
    int win = 0;
    int start = 0;
    int bombCount = 0;
    int choiceCellX;
    int choiceCellY;
    Cell** board = createBoard(); // Create the game board
    askCoord(board, &choiceCellX, &choiceCellY); // Ask the user for the first cell to reveal
    bombPlacement(board, choiceCellX, choiceCellY, bombCount); // Place bombs on the board
    revealAdjacentCells(board, choiceCellX, choiceCellY); // Reveal adjacent cells to the first cell
    showBoard(board, choiceCellX, choiceCellY); // Show the board

    // Main game loop
    while (start == 0) {
        askCoord(board, &choiceCellX, &choiceCellY); // Ask the user for the next cell to reveal
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
    printf("\n");

    revealGrid(board);

    showBoard(board, choiceCellX, choiceCellY);

    if (win == 0) {
        printf("\033[1;31m \n You lose !\n\033[0m");
    }
    else {
        printf("\033[1;32m \n You win !\n\033[0m");
    }

    freeBoard(board); // Free memory allocated for the board
    return 0;
}
