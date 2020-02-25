/*
 * solver.c
 * This module implements the backtracking algorithm.
 */
#ifndef SOLVER_H_
#define SOLVER_H_
#define BLOCK_SIZE 3
#define BOARD_SIZE 9


int fillTheBoard(Cell board[BOARD_SIZE+1][BOARD_SIZE+1], int algorithem_type);
/*algorithem_type==0 --> Deterministic
 * algorithem_type==1 --> random
 * get board and algorithm and return 1 if there a solution to the board and update the board
 * if there no solution return 0
 */

void setCellForAlgo(int row, int column, int value,Cell board[BOARD_SIZE+1][BOARD_SIZE+1]);
/*get the cell index and value and update the cell*/

#endif /* SOLVER_H_ */
