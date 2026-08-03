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
            .events_own = 0,
            .play_order = 5, // set as 5 for sorting process when deciding the player order
            .die_roll = NONE,
            .cash = STARTUP_CASH,
            .taxes_due = 0,
            .place = 0
        };

        for (int j = 0; j < 20; j++) {
            players[i].events[j] = (National_Events) {j, 0};
        }
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
            net_worth += board[i].value.building_value;

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
    net_worth -= player.taxes_due;

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

void check_for_bankruptcy(Player *player, Cell board[], Player players[], Game game_status) {
    Status player_status = calculate_player_status(*player, board);
    if (player_status.net_worth < 0 && player->isBankrupt == FALSE) {
        player->isBankrupt = TRUE;
        announce_bankruptcy(player, board, players, game_status);
    } 
}

void announce_bankruptcy(Player *player, Cell board[], Player players[], Game game_status) {
    if (player->isBankrupt == TRUE) {
        player->place = 0;
        printf("%s has been declared bankrupt.\n", player->name);
        printf("Remaining assets transferred to the Bank.\n\n");

        for (int i = 0; i < NO_OF_CELLS; i++) {
            if (board[i].owner == player->id) {
                destroy_property(&board[i]);
                auction(players, &board[i], BANK_OF_CEYLON, game_status);
            }
        }
    }
}

void check_for_bank_action(Player *player, Cell board[], Game game_status) {
    printf("%s Landed on Bank of Ceylon.\n", player->name);
    if (player->loan_status.no_of_loans == 0) {
        obtain_loan(player, board, game_status);
    } else {
        int choice = rand() % 4;
        if (choice == 0) {
            repay_part_of_loan(player, board);
        } else if (choice == 1) {
            repay_full_loan(player, board);
        } else if (choice == 2) {
            extend_loan(player);
        } else {
            increase_loan(player, board, game_status);
        }
    }
}

void check_for_insurance_action(Player *player, Cell place, Cell board[]) {
    printf("%s landed on %s.\n", player->name, place.name);

    int insurance_company = place.type;
    Status player_status = calculate_player_status(*player, board);

    if (player_status.total_properties > 0) {
        int non_insured_properties[player_status.total_properties];
        Cell *policy_near_expiry[player_status.total_properties];
        int total_non_insured_properties = 0;
        int total_policy_near_expiry = 0;

        for (int i = 0; i < NO_OF_CELLS; i++) {
            if (board[i].owner == player->id && board[i].type == PROPERTY && board[i].insurance.policy == NO_INSURANCE) {
                non_insured_properties[total_non_insured_properties] = i;
                total_non_insured_properties++;
            } else if (board[i].owner == player->id && board[i].type == PROPERTY && board[i].insurance.policy != NO_INSURANCE && board[i].insurance.duration < 3 && board[i].insurance.provider == insurance_company) {
                policy_near_expiry[total_policy_near_expiry] = &board[i];
                total_policy_near_expiry++;
            }
        }

        if (total_non_insured_properties > 0) {
            int property = rand() % total_non_insured_properties;
            obtain_insurance(player, &board[non_insured_properties[property]], insurance_company);
        } 
        if (total_policy_near_expiry > 0) {
            renew_insurance(player, policy_near_expiry, total_policy_near_expiry);
        }
    } else {
        printf("No properties to be insured.\n\n");
    }
}

void buy(Player players[], Player *player, Cell *place, Game game_status) {
    if (place->owner == BANK_OF_CEYLON) {
        int choice = rand() % 2;
        if (choice == 0) {
            if (player->cash >= place->value.market_price) {
                place->owner = player->id;
                place->ownerptr = player;

                printf("%s purchased %s for LKR %i.\n", player->name, place->name, place->value.market_price);
                player->cash -= place->value.market_price;
                printf("Remaining Balance : LKR %i.\n\n", player->cash);
            }
        } else {
            auction(players, place, BANK_OF_CEYLON, game_status);
        }
    }
}

