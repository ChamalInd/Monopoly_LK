// Economic events and government regulations
#include "functions.h"

void property_depreciation(Cell board[]) {
    for (int i = 0; i < NO_OF_CELLS; i++) {
        if (board[i].type == PROPERTY && board[i].owner != NO_OWNER && board[i].owner != BANK_OF_CEYLON) {
            board[i].depreciation.age++;

            if (board[i].depreciation.age >= 50 && board[i].depreciation.percentage < MAX_DEPRECIATION) {
                board[i].depreciation.percentage++;
                board[i].value.market_price -= (int) ((float) board[i].value.market_price * (1.0 / 100.0));

                printf("%s has depreciated by %i%%.\n", board[i].name, board[i].depreciation.percentage);
                printf("Current Value : LKR %i.\n\n", board[i].value.market_price);
            }
        }
    }
}

void building_depreciation(Cell board[]) {
    for (int i = 0; i < NO_OF_CELLS; i++) {
        if (board[i].type == PROPERTY && board[i].owner != NO_OWNER && board[i].owner != BANK_OF_CEYLON) {
            if ((board[i].buildings.no_of_houses + board[i].buildings.no_of_hotels) > 0) {
                board[i].buildings.age++;

                if (board[i].buildings.condition != 0) {
                    board[i].buildings.condition -= 2;
                }

                if (board[i].buildings.condition > 90) {
                    board[i].buildings.rent_reduction_rate = 0;

                } else if (board[i].buildings.condition > 75) {
                    board[i].buildings.rent_reduction_rate = 10;

                } else if (board[i].buildings.condition > 50) {
                    board[i].buildings.rent_reduction_rate = 25;
                    
                } else if (board[i].buildings.condition > 25) {
                    board[i].buildings.rent_reduction_rate = 50;
                    
                } else {
                    board[i].buildings.rent_reduction_rate = NONE;
                    board[i].buildings.has_damaged = TRUE;
                }

            }
        }
    }
}

void inflation(Cell board[], Game *game_status) {
    int inflation_rates[] = {-3, 0, 2, 5, 8, 12};
    game_status->inflation_rate = inflation_rates[rand() % (sizeof(inflation_rates) / sizeof(int))];
    float inflation_value = 1.0 + ((float) game_status->inflation_rate / 100.0);
    game_status->interest_rate = game_status->interest_rate * inflation_value;

    for (int i = 0; i < NO_OF_CELLS; i++) {
        if (board[i].type == PROPERTY || board[i].type == RAILWAY || board[i].type == UTILITY) {
            board[i].value.market_price = (int) (board[i].value.market_price * inflation_value);
            board[i].value.current_market_price = (int) (board[i].value.current_market_price * inflation_value);
            board[i].value.base_rent = (int) (board[i].value.base_rent * inflation_value);

            if (board[i].type == PROPERTY) {
                board[i].value.hotel_construction_cost = (int) (board[i].value.hotel_construction_cost * inflation_value);
                board[i].value.house_construction_cost = (int) (board[i].value.house_construction_cost * inflation_value);
                board[i].value.building_value = (int) (board[i].value.building_value * inflation_value);
            }
        }
    }
}

