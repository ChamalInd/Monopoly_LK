// Game controller and simulation engine
#include "functions.h"

void print_game(Game game_status, Player players[], Cell board[], int game_over, Events national_events[]) {
    if (game_status.rounds == 0) {
        // declare the start of the game
        for (int i = 0; i < 60; i++) {
            printf("=");
        }
        printf("\nMONOPOLY-LK Simulation\n");
        for (int i = 0; i < 60; i++) {
            printf("=");
        }
        printf("\nPlayer 1 : Aggressive Investor\nPlayer 2 : Conservative Banker\nPlayer 3 : Risk Taker\nPlayer 4 : Opportunistic Trader\n\nEach player begins with LKR 30000.\n\n");

    } else {
        // prints round and market summary
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

                printf("\n%s\nCash : LKR %i\nNet Worth : LKR %i\nProperties : %i\nHotels : %i\nOutstanding Loans : LKR %i\n", players[i].name, players[i].cash, player_status.net_worth, player_status.total_properties, player_status.hotels_built, players[i].loan_status.total_payable);
                
                printf("\nActive National Event Cards : \n");
                for (int j = 0; j < 20; j++) {
                    if (players[i].events[j].remaining_effect != 0) {
                        printf("\t%s : ( Remaining Rounds : %i )\n", national_events[players[i].events[j].event].name, players[i].events[j].remaining_effect);
                    }
                }
                printf("\n");

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

        char *property_groups[] = {
            "Colombo Central",   // BROWN
            "Colombo South",     // LIGHTBLUE
            "Colombo Suburbs",   // PINK
            "Airport Corridor",  // ORANGE
            "Kandy District",    // RED
            "Southern Province", // YELLOW
            "Northern Province", // GREEN
            "Premium Estates",   // DARKBLUE
        };

        if (game_status.dynamic_market.event != NORMAL) {
            char *value;
            if (game_status.dynamic_market.event == MARKET_BOOM) {
                printf("\n\nMarket Boom\n");
                value = "+20%";
            } else {
                printf("\n\nMarket Decline\n");
                value = "-15%";
            }

            for (int i = 0; i < 16; i++) {
                printf("-");
            }
            printf("\n%s (%s)\n", property_groups[game_status.dynamic_market.property_group], value);
            printf("Rounds Remaining : %i\n", 10 - game_status.rounds % 10);
        }

        printf("\nInflation\n");
        for (int i = 0; i < 11; i++) {
            printf("-");
        }
        if (game_status.inflation_rate > 0) {
            printf("\n+%i%%\n", game_status.inflation_rate);
        } else {
            printf("\n%i%%\n", game_status.inflation_rate);
        }
        printf("\nCurrent Loan Interest\n");
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
        // declare the end of the game
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

void game_loop(Game *game_status, Player players[], Cell board[], Cell *property_groups[][3], Events national_events[]) {
    int current_player = 0, pass_go = FALSE, round_done = TRUE;
    int round_tracker[] = {0, 0, 0, 0};

    while (TRUE) {
        // skips bankrupt players
        if (players[current_player].isBankrupt == TRUE) {
            round_tracker[current_player] = 1;
            current_player = ((current_player + 1) % NO_OF_PLAYERS);
            continue;
        } 

        // skips jailed players after giving them a chance to get out
        if (players[current_player].jail_status.isJailed == TRUE) {
            check_for_jailed(&players[current_player]);
            if (players[current_player].jail_status.isJailed == TRUE) {
                current_player = ((current_player + 1) % NO_OF_PLAYERS);
                continue;
            }
        }

        int game_over = TRUE;

        // checks for game end signal
        for (int i = 0; i < NO_OF_PLAYERS; i++) {
            check_for_bankruptcy(&players[i], board, players, *game_status);
            if (players[i].id != players[current_player].id && players[i].isBankrupt == FALSE) {
                game_over = FALSE;
                break;
            } 
        }

        if (game_over) {
            game_status->rounds++;
            print_game(*game_status, players, board, game_over, national_events);
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
            players[current_player].cash += GO_REWARD;
            round_tracker[current_player] = 1;

            accumulated_interest(&players[current_player]);
            check_for_loan_status(&players[current_player], players, board, *game_status);
            national_event_card_expiry(&players[current_player]);
            
            printf("%s passed GO.\n", players[current_player].name);
            printf("Collected LKR 2000.\nCurrent Balance LKR %i.\n\n", players[current_player].cash);
        }

        for (int i = 0; i < NO_OF_PLAYERS; i++) {
            if (round_tracker[i] == 0) {
                round_done = FALSE;
                break;
            }
        }

        if (players[current_player].place != 0) {
            printf("%s Landed on %s.\n\n", players[current_player].name, board[players[current_player].place].name);
        }

        if (board[players[current_player].place].type == PROPERTY || board[players[current_player].place].type == RAILWAY || board[players[current_player].place].type == UTILITY) {
            if (board[players[current_player].place].type == PROPERTY) {
                constructions(&players[current_player], &board[players[current_player].place], property_groups);
                property_renovations(&players[current_player], &board[players[current_player].place]);
                building_renovations(&players[current_player], board);
            }
            rent(players, &players[current_player], &board[players[current_player].place], board, *game_status);
            buy(players, &players[current_player], &board[players[current_player].place], *game_status);

        } else {
            if (players[current_player].place == 2) { // Community Development Fund
                // printf("%s Landed on Community Development Fund.\n\n", players[current_player].name);

            } else if (players[current_player].place == 4) { // Income Tax
                income_tax_payment(&players[current_player], *game_status, board);

            } else if (players[current_player].place == 7 || players[current_player].place == 22 || players[current_player].place == 36) { // National Event Card
                national_event_card_draw(&players[current_player], board, national_events, game_status);
                
            } else if (players[current_player].place == 17 || players[current_player].place == 33) { // Insurance
                check_for_insurance_action(&players[current_player], board[players[current_player].place], board);
                
            } else if (players[current_player].place == 30) { // Jail square
                check_for_jailed(&players[current_player]);

            } else if (players[current_player].place == 38) { // Bank square
                check_for_bank_action(&players[current_player], board, *game_status);

            } 
        }

        if (round_done) {
            // tasks happening at every round
            game_status->rounds++;
            for (int i = 0; i < NO_OF_PLAYERS; i++) {
                round_tracker[i] = 0;
            }

            if (game_status->rounds == MAX_ROUNDS) {
                break;
            }

            check_for_insurance_status(board);
            building_depreciation(board);

            if (game_status->rounds % 5 == 0) {
                property_depreciation(board);
            } 
            if (game_status->rounds % 10 == 0) {
                inflation(board, game_status);
                dynamic_property_market(property_groups, game_status);
            }

            print_game(*game_status, players, board, game_over, national_events);
        }

        current_player++;
        current_player %= NO_OF_PLAYERS;
    } 
}