int auction(Player players[], Cell *place, Ownership beneficiary, Game game_status) {
    int starting_price = 0, bidding_players = 0;

    if (place->value.market_price / 2 < place->value.base_price) {
        starting_price = place->value.base_price;
    } else {
        starting_price = place->value.market_price / 2;
    }

    if (game_status.dynamic_market.event == MARKET_DECLINE) {
        if ((starting_price * 75.0 / 100.0) > place->value.base_price) {
            starting_price = (int) ((float) starting_price * 75.0 / 100.0);
        }
    }

    for (int i = 0; i < NO_OF_PLAYERS; i++) {
        if (players[i].isBankrupt == FALSE && players[i].id != beneficiary) {
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
                if (withdrawn[j] == players[i].id ) {
                    can_bid = FALSE;
                    break;
                }
            }
            if (players[i].cash >= highest_bid + 250 && players[i].id != beneficiary) {
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
            } else if (players[i].isBankrupt == FALSE && players[i].id != beneficiary) {
                withdrawn[withdrawn_count] = players[i].id;
                withdrawn_count++;
                printf("%s withdraws.\n", players[i].name);
            }
        }
        printf("\n");
        bid_round++;

        if (((withdrawn_count == bidding_players) || (withdrawn_count >= (bidding_players - 1))) && bid_round >= 1 ) {
            break;
        }
    }

    if (bidder != NONE) {
        if (beneficiary != BANK_OF_CEYLON) {
            for (int i = 0; i < NO_OF_PLAYERS; i++) {
                if (players[i].id == beneficiary) {
                    players[i].cash += highest_bid;
                    destroy_property(place);
                    printf("%s sold %s for LKR %i in the auction.\n", players[i].name, place->name, highest_bid);
                    printf("Cash Balance : LKR %i.\n\n", players[i].cash);
                    break;
                }
            }
        }

        place->owner = players[bidder].id;
        place->ownerptr = &players[bidder];
        players[bidder].cash -= highest_bid;

        printf("%s wins the auction.\n", players[bidder].name);
        printf("%s purchased %s for LKR %i.\n", players[bidder].name, place->name, highest_bid);
        printf("Remaining Balance : LKR %i.\n\n", players[bidder].cash);

        return TRUE;

    } else {
        if (beneficiary == BANK_OF_CEYLON) {
            printf("No bidder property goes back to bank.\n\n");
        } else {
            printf("No bidder property goes back to owner.\n\n");
        }

        return FALSE;
    }
}

