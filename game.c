// Game controller and simulation engine
#include "functions.h"

void print_game(Game game_status, Player players[], Cell board[], int game_over) {
    if (game_status.rounds == 0) {
        for (int i = 0; i < 60; i++) {
            printf("=");
        }
        printf("\nMONOPOLY-LK Simulation\n");
        for (int i = 0; i < 60; i++) {
            printf("=");
        }
        printf("\nPlayer 1 : Aggressive Investor\nPlayer 2 : Conservative Banker\nPlayer 3 : Risk Taker\nPlayer 4 : Opportunistic Trader\n\nEach player begins with LKR 30000.\n\n");

    } else {
        for (int i = 0; i < 60; i++) {
            printf("=");
        }
        printf("\nRound %i Summary\n", game_status.rounds);
        for (int i = 0; i < 60; i++) {
            printf("=");
        }
        printf("\n");
        for (int i = 0; i < NO_OF_PLAYERS; i++) {
            if (players[i].isBankrupt == FALSE) {
                Status player_status = calculate_player_status(players[i], board);

                printf("\n%s\nCash : LKR %i\nNet Worth : LKR %i\nProperties : %i\nHotels : %i\nOutstanding Loans : LKR %i\n\n", players[i].name, players[i].cash, player_status.net_worth, player_status.total_properties, player_status.hotels_built, players[i].loan_status.total_payable);
                for (int j = 0; j < 60; j++) {
                    printf("-");
                }
                printf("\n");
            }
        }
        printf("\n");

        for (int i = 0; i < 60; i++) {
            printf("=");
        }
        printf("\nCurrent Market Conditions\n");
        for (int i = 0; i < 60; i++) {
            printf("=");
        }

        printf("\n\nInflation\n");
        for (int i = 0; i < 11; i++) {
            printf("-");
        }
        if (game_status.inflation_rate > 0) {
            printf("\n+%i%%\n\n", game_status.inflation_rate);
        } else {
            printf("\n%i%%\n\n", game_status.inflation_rate);
        }
        printf("Current Loan Interest\n");
        for (int i = 0; i < 23; i++) {
            printf("-");
        }
        printf("\n%.2f%%\n\n", game_status.interest_rate);
        for (int i = 0; i < 60; i++) {
            printf("=");
        }

        printf("\n\n");

    }
    
    if (game_over == TRUE || game_status.rounds == MAX_ROUNDS) {
        int winner_id = decide_winner(players, board);
        Status player_status = calculate_player_status(players[winner_id], board);

        for (int i = 0; i < 60; i++) {
            printf("=");
        }
        printf("\n\nGAME OVER\n\nWinner : %s\nTotal Cash : LKR %i\nTotal Property Value : LKR %i\nOutstanding Loans : LKR %i\nNet Worth : LKR %i\n\n", players[winner_id].name, players[winner_id].cash, player_status.total_property_value, players[winner_id].loan_status.total_payable, player_status.net_worth);
        for (int i = 0; i < 60; i++) {
            printf("=");
        }
        printf("\n");
    }
}

