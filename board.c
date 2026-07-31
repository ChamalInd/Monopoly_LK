// Board initialization and movement logic
#include "functions.h"

void generate_board(Cell board[]) {
    char *cell_names[NO_OF_CELLS] = {
        "GO",
        "Pettah",
        "Community Development Fund",
        "Maradana",
        "Income Tax",
        "Colombo Fort Railway Station",
        "Bambalapitiya",
        "National Event Cards",
        "Wellawatta",
        "Mount Lavinia",
        "Jail / Just Visiting",
        "Nugegoda",
        "Ceylon Electricity Board",
        "Maharagama",
        "Kottawa",
        "Kandy Railway Station",
        "Negombo",
        "Sri Lanka Insurance",
        "Katunayake",
        "Ja-Ela",
        "Free Parking",
        "Kandy City",
        "National Event Card",
        "Peradeniya",
        "Katugastota",
        "Galle Railway Station",
        "Galle Fort",
        "Unawatuna",
        "National Water Supply and Drainage Board",
        "Hikkaduwa",
        "Go To Jail",
        "Jaffna Town",
        "Nallur",
        "Ceylinco Insurance",
        "Trincomalee",
        "Jaffna Railway Station",
        "National Event Card",
        "Nuwara Eliya",
        "Bank of Ceylon",
        "Galle Face"
    };

    Type cell_types[NO_OF_CELLS] = {
        START,      PROPERTY,   EVENT,          PROPERTY,   TAX,
        RAILWAY,    PROPERTY,   EVENT,          PROPERTY,   PROPERTY,
        SPECIAL,    PROPERTY,   UTILITY,        PROPERTY,   PROPERTY,
        RAILWAY,    PROPERTY,   SRI_LANKA_INSURANCE,      PROPERTY,   PROPERTY,
        SPECIAL,    PROPERTY,   EVENT,          PROPERTY,   PROPERTY,
        RAILWAY,    PROPERTY,   PROPERTY,       UTILITY,    PROPERTY,
        SPECIAL,    PROPERTY,   PROPERTY,       CEYLINCO,  PROPERTY,
        RAILWAY,    EVENT,      PROPERTY,       BANK,       PROPERTY
    };

    Color cell_colors[NO_OF_CELLS] = {
        NO_COLOR,   BROWN,      NO_COLOR,    BROWN,      NO_COLOR,
        NO_COLOR,   LIGHT_BLUE, NO_COLOR,    LIGHT_BLUE, LIGHT_BLUE,
        NO_COLOR,   PINK,       NO_COLOR,    PINK,       PINK,
        NO_COLOR,   ORANGE,     NO_COLOR,    ORANGE,     ORANGE,
        NO_COLOR,   RED,        NO_COLOR,    RED,        RED,
        NO_COLOR,   YELLOW,     YELLOW,      NO_COLOR,   YELLOW,
        NO_COLOR,   GREEN,      GREEN,       NO_COLOR,   GREEN,
        NO_COLOR,   NO_COLOR,   DARK_BLUE,   NO_COLOR,   DARK_BLUE
    };

    Ownership cell_owners[NO_OF_CELLS] = {
        NO_OWNER,       BANK_OF_CEYLON, NO_OWNER,       BANK_OF_CEYLON, NO_OWNER,
        BANK_OF_CEYLON, BANK_OF_CEYLON, NO_OWNER,       BANK_OF_CEYLON, BANK_OF_CEYLON,
        NO_OWNER,       BANK_OF_CEYLON, BANK_OF_CEYLON, BANK_OF_CEYLON, BANK_OF_CEYLON,
        BANK_OF_CEYLON, BANK_OF_CEYLON, NO_OWNER,       BANK_OF_CEYLON, BANK_OF_CEYLON,
        NO_OWNER,       BANK_OF_CEYLON, NO_OWNER,       BANK_OF_CEYLON, BANK_OF_CEYLON,
        BANK_OF_CEYLON, BANK_OF_CEYLON, BANK_OF_CEYLON, BANK_OF_CEYLON, BANK_OF_CEYLON,
        NO_OWNER,       BANK_OF_CEYLON, BANK_OF_CEYLON, NO_OWNER,       BANK_OF_CEYLON,
        BANK_OF_CEYLON, NO_OWNER,       BANK_OF_CEYLON, NO_OWNER,       BANK_OF_CEYLON
    };

    int cell_base_price[NO_OF_CELLS] = {
        NONE,  1500,   NONE,   1800,   NONE,
        1,     2500,   NONE,   2700,   3000,
        NONE,  3500,   1,      3800,   4000,
        1,     4500,   NONE,   4700,   5000,
        NONE,  5500,   NONE,   5800,   6000,
        1,     6500,   6800,   1,      7000,
        NONE,  8000,   8300,   NONE,   8500,
        1,     NONE,  10000,   NONE,  12000
    };

    int cell_base_rent[NO_OF_CELLS] = {
        NONE, 100,  NONE, 120,  NONE,
        NONE, 180,  NONE, 200,   220,
        NONE, 260,  NONE, 280,   300,
        NONE, 350,  NONE, 370,   400,
        NONE, 450,  NONE, 480,   500,
        NONE, 600,   620, NONE,  650,
        NONE, 750,   780, NONE,  800,
        NONE, NONE, 1000, NONE, 1200
    };

    int cell_no_of_houses[NO_OF_CELLS] = {
        NONE,    0, NONE,    0, NONE,
        NONE,    0, NONE,    0,    0,
        NONE,    0, NONE,    0,    0,
        NONE,    0, NONE,    0,    0,
        NONE,    0, NONE,    0,    0,
        NONE,    0,    0, NONE,    0,
        NONE,    0,    0, NONE,    0,
        NONE, NONE,    0, NONE,    0
    };

    int cell_price_of_house[NO_OF_CELLS] = {
        NONE,   500,  NONE,   500,  NONE,
        NONE,   750,  NONE,   750,   750,
        NONE,  1000,  NONE,  1000,  1000,
        NONE,  1250,  NONE,  1250,  1250,
        NONE,  1500,  NONE,  1500,  1500,
        NONE,  2000,  2000,  NONE,  2000,
        NONE,  2500,  2500,  NONE,  2500,
        NONE,  NONE,  3000,  NONE,  3000
    };

    int cell_no_of_hotels[NO_OF_CELLS] = {
        NONE,    0, NONE,    0, NONE,
        NONE,    0, NONE,    0,    0,
        NONE,    0, NONE,    0,    0,
        NONE,    0, NONE,    0,    0,
        NONE,    0, NONE,    0,    0,
        NONE,    0,    0, NONE,    0,
        NONE,    0,    0, NONE,    0,
        NONE, NONE,    0, NONE,    0
    };

    int cell_price_of_hotel[NO_OF_CELLS] = {
        NONE,  2000,  NONE,  2000,  NONE,
        NONE,  3000,  NONE,  3000,  3000,
        NONE,  4000,  NONE,  4000,  4000,
        NONE,  5000,  NONE,  5000,  5000,
        NONE,  6000,  NONE,  6000,  6000,
        NONE,  8000,  8000,  NONE,  8000,
        NONE, 10000, 10000,  NONE, 10000,
        NONE,  NONE, 12000,  NONE, 12000
    };

    int building_value[NO_OF_CELLS] = {
        NONE,    0, NONE,    0, NONE,
        NONE,    0, NONE,    0,    0,
        NONE,    0, NONE,    0,    0,
        NONE,    0, NONE,    0,    0,
        NONE,    0, NONE,    0,    0,
        NONE,    0,    0, NONE,    0,
        NONE,    0,    0, NONE,    0,
        NONE, NONE,    0, NONE,    0
    };

    Mortgage_Status cell_mortgage_status[NO_OF_CELLS] = {
        CANNOT_MORTGAGED, UNMORTGAGED, CANNOT_MORTGAGED, UNMORTGAGED, CANNOT_MORTGAGED,
        UNMORTGAGED,      UNMORTGAGED, CANNOT_MORTGAGED, UNMORTGAGED, UNMORTGAGED,
        CANNOT_MORTGAGED, UNMORTGAGED, UNMORTGAGED,      UNMORTGAGED, UNMORTGAGED,
        UNMORTGAGED,      UNMORTGAGED, CANNOT_MORTGAGED, UNMORTGAGED, UNMORTGAGED,
        CANNOT_MORTGAGED, UNMORTGAGED, CANNOT_MORTGAGED, UNMORTGAGED, UNMORTGAGED,
        UNMORTGAGED,      UNMORTGAGED, UNMORTGAGED,      UNMORTGAGED, UNMORTGAGED,
        CANNOT_MORTGAGED, UNMORTGAGED, UNMORTGAGED,      CANNOT_MORTGAGED, UNMORTGAGED,
        UNMORTGAGED,      CANNOT_MORTGAGED, UNMORTGAGED, CANNOT_MORTGAGED, UNMORTGAGED
    };

    int cell_mortgage_value[NO_OF_CELLS] = {
        NONE,   750,  NONE,   750,  NONE,
        1,     1250,  NONE,  1250,  1250,
        NONE,  1750,  1,     1750,  1750,
        1,     2250,  NONE,  2250,  2250,
        NONE,  2750,  NONE,  2750,  2750,
        1,     3250,  3250,  1,     3250,
        NONE,  4000,  4000,  NONE,  4000,
        1,     NONE,  5000,  NONE,  5000
    };

    for (int i = 0; i < NO_OF_CELLS; i++) {
        board[i] = (Cell) {
            .name = cell_names[i],
            .depreciation = (Depreciation) {0, 0},
            .type = cell_types[i],
            .group = cell_colors[i],
            .owner = cell_owners[i],
            .ownerptr = NULL,
            .insurance = (Insurance) {
                .policy = NO_INSURANCE,
                .provider = NONE,
                .duration = 0
            },
            .value = (Values) {
                .base_price = cell_base_price[i],
                .market_price = cell_base_price[i],
                .current_market_price = cell_base_price[i],
                .base_rent = cell_base_rent[i]
            },
            .buildings = (Building) {
                .no_of_houses = cell_no_of_houses[i],
                .price_of_house = cell_price_of_house[i],
                .no_of_hotels = cell_no_of_hotels[i],
                .price_of_hotel = cell_price_of_hotel[i],
                .building_value = building_value[i]
            },
            .mortgage = (Mortgage) {
                .status = cell_mortgage_status[i],
                .value = cell_mortgage_value[i]
            }
        };
    }

    Player players[NO_OF_PLAYERS];

    Cell *property_groups[8][3] = {
        {&board[1], &board[3], NULL},
        {&board[6], &board[8], &board[9]},
        {&board[11], &board[13], &board[14]},
        {&board[16], &board[18], &board[19]},
        {&board[21], &board[23], &board[24]},
        {&board[26], &board[27], &board[29]},
        {&board[31], &board[32], &board[34]},
        {&board[37], &board[39], NULL}
    };

    Game game_status = (Game) {
        .rounds = 0,
        .inflation_rate = 0,
        .interest_rate = 2 // demo value
    };

    initialize_players(players);
    print_game(game_status, players, board, FALSE);
    decide_player_order(players);
    game_loop(&game_status, players, board, property_groups);
}

void destroy_property(Player player, Cell board[], Cell *place, int size) {
    if (size == 1) {
        if (place->owner == player.id) {
            place->mortgage.status = UNMORTGAGED;
            place->owner = BANK_OF_CEYLON;
            place->ownerptr = NULL;
            place->insurance = (Insurance) {NO_INSURANCE, NONE, 0};
            place->depreciation = (Depreciation) {0, 0};
            place->buildings.building_value = 0;
            place->buildings.no_of_hotels = 0;
            place->buildings.no_of_houses = 0;
        }
    } else {
        for (int i = 0; i < size; i++) {
            if (board[i].owner == player.id) {
                board[i].mortgage.status = UNMORTGAGED;
                board[i].owner = BANK_OF_CEYLON;
                board[i].ownerptr = NULL;
                board[i].insurance = (Insurance) {NO_INSURANCE, NONE, 0};
                board[i].depreciation = (Depreciation) {0, 0};
                board[i].buildings.building_value = 0;
                board[i].buildings.no_of_hotels = 0;
                board[i].buildings.no_of_houses = 0;
            }
        }
    }
}

void print_board(Cell board[]) {
    for (int i = 0; i < NO_OF_CELLS; i++) {
        printf("%i \tName: %s \n\tType: %i \n\tGroup: %i \n\tOwner: %i \n\tOwner Pointer: %p \n\tBase Price: %i \n\tMarket Price: %i \n\tBase Rent: %i \n\tNo of Houses: %i \n\tPrice of a House: %i \n\tNo of Hotels: %i \n\tPrice of a Hotel: %i \n\tBuilding Value: %i \n\tMortgage Status: %i \n\tMortgage Value: %i\n\n", (i + 1), board[i].name, board[i].type, board[i].group, board[i].owner, board[i].ownerptr, board[i].value.base_price, board[i].value.market_price, board[i].value.base_rent, board[i].buildings.no_of_houses, board[i].buildings.price_of_house, board[i].buildings.no_of_hotels, board[i].buildings.price_of_hotel, board[i].buildings.building_value, board[i].mortgage.status, board[i].mortgage.value);
    }
}