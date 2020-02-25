#include "parser.h"
#include "game.h"
#include "mainAux.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char* seed;
	int win = 0;
	char input[1024] = {-1};
	char command[1024][1024] = {{-1}};
	int seed_int;
	char* trash;
	int successful_command = 0;
	Game game;
	int num_of_fixed_cells;
	clearCommand(command);
	clearInput(input);
	if(argc > 1){
		seed = argv[1];
		seed_int = strtol(seed, &trash, 10);
	}
	else{
		seed_int = 5;
	}
	srand(seed_int);
	num_of_fixed_cells = getNumberOfFixedCells();
	initilizeNewGame(num_of_fixed_cells, &game);
	printBoard(game);
	while(1){
		successful_command = 0;
		while(successful_command == 0){
			getCommandFromUser(input, command);
			clearInput(input);
			successful_command = processCommand(command, &game, win);
			clearCommand(command);
		}
		if(successful_command != 2){
			printBoard(game);
		}
		win = isWin(&game);
		if(win){
			printWinMessage();
		}
	}
	return 0;
}
