// Mustafa Mannan//

/* this is a tic tac toe game with an unbeatable ai using the minimax algorithm */
/* plan to add difficulty levels and adjust the difficulty of AI for 3 modes easy, medium and impossible*/




#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

void reset_board();
int check_spaces();
void p_move();
void c_move();
char checkwin();
void Winner(char);

const char PLAYER = 'X';
const char CPU = 'O';

char grid[3][3];

void display_board() {
    printf("        |            |              \n");
    printf("   %c    |     %c      |     %c       \n", grid[0][0], grid[0][1], grid[0][2]);
    printf("        |            |              \n");
    printf("________|____________|________      \n");
    printf("        |            |              \n");
    printf("   %c    |     %c      |     %c       \n", grid[1][0], grid[1][1], grid[1][2]);
    printf("        |            |              \n");
    printf("________|____________|________      \n");
    printf("        |            |              \n");
    printf("   %c    |     %c      |     %c       \n", grid[2][0], grid[2][1], grid[2][2]);
    printf("        |            |              \n");
}

void reset_board() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            grid[i][j] = ' ';
        }
    }
}

int check_spaces() {
    int free_space = 9;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] != ' ') {
                free_space--;
            }
        }
    }

    return free_space;
}



void p_move() {
    int space;

    printf("Enter the number of the space you want to mark (1-9): ");
    scanf("%d", &space);

    while (space < 1 || space > 9) {
        printf("Invalid move. Try again.\n");
        printf("Enter the number of the space you want to mark (1-9): ");
        scanf("%d", &space);
    }

    int row = (space - 1) / 3;
    int col = (space - 1) % 3;

    while (grid[row][col] != ' ') {
        printf("Invalid move. Try again.\n");
        printf("Enter the number of the space you want to mark (1-9): ");
        scanf("%d", &space);

        while (space < 1 || space > 9) {
            printf("Invalid move. Try again.\n");
            printf("Enter the number of the space you want to mark (1-9): ");
            scanf("%d", &space);
        }

        row = (space - 1) / 3;
        col = (space - 1) % 3;
    }

    grid[row][col] = PLAYER;
}


int evaluateBoard() {
    for (int i = 0; i < 3; i++) {
        if (grid[i][0] != ' ' && grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2]) {
            if (grid[i][0] == CPU)
                return 10;
            else
                return -10;
        }
    }

    for (int i = 0; i < 3; i++) {
        if (grid[0][i] != ' ' && grid[0][i] == grid[1][i] && grid[0][i] == grid[2][i]) {
            if (grid[0][i] == CPU)
                return 10;
            else
                return -10;
        }
    }

    if (grid[0][0] != ' ' && grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2]) {
        if (grid[0][0] == CPU)
            return 10;
        else
            return -10;
    }

    if (grid[0][2] != ' ' && grid[0][2] == grid[1][1] && grid[0][2] == grid[2][0]) {
        if (grid[0][2] == CPU)
            return 10;
        else
            return -10;
    }

    return 0; // Game is a draw
}

int minimax(int depth, int isMaximizing) { // implementing the minimax algorithm
    int score = evaluateBoard();
    if (score == 10 || score == -10) {
        return score;
    }
    if (check_spaces() == 0) {
        return 0; // Game ended in a draw
    }

    if (isMaximizing) {
        int maxScore = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i][j] == ' ') {
                    grid[i][j] = CPU;
                    int currentScore = minimax(depth + 1, 0);
                    grid[i][j] = ' ';
                    if (currentScore > maxScore) {
                        maxScore = currentScore;
                    }
                }
            }
        }
        return maxScore;
    } else {
        int minScore = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i][j] == ' ') {
                    grid[i][j] = PLAYER;
                    int currentScore = minimax(depth + 1, 1);
                    grid[i][j] = ' ';
                    if (currentScore < minScore) {
                        minScore = currentScore;
                    }
                }
            }
        }
        return minScore;
    }
}

void c_move() {
    int bestScore = -1000;
    int bestMoveRow = -1;
    int bestMoveCol = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] == ' ') {
                grid[i][j] = CPU;
                int moveScore = minimax(0, 0);
                grid[i][j] = ' ';
                if (moveScore > bestScore) {
                    bestScore = moveScore;
                    bestMoveRow = i;
                    bestMoveCol = j;
                }
            }
        }
    }

    grid[bestMoveRow][bestMoveCol] = CPU;
    printf("AI player (O) made its move.\n");
}

char checkwin() {
    for (int i = 0; i < 3; i++) {
        if (grid[i][0] != ' ' && grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2]) {
            return grid[i][0];
        }
        if (grid[0][i] != ' ' && grid[0][i] == grid[1][i] && grid[0][i] == grid[2][i]) {
            return grid[0][i];
        }
    }

    if (grid[0][0] != ' ' && grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2]) {
        return grid[0][0];
    }

    if (grid[0][2] != ' ' && grid[0][2] == grid[1][1] && grid[0][2] == grid[2][0]) {
        return grid[0][2];
    }

    return ' ';
}

void print_winner() {
    char winner = checkwin();
    if (winner == PLAYER) {
        printf("Congratulations! You won!\n");
    } else if (winner == CPU) {
        printf("AI player (O) won!\n");
    } else {
        printf("It's a draw!\n");
    }
}

int main() {
    char winner = ' ';

    reset_board();

    while (winner == ' ' && check_spaces() != 0) {
        display_board();

        p_move();
        winner = checkwin();
        if (winner != ' ' || check_spaces() == 0) {
            break;
        }

        c_move();
        winner = checkwin();
        if (winner != ' ' || check_spaces() == 0) {
            break;
        }
    }

    display_board();
    print_winner();

    return 0;
}
