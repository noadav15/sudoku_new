
/*
 * game.c
	this module encapsulates the Sudoku puzzle game and the Sudoku board.
	It is used to store and manipulate the game and it's functions include the possible game moves.
 */
#define BLOCK_SIZE 3
#define BOARD_SIZE 9
#include "structs.h"
#include "solver.h"
#include <stdio.h>
#include <stdlib.h>

/*print cell*/
void printCell(Cell c){
	if(c.value!=0){
		int value= c.value;
		if(c.fixed==1){
			printf("%d. ",value);
		}
		else{
			if(c.invalid==1){
				printf("%d* ",value);
			}
			printf(" %d ",value);
		}
	}
	else{
		printf("   ");
	}
}
/*print ----------- 34 times*/
void printRowSepration(int m, int n){
	int i=1;
	int N =n*m;
	for(i=1;i<=34;i++){
		printf("-");
	}
	printf("\n");
}
/*print part of the board game*/
void printBlockRow(int i, Game game){
	int j=1,k=0;
	printRowSepration();
	for(k=i;k<i+BLOCK_SIZE;k++){
		for(j=1;j<=BOARD_SIZE;j++){
			if(j%BLOCK_SIZE==1){
				printf("| ");
			}
			printCell((game.game_board[k][j]));
		}
		printf("|\n");
	}
}
/*print game board*/
void printBoard(Game game){
	int k;
	for(k=0;k<BLOCK_SIZE;k++){
		printBlockRow(k*BLOCK_SIZE +1, game);
	}
	printRowSepration();
}
/*fill cell to be empty cell*/
void intilizeEmptyCell(Cell *c){
	c->empty=1;
	c->fixed=0;
	c->number=-1;

}
/*Create an empty board game*/
void intilizeEmptyBoard(Cell board[BOARD_SIZE+1][BOARD_SIZE+1]){
	int i,j;
	for(i=1;i<=BOARD_SIZE;i++){
		for(j=1;j<=BOARD_SIZE;j++){
			intilizeEmptyCell(&board[i][j]);
		}
	}
}

/*check if the game board current row values are valid
 * return 1 if valid, else return 0
 */
int checkRowValid(int row ,Cell board[BOARD_SIZE+1][BOARD_SIZE+1]){
	int i=1;
	int value;
	int arr[BOARD_SIZE+1]={0};
	for(i=1;i<=BOARD_SIZE;i++){
		if(!board[row][i].empty){
			value=board[row][i].number;
			arr[value]++;
		}
	}
	for(i=1;i<BOARD_SIZE+1;i++){
		if(arr[i]>1){
			return 0;
		}
	}
	return 1;
}
/*/*check if the game board current column values are valid
 * return 1 if valid, else return 0
 */
int checkColumnValid(int column,Cell board[BOARD_SIZE+1][BOARD_SIZE+1]){
	int i=1;
	int value;
	int arr[BOARD_SIZE+1]={0};
	for(i=1;i<=BOARD_SIZE;i++){
		if(!board[i][column].empty){
			value=board[i][column].number;
			arr[value]++;
		}
	}
	for(i=1;i<BOARD_SIZE+1;i++){
		if(arr[i]>1){
			return 0;
		}
	}
	return 1;
}
/*/*check if the game board current block values are valid
 * return 1 if valid, else return 0
 */
int checkBlockValid(int row,int column,Cell board[BOARD_SIZE+1][BOARD_SIZE+1]){
	int i,j,value,k=0;
	int arr[BOARD_SIZE+1]={0};
	for(i=row;i<row+BLOCK_SIZE;i++){
		for(j=column;j<column+BLOCK_SIZE;j++){
			if(!board[i][j].empty){
				value=board[i][j].number;
				arr[k]=value;
			}
			k++;
		}
	}
	for(i=1;i<BOARD_SIZE+1;i++){
		value=0;
		for(j=1;j<BOARD_SIZE+1;j++){
			if(arr[j]==i){
				if(value>0){
					return 0;
				}
				else{
					value=1;
				}
			}
		}
	}
	return 1;
}
/*check if the game board values are valid
 * return 1 if valid, else return 0
 */
