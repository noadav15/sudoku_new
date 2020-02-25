/*
 * solver.c
 * This module implements the backtracking algorithm.
 */

#define BLOCK_SIZE 3
#define BOARD_SIZE 9
#include "structs.h"
#include <stdlib.h>
/*get an array and game board and update the array- array[i]==0 -> i is an valid number to the cell, else i is unvalid option
 *
 */
void fillArrWithOption(int *arr_of_options,Cell board[BOARD_SIZE+1][BOARD_SIZE+1],int row,int column){
	int i,j,value1=0,value2;
	int column_start_point;
	int row_start_point ;
	if(column%BLOCK_SIZE==0){
		column_start_point= column -BLOCK_SIZE+1;
	}
	else{
		column_start_point= column -column%BLOCK_SIZE+1;
	}
	if(row%BLOCK_SIZE==0){
		row_start_point= row -BLOCK_SIZE+1;
	}
	else{
		row_start_point= row -row%BLOCK_SIZE+1;
	}
	for(i=1;i<=BOARD_SIZE;i++){
		if(!board[i][column].empty){
			value1= board[i][column].number;
			arr_of_options[value1]++;
		}
		if(!board[row][i].empty){
			value2= board[row][i].number;
			arr_of_options[value2]++;
		}
	}
	for(i=row_start_point;i<row_start_point+BLOCK_SIZE;i++){
		for(j=column_start_point;j<column_start_point+BLOCK_SIZE;j++){
			if(!board[i][j].empty){
				value1=board[i][j].number;
				arr_of_options[value1]++;
			}
		}
	}
}
/*get the cell index and value and update the cell */
void setCellForAlgo(int row, int column, int value,Cell board[BOARD_SIZE+1][BOARD_SIZE+1]){
	board[row][column].empty=0;
	board[row][column].number=value;
}
/*get the algorithm and put a number in the current cell
 * return 1 if the cell is valid else return 0
 */
int fillCellByAlgo(int row, int column,Cell board[BOARD_SIZE+1][BOARD_SIZE+1], int algorithem_type, int *arr_of_options){
	int i=1,number_of_option=0,random_index,k=0;
	if(algorithem_type==0){
		for(i=1;i<=BOARD_SIZE;i++){
			if(arr_of_options[i]==0){
				arr_of_options[i]=1;
				setCellForAlgo(row,column,i,board);
				return 1;
			}
		}
		return 0;
	}
	if(algorithem_type==1){
		for(i=1;i<=BOARD_SIZE;i++){
			if(arr_of_options[i]==0){
				number_of_option++;
			}
		}
		if(number_of_option==0){
			return 0;
		}
		if(number_of_option==1){
			for(i=1;i<=BOARD_SIZE;i++){
				if(arr_of_options[i]==0){
					arr_of_options[i]=1;
					setCellForAlgo(row,column,i,board);
					return 1;
				}
			}
		}
		else{
			random_index= rand()%number_of_option;
			for(i=1;i<=BOARD_SIZE;i++){
				if(arr_of_options[i]==0){
					if(k==random_index){
						arr_of_options[i]=1;
						setCellForAlgo(row,column,i,board);
						return 1;
					}
					k++;
				}
			}
		}
	}
	return 0;
}
/*get array of option to fill a cell
 * return 1 if there are option available else return 0
 */
int stillHasOptionForCell(int *arr_of_options){
	int i=1;
	for(i=1;i<=BOARD_SIZE;i++){
		if(arr_of_options[i]==0){
			return 1;
		}
	}
	return 0;
}
/*backtracking algorithm as we saw at class
 * return 1 if there a solution else return 0 */
int backTracking(int i, int j,int start_index_row,int start_index_column, Cell board[BOARD_SIZE+1][BOARD_SIZE+1], int algorithem_type){

	int succeed=0,next_succeed=0;
	int arr_of_options[BOARD_SIZE+1]={0};
	/*if the cell already not empty continue to next*/
	if(!board[i][j].empty){
		if(j<BOARD_SIZE){
			return backTracking(i,j+1,start_index_row,start_index_column,board,algorithem_type);
		}
		else{
			if(i<BOARD_SIZE){
				return backTracking(i+1,1,start_index_row,start_index_column,board,algorithem_type);
			}
			/*the last item not empty*/
			else{
				return 1;
			}
		}
	}
	/*should fill the cell*/
	else{
		fillArrWithOption(arr_of_options,board,i,j);
		while(stillHasOptionForCell(arr_of_options)){
			succeed= fillCellByAlgo(i,j,board,algorithem_type,arr_of_options);
			if(succeed){
				if(j<BOARD_SIZE){
					next_succeed= backTracking(i,j+1,start_index_row,start_index_column,board,algorithem_type);
				}
				else{
					if(i<BOARD_SIZE){
						next_succeed= backTracking(i+1,1,start_index_row,start_index_column,board,algorithem_type);
					}
					/*the last item not empty*/
					else{
						return 1;
					}
				}
				if(next_succeed==1){
					return 1;
				}
			}
		}
		/*no more option*/
		board[i][j].empty=1;
		board[i][j].number=-1;
		return 0;

	}
}
/*algorithem_type==0 --> Deterministic
 * algorithem_type==1 --> random
 * get board and algorithm and return 1 if there a solution to the board and update the board
 * if there no solution return 0
 */
int fillTheBoard(Cell board[BOARD_SIZE+1][BOARD_SIZE+1], int algorithem_type){
	int i=1,j=1,succeed, start_index_row, start_index_column, check=0;
	for(i=1;i<=BOARD_SIZE && check ==0;i++){
		for(j=1;j<=BOARD_SIZE && check ==0;j++){
			if(board[i][j].empty ){
				if(check==0){
					start_index_row=i;
					start_index_column=j;
					check=1;
				}
			}
		}
	}
	return succeed= backTracking(start_index_row,start_index_column,start_index_row,start_index_column,board,algorithem_type);

}
