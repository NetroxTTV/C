#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int BOARD_LENGTH = 10;

typedef struct Cell {
    int isUncover;
    int isBomb;
    int isFlag;
}Cell;

typedef struct Grid {
    int sizeX;
    int sizeY;
}Grid;

char** tableau() { // creating the board
    Grid grid;
    char** table = (char**)malloc(sizeof(char*) * BOARD_LENGTH);
    
    grid.sizeX = BOARD_LENGTH;
    grid.sizeY = BOARD_LENGTH;

    for (int i = 0; i < grid.sizeX; i++) { // creating row
        table[i] = (char*)malloc(sizeof(char) * BOARD_LENGTH);
        for (int j = 0; j < grid.sizeY; j++) { // creating column
            table[i][j] = '*';
        }
    }
    return table;
}

void show_tableau(char** tableau) { // show the board
    Grid grid;

    grid.sizeX = BOARD_LENGTH;
    grid.sizeY = BOARD_LENGTH;
    for (int i = 0; i < grid.sizeX; i++) {
        for (int j = 0; j < grid.sizeY; j++) {
            printf("%c ", tableau[i][j]); // print *
        }
        printf("\n"); // go back to line for each row
    }
}

void bomb_placement(char** tableau){
    for (int i = 0; i < BOARD_LENGTH; i++) {
        srand(time(NULL)); // generate random seed  
        int bomb_x = rand() % BOARD_LENGTH + 0;
        int bomb_y = rand() % BOARD_LENGTH + 0; 
        if (tableau[bomb_x][bomb_y] != 'B'){
            tableau[bomb_x][bomb_y] = 'B';
        }
    }
}


void detect_bomb(){
    
}

int main() {
    char** tf = tableau();
    bomb_placement(tf);
    show_tableau(tf);


    for (int i = 0; i < BOARD_LENGTH; i++) {
        free(tf[i]); // free memory for each list cause tf[i] -> list[list[str]]
    }
    free(tf); // free tf memory cause tf -> list[]

    return 0;
}



