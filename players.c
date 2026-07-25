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
            .die_roll = NONE,
            .cash = 30000,
            .place = 0,
            .properties = {
                {NONE, NONE, NONE},
                {NONE, NONE, NONE},
                {NONE, NONE, NONE},
                {NONE, NONE, NONE},
                {NONE, NONE, NONE},
                {NONE, NONE, NONE},
                {NONE, NONE, NONE},
                {NONE, NONE, NONE}
            },
            .property_owned = {0, 0, 0, 0, 0, 0, 0, 0},
            .railways = {NONE, NONE, NONE, NONE},
            .railway_owned = 0,
            .utilities = {NONE, NONE},
            .utilities_owned = 0
        };
    }
}

void print_player(Player players[]) {
    for (int i = 0; i < NO_OF_PLAYERS; i++) {
        printf("Name: %s\nID: %i\nPlay Order: %i\nCash: %i\nPlace: %i\n", players[i].name, players[i].id, players[i].play_order, players[i].cash, players[i].place);
        printf("Properties: ");
        for (int x = 0; x < 8; x++) {
            printf("\n%i\t", x);
            for (int y = 0; y < 3; y++) {
                printf("%i\t", players[i].properties[x][y]);
            }
        }
        printf("\nRailways: ");
        for (int x = 0; x < 4; x++) {
            printf("%i\t", players[i].railways[x]);
        }
        printf("\nUtilities: ");
        for (int x = 0; x < 2; x++) {
            printf("%i\t", players[i].utilities[x]);
        }
        printf("\n\n");
    }
}

void buy(Player *player, Cell *place) {
    if (place->owner == BANK_OF_CEYLON && player->cash >= place->value.market_price) {
        place->owner = player->id;

        char price[20], cash[20];
        format_cash_value(place->value.market_price, price);
        format_cash_value(player->cash, cash);

        printf("%s purchased %s for LKR %s.\n", player->name, place->name, price);
        player->cash -= place->value.market_price;
        printf("Remaining Balance : LKR %s.\n\n", cash);
        
        if (place->type == PROPERTY) { 
            player->properties[place->group][player->property_owned[place->group]] = player->place;
            player->property_owned[place->group]++;
        } else if (place->type == RAILWAY) {
            player->railways[player->railway_owned] = player->place;
            player->railway_owned++;
        } else if (place->type == UTILITY) {
            player->utilities[player->utilities_owned] = player->place;
            player->utilities_owned++;
        }
    }
}

void rent(Player players[], int player, Cell *place) {
    if (place->owner != players[player].id) {

    }
}