void rent(Player players[], Player *player, Cell *place, Cell board[], Game game_status) {
    if (place->owner != player->id && place->owner > 0) {
        int rent = 0;
        Status owner_status = calculate_player_status(*place->ownerptr, board);
        Status player_status = calculate_player_status(*player, board);
        
        if (place->type == PROPERTY) {
            int house_rent_multiplier[] = {2, 3, 5, 7};

            if (place->buildings.no_of_houses != 0) {
                rent = place->value.base_rent * house_rent_multiplier[place->buildings.no_of_houses - 1];

            } else if (place->buildings.no_of_hotels != 0) {
                rent = place->value.base_rent * 10;

            } else {
                rent = place->value.base_rent;

            }

            // additional calculation for building depreciation
            if (place->buildings.has_damaged == TRUE) {
                rent = 0;
            } else if (place->buildings.age >= 20) {
                rent -= (int) ((float) rent * (25.0 / 100.0));
            } else {
                rent -= (int) ((float) rent * (place->buildings.rent_reduction_rate / 100.0));
            }

        } else if (place->type == RAILWAY) {
            int rent_values[] = {250, 500, 1000, 2000};
            rent = rent_values[owner_status.total_railways - 1];

        } else if (place->type == UTILITY) {
            int rent_values[] = {4 * player->die_roll, 10 * player->die_roll};
            rent = rent_values[owner_status.total_utilities - 1];
        }
        
        // if low on cash sell property to pay rent
        if ((player->cash < 0 || (player->cash - rent) < 0)) {
            printf("%s do not have enough cash to pay rent.\n", player->name);
            printf("Cash Balance : LKR %i.\nRequired Amount : LKR %i\n\n", player->cash, rent);

            if (player_status.total_property_value >= rent) {
                int prev_property = 0;
                while (TRUE) {
                    Cell *temp = NULL;
                    for (int i = 0; i < NO_OF_CELLS; i++) {
                        if ((prev_property != i) && (board[i].owner == player->id) && (board[i].mortgage.status == UNMORTGAGED) && (board[i].type == PROPERTY)) {
                            temp = &board[i];
                            prev_property = i;
                            break;
                        } 
                    }
                    if (temp != NULL) {
                        printf("%s decided to sell a property.\n\n", player->name);
                        int result = auction(players, temp, player->id, game_status);
                        if (result == TRUE && player->cash >= rent) {
                            break;
                        } 
                    } else { // declared bankrupt if failed to sell property
                        player->isBankrupt = TRUE;
                        announce_bankruptcy(player, board, players, game_status);
                        return; 
                    }
                }
            } else { // not enough property so declared bankrupt
                player->isBankrupt = TRUE;
                announce_bankruptcy(player, board, players, game_status);
                return;
            }
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
        if (place->buildings.no_of_houses < 4 && place->buildings.no_of_hotels == 0 && player->cash >= place->value.house_construction_cost) {
            for (int i = 0; i < 3; i++) {
                if (property_groups[place->group][i] == NULL) {
                    continue;
                }
                if (place->buildings.no_of_houses > (property_groups[place->group][i]->buildings.no_of_houses + 1) && property_groups[place->group][i]->buildings.no_of_hotels == 0) {
                    return;
                }
            }
            place->buildings.no_of_houses++;
            place->value.building_value = place->value.house_construction_cost * place->buildings.no_of_houses;
            player->cash -= place->value.house_construction_cost;

            printf("%s constructed one house on %s.\n", player->name, place->name);
            printf("Construction cost : LKR %i.\n\n", place->value.house_construction_cost);
        }
        if (place->buildings.no_of_houses == 4 && player->cash >= place->value.hotel_construction_cost) {
            place->buildings.no_of_houses = 0;
            place->buildings.no_of_hotels++;
            place->value.building_value = place->value.hotel_construction_cost;
            player->cash -= place->value.hotel_construction_cost;

            place->buildings.age = 0;
            place->buildings.condition = 100;
            place->buildings.has_damaged = FALSE;
            place->buildings.rent_reduction_rate = 0;

            printf("%s upgraded houses in %s to a Hotel.\n", player->name, place->name);
            printf("Upgrade cost : LKR %i.\n\n", place->value.hotel_construction_cost);
        }
    }
}

void property_renovations(Player *player, Cell *place) {
    if (place->owner == player->id && place->depreciation.age >= 50) {
        float renovation_cost = (float) place->value.current_market_price * (10.0 / 100.0);
        if (player->cash >= (int) renovation_cost) {
            player->cash -= (int) renovation_cost;
            place->depreciation.age = 0;
            place->depreciation.percentage = 0;
            place->value.market_price = place->value.current_market_price;

            printf("%s renovated %s for LKR %i.\n", player->name, place->name, (int) renovation_cost);
            printf("Remaining Balance : LKR %i.\n\n", player->cash);
        }
    }
}

void building_renovations(Player *player, Cell board[]) {
    for (int i = 0; i < NO_OF_CELLS; i++) {
        if (board[i].owner == player->id && (board[i].buildings.no_of_houses + board[i].buildings.no_of_hotels) > 0 && board[i].buildings.age > 0) {
            float maintenance_cost = 0.0f;

            if (board[i].buildings.no_of_hotels > 0) {
                if (board[i].buildings.age >= 20) {
                    maintenance_cost = (float) (board[i].value.hotel_construction_cost * (8.0 / 100.0)) * (50.0 / 100);
                } else {
                    maintenance_cost = (float) board[i].value.hotel_construction_cost * (8.0 / 100.0);
                }
            } else {
                if (board[i].buildings.age >= 20) {
                    maintenance_cost = (float) (board[i].value.house_construction_cost * (5.0 / 100.0)) * (50.0 / 100);
                } else {
                    maintenance_cost = (float) board[i].value.house_construction_cost * (5.0 / 100.0);
                }
                
            }

            if (player->cash >= (int) maintenance_cost) {
                player->cash -= (int) maintenance_cost;
                board[i].buildings.age = 0;
                board[i].buildings.condition = 100;
                board[i].buildings.has_damaged = FALSE;
                board[i].buildings.rent_reduction_rate = 0;
                printf("%s renovated buildings in %s for LKR %i.\n", player->name, board[i].name, (int) maintenance_cost);
                printf("Remaining Balance : LKR %i.\n\n", player->cash);
            }
        }
    }
}