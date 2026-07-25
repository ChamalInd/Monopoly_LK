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

Status calculate_player_status(Player player, Cell *board) {
    int properties = 0, hotels = 0, net_worth = 0;
    for (int j = 0; j < 8; j++) {
        properties += player.property_owned[j];
        for (int k = 0; k < 3; k++) {
            if (player.properties[j][k] != NONE) {
                printf("%i ", player.properties[j][k]);
                hotels += board[player.properties[j][k]].buildings.no_of_hotels;
                net_worth += board[player.properties[j][k]].value.market_price;
                net_worth += board[player.properties[j][k]].buildings.building_value;
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        if (player.railways[i] != NONE) {
            printf("%i ", player.railways[i]);
            net_worth += board[player.railways[i]].value.market_price;
        }
    }

    for (int i = 0; i < 2; i++) {
        if (player.utilities[i] != NONE) {
            printf("%i ", player.utilities[i]);
            net_worth += board[player.utilities[i]].value.market_price;
        }
    }

    net_worth += player.cash;

    Status status = (Status) {
        .total_properties = properties,
        .hotels_built = hotels,
        .net_worth = net_worth
    };

    return status;
}

void buy(Player *player, Cell *place) {
    if (place->owner == BANK_OF_CEYLON && player->cash >= place->value.market_price) {
        place->owner = player->id;

        printf("%s purchased %s for LKR %i.\n", player->name, place->name, place->value.market_price);
        player->cash -= place->value.market_price;
        printf("Remaining Balance : LKR %i.\n\n", player->cash);

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