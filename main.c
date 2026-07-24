// Program entry point
#include "functions.h"
#include "types.h"

int main(void) {
    Cell board[NO_OF_CELLS];
    int game_round = 0;
    int players[4][3] = { // set as 5 for sorting process when deciding the player order d
        {AGGRESSIVE_INVESTOR, 5, -1}, 
        {CONSERVATIVE_BANKER, 5, -1}, 
        {RISK_TAKER, 5, -1}, 
        {OPPORTUNISTIC_TRADER, 5, -1}
    };
    char *player_names[] = {"Aggressive Investor", "Conservative Banker", "Risk Taker", "Opportunistic Trader"};

    srand(1);

    print_game(&game_round);
    decide_player_order(players, player_names);
    generate_board(board);
    // print_board(board);
    return 0;
}