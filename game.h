/*
 * game.c
	this module encapsulates the Sudoku puzzle game and the Sudoku board.
	It is used to store and manipulate the game and it's functions include the possible game moves.
 */
#include "structs.h"
#ifndef GAME_H_
#define GAME_H_
#define BLOCK_SIZE 3
#define BOARD_SIZE 9

void printBoard(Game game);
/*print the game board in the game*/

void initilizeNewGame(int number_of_fix_cells,Game *game);
/*get a game and number of cell to the begin
 * find a solution and save it and create the game board
 * with number of fixed cell
 */


int setCell(int x, int y, int z, Game *game);
/*sets cell in game board (z > 0)
 * if illegal input and returns returns 0
 * if cell is fixed prints: cell is fixed and returns 0
 * if cell exists in one of it's neighbors prints: value is invalid and returns 0
 * otherwise, keeps the cell and returns 1
 * */

int clearCell(int x, int y, Game *game);
/*checks if cell is fixed
 * if not, clears it and returns 1
 * otherwise returns 0
 * */

int isWin(Game *game);
/*returns 1 if win
 * returns 0 otherwise
 */

void hint(int x, int y, Game *game);
/*prints hint (the value x y in the solution board)*/


void intilizeEmptyBoard(Cell board[BOARD_SIZE+1][BOARD_SIZE+1]);
/*Initialize all the cells at board to be empty*/
#endif /* GAME_H_ */
