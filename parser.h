/*
 * parser.h
 * this module includes all the functions that are responsible for reading and interpreting
 * the input from the user.
 *
 */

#ifndef PARSER_H_
#define PARSER_H_
#include "structs.h"

int getCommandFromUser(char input[1024], char command[1024][1024]);
/*gets command from user and writes it to the command array*/


void clearCommand(char command[1024][1024]);
/*clears command array (initializes all values to 0)*/


void clearInput(char input[1024]);
/*clears input array (initializes all values to 0)*/

int getNumberOfFixedCells();
/*gets the number of fixed cells from the user
 *if not int or EOF exits
 *if int but not in range, tries again
 *returns the number of fixed cells
 */


int processCommand(char command[1024][1024] ,Game *game, int win);
/*processes the command  and does it if valid (if the user won - checks if command is restart or exit)
 * returns 1 if the command was valid and successful
 * returns 2 if successful but no need to print the board
 * returns 0 otherwise
 */


#endif /* PARSER_H_ */
