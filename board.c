// Board initialization and movement logic
#include "functions.h"

void generate_board(Cell board[]) {
    board[0] = (Cell) {
        .name = "GO",
        .type = START,
        .group = NO_COLOR,
        .owner = NO_OWNER,
        .value = (Values) {
            .purchase_price = -1,
            .market_price = -1,
            .base_rent = -1
        },
        .buildings = (Building) {
            .no_of_houses = -1,
            .price_of_house = -1,
            .no_of_hotels = -1,
            .price_of_hotel = -1
        },
        .mortgage = (Mortgage) {
            .status = CANNOT_MORTGAGED,
            .value = -1
        }
    };

    board[1] = (Cell) {
        .name = "Pettah",
        .type = PROPERTY,
        .group = BROWN,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 1500,
            .market_price = 1500,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = 0,
            .price_of_house = 500,
            .no_of_hotels = 0,
            .price_of_hotel = 2000
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 750
        }
    };

    board[2] = (Cell) {
        .name = "Community Development Fund",
        .type = EVENT,
        .group = NO_COLOR,
        .owner = NO_OWNER,
        .value = (Values) {
            .purchase_price = -1,
            .market_price = -1,
            .base_rent = -1
        },
        .buildings = (Building) {
            .no_of_houses = -1,
            .price_of_house = -1,
            .no_of_hotels = -1,
            .price_of_hotel = -1
        },
        .mortgage = (Mortgage) {
            .status = CANNOT_MORTGAGED,
            .value = -1
        }
    };

    board[3] = (Cell) {
        .name = "Maradana",
        .type = PROPERTY,
        .group = BROWN,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 1500,
            .market_price = 1500,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = 0,
            .price_of_house = 500,
            .no_of_hotels = 0,
            .price_of_hotel = 2000
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 750
        }
    };

    board[4] = (Cell) {
        .name = "Income Tax",
        .type = TAX,
        .group = NO_COLOR,
        .owner = NO_OWNER,
        .value = (Values) {
            .purchase_price = -1,
            .market_price = -1,
            .base_rent = -1
        },
        .buildings = (Building) {
            .no_of_houses = -1,
            .price_of_house = -1,
            .no_of_hotels = -1,
            .price_of_hotel = -1
        },
        .mortgage = (Mortgage) {
            .status = CANNOT_MORTGAGED,
            .value = -1
        }
    };
    
    board[5] = (Cell) {
        .name = "Colombo Fort Railway Station",
        .type = RAILWAY,
        .owner = BANK_OF_CEYLON,
        .group = NO_COLOR,
        .value = (Values) {
            .purchase_price = 1,
            .market_price = 1,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = -1,
            .price_of_house = -1,
            .no_of_hotels = -1,
            .price_of_hotel = -1
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 1
        }
    };

    board[6] = (Cell) {
        .name = "Bambalapitiya",
        .type = PROPERTY,
        .group = LIGHT_BLUE,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 2500,
            .market_price = 2500,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = 0,
            .price_of_house = 750,
            .no_of_hotels = 0,
            .price_of_hotel = 3000
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 1250
        }
    };

    board[7] = (Cell) {
        .name = "National Event Cards",
        .type = EVENT,
        .group = NO_COLOR,
        .owner = NO_OWNER,
        .value = (Values) {
            .purchase_price = -1,
            .market_price = -1,
            .base_rent = -1
        },
        .buildings = (Building) {
            .no_of_houses = -1,
            .price_of_house = -1,
            .no_of_hotels = -1,
            .price_of_hotel = -1
        },
        .mortgage = (Mortgage) {
            .status = CANNOT_MORTGAGED,
            .value = -1
        }
    };

    board[8] = (Cell) {
        .name = "Wellawatta",
        .type = PROPERTY,
        .group = LIGHT_BLUE,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 2500,
            .market_price = 2500,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = 0,
            .price_of_house = 750,
            .no_of_hotels = 0,
            .price_of_hotel = 3000
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 1250
        }
    };

    board[9] = (Cell) {
        .name = "Mount Lavinia",
        .type = PROPERTY,
        .group = LIGHT_BLUE,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 2500,
            .market_price = 2500,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = 0,
            .price_of_house = 750,
            .no_of_hotels = 0,
            .price_of_hotel = 3000
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 1250
        }
    };

    board[10] = (Cell) {
        .name = "Jail / Just Visiting",
        .type = SPECIAL,
        .group = NO_COLOR,
        .owner = NO_OWNER,
        .value = (Values) {
            .purchase_price = -1,
            .market_price = -1,
            .base_rent = -1
        },
        .buildings = (Building) {
            .no_of_houses = -1,
            .price_of_house = -1,
            .no_of_hotels = -1,
            .price_of_hotel = -1
        },
        .mortgage = (Mortgage) {
            .status = CANNOT_MORTGAGED,
            .value = -1
        }
    };

    board[11] = (Cell) {
        .name = "Nugegoda",
        .type = PROPERTY,
        .group = PINK,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 3500,
            .market_price = 3500,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = 0,
            .price_of_house = 1000,
            .no_of_hotels = 0,
            .price_of_hotel = 4000
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 1750
        }
    };

    board[12] = (Cell) {
        .name = "Ceylon Electricity Board",
        .type = UTILITY,
        .group = NO_COLOR,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 1,
            .market_price = 1,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = -1,
            .price_of_house = -1,
            .no_of_hotels = -1,
            .price_of_hotel = -1
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 1
        }
    };

    board[13] = (Cell) {
        .name = "Maharagama",
        .type = PROPERTY,
        .group = PINK,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 3500,
            .market_price = 3500,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = 0,
            .price_of_house = 1000,
            .no_of_hotels = 0,
            .price_of_hotel = 4000
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 1750
        }
    };

    board[14] = (Cell) {
        .name = "Kottawa",
        .type = PROPERTY,
        .group = PINK,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 3500,
            .market_price = 3500,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = 0,
            .price_of_house = 1000,
            .no_of_hotels = 0,
            .price_of_hotel = 4000
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 1750
        }
    };

    board[15] = (Cell) {
        .name = "Kandy Railway Station",
        .type = RAILWAY,
        .group = NO_COLOR,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 1,
            .market_price = 1,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = -1,
            .price_of_house = -1,
            .no_of_hotels = -1,
            .price_of_hotel = -1
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 1
        }
    };

    board[16] = (Cell) {
        .name = "Negombo",
        .type = PROPERTY,
        .group = ORANGE,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 4500,
            .market_price = 4500,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = 0,
            .price_of_house = 1250,
            .no_of_hotels = 0,
            .price_of_hotel = 5000
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 2250
        }
    };

    board[17] = (Cell) {
        .name = "Sri Lanka Insurance",
        .type = INSURANCE,
        .group = NO_COLOR,
        .owner = NO_OWNER,
        .value = (Values) {
            .purchase_price = -1,
            .market_price = -1,
            .base_rent = -1
        },
        .buildings = (Building) {
            .no_of_houses = -1,
            .price_of_house = -1,
            .no_of_hotels = -1,
            .price_of_hotel = -1
        },
        .mortgage = (Mortgage) {
            .status = CANNOT_MORTGAGED,
            .value = -1
        }
    };

    board[18] = (Cell) {
        .name = "Katunayake",
        .type = PROPERTY,
        .group = ORANGE,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 4500,
            .market_price = 4500,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = 0,
            .price_of_house = 1250,
            .no_of_hotels = 0,
            .price_of_hotel = 5000
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 2250
        }
    };

    board[19] = (Cell) {
        .name = "Ja-Ela",
        .type = PROPERTY,
        .group = ORANGE,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 4500,
            .market_price = 4500,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = 0,
            .price_of_house = 1250,
            .no_of_hotels = 0,
            .price_of_hotel = 5000
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 2250
        }
    };

    board[20] = (Cell) {
        .name = "Free Parking",
        .type = SPECIAL,
        .group = NO_COLOR,
        .owner = NO_OWNER,
        .value = (Values) {
            .purchase_price = -1,
            .market_price = -1,
            .base_rent = -1
        },
        .buildings = (Building) {
            .no_of_houses = -1,
            .price_of_house = -1,
            .no_of_hotels = -1,
            .price_of_hotel = -1
        },
        .mortgage = (Mortgage) {
            .status = CANNOT_MORTGAGED,
            .value = -1
        }
    };

    board[21] = (Cell) {
        .name = "Kandy City",
        .type = PROPERTY,
        .group = RED,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 5500,
            .market_price = 5500,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = 0,
            .price_of_house = 1500,
            .no_of_hotels = 0,
            .price_of_hotel = 6000
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 2750
        }
    };

    board[22] = (Cell) {
        .name = "National Event Card",
        .type = EVENT,
        .group = NO_COLOR,
        .owner = NO_OWNER,
        .value = (Values) {
            .purchase_price = -1,
            .market_price = -1,
            .base_rent = -1
        },
        .buildings = (Building) {
            .no_of_houses = -1,
            .price_of_house = -1,
            .no_of_hotels = -1,
            .price_of_hotel = -1
        },
        .mortgage = (Mortgage) {
            .status = CANNOT_MORTGAGED,
            .value = -1
        }
    };

    board[23] = (Cell) {
        .name = "Peradeniya",
        .type = PROPERTY,
        .group = RED,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 5500,
            .market_price = 5500,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = 0,
            .price_of_house = 1500,
            .no_of_hotels = 0,
            .price_of_hotel = 6000
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 2750
        }
    };

    board[24] = (Cell) {
        .name = "Katugastota",
        .type = PROPERTY,
        .group = RED,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 5500,
            .market_price = 5500,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = 0,
            .price_of_house = 1500,
            .no_of_hotels = 0,
            .price_of_hotel = 6000
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 2750
        }
    };

    board[25] = (Cell) {
        .name = "Galle Railway Station",
        .type = RAILWAY,
        .group = NO_COLOR,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 1,
            .market_price = 1,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = -1,
            .price_of_house = -1,
            .no_of_hotels = -1,
            .price_of_hotel = -1
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 1
        }
    };

    board[26] = (Cell) {
        .name = "Galle Fort",
        .type = PROPERTY,
        .group = YELLOW,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 6500,
            .market_price = 6500,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = 0,
            .price_of_house = 2000,
            .no_of_hotels = 0,
            .price_of_hotel = 8000
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 3250
        }
    };

    board[27] = (Cell) {
        .name = "Unawatuna",
        .type = PROPERTY,
        .group = YELLOW,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 6500,
            .market_price = 6500,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = 0,
            .price_of_house = 2000,
            .no_of_hotels = 0,
            .price_of_hotel = 8000
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 3250
        }
    };

    board[28] = (Cell) {
        .name = "National Water Supply and Drainage Board",
        .type = UTILITY,
        .group = NO_COLOR,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 1,
            .market_price = 1,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = -1,
            .price_of_house = -1,
            .no_of_hotels = -1,
            .price_of_hotel = -1
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 1
        }
    };

    board[29] = (Cell) {
        .name = "Hikkaduwa",
        .type = PROPERTY,
        .group = YELLOW,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 6500,
            .market_price = 6500,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = 0,
            .price_of_house = 2000,
            .no_of_hotels = 0,
            .price_of_hotel = 8000
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 3250
        }
    };

    board[30] = (Cell) {
        .name = "Go To Jail",
        .type = SPECIAL,
        .group = NO_COLOR,
        .owner = NO_OWNER,
        .value = (Values) {
            .purchase_price = -1,
            .market_price = -1,
            .base_rent = -1
        },
        .buildings = (Building) {
            .no_of_houses = -1,
            .price_of_house = -1,
            .no_of_hotels = -1,
            .price_of_hotel = -1
        },
        .mortgage = (Mortgage) {
            .status = CANNOT_MORTGAGED,
            .value = -1
        }
    };

    board[31] = (Cell) {
        .name = "Jaffna Town",
        .type = PROPERTY,
        .group = GREEN,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 8000,
            .market_price = 8000,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = 0,
            .price_of_house = 2500,
            .no_of_hotels = 0,
            .price_of_hotel = 10000
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 4000
        }
    };

    board[32] = (Cell) {
        .name = "Nallur",
        .type = PROPERTY,
        .group = GREEN,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 8000,
            .market_price = 8000,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = 0,
            .price_of_house = 2500,
            .no_of_hotels = 0,
            .price_of_hotel = 10000
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 4000
        }
    };

    board[33] = (Cell) {
        .name = "Ceylinco Insurance",
        .type = INSURANCE,
        .group = NO_COLOR,
        .owner = NO_OWNER,
        .value = (Values) {
            .purchase_price = -1,
            .market_price = -1,
            .base_rent = -1
        },
        .buildings = (Building) {
            .no_of_houses = -1,
            .price_of_house = -1,
            .no_of_hotels = -1,
            .price_of_hotel = -1
        },
        .mortgage = (Mortgage) {
            .status = CANNOT_MORTGAGED,
            .value = -1
        }
    };

    board[34] = (Cell) {
        .name = "Trincomalee",
        .type = PROPERTY,
        .group = GREEN,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 8000,
            .market_price = 8000,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = 0,
            .price_of_house = 2500,
            .no_of_hotels = 0,
            .price_of_hotel = 10000
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 4000
        }
    };

    board[35] = (Cell) {
        .name = "Jaffna Railway Station",
        .type = RAILWAY,
        .group = NO_COLOR,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 1,
            .market_price = 1,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = -1,
            .price_of_house = -1,
            .no_of_hotels = -1,
            .price_of_hotel = -1
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 1
        }
    };

    board[36] = (Cell) {
        .name = "National Event Card",
        .type = EVENT,
        .group = NO_COLOR,
        .owner = NO_OWNER,
        .value = (Values) {
            .purchase_price = -1,
            .market_price = -1,
            .base_rent = -1
        },
        .buildings = (Building) {
            .no_of_houses = -1,
            .price_of_house = -1,
            .no_of_hotels = -1,
            .price_of_hotel = -1
        },
        .mortgage = (Mortgage) {
            .status = CANNOT_MORTGAGED,
            .value = -1
        }
    };

    board[37] = (Cell) {
        .name = "Nuwara Eliya",
        .type = PROPERTY,
        .group = DARK_BLUE,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 10000,
            .market_price = 10000,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = 0,
            .price_of_house = 3000,
            .no_of_hotels = 0,
            .price_of_hotel = 12000
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 5000
        }
    };

    board[38] = (Cell) {
        .name = "Bank of Ceylon",
        .type = BANK,
        .group = NO_COLOR,
        .owner = NO_OWNER,
        .value = (Values) {
            .purchase_price = -1,
            .market_price = -1,
            .base_rent = -1
        },
        .buildings = (Building) {
            .no_of_houses = -1,
            .price_of_house = -1,
            .no_of_hotels = -1,
            .price_of_hotel = -1
        },
        .mortgage = (Mortgage) {
            .status = CANNOT_MORTGAGED,
            .value = -1
        }
    };

    board[39] = (Cell) {
        .name = "Galle Face",
        .type = PROPERTY,
        .group = DARK_BLUE,
        .owner = BANK_OF_CEYLON,
        .value = (Values) {
            .purchase_price = 10000,
            .market_price = 10000,
            .base_rent = 1
        },
        .buildings = (Building) {
            .no_of_houses = 0,
            .price_of_house = 3000,
            .no_of_hotels = 0,
            .price_of_hotel = 12000
        },
        .mortgage = (Mortgage) {
            .status = UNMORTGAGED,
            .value = 5000
        }
    };

}

void print_board(Cell board[]) {
    for (int i = 0; i < NO_OF_CELLS; i++) {
        printf("%i \tName: %s \n\tType: %i \n\tGroup: %i \n\tOwner: %i \n\tPurchased Price: %i \n\tMarket Price: %i \n\tBase Rent: %i \n\tNo of Houses: %i \n\tPrice of a House: %i \n\tNo og Hotels: %i \n\tPrice of a Hotel: %i \n\tMortgage Status: %i \n\tMortgage Value: %i\n\n", (i + 1), board[i].name, board[i].type, board[i].group, board[i].owner, board[i].value.purchase_price, board[i].value.market_price, board[i].value.base_rent, board[i].buildings.no_of_houses, board[i].buildings.price_of_house, board[i].buildings.no_of_hotels, board[i].buildings.price_of_hotel, board[i].mortgage.status, board[i].mortgage.value);
    }
}