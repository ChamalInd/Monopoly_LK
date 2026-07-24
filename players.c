// Player decision-making algorithms
#include "functions.h"

void initialize_players(Player players[]) {
    char *player_names[] = {"Aggressive Investor", "Conservative Banker", "Risk Taker", "Opportunistic Trader"};
    int plays[] = {AGGRESSIVE_INVESTOR, CONSERVATIVE_BANKER, RISK_TAKER, OPPORTUNISTIC_TRADER};

    for (int i = 0; i < NO_OF_PLAYERS; i++) {
        players[i] = (Player) {
            .name = player_names[i],
            .id = plays[i],
            .play_order = 5, // set as 5 for sorting process when deciding the player order
            .die_roll = 0,
            .cash = 30000,
            .place = 0,
            .properties = {
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0}
            },
            .property_owned = {0, 0, 0, 0, 0, 0, 0, 0},
            .railways = {0, 0, 0, 0},
            .railway_owned = 0,
            .utilities = {0, 0},
            .utilities_owned = 0
        };
    }
}

void buy(Player *player, Cell *place) {
    if (place->owner == BANK_OF_CEYLON && player->cash >= place->value.market_price) {
        place->owner = player->id;
        printf("%s purchased %s for LKR %i.\n", player->name, place->name, place->value.market_price);
        player->cash -= place->value.market_price;
        printf("Remaining Balance : LKR %i.\n\n", player->cash);
        if (place->type == PROPERTY) { 
            player->properties[place->group][player->property_owned[place->group]] = player->place;
        } else if (place->type == RAILWAY) {
            player->railways[player->railway_owned] = player->place;
        } else if (place->type == UTILITY) {
            player->utilities[player->utilities_owned] = player->place;
        }
    }
}

void rent(Player players[], int player, Cell place) {
    if (place.owner != players[player].id) {

    }
}