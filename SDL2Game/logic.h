#ifndef _LOGIC__H
#define _LOGIC__H


#define BOARD_SIZE 3 
#define EMPTY_CELL ' '
#define O_CELL 'o'
#define X_CELL 'x'



struct Tictactoe {
    char board[BOARD_SIZE][BOARD_SIZE];
    char nextMove = O_CELL;
    void init() {
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++) board[i][j] = EMPTY_CELL;
    }
    void move(int row, int column) {
        if (row >= 0 && row < BOARD_SIZE &&
            column >= 0 && column < BOARD_SIZE)
        {
            board[row][column] = nextMove;
            if (nextMove == O_CELL) {
                nextMove = X_CELL;
            }
            else {
                nextMove = O_CELL;
            }
        }
    }

};

#endif
