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
        RAILWAY,    PROPERTY,   INSURANCE,      PROPERTY,   PROPERTY,
        SPECIAL,    PROPERTY,   EVENT,          PROPERTY,   PROPERTY,
        RAILWAY,    PROPERTY,   PROPERTY,       UTILITY,    PROPERTY,
        SPECIAL,    PROPERTY,   PROPERTY,       INSURANCE,  PROPERTY,
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

    int cell_purchase_price[NO_OF_CELLS] = {
        NONE,     1500,   NONE,     1500,   NONE,
        1,      2500,   NONE,     2500,   2500,
        NONE,     3500,   1,      3500,   3500,
        1,      4500,   NONE,     4500,   4500,
        NONE,     5500,   NONE,     5500,   5500,
        1,      6500,   6500,   1,      6500,
        NONE,     8000,   8000,   NONE,     8000,
        1,      NONE,     10000,  NONE,     10000
    };

    int cell_market_price[NO_OF_CELLS] = {
        NONE,     1500,   NONE,     1500,   NONE,
        1,      2500,   NONE,     2500,   2500,
        NONE,     3500,   1,      3500,   3500,
        1,      4500,   NONE,     4500,   4500,
        NONE,     5500,   NONE,     5500,   5500,
        1,      6500,   6500,   1,      6500,
        NONE,     8000,   8000,   NONE,     8000,
        1,      NONE,     10000,  NONE,     10000
    };

    int cell_base_rent[NO_OF_CELLS] = {
        NONE, 1, NONE, 1, NONE,
         1, 1, NONE, 1,  1,
        NONE, 1,  1, 1,  1,
         1, 1, NONE, 1,  1,
        NONE, 1, NONE, 1,  1,
         1, 1,  1, 1,  1,
        NONE, 1,  1, NONE,  1,
         1, NONE,  1, NONE,  1
    };

    int cell_no_of_houses[NO_OF_CELLS] = {
        NONE, 0, NONE, 0, NONE,
        NONE, 0, NONE, 0,  0,
        NONE, 0, NONE, 0,  0,
        NONE, 0, NONE, 0,  0,
        NONE, 0, NONE, 0,  0,
        NONE, 0,  0, NONE,  0,
        NONE, 0,  0, NONE,  0,
        NONE, NONE,  0, NONE,  0
    };

    int cell_price_of_house[NO_OF_CELLS] = {
        NONE,   500,  NONE,   500,  NONE,
        NONE,   750,  NONE,   750,  750,
        NONE,  1000,  NONE,  1000, 1000,
        NONE,  1250,  NONE,  1250, 1250,
        NONE,  1500,  NONE,  1500, 1500,
        NONE,  2000,  2000, NONE,  2000,
        NONE,  2500,  2500, NONE,  2500,
        NONE,   NONE,  3000,  NONE,  3000
    };

    int cell_no_of_hotels[NO_OF_CELLS] = {
        NONE, 0, NONE, 0, NONE,
        NONE, 0, NONE, 0,  0,
        NONE, 0, NONE, 0,  0,
        NONE, 0, NONE, 0,  0,
        NONE, 0, NONE, 0,  0,
        NONE, 0,  0, NONE,  0,
        NONE, 0,  0, NONE,  0,
        NONE, NONE,  0, NONE,  0
    };

    int cell_price_of_hotel[NO_OF_CELLS] = {
        NONE,  2000,  NONE,  2000,  NONE,
        NONE,  3000,  NONE,  3000,  3000,
        NONE,  4000,  NONE,  4000,  4000,
        NONE,  5000,  NONE,  5000,  5000,
        NONE,  6000,  NONE,  6000,  6000,
        NONE,  8000,  8000,  NONE,  8000,
        NONE, 10000, 10000,  NONE, 10000,
        NONE,   NONE, 12000,  NONE, 12000
    };

    int building_value[NO_OF_CELLS] = {
        NONE, 0, NONE, 0, NONE,
        NONE, 0, NONE, 0,  0,
        NONE, 0, NONE, 0,  0,
        NONE, 0, NONE, 0,  0,
        NONE, 0, NONE, 0,  0,
        NONE, 0,  0, NONE,  0,
        NONE, 0,  0, NONE,  0,
        NONE, NONE,  0, NONE,  0
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
        NONE,   750, NONE,   750, NONE,
         1,  1250, NONE,  1250, 1250,
        NONE,  1750,  1,  1750, 1750,
         1,  2250, NONE,  2250, 2250,
        NONE,  2750, NONE,  2750, 2750,
         1,  3250, 3250,  1,  3250,
        NONE,  4000, 4000, NONE,  4000,
         1,   NONE,  5000, NONE,  5000
    };

    for (int i = 0; i < NO_OF_CELLS; i++) {
        board[i] = (Cell) {
            .name = cell_names[i],
            .type = cell_types[i],
            .group = cell_colors[i],
            .owner = cell_owners[i],
            .ownerptr = NULL,
            .value = (Values) {
                .purchase_price = cell_purchase_price[i],
                .market_price = cell_market_price[i],
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
}

void print_board(Cell board[]) {
    for (int i = 0; i < NO_OF_CELLS; i++) {
        printf("%i \tName: %s \n\tType: %i \n\tGroup: %i \n\tOwner: %i \n\tOwner Pointer: %p \n\tPurchased Price: %i \n\tMarket Price: %i \n\tBase Rent: %i \n\tNo of Houses: %i \n\tPrice of a House: %i \n\tNo of Hotels: %i \n\tPrice of a Hotel: %i \n\tBuilding Value: %i \n\tMortgage Status: %i \n\tMortgage Value: %i\n\n", (i + 1), board[i].name, board[i].type, board[i].group, board[i].owner, board[i].ownerptr, board[i].value.purchase_price, board[i].value.market_price, board[i].value.base_rent, board[i].buildings.no_of_houses, board[i].buildings.price_of_house, board[i].buildings.no_of_hotels, board[i].buildings.price_of_hotel, board[i].buildings.building_value, board[i].mortgage.status, board[i].mortgage.value);
    }
}