// Prototypes of functions
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "types.h"

// Functions in board.c
void generate_board(Cell board[]);
void print_board(Cell board[]);

// Functions in game.c
void print_game(int game_round, Player players[], Cell board[]);
int dice_roll(void);
void sort_players(Player players[]);
void decide_player_order(Player players[]);
void game_loop(int game_round, Player players[], Cell board[], Cell *property_groups[][3]);

// Functions player.c
void initialize_players(Player players[]);
void print_player(Player players[]);
Status calculate_player_status(Player player, Cell board[]);
void check_for_bankruptcy(Player *player, Cell board[]);
void buy(Player *player, Cell *place);
void rent(Player *player, Cell *place);
void constructions(Player *player, Cell *place, Cell *property_groups[][3]);

#endif