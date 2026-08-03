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
        "Jail (Just Visiting)",
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
                .base_rent = cell_base_rent[i],
                .house_construction_cost = cell_price_of_house[i],
                .hotel_construction_cost = cell_price_of_hotel[i],
                .building_value = 0
            },
            .buildings = (Building) {
                .no_of_houses = 0,
                .no_of_hotels = 0,
                .condition = 100,
                .rent_reduction_rate = 0,
                .age = 0,
                .has_damaged = FALSE
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

    Events national_events[20];

    Game game_status = (Game) {
        .rounds = 0,
        .current_player = 0,
        .dynamic_market = (Dynamic_Market) {
            .event = NORMAL,
            .property_group = NONE
        },
        .national_event_pointer = 0,
        .inflation_rate = 0,
        .interest_rate = 2.0f,  // demo value
        .income_tax_rate = 10   // demo value
    };

    generate_event_cards(national_events);
    initialize_players(players);
    print_game(game_status, players, board, FALSE, national_events);
    decide_player_order(players);
    game_loop(&game_status, players, board, property_groups, national_events);
}

void generate_event_cards(Events national_events[]) {
    char *event_names[] = {
        "Tourism Hype", "Fuel Shortage", "Heavy Floods", "Political Rally", 
        "Stock Market Rise", "Economic Downturn", "Housing Subsidy", 
        "Interest Rate Cut", "Interest Rate Increase", "Tax Amnesty", 
        "Power Failure", "Foreign Funding", "Port Expansion", "Festival Season", 
        "Labour Strike", "Insurance Discount", "Property Revaluation", 
        "Currency Depreciation", "Government Grant", "National Disaster"
    };

    char *event_description[] = {
        "Hotels earn double rent for 5 rounds",
        "Railway rent doubles for 5 rounds",
        "Random coastal property damaged",
        "One random property closed for 2 rounds",
        "All property values increase by 10%",
        "Property values decrease by 15%",
        "House construction cost reduced by 30%",
        "Loan interest reduced by 2%",
        "Loan interest increased by 2%",
        "Each player receives LKR 2,000",
        "Utility income halved for 3 rounds",
        "Commercial property values increase by 15%",
        "Railway station values increase by 20%",
        "Hotels receive 50% additional rent",
        "Construction suspended for 2 rounds",
        "Premiums reduced by 20%",
        "Random property group appreciates by 15%",
        "Construction costs increase by 10%",
        "Random player receives LKR 5,000",
        "Random developed property damaged"
    };

    Event_Nums event_ids[] = {
        TOURISM_HYPE, FUEL_SHORTAGE, HEAVY_FLOODS, POLITICAL_RALLY, 
        STOCK_MARKET_RISE, ECONOMIC_DOWNTURN, HOUSING_SUBSIDY, 
        INTEREST_RATE_CUT, INTEREST_RATE_INCREASE, TAX_AMNESTY, POWER_FAILURE, 
        FOREIGN_FUNDING, PORT_EXPANSION, FESTIVAL_SEASON, LABOUR_STRIKE, 
        INSURANCE_DISCOUNT, PROPERTY_REVALUATION, CURRENCY_DEPRECIATION, 
        GOVERNMENT_GRANT, NATIONAL_DISASTER
    };

    for (int i = 0; i < 20; i++) {
        national_events[i] = (Events) {
            .id = event_ids[i],
            .name = event_names[i],
            .event = event_description[i]
        };
    }
      
}

void destroy_property(Cell *place) {
    place->mortgage.status = UNMORTGAGED;
    place->owner = BANK_OF_CEYLON;
    place->ownerptr = NULL;
    place->insurance = (Insurance) {NO_INSURANCE, NONE, 0};
    place->depreciation = (Depreciation) {0, 0};
    place->buildings.no_of_hotels = 0;
    place->buildings.no_of_houses = 0;
    place->buildings.condition = 100;
    place->buildings.rent_reduction_rate = 0;
    place->buildings.age = 0;
    place->buildings.has_damaged = FALSE;
}

void sort_players(Player players[]) {
    int swapped = TRUE;

    while (swapped) {
        swapped = FALSE;
        for (int i = 0; i < NO_OF_PLAYERS - 1; i++) {
            if (players[i].play_order > players[i + 1].play_order) {
                Player temp;
                temp = players[i];
                players[i] = players[i + 1];
                players[i + 1] = temp;
                swapped = TRUE;
            }
        }
    }
}

void decide_player_order(Player players[]) {
    int max[] = {-1, -1};
    int i = 0, assigned_players = 0, count;

    while (assigned_players < 4) {
        for (i = 0; i < NO_OF_PLAYERS; i++) {
            if (players[i].play_order == 5) {
                players[i].die_roll = dice_roll();
                printf("%s rolls %i.\n", players[i].name, players[i].die_roll);
            }
        }
    
        for (int x = assigned_players; x < NO_OF_PLAYERS; x++) {
            max[0] = 0;
            for (int y = 0; y < NO_OF_PLAYERS; y++) {
                if (players[y].play_order == 5 && max[0] < players[y].die_roll) {
                    max[0] = players[y].die_roll;
                    max[1] = y;
                }
            }
            count = 0;
            for (int y = 0; y < NO_OF_PLAYERS; y++) {
                if (players[y].play_order == 5 && max[0] == players[y].die_roll) {
                    count++;
                }
            }
            if (count != 1) {
                continue;
            }
            
            players[max[1]].play_order = x + 1;
        }

        sort_players(players);

        printf("\n");

        assigned_players = 0;
        for (i = 0; i < NO_OF_PLAYERS; i++) {
            if (players[i].play_order != 5) {
                assigned_players++;
            }
        }  
    }

    printf("%s will begin the game.\n\n", players[0].name);
    printf("Turn order:\n");
    for (i = 0; i < NO_OF_PLAYERS; i++) {
        printf("%s\n", players[i].name);
    }
    printf("\n");

}