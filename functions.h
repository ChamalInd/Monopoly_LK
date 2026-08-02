// Prototypes of functions
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "types.h"

// Functions in board.c
void generate_board(Cell board[]);
void destroy_property(Cell *place);
void sort_players(Player players[]);
void decide_player_order(Player players[]);

// Functions in game.c
void print_game(Game game_status, Player players[], Cell board[], int game_over);
int dice_roll(void);
int decide_winner(Player players[], Cell board[]);
void game_loop(Game *game_status, Player players[], Cell board[], Cell *property_groups[][3]);

// Functions in players.c
void initialize_players(Player players[]);
Status calculate_player_status(Player player, Cell board[]);
void check_for_jailed(Player *player);
void check_for_bankruptcy(Player *player, Cell board[]);
void announce_bankruptcy(Player *player, Cell board[]);
void check_for_bank_action(Player *player, Cell board[], Game game_status);
void check_for_insurance_action(Player *player, Cell place, Cell board[]);
void buy(Player players[], Player *player, Cell *place);
int auction(Player players[], Cell *place, Ownership beneficiary);
void rent(Player players[], Player *player, Cell *place, Cell board[]);
void constructions(Player *player, Cell *place, Cell *property_groups[][3]);
void property_renovations(Player *player, Cell *place);
void building_renovations(Player *player, Cell board[]);

// Functions in finance.c
void obtain_loan(Player *player, Cell board[], Game game_status);
void accumulated_interest(Player players[]);
void check_for_loan_status(Player players[], Cell board[]);
void repay_part_of_loan(Player *player, Cell board[]);
void repay_full_loan(Player *player, Cell board[]);
void extend_loan(Player *player);
void increase_loan(Player *player, Cell board[], Game game_status);
void obtain_insurance(Player *player, Cell *place, int provider);
void check_for_insurance_status(Cell board[]);
void renew_insurance(Player *player, Cell *board[], int length);
void income_tax_payment(Player *player, Game game_status, Cell board[]);

// Functions in events.c
void property_depreciation(Cell board[]);
void building_depreciation(Cell board[]);
void inflation(Cell board[], Game *game_status);
// void dynamic_property_market(Cell *property_groups[][3], int selected_property_market);

#endif