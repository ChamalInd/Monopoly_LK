// Game controller and simulation engine
#include "functions.h"

void print_game(int *game_round) {
    if (*game_round == 0) {
        printf("MONOPOLY-LK Simulation\n\nPlayer 1 : Aggressive Investor\nPlayer 2 : Conservative Banker\nPlayer 3 : Risk Taker\nPlayer 4 : Opportunistic Trader\n\nEach player begins with LKR 30,000.\n\n");
    }
}

int dice_roll(void) {
    return (rand() % 11) + 2;
}

void sort_players(Player players[]) {
    int swapped = TRUE;

    while (swapped) {
        swapped = FALSE;
        for (int i = 0; i < NO_OF_PLAYERS - 1; i++) {
            if (players[i].play_order > players[i + 1].play_order) {
                Player temp;
                temp = players[i];
                players[i] = players[i + 1];
                players[i + 1] = temp;
                swapped = TRUE;
            }
        }
    }
}

void decide_player_order(Player players[]) {
    int max[] = {-1, -1};
    int i = 0, assigned_players = 0, count;

    while (assigned_players < 4) {
        for (i = 0; i < NO_OF_PLAYERS; i++) {
            if (players[i].play_order == 5) {
                players[i].die_roll = dice_roll();
                printf("%s rolls %i.\n", players[i].name, players[i].die_roll);
            }
        }
    
        for (int x = assigned_players; x < NO_OF_PLAYERS; x++) {
            max[0] = 0;
            for (int y = 0; y < NO_OF_PLAYERS; y++) {
                if (players[y].play_order == 5 && max[0] < players[y].die_roll) {
                    max[0] = players[y].die_roll;
                    max[1] = y;
                }
            }
            count = 0;
            for (int y = 0; y < NO_OF_PLAYERS; y++) {
                if (players[y].play_order == 5 && max[0] == players[y].die_roll) {
                    count++;
                }
            }
            if (count != 1) {
                continue;
            }
            
            players[max[1]].play_order = x + 1;
        }

        sort_players(players);

        printf("\n\n");

        assigned_players = 0;
        for (i = 0; i < NO_OF_PLAYERS; i++) {
            if (players[i].play_order != 5) {
                assigned_players++;
            }
        }  
    }

    printf("%s will begin the game.\n\n", players[0].name);
    printf("Turn order:\n");
    for (i = 0; i < NO_OF_PLAYERS; i++) {
        printf("%s\n", players[i].name);
    }
    printf("\n");

}

void game_loop(int game_round, Player players[], Cell board[]) {
    int current_player = 0, pass_go = FALSE;
    while (game_round < 500) {
        pass_go = FALSE;

        players[current_player].die_roll = dice_roll();
        printf("%s rolled %i.\n", players[current_player].name, players[current_player].die_roll);
        
        printf("%s moves from Square %i ", players[current_player].name, players[current_player].place + 1);
        players[current_player].place += players[current_player].die_roll;
        if (players[current_player].place > 39) {
            pass_go = TRUE;
        }
        players[current_player].place %= 39;
        printf("to Square %i.\n\n", players[current_player].place + 1);

        if (pass_go) {
            players[current_player].cash += 2000;
            printf("%s passed GO.\n", players[current_player].name);
            printf("Collected LKR 2000.\nCurrent Balance LKR %i.\n\n", players[current_player].cash);
        }
        
        buy(&players[current_player], &board[players[current_player].place]);
        rent(players, current_player, board[players[current_player].place]);

        current_player++;
        current_player %= 4;
        game_round++;
    } 
}