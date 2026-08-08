// Helper functions
#include "functions.h"

int round_off(double num) {
    if ((num - (int) num) >= 0.5) {
        return (int) num + 1;
    } else {
        return (int) num;
    }
}

void destroy_property(Cell *place) {
    place->mortgage.status = UNMORTGAGED;
    place->owner = BANK_OF_CEYLON;
    place->value.building_value = 0;
    place->ownerptr = NULL;
    place->insurance = (Insurance) {NO_INSURANCE, NONE, 0};
    place->depreciation = (Depreciation) {0, 0};
    place->buildings.no_of_hotels = 0;
    place->buildings.no_of_houses = 0;
    place->buildings.condition = 100;
    place->buildings.rent_reduction_rate = 0;
    place->buildings.age = 0;
    place->buildings.has_damaged = FALSE;
}

void unmortgage_property(Cell board[], Player player) {
    for (int i = 0; i < NO_OF_CELLS; i++) {
        if (board[i].owner == player.id && board[i].mortgage.status == MORTGAGED) {
            board[i].mortgage.status = UNMORTGAGED;
        }
    }
}


int dice_roll(void) {
    int die_1 = (rand() % 6) + 1;
    int die_2 = (rand() % 6) + 1;
    return die_1 + die_2;
}

int decide_winner(Player players[], Cell board[]) {
    int winner_id = NONE, non_bankrupt_count = 0, max_net_worth = NONE;
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

void check_for_jailed(Player *player) {
    if (player->jail_status.isJailed == FALSE) {
        player->jail_status.isJailed = TRUE;
        player->jail_status.no_of_rounds = 0;
        printf("%s is in Jail.\n%s moves from Square %i to Square 11.\n\n", player->name, player->name, player->place + 1);

        player->place = 10;

    } else if (player->jail_status.isJailed == TRUE) {
        player->jail_status.no_of_rounds++;

        if (player->jail_status.no_of_rounds == 3) {
            player->jail_status.isJailed = FALSE;
            player->jail_status.no_of_rounds = 0;
            printf("%s got out of Jail after spending 3 turns idle.\n\n", player->name);

        } else {
            int choice = rand() % 3;
            if (choice == 0 && player->cash >= 300) {
                player->cash -= 300;
                player->jail_status.isJailed = FALSE;
                player->jail_status.no_of_rounds = 0;
                printf("%s got out of Jail by paying bail of LKR 300.\n\n", player->name);
            } else if (choice == 1) {
                int die_1 = (rand() % 6) + 1;
                int die_2 = (rand() % 6) + 1;
                if (die_1 == die_2) {
                    player->jail_status.isJailed = FALSE;
                    player->jail_status.no_of_rounds = 0;
                    printf("%s got out of Jail by rolling doubles.\n\n", player->name);
                }
            }
        }
    }
}

void check_for_bankruptcy(Player players[], Cell board[], Game game_status, int player) {
    Status player_status = calculate_player_status(players[player], board);
    
    if (players[player].isBankrupt == FALSE && player_status.net_worth <= 0) {
        players[player].isBankrupt = TRUE;
        announce_bankruptcy(players, board, game_status, player);
    } 
}

void announce_bankruptcy(Player players[], Cell board[], Game game_status, int player) {
    players[player].place = 0;
    players[player].cash = 0;
    players[player].loan_status.total_payable = 0;
    printf("%s has been declared bankrupt.\n", players[player].name);
    printf("Remaining assets transferred to the Bank.\n\n");

    for (int i = 0; i < 20; i++) {
        players[player].events[i].remaining_effect = 0;
    }

    for (int i = 0; i < NO_OF_CELLS; i++) {
        if (board[i].owner == players[player].id) {
            destroy_property(&board[i]);
            auction(players, board, &board[i], BANK_OF_CEYLON, game_status);
        }
    }
}

Status calculate_player_status(Player player, Cell board[]) {
    int properties = 0, railways = 0, utilities = 0, hotels = 0, net_worth = 0, unmortgaged_properties = 0, total_property_value = 0, assets = 0, liabilities = 0;
    // Net worth = cash + property value + building value + railway value + utility value + insurance claims receivables - outstanding loans - accrued interest - taxes due

    assets += player.cash;

    for (int i = 0; i < NO_OF_CELLS; i++) {
        if (board[i].owner == player.id) {
            switch (board[i].type) {
                case PROPERTY : {
                    hotels += board[i].buildings.no_of_hotels;
                    assets += board[i].value.building_value;
                    properties++;
                    break;
                }
                case RAILWAY : {
                    railways++;
                    break;
                } 
                case UTILITY : {
                    utilities++;
                    break;
                }
                default : {
                    continue;
                }
            }

            if (board[i].mortgage.status == UNMORTGAGED) {
                unmortgaged_properties++;
            }
            total_property_value += board[i].value.market_price;
            assets += board[i].value.market_price;
        }
    }

    liabilities += player.loan_status.total_payable;
    liabilities += player.taxes_due;

    net_worth = assets - liabilities;

    Status status = (Status) {
        .total_properties = properties,
        .total_property_value = total_property_value,
        .total_railways = railways,
        .total_utilities = utilities,
        .unmortgaged_properties = unmortgaged_properties,
        .hotels_built = hotels,
        .net_worth = net_worth
    };

    return status;
}