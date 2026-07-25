// Program entry point
#include "functions.h"
#include "types.h"

int main(void) {
    Cell board[NO_OF_CELLS];
    Player players[NO_OF_PLAYERS];
    int game_round = 0;

    srand(1);
    // 1 = constructions will occur
    // 5 = tie occur


    print_game(game_round, players, board);
    initialize_players(players);
    decide_player_order(players);

    generate_board(board);
    Cell *property_groups[8][3] = {
        {&board[1], &board[3], NULL},
        {&board[6], &board[8], &board[9]},
        {&board[11], &board[13], &board[14]},
        {&board[16], &board[18], &board[19]},
        {&board[21], &board[23], &board[24]},
        {&board[26], &board[27], &board[29]},
        {&board[31], &board[32], &board[34]},
        {&board[37], &board[39], NULL}
    };

    game_loop(game_round, players, board, property_groups);
    // print_board(board);
    // print_player(players);
    return 0;
}