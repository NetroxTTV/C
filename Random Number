#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int round = 0;

int ask_int(const char* prompt) {
    int value;
    char newline;
    while (1) {
        printf("%s", prompt);
        if (scanf_s("%d%c", &value, &newline) == 2 && newline == '\n') {
            break;
        }
        else {
            printf("Enter a valid number !\n");
            while (getchar() != '\n');
        }
    }
    return value;
}

int ask_int_range(const char* prompt, int min_val, int max_val) {
    while (1) {
        int value = ask_int(prompt);
        if (min_val <= value && value <= max_val) {
            return value;
        }
        else {
            printf("Enter a number between %d and %d inclusive!\n", min_val, max_val);
        }
    }
}

char ask_char(const char* prompt, char list[]) {
    char value;
    int i;
    while (1) {
        printf("%s", prompt);
        scanf_s("%c", &value);
        
        for (i = 0; list[i] != '\0'; i++) {
            if (value == list[i]) {
                return value;
            }
        }
    }
    printf("Enter a valid answer !");
}

int restart() {
    char list[] = { 'y', 'Y', 'n', 'N' }; // list of valid answers for the restart
    char choice; // answer for the restart

    printf("\nDo you want to restart the game? (y/n): ");
    choice = ask_char("", list);

    if (choice == 'y' || choice == 'Y') {
        return 1; // return true to indicate game restart
    }
    else {
        return 0; // return false to indicate game end
    }
}

int main() {
    int min; // minimum number
    int max; // maximum number
    int n; // Random Number
    int playerNum; // Player Number
    int victory = 0; // Victory condition
    int move = 10; // player base move
    int restart_game = 1; // flag to control game restart
    int* list = (int*)malloc(sizeof(int) * round);
    free(list);
    


    srand(time(NULL)); // generate random seed for rand

    while (restart_game) { // main loop
        while (1) {
            printf("Enter the minimum number: ");
            min = ask_int("");
            printf("Enter the maximum number: ");
            max = ask_int("");

            if (max > min) {
                break;
            }
            else {
                printf("Maximum number must be greater than minimum number!\n");
            }
        }

        n = rand() % max + min; // set n has random number
        move = 10; // reset move count for each game

        while (move != 0 && victory != 1) { // while there no victory or moves left
            printf("\nInsert your guess: ");
            playerNum = ask_int_range("", min, max); // ask the player number to be an int
            printf("\nYour number is %d", playerNum);
            printf("\nYou have %d moves left", move);

            if (playerNum == n) { // if victory
                printf("\nVictory");
                victory = 1;
            }
            else if (playerNum < n) { // if player number is smaller
                printf("\nHigher");
                move--;
            }
            else if (playerNum > n) { // if player number is higher
                printf("\nSmaller");
                move--;
            }
        }

        if (move == 0) {
            printf("\nDefeat");
        }

        printf("\nThe number was: %d\n", n);

        
        round++; // round = round + 1
        printf("List of the mysteries numbers : ");
        for (int i = 1; i <= round; i++) { // show the acient result list
            list[round] = n; // define the result as ancient result
            printf("%d, ", list[i]);
        }
        

        restart_game = restart(); // check if the game should be restarted
        victory = 0; // reset victory for next game
    }

    return 0;
}
