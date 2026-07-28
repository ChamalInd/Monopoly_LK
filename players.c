// Player decision-making algorithms
#include "functions.h"

void initialize_players(Player players[]) {
    char *player_names[] = {"Aggressive Investor", "Conservative Banker", "Risk Taker", "Opportunistic Trader"};
    int plays[] = {AGGRESSIVE_INVESTOR, CONSERVATIVE_BANKER, RISK_TAKER, OPPORTUNISTIC_TRADER};

    for (int i = 0; i < NO_OF_PLAYERS; i++) {
        players[i] = (Player) {
            .name = player_names[i],
            .id = plays[i],
            .isBankrupt = FALSE,
            .jail_status = (Jail) {FALSE, 0},
            .loan_status = (Loan) {0, 0, 0, 2}, // 2 is a demo number
            .play_order = 5, // set as 5 for sorting process when deciding the player order
            .die_roll = NONE,
            .cash = 30000,
            .place = 0
        };
    }
}

void print_player(Player players[]) {
    for (int i = 0; i < NO_OF_PLAYERS; i++) {
        printf("Name: %s\nID: %i\nPlay Order: %i\nCash: %i\nPlace: %i\n", players[i].name, players[i].id, players[i].play_order, players[i].cash, players[i].place);
        printf("\n\n");
    }
}

