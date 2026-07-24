// Prototypes of functions
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "types.h"

// Functions in board.c
void generate_board(Cell board[]);
void print_board(Cell board[]);

// Functions in game.c
void print_game(int *game_round);
void decide_player_order(int players[][3], char *player_names[]); // because the computer's RAM is linear, but a 2D array is structured as rows and columns. The compiler needs the column size to calculate where a row ends and where the next row begins in that linear memory
void sort_players(int players[][3]);
int dice_roll(void);


#endif