int boardValueAreValid(Cell board[BOARD_SIZE+1][BOARD_SIZE+1]){
	int i,correct,j;
	for(i=1;i<=BOARD_SIZE;i++){
		correct=checkColumnValid(i,board);
		if(correct==0){
			return 0;
		}
	}
	for(i=1;i<=BOARD_SIZE;i++){
		correct=checkRowValid(i,board);
		if(correct==0){
			return 0;
		}
	}
	for(i=1;i<=BOARD_SIZE;i=i+BLOCK_SIZE){
		for(j=1;j<=BOARD_SIZE;j=j+BLOCK_SIZE){
			correct=checkBlockValid(i, j, board);
			if(correct==0){
				return 0;
			}
		}
	}
	return 1;
}

/*get game board and delete all unfixed cell*/
void emptyAllUnfixedCells(Cell board[BOARD_SIZE+1][BOARD_SIZE+1]){
	int i,j;
	for( i=1;i<=BOARD_SIZE;i++){
		for(j=1;j<=BOARD_SIZE;j++){
			if(board[i][j].fixed==0){
				board[i][j].empty=1;
				board[i][j].number=-1;
			}
		}
	}
}
/*get a game and number of cell to the begin
 * find a solution and save it and create the game board
 * with number of fixed cell
 */
void initilizeNewGame(int number_of_fix_cells,Game *game){
	int i,j,k=1;
	int x,y;
	intilizeEmptyBoard(game->solution_board);
	fillTheBoard(game->solution_board,1);
	for(i=1;i<=BOARD_SIZE;i++){
		for(j=1;j<=BOARD_SIZE;j++){
			game->game_board[i][j]=game->solution_board[i][j];
		}
	}
	while(k<=number_of_fix_cells){
		x=rand()%BOARD_SIZE+1;
		y=rand()%BOARD_SIZE+1;
		while(game->game_board[y][x].fixed==1){
			x=rand()%BOARD_SIZE+1;
			y=rand()%BOARD_SIZE+1;
		}
		game->game_board[y][x].fixed=1;
		k++;
	}
	emptyAllUnfixedCells(game->game_board);

}

/*sets cell in game board (z > 0)
 * if illegal input and returns returns 0
 * if cell is fixed prints: cell is fixed and returns 0
 * if cell exists in one of it's neighbors prints: value is invalid and returns 0
 * otherwise, keeps the cell and returns 1
 * */
int setCell(int x, int y, int z, Game *game){
	int prev_empty;
	int prev_cell_value;
	int valid_insertion = 0;
	if((game->game_board)[y][x].fixed){
		printf("Error: cell is fixed\n");
		return 0;
	}
	prev_cell_value = (game->game_board)[y][x].number;
	prev_empty = (game->game_board)[y][x].empty;
	(game->game_board)[y][x].number = z;
	(game->game_board)[y][x].empty = 0;
	valid_insertion = boardValueAreValid((game->game_board));
	if(!valid_insertion){
		(game->game_board)[y][x].number = prev_cell_value;
		(game->game_board)[y][x].empty = prev_empty;
		printf("Error: value is invalid\n");
		return 0;
	}
	return 1;
}

/*checks if cell is fixed
 * if not, clears it and returns 1
 * otherwise returns 0
 * */
int clearCell(int x, int y, Game *game){
	if((game->game_board)[y][x].fixed){
		printf("Error: cell is fixed\n");
		return 0;
	}
	(game->game_board)[y][x].number = -1;
	(game->game_board)[y][x].empty = 1;
	return 1;
}

/*prints hint (the value x y in the solution board)*/
void hint(int x, int y, Game *game){
	printf("Hint: set cell to %d\n", (game->solution_board)[y][x].number);
}

/*returns 1 if win
 * returns 0 otherwise
 */
int isWin(Game *game){
	int i;
	int j;
	for(i = 0; i < BOARD_SIZE+1; i++){
		for(j = 0; j < BOARD_SIZE+1; j++){
			if((game->game_board)[j][i].empty){
				return 0;
			}
		}
	}
	return 1;
}