Status calculate_player_status(Player player, Cell board[]) {
    int properties = 0, railways = 0, utilities = 0, hotels = 0, net_worth = 0, unmortgaged_properties = 0, total_property_value = 0;
    // Net worth = cash + property value + building value + railway value + utility value + insurance claims receivables - outstanding loans - accrued interest - taxes due

    net_worth += player.cash;

    for (int i = 0; i < NO_OF_CELLS; i++) {
        if (board[i].owner == player.id && board[i].type == PROPERTY) {
            if (board[i].mortgage.status == UNMORTGAGED) {
                unmortgaged_properties++;
            }
            total_property_value += board[i].value.market_price;
            hotels += board[i].buildings.no_of_hotels;
            net_worth += board[i].value.market_price;
            net_worth += board[i].buildings.building_value;

            properties++;
        } else if (board[i].owner == player.id && board[i].type == RAILWAY) {
            if (board[i].mortgage.status == UNMORTGAGED) {
                unmortgaged_properties++;
            }
            net_worth += board[i].value.market_price;
            railways++;
        } else if (board[i].owner == player.id && board[i].type == UTILITY) {
            if (board[i].mortgage.status == UNMORTGAGED) {
                unmortgaged_properties++;
            }
            net_worth += board[i].value.market_price;
            utilities++;
        }
    }

    net_worth -= player.loan_status.total_payable;

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

void check_for_jailed(Player *player, Cell board[]) {
    if (player->jail_status.isJailed == FALSE) {
        player->jail_status.isJailed = TRUE;
        player->jail_status.no_of_rounds = 0;
        printf("%s is in Jail.\n%s moves from Square %i to 11.\n\n", player->name, player->name, player->place + 1);

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

void check_for_bankruptcy(Player *player, Cell board[]) {
    Status player_status = calculate_player_status(*player, board);
    if (player_status.net_worth < 0 && player->isBankrupt == FALSE) {
        player->isBankrupt = TRUE;
        announce_bankruptcy(player, board);
    } 
}

void announce_bankruptcy(Player *player, Cell board[]) {
    if (player->isBankrupt == TRUE) {
        player->place = 0;

        for (int i = 0; i < NO_OF_CELLS; i++) {
            if (board[i].owner == player->id && board[i].type == PROPERTY) {
                board[i].mortgage.status = UNMORTGAGED;
                board[i].owner = BANK_OF_CEYLON;
                board[i].ownerptr = NULL;
                board[i].buildings.building_value = 0;
                board[i].buildings.no_of_hotels = 0;
                board[i].buildings.no_of_houses = 0;
            } else if (board[i].owner == player->id && (board[i].type == UTILITY || board[i].type == RAILWAY)) {
                board[i].mortgage.status = UNMORTGAGED;
                board[i].owner = BANK_OF_CEYLON;
                board[i].ownerptr = NULL;
            }
        }

        Player current_players[NO_OF_PLAYERS];

        printf("%s has been declared bankrupt.\n", player->name);
        printf("Remaining assets transferred to the Bank.\n\n");
    }
}

void check_for_bank_action(Player *player, Cell board[]) {
    printf("%s Landed on Bank of Ceylon.\n", player->name);
    if (player->loan_status.no_of_loans == 0) {
        obtain_loan(player, board);
    } else {
        int choice = rand() % 4;
        if (choice == 0) {
            repay_part_of_loan(player, board);
        } else if (choice == 1) {
            repay_full_loan(player, board);
        } else if (choice == 2) {
            extend_loan(player);
        } else {
            increase_loan(player, board);
        }
    }
}

void buy(Player players[], Player *player, Cell *place) {
    int choice = rand() % 2;
    if (choice == 0) {
        if (place->owner == BANK_OF_CEYLON && player->cash >= place->value.market_price) {
            place->owner = player->id;
            place->ownerptr = player;

            printf("%s purchased %s for LKR %i.\n", player->name, place->name, place->value.market_price);
            player->cash -= place->value.market_price;
            printf("Remaining Balance : LKR %i.\n\n", player->cash);
        }
    } else {
        auction(players, place);
    }
}

void auction(Player players[], Cell *place) {
    int starting_price = 0, bidding_players = 0;

    if (place->value.market_price / 2 < place->value.purchase_price) {
        starting_price = place->value.purchase_price;
    } else {
        starting_price = place->value.market_price / 2;
    }

    for (int i = 0; i < NO_OF_PLAYERS; i++) {
        if (players[i].isBankrupt == FALSE) {
            bidding_players++;
        }
    }

    printf("Auction Started.\n");
    printf("Property :\n\t%s\n", place->name);
    printf("Opening Bid : \n\tLKR %i.\n\n", starting_price);

    int highest_bid = starting_price, withdrawn_count = 0, can_bid = FALSE, bidder = NONE, bid_round = 0;
    int withdrawn[bidding_players];

    while (TRUE) {
        for (int i = 0; i < NO_OF_PLAYERS; i++) {
            can_bid = TRUE;
            for (int j = 0; j < withdrawn_count; j++) {
                if (withdrawn[j] == players[i].id) {
                    can_bid = FALSE;
                    break;
                }
            }
            if (players[i].cash >= highest_bid + 250) {
                if (can_bid && players[i].isBankrupt == FALSE) {
                    int choice = rand() % 2;
                    if (choice == 0) {
                        highest_bid += 250;
                        bidder = i;
                        printf("%s bids LKR %i.\n", players[i].name, highest_bid);
                    } else {
                        withdrawn[withdrawn_count] = players[i].id;
                        withdrawn_count++;
                        printf("%s withdraws.\n", players[i].name);
                    }
                }
            } else if (players[i].isBankrupt == FALSE) {
                withdrawn[withdrawn_count] = players[i].id;
                withdrawn_count++;
                printf("%s withdraws.\n", players[i].name);
            }
            if ((withdrawn_count == bidding_players) || (withdrawn_count >= (bidding_players - 1)) && bid_round >= 1 ) {
                break;
            }
        }
        printf("\n");
        bid_round++;

        if ((withdrawn_count == bidding_players) || (withdrawn_count >= (bidding_players - 1)) && bid_round >= 1 ) {
            break;
        }
    }

    if (bidder != NONE) {
        place->owner = players[bidder].id;
        place->ownerptr = &players[bidder];
        players[bidder].cash -= highest_bid;

        printf("%s wins the auction.\n", players[bidder].name);
        printf("%s purchased %s for LKR %i.\n", players[bidder].name, place->name, highest_bid);
        printf("Remaining Balance : LKR %i.\n\n", players[bidder].cash);

    } else {
        printf("No bidder property goes back to bank.\n\n");
    }
}

void rent(Player *player, Cell *place, Cell board[]) {
    if (place->owner != player->id && place->owner > 0) {
        int rent = 0;
        Status owner_status = calculate_player_status(*place->ownerptr, board);
        Status player_status = calculate_player_status(*place->ownerptr, board);
        
        if (place->type == PROPERTY) {
            int house_rent_multiplier[] = {2, 3, 5, 7};

            if (place->buildings.no_of_houses != 0) {
                rent = place->value.base_rent * house_rent_multiplier[place->buildings.no_of_houses];

            } else if (place->buildings.no_of_hotels != 0) {
                rent = place->value.base_rent * 10;

            } else {
                rent = place->value.base_rent;

            }

        } else if (place->type == RAILWAY) {
            int rent_values[] = {250, 500, 1000, 2000};
            rent = rent_values[owner_status.total_railways - 1];

        } else if (place->type == UTILITY) {
            int rent_values[] = {4 * player->die_roll, 10 * player->die_roll};
            rent = rent_values[owner_status.total_utilities - 1];
        }

        printf("%s landed on %s.\n", player->name, place->name);
        
        if (player->cash < 0 || (player->cash - rent) < 0) {
            player->isBankrupt = TRUE;
            printf("%s do not have enough cash to pay rent.\n", player->name);
            printf("Available Balance : LKR %i.\nRequired Amount : LKR %i\n\n", player->cash, rent);
            announce_bankruptcy(player, board);
            return;
        }   
        
        player->cash -= rent;
        place->ownerptr->cash += rent;

        printf("Rent Paid : LKR %i.\n", rent);
        printf("Owner : %s.\n\n", place->ownerptr->name); 
    } 
}

void constructions(Player *player, Cell *place, Cell *property_groups[][3]) {
    if (place->owner == player->id && place->group != NO_COLOR) {
        for (int j = 0; j < 3; j++) {
            if (property_groups[place->group][j] == NULL) {
                continue;
            }
            if (property_groups[place->group][j]->owner != player->id) {
                return;
            }
        }
        if (place->buildings.no_of_houses < 4 && place->buildings.no_of_hotels == 0 && player->cash >= place->buildings.price_of_house) {
            for (int i = 0; i < 3; i++) {
                if (property_groups[place->group][i] == NULL) {
                    continue;
                }
                if (place->buildings.no_of_houses > (property_groups[place->group][i]->buildings.no_of_houses + 2) && property_groups[place->group][i]->buildings.no_of_hotels == 0) {
                    return;
                }
            }
            place->buildings.no_of_houses++;
            player->cash -= place->buildings.price_of_house;
            place->buildings.building_value = place->buildings.price_of_house * place->buildings.no_of_houses;
            printf("%s constructed one house on %s.\n", player->name, place->name);
            printf("Construction cost : LKR %i.\n\n", place->buildings.price_of_house);
        }
        if (place->buildings.no_of_houses == 4 && player->cash >= place->buildings.price_of_hotel) {
            place->buildings.no_of_houses = 0;
            place->buildings.no_of_hotels++;
            player->cash -= place->buildings.price_of_hotel;
            place->buildings.building_value = place->buildings.price_of_hotel * place->buildings.no_of_hotels;
            printf("%s upgraded %s to a Hotel.\n\n", player->name, place->name);
        }
    }
}