void dynamic_property_market(Cell *property_groups[][3], Game *game_status) {
    if (game_status->dynamic_market.property_group == NONE) {
        game_status->dynamic_market.property_group = rand() % 8;

    } else {
        int new_market = NONE;

        while (TRUE) {
            new_market = rand() % 8;

            if (game_status->dynamic_market.property_group != new_market) {
                game_status->dynamic_market.property_group = new_market;
                break;
            }
        }
    }

    int event = rand() % 2;
    game_status->dynamic_market.event = event;

    if (event == MARKET_BOOM) {
        for (int i = 0; i < 3; i++) {
            if (property_groups[game_status->dynamic_market.property_group][i] != NULL) {
                property_groups[game_status->dynamic_market.property_group][i]->value.market_price += (int) ((float) property_groups[game_status->dynamic_market.property_group][i]->value.market_price * (15.0 / 100.0));
                property_groups[game_status->dynamic_market.property_group][i]->value.current_market_price += (int) ((float) property_groups[game_status->dynamic_market.property_group][i]->value.current_market_price * (15.0 / 100.0));
                property_groups[game_status->dynamic_market.property_group][i]->mortgage.value += (int) ((float) property_groups[game_status->dynamic_market.property_group][i]->mortgage.value * (15.0 / 100.0));
                property_groups[game_status->dynamic_market.property_group][i]->value.base_rent += (int) ((float) property_groups[game_status->dynamic_market.property_group][i]->value.base_rent * (25.0 / 100.0));
                property_groups[game_status->dynamic_market.property_group][i]->value.house_construction_cost += (int) ((float) property_groups[game_status->dynamic_market.property_group][i]->value.house_construction_cost * (10.0 / 100.0));
                property_groups[game_status->dynamic_market.property_group][i]->value.hotel_construction_cost += (int) ((float) property_groups[game_status->dynamic_market.property_group][i]->value.hotel_construction_cost * (10.0 / 100.0));
                property_groups[game_status->dynamic_market.property_group][i]->value.base_price += (int) ((float) property_groups[game_status->dynamic_market.property_group][i]->value.base_price * (20.0 / 100.0));
            }
        }
    } else {
        for (int i = 0; i < 3; i++) {
            if (property_groups[game_status->dynamic_market.property_group][i] != NULL) {
                property_groups[game_status->dynamic_market.property_group][i]->value.market_price -= (int) ((float) property_groups[game_status->dynamic_market.property_group][i]->value.market_price * (15.0 / 100.0));
                property_groups[game_status->dynamic_market.property_group][i]->value.current_market_price -= (int) ((float) property_groups[game_status->dynamic_market.property_group][i]->value.current_market_price * (15.0 / 100.0));
                property_groups[game_status->dynamic_market.property_group][i]->mortgage.value -= (int) ((float) property_groups[game_status->dynamic_market.property_group][i]->mortgage.value * (10.0 / 100.0));
                property_groups[game_status->dynamic_market.property_group][i]->value.base_rent -= (int) ((float) property_groups[game_status->dynamic_market.property_group][i]->value.base_rent * (20.0 / 100.0));
            }
        }
    }
}

void national_event_card_draw(Player players[], Cell board[], Events national_events[], Game *game_status) {
    printf("%s draws %s Card.\n", players[game_status->current_player].name, national_events[game_status->national_event_pointer].name);
    printf("%s.\n\n", national_events[game_status->national_event_pointer].event);

    switch (game_status->national_event_pointer) {
        case TOURISM_HYPE :
            players[game_status->current_player].events[game_status->national_event_pointer].remaining_effect = 5;
            break;
        case FUEL_SHORTAGE :
            players[game_status->current_player].events[game_status->national_event_pointer].remaining_effect = 5;
            break;
        case HEAVY_FLOODS :
            players[game_status->current_player].events[game_status->national_event_pointer].remaining_effect = 0;
            // to be implemented
            break;
        case POLITICAL_RALLY :
            players[game_status->current_player].events[game_status->national_event_pointer].remaining_effect = 2;
            break;
        case TAX_AMNESTY :
            players[game_status->current_player].events[game_status->national_event_pointer].remaining_effect = 0;
            for (int i = 0; i < NO_OF_PLAYERS; i++) {
                if (players[i].isBankrupt == FALSE) {
                    players[i].cash += 2000;
                }
            }
            break;
        case POWER_FAILURE :
            players[game_status->current_player].events[game_status->national_event_pointer].remaining_effect = 3;
            break;
        case LABOUR_STRIKE :
            players[game_status->current_player].events[game_status->national_event_pointer].remaining_effect = 2;
            break;
        default :
            players[game_status->current_player].events[game_status->national_event_pointer].remaining_effect = 15;
            break;
    }

    game_status->national_event_pointer++;
    game_status->national_event_pointer %= 20;
}

void national_event_card_expiry(Player *player) {
    for (int i = 0; i < 20; i++) {
        if (player->events[i].remaining_effect > 0) {
            player->events[i].remaining_effect--;
        }
    }
}