int dice_roll(void) {
    int die_1 = (rand() % 6) + 1;
    int die_2 = (rand() % 6) + 1;
    return die_1 + die_2;
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

        printf("\n");

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

int decide_winner(Player players[], Cell board[]) {
    int winner_id = NONE, non_bankrupt_count = 0, max_net_worth = 0;
    int non_bankrupt_players[NO_OF_PLAYERS] = {NONE, NONE, NONE, NONE};

    for (int i = 0; i < NO_OF_PLAYERS; i++) {
        if (players[i].isBankrupt == FALSE) {
            non_bankrupt_players[non_bankrupt_count] = i;
            non_bankrupt_count++;
        }
    }

    for (int i = 0; i < non_bankrupt_count; i++) {
        Status player_status = calculate_player_status(players[non_bankrupt_players[i]], board);

        if (max_net_worth < player_status.net_worth) {
            max_net_worth = player_status.net_worth;
            winner_id = non_bankrupt_players[i];
        }
    }

    return winner_id;
}

void game_loop(Game *game_status, Player players[], Cell board[], Cell *property_groups[][3]) {
    int current_player = 0, pass_go = FALSE, round_done = TRUE;
    int round_tracker[] = {0, 0, 0, 0};
    int selected_property_market = NONE;

    while (TRUE) {
        if (players[current_player].isBankrupt == TRUE) {
            round_tracker[current_player] = 1;
            current_player = ((current_player + 1) % NO_OF_PLAYERS);
            continue;
        } 

        if (players[current_player].jail_status.isJailed == TRUE) {
            check_for_jailed(&players[current_player], board);
            if (players[current_player].jail_status.isJailed == TRUE) {
                current_player = ((current_player + 1) % NO_OF_PLAYERS);
                continue;
            }
        }

        int game_over = TRUE;

        for (int i = 0; i < NO_OF_PLAYERS; i++) {
            check_for_bankruptcy(&players[i], board);
            if (players[i].id != players[current_player].id && players[i].isBankrupt == FALSE) {
                game_over = FALSE;
                break;
            } 
        }

        if (game_over) {
            game_status->rounds++;
            print_game(*game_status, players, board, game_over);
            break;
        }

        pass_go = FALSE;
        round_done = TRUE;

        players[current_player].die_roll = dice_roll();
        printf("%s rolled %i.\n", players[current_player].name, players[current_player].die_roll);
        
        printf("%s moves from Square %i ", players[current_player].name, players[current_player].place + 1);
        players[current_player].place += players[current_player].die_roll;
        if (players[current_player].place >= NO_OF_CELLS) {
            pass_go = TRUE;
        }
        players[current_player].place %= NO_OF_CELLS;
        printf("to Square %i.\n\n", players[current_player].place + 1);

        if (pass_go) {
            players[current_player].cash += 2000;
            round_tracker[current_player] = 1;
            printf("%s passed GO.\n", players[current_player].name);
            printf("Collected LKR 2000.\nCurrent Balance LKR %i.\n\n", players[current_player].cash);
        }

        for (int i = 0; i < NO_OF_PLAYERS; i++) {
            if (round_tracker[i] == 0) {
                round_done = FALSE;
                break;
            }
        }

        if (board[players[current_player].place].type == PROPERTY || board[players[current_player].place].type == RAILWAY || board[players[current_player].place].type == UTILITY) {
            sell(players, &players[current_player], &board[players[current_player].place]);
            
            if (board[players[current_player].place].type == PROPERTY) {
                constructions(&players[current_player], &board[players[current_player].place], property_groups);
                property_renovations(&players[current_player], &board[players[current_player].place]);
            }
            rent(&players[current_player], &board[players[current_player].place], board);
            buy(players, &players[current_player], &board[players[current_player].place]);

        } else {
            if (players[current_player].place == 2) { // Community Development Fund
                printf("%s Landed on Community Development Fund.\n\n", players[current_player].name);

            } else if (players[current_player].place == 4) { // Income Tax
                printf("%s Landed on Income Tax.\n\n", players[current_player].name);

            } else if (players[current_player].place == 7 || players[current_player].place == 22) { // National Event Card
                printf("%s Landed on National Event Card.\n\n", players[current_player].name);
                
            } else if (players[current_player].place == 10) { // Just visiting
                printf("%s Landed on Jail as a visit.\n\n", players[current_player].name);
                
            } else if (players[current_player].place == 17 || players[current_player].place == 33) { // Insurance
                check_for_insurance_action(&players[current_player], board[players[current_player].place], board);
                
            } else if (players[current_player].place == 20) { // Free Parking
                printf("%s Landed on Free Parking.\n\n", players[current_player].name);
                
            } else if (players[current_player].place == 30) { // Jail square
                check_for_jailed(&players[current_player], board);

            } else if (players[current_player].place == 38) { // Bank square
                check_for_bank_action(&players[current_player], board, *game_status);

            } 
        }

        if (round_done) {
            game_status->rounds++;
            for (int i = 0; i < NO_OF_PLAYERS; i++) {
                round_tracker[i] = 0;
            }
            print_game(*game_status, players, board, game_over);

            if (game_status->rounds == MAX_ROUNDS) {
                break;
            }

            accumulated_interest(players);
            check_for_loan_status(players, board);
            check_for_insurance_status(board);

            if (game_status->rounds % 5 == 0) {
                property_depreciation(board);
            } 
            if (game_status->rounds % 10 == 0) {
                inflation(board, game_status);
            }
        }

        current_player++;
        current_player %= NO_OF_PLAYERS;
    } 
}