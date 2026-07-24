// Program entry point
#include "functions.h"
#include "types.h"

int main(void) {
    Cell board[NO_OF_CELLS];
    int game_round = 0;
    Player players[NO_OF_PLAYERS];

    srand(1);

    print_game(&game_round);
    initialize_players(players);
    decide_player_order(players);
    generate_board(board);
    // game_loop(game_round, players, board);
    print_board(board);
    return 0;
}