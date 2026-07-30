// Economic events and government regulations
#include "functions.h"

void property_depreciation(Cell board[]) {
    for (int i = 0; i < NO_OF_CELLS; i++) {
        if (board[i].type == PROPERTY && board[i].owner != NO_OWNER && board[i].owner != BANK_OF_CEYLON) {
            board[i].depreciation.age++;

            if (board[i].depreciation.age >= 50 && board[i].depreciation.percentage < MAX_DEPRECIATION) {
                board[i].depreciation.percentage++;
                board[i].value.market_price -= (int) ((float) board[i].value.market_price * (1.0 / 100.0));

                printf("%s has depreciated by 1%%.\n", board[i].name);
                printf("Current Value : LKR %i.\n\n", board[i].value.market_price);
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