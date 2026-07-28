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

// Functions in players.c
void initialize_players(Player players[]);
void print_player(Player players[]);
Status calculate_player_status(Player player, Cell board[]);
void check_for_jailed(Player *player, Cell board[]);
void check_for_bankruptcy(Player *player, Cell board[]);
void announce_bankruptcy(Player *player, Cell board[]);
void check_for_bank_action(Player *player, Cell board[]);
void buy(Player players[], Player *player, Cell *place);
void auction(Player players[], Cell *place);
void rent(Player *player, Cell *place, Cell board[]);
void constructions(Player *player, Cell *place, Cell *property_groups[][3]);

// functions in finance.c
void obtain_loan(Player *player, Cell board[]);
void accumulated_interest(Player *player);
void check_for_loan_status(Player *player, Cell board[]);
void repay_part_of_loan(Player *player, Cell board[]);
void repay_full_loan(Player *player, Cell board[]);
void extend_loan(Player *player);
void increase_loan(Player *player, Cell board[]);

#endif