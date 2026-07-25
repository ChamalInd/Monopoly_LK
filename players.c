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
            .owned_properties = (Owned) {
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
            }
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
                printf("%i\t", players[i].owned_properties.properties[x][y]);
            }
        }
        printf("\nRailways: ");
        for (int x = 0; x < 4; x++) {
            printf("%i\t", players[i].owned_properties.railways[x]);
        }
        printf("\nUtilities: ");
        for (int x = 0; x < 2; x++) {
            printf("%i\t", players[i].owned_properties.utilities[x]);
        }
        printf("\n\n");
    }
}

Status calculate_player_status(Player player, Cell *board) {
    int properties = 0, hotels = 0, net_worth = 0;
    for (int j = 0; j < 8; j++) {
        properties += player.owned_properties.property_owned[j];
        for (int k = 0; k < 3; k++) {
            if (player.owned_properties.properties[j][k] != NONE) {
                hotels += board[player.owned_properties.properties[j][k]].buildings.no_of_hotels;
                net_worth += board[player.owned_properties.properties[j][k]].value.market_price;
                net_worth += board[player.owned_properties.properties[j][k]].buildings.building_value;
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        if (player.owned_properties.railways[i] != NONE) {
            net_worth += board[player.owned_properties.railways[i]].value.market_price;
        }
    }

    for (int i = 0; i < 2; i++) {
        if (player.owned_properties.utilities[i] != NONE) {
            net_worth += board[player.owned_properties.utilities[i]].value.market_price;
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
        place->ownerptr = player;

        printf("%s purchased %s for LKR %i.\n", player->name, place->name, place->value.market_price);
        player->cash -= place->value.market_price;
        printf("Remaining Balance : LKR %i.\n\n", player->cash);

        if (place->type == PROPERTY) { 
            player->owned_properties.properties[place->group][player->owned_properties.property_owned[place->group]] = player->place;
            player->owned_properties.property_owned[place->group]++;
        } else if (place->type == RAILWAY) {
            player->owned_properties.railways[player->owned_properties.railway_owned] = player->place;
            player->owned_properties.railway_owned++;
        } else if (place->type == UTILITY) {
            player->owned_properties.utilities[player->owned_properties.utilities_owned] = player->place;
            player->owned_properties.utilities_owned++;
        }
    }
}

void rent(Player *player, Cell *place) {
    if (place->owner != player->id && place->type == PROPERTY) {
        int rent = place->value.base_rent;

        player->cash -= rent;
        place->ownerptr->cash += rent;

        printf("%s landed on %s.\n", player->name, place->name);
        printf("Rent Paid : LKR %i.\n", rent);
        printf("Owner : %s.\n\n", place->ownerptr->name);        

    } else if (place->owner != player->id && place->type == RAILWAY) {
        int rent_values[] = {250, 500, 1000, 2000};
        int rent = rent_values[place->ownerptr->owned_properties.railway_owned - 1];
        
        player->cash -= rent;
        place->ownerptr->cash += rent;

        printf("%s landed on %s.\n", player->name, place->name);
        printf("Rent Paid : LKR %i.\n", rent);
        printf("Owner : %s.\n\n", place->ownerptr->name);
    } else if (place->owner != player->id && place->type == UTILITY) {
        int rent_values[] = {4 * player->die_roll, 10 * player->die_roll};
        int rent = rent_values[place->ownerptr->owned_properties.utilities_owned - 1];
        
        player->cash -= rent;
        place->ownerptr->cash += rent;

        printf("%s landed on %s.\n", player->name, place->name);
        printf("Rent Paid : LKR %i.\n", rent);
        printf("Owner : %s.\n\n", place->ownerptr->name);
    }
}