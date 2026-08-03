// Prototypes of functions
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "types.h"

// Functions in board.c
void generate_board(Cell board[]);
void generate_event_cards(Events national_events[]);
void destroy_property(Cell *place);
void sort_players(Player players[]);
void decide_player_order(Player players[]);

// Functions in game.c
void print_game(Game game_status, Player players[], Cell board[], int game_over, Events national_events[]);
int dice_roll(void);
int decide_winner(Player players[], Cell board[]);
void game_loop(Game *game_status, Player players[], Cell board[], Cell *property_groups[][3], Events national_events[]);

// Functions in players.c
void initialize_players(Player players[]);
Status calculate_player_status(Player player, Cell board[]);
void player_actions(Player players[], Cell board[], Cell *property_groups[][3], Game *game_status, Events national_events[]);
void check_for_jailed(Player *player);
void check_for_bankruptcy(Player players[], Cell board[], Game game_status, int player);
void announce_bankruptcy(Player players[], Cell board[], Game game_status, int player);
void check_for_bank_action(Player *player, Cell board[], Game game_status);
void check_for_insurance_action(Player *player, Cell place, Cell board[]);
void buy(Player players[], Cell *place, Game game_status);
int auction(Player players[], Cell *place, Ownership beneficiary, Game game_status);
void rent(Player players[], Cell *place, Cell board[], Game game_status);
void constructions(Player *player, Cell *place, Cell *property_groups[][3]);
void property_renovations(Player *player, Cell *place);
void building_renovations(Player *player, Cell board[]);

// Functions in finance.c
void obtain_loan(Player *player, Cell board[], Game game_status);
void accumulated_interest(Player *player);
void check_for_loan_status(Player players[], Cell board[], Game game_status);
void repay_part_of_loan(Player *player, Cell board[]);
void repay_full_loan(Player *player, Cell board[]);
void extend_loan(Player *player);
void increase_loan(Player *player, Cell board[], Game game_status);
void obtain_insurance(Player *player, Cell *place, int provider);
void check_for_insurance_status(Cell board[]);
void renew_insurance(Player *player, Cell *board[], int length);
void income_tax_payment(Player players[], Cell board[], Game game_status);

// Functions in events.c
void property_depreciation(Cell board[]);
void building_depreciation(Cell board[]);
void inflation(Cell board[], Game *game_status);
void dynamic_property_market(Cell *property_groups[][3], Game *game_status);
void national_event_card_draw(Player *player, Cell board[], Events national_events[], Game *game_status);
void national_event_card_expiry(Player *player);

#endif