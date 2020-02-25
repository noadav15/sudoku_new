/*
 * structs.h
 * this module contains all the structs that are needed for the game.
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_
#define BLOCK_SIZE 3
#define BOARD_SIZE 9

typedef struct{
	int invalid;
	int value;
	int fixed;
	} Cell;

typedef struct{
	int n;
	int m;
	int marked;
	Cell *board;
	} Game;

#endif /* STRUCTS_H_ */
