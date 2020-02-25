/*
 * parser.c
 * this module includes all the functions that are responsible for reading and interpreting
 * the input from the user.
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "game.h"
#include "solver.h"

/*exits the game and prints the right message
 */
void exitGame(){
	printf("Exiting...\n");
	exit(0);
}

/*gets the number of fixed cells from the user
 *if not int or EOF exits
 *if int but not in range, tries again
 *returns the number of fixed cells
 */
int getNumberOfFixedCells(){
	int num_of_cells;
			int scan_value;
			scan_value = -1;
			printf("Please enter the number of cells to fill [0-80]:\n");
			while(1){
				scan_value = scanf("%d", &num_of_cells);
				if(scan_value < 0){
					exitGame();
				}
				if(scan_value == 0){
					exitGame();
				}
				if(!feof(stdin) || scan_value == 1){
					if(num_of_cells >= 0 && num_of_cells <= 80){
						fflush(stdin);
						return num_of_cells;
					}
					else{
						printf("Error: invalid number of cells to fill (should be between 0 and 80)\n");
						printf("Please enter the number of cells to fill [0-80]:\n");
					}
				}
			}
			exitGame();

	}
/*the function copies the board to another board
 */
void copyBoardGame(Cell copy_from[BOARD_SIZE+1][BOARD_SIZE+1],Cell copy_to[BOARD_SIZE+1][BOARD_SIZE+1]){
	int i,j;
	for(i=1;i<=BOARD_SIZE;i++){
		for(j=1;j<=BOARD_SIZE;j++){
			copy_to[i][j].empty=copy_from[i][j].empty;
			copy_to[i][j].fixed=copy_from[i][j].fixed;
			copy_to[i][j].number=copy_from[i][j].number;
		}
	}
}

/*returns 1 if command is validate and validates
 * returns 0 otherwise
 * */
int checkIfCommandIsValidateAndDo(char command[1024][1024] ,Game *game){
	int there_is_solution=0,compare;
	Cell new_solution[BOARD_SIZE+1][BOARD_SIZE+1];
	if(command[1]!=NULL){
		compare = strcmp(command[1],"validate");
		if(!compare){
			copyBoardGame(game->game_board,new_solution);
			there_is_solution=fillTheBoard(new_solution,0);
			if(there_is_solution){
				printf("Validation passed: board is solvable\n");
				copyBoardGame(new_solution,game->solution_board);
			}
			else{
				printf("Validation failed: board is unsolvable\n");
			}
			return 1;
		}
	}
	return 0;
}

/*returns 1 if command is restart and restarts the game
 * returns 0 otherwise
 * */
int checkIfCommandIsRestartAndDo(char command[1024][1024] ,Game *game){
	int compare, number_of_fixed;
	if(command[1]!=NULL){
		compare = strcmp(command[1],"restart");
		if(!compare){
			number_of_fixed= getNumberOfFixedCells();
			initilizeNewGame(number_of_fixed,game);
			return 1;
		}
	}
	return 0;
}

/*returns 1 if was able to set
 * returns 2 if value is invalid
 * returns 0 if not a set command
 * */
int checkIfCommandIsSetAndDo(char command[1024][1024], Game *game){
	int compare, x = -1, y = -1, z = -1;
	int successful_set = 0;
	char* trash;
	if(command[1]!=NULL){
			compare = strcmp(command[1],"set");
			if(!compare){
				if(command[2][0] != -1 && command[3][0] != -1 && command[4][0] != -1){
					x = strtol(command[2], &trash, 10);
					y = strtol(command[3], &trash, 10);
					z = strtol(command[4], &trash, 10);
					if(z > 0 && z < 10){
						 successful_set= setCell(x, y , z, game);
						 if(!successful_set){
							 return 2;
						 }
					}
					if(z == 0){
						successful_set= clearCell(x, y, game);
						if(!successful_set){
							return 2;
						}
					}
				}

			}
		}
	return successful_set;
}

/*returns 1 and gives a hint if the command is hint
 * returns 0 if not a hint command
 * */
int checkIfCommandIsHintAndDo(char command[1024][1024],Game *game){
	int compare, x , y;
	char* trash;
	if(command[1]!=NULL){
			compare = strcmp(command[1],"hint");
			if(!compare){
				if(command[2][0] != -1 && command[3][0] != -1){
					x = strtol(command[2], &trash, 10);
					y = strtol(command[3], &trash, 10);

					hint(x, y, game);
					return 1;
				}
			}
	}
	return 0;
}


/* exits the game if command is exit
 * */
void checkIfCommandIsExit(char command[1024][1024]){
	int compare;
	if(command[1]!=NULL){
			compare = strcmp(command[1],"exit");
			if(!compare){
				exitGame();
			}
	}
}

/*processes the command  and does it if valid (if the user won - checks if command is restart or exit)
 * returns 1 if the command was valid and successful
 * returns 2 if successful but no need to print the board
 * returns 0 otherwise
 */
int processCommand(char command[1024][1024], Game *game, int win){
	int set_return_value;
	if(command[1][0] == -1){
		return 0;
	}
	checkIfCommandIsExit(command);
	if(checkIfCommandIsRestartAndDo(command,game)){

			return 1;
	}
	if(win != 1){
		if(checkIfCommandIsValidateAndDo(command,game)){
			return 2;
		}
		set_return_value = checkIfCommandIsSetAndDo(command, game);
		if(set_return_value != 0){
			return set_return_value;
		}
		if(checkIfCommandIsHintAndDo(command, game)){
			return 2;
		}
	}
	printf("Error: invalid command\n");
	return 0;
}

/*gets command from user and writes it to the command array*/
int getCommandFromUser(char input[1024], char command[1024][1024]){
	char* cur_word_pointer;
	int i = 1;
	const char delimiters[] = " \t\r\n";
	fflush(stdin);
	if(feof(stdin)){
			exitGame();
	}
	fgets(input,1024,stdin);
	cur_word_pointer = strtok(input, delimiters);
	while(cur_word_pointer != NULL){
		strcpy(command[i], cur_word_pointer);
		i++;
		cur_word_pointer = strtok(NULL, delimiters);
	}
	return 1;
}

/*clears input array (initializes all values to 0)*/
void clearInput(char input[1024]){
	int i;
	for(i = 0; i < 1024; i++){
		input[i] = -1;
	}
}

/*clears command array (initializes all values to 0)*/
void clearCommand(char command[1024][1024]){
	int i;
	int j;
	for(j = 0; j < 1024; j++){
		for(i = 0; i < 1024; i++){
			command[j][i] = -1;
		}
	}
}

