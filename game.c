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

void sort_players(int players[][3]) {
    int swapped = TRUE;

    while (swapped) {
        swapped = FALSE;
        for (int i = 0; i < NO_OF_PLAYERS - 1; i++) {
            if (players[i][1] > players[i + 1][1]) {
                int temp[3];
                for (int j = 0; j < 3; j++) {
                    temp[j] = players[i][j];
                    players[i][j] = players[i + 1][j];
                    players[i + 1][j] = temp[j];
                }
                swapped = TRUE;
            }
        }
    }
}

void decide_player_order(int players[][3], char *player_names[]) {
    int max[] = {-1, -1};
    int i = 0, assigned_players = 0, count;

    while (assigned_players < 4) {
        for (i = 0; i < NO_OF_PLAYERS; i++) {
            if (players[i][1] == 5) {
                players[i][2] = dice_roll();
                printf("%s rolls %i.\n", player_names[players[i][0] - 1], players[i][2]);
            }
        }
    
        for (int x = assigned_players; x < NO_OF_PLAYERS; x++) {
            max[0] = 0;
            for (int y = 0; y < NO_OF_PLAYERS; y++) {
                if (players[y][1] == 5 && max[0] < players[y][2]) {
                    max[0] = players[y][2];
                    max[1] = y;
                }
            }
            count = 0;
            for (int y = 0; y < NO_OF_PLAYERS; y++) {
                if (players[y][1] == 5 && max[0] == players[y][2]) {
                    count++;
                }
            }
            if (count != 1) {
                continue;
            }
            
            players[max[1]][1] = x + 1;
        }

        sort_players(players);

        printf("\n\n");

        assigned_players = 0;
        for (i = 0; i < NO_OF_PLAYERS; i++) {
            if (players[i][1] != 5) {
                assigned_players++;
            }
        }  
    }

    printf("%s will begin the game.\n\n", player_names[players[0][0] - 1]);
    printf("Turn order:\n");
    for (i = 0; i < NO_OF_PLAYERS; i++) {
        printf("%s\n", player_names[players[i][0] - 1]);
    }

}