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

            if (board[i].type == PROPERTY) {
                board[i].value.hotel_construction_cost = (int) (board[i].value.hotel_construction_cost * inflation_value);
                board[i].value.house_construction_cost = (int) (board[i].value.house_construction_cost * inflation_value);
                board[i].value.building_value = (int) (board[i].value.building_value * inflation_value);
            }
        }
    }
}

// void dynamic_property_market(Cell *property_groups[][3], int selected_property_market) {
//     if (selected_property_market == NONE) {
//         selected_property_market = rand() % 8;
//     } else {
//         int new_market = NONE;
//         while (selected_property_market != new_market) {
//             new_market = rand() % 8;
//         }
//         selected_property_market = new_market;
//     }

//     int event = rand() % 2;
//     if (event == 0) {
//         for (int i = 0; i < 3; i++) {
//             if (property_groups[selected_property_market][i] != NULL) {
//                 property_groups[selected_property_market][i]->value.market_price += (int) ((float) property_groups[selected_property_market][i]->value.market_price * (15.0 / 100.0));
//                 property_groups[selected_property_market][i]->value.current_market_price += (int) ((float) property_groups[selected_property_market][i]->value.current_market_price * (15.0 / 100.0));
//                 property_groups[selected_property_market][i]->mortgage.value += (int) ((float) property_groups[selected_property_market][i]->mortgage.value * (15.0 / 100.0));
//                 property_groups[selected_property_market][i]->value.base_rent += (int) ((float) property_groups[selected_property_market][i]->value.base_rent * (25.0 / 100.0));
//                 property_groups[selected_property_market][i]->buildings.price_of_house += (int) ((float) property_groups[selected_property_market][i]->buildings.price_of_house * (10.0 / 100.0));
//                 property_groups[selected_property_market][i]->buildings.price_of_hotel += (int) ((float) property_groups[selected_property_market][i]->buildings.price_of_hotel * (10.0 / 100.0));
//             }
//         }
//     }
// }