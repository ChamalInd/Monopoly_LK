// Board initialization and movement logic
#include "functions.h"

void initialize_game(Cell board[]) {
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
    Regional regional_cards[12];

    Game game_status = (Game) {
        .rounds = 0,
        .current_player = 0,
        .dynamic_market = {
            (Dynamic_Market) {
                .event = NORMAL,
                .property_group = NONE
            },
            (Dynamic_Market) {
                .event = NORMAL,
                .property_group = NONE
            }
        },
        .economic_event = NO_EVENT,
        .government_regulation = NO_REGULATION,
        .regional_card = NONE,
        .national_event_pointer = 0,
        .inflation_rate = 0,
        .interest_rate = 8.0f,  // assuming stable economy
        .income_tax_rate = 15.0f,
        .community_fund_rate = 10.0f
    };

    generate_board(board);
    generate_event_cards(national_events, regional_cards);
    initialize_players(players);
    print_game_start();
    decide_player_order(players, &game_status);
    game_loop(&game_status, players, board, property_groups, national_events, regional_cards);
}

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
        1500,  2500,   NONE,   2700,   3000,
        NONE,  3500,   1500,   3800,   4000,
        1500,  4500,   NONE,   4700,   5000,
        NONE,  5500,   NONE,   5800,   6000,
        1500,  6500,   6800,   1500,   7000,
        NONE,  8000,   8300,   NONE,   8500,
        1500,  NONE,  10000,   NONE,  12000
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

    for (int i = 0; i < NO_OF_CELLS; i++) {
        board[i] = (Cell) {
            .name = cell_names[i],
            .id = i,
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
                .value = cell_base_price[i] / 2
            }
        };
    }
}

void initialize_players(Player players[]) {
    char *player_names[] = {"Aggressive Investor", "Conservative Banker", "Risk Taker", "Opportunistic Trader"};
    int plays[] = {AGGRESSIVE_INVESTOR, CONSERVATIVE_BANKER, RISK_TAKER, OPPORTUNISTIC_TRADER};

    for (int i = 0; i < NO_OF_PLAYERS; i++) {
        players[i] = (Player) {
            .name = player_names[i],
            .id = plays[i],
            .isBankrupt = FALSE,
            .has_disaster_occurred = FALSE,
            .going_to_bid = FALSE,
            .jail_status = (Jail) {FALSE, 0},
            .loan_status = (Loan) {0, 0, 0, 8}, 
            .events_own = 0,
            .play_order = NONE, 
            .die_roll = NONE,
            .cash = STARTUP_CASH,
            .taxes_due = 0,
            .place = 0
        };

        for (int j = 0; j < 20; j++) {
            players[i].events[j] = (National_Events) {j, NONE, NONE};
        }
    }
}

void generate_event_cards(Events national_events[], Regional regional_cards[]) {
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

    char *regional_names[] = {
        "Southern Tourism Boom", "Port City Expansion", "IT Industry Growth", "Northern Development Programme", 
        "Tea Export Boom", "Airport Expansion", "University City Growth", "Beach Pollution",
        "Flood Damage", "Transport Strike", "Electricity Tariff Increase", "Water Shortage"
    };

    char *regional_values[] = {"+40%", "+25%", "+20%", "+30%", "+35%", "+30%", "+20%", "-30%", "-20%", "-40%", "+25%", "+20%"};

    for (int i = 0; i < 20; i++) {
        national_events[i] = (Events) {
            .name = event_names[i],
            .event = event_description[i]
        };
    }

    for (int i = 0; i < 12; i++) {
        regional_cards[i] = (Regional) {
            .name = regional_names[i],
            .value = regional_values[i]
        };
    }
      
}

void decide_player_order(Player players[], Game *game_status) {
    while (TRUE) {
        for (int i = 0; i < NO_OF_PLAYERS; i++) {
            if (players[i].play_order == NONE) {
                players[i].die_roll = dice_roll();
                printf("%s rolls %i.\n", players[i].name, players[i].die_roll);
            }
        }

        int max = 0, count = 0, player = NONE;

        for (int i = 0; i < NO_OF_PLAYERS; i++) {
            if (players[i].play_order == NONE && max < players[i].die_roll) {
                max = players[i].die_roll;
                player = i;
            }
        }

        for (int i = 0; i < NO_OF_PLAYERS; i++) {
            if (players[i].play_order == NONE && max == players[i].die_roll) {
                count++;
            }
        }

        if (count == 1) {
            game_status->current_player = player;
            printf("\n%s will begin the game.\n\n", players[game_status->current_player].name);
            
            int i = game_status->current_player;
            do {
                printf("%s\n", players[i].name);
                i++;
                i %= NO_OF_PLAYERS;
            } while (i != game_status->current_player);
            printf("\n");
            break;

        } else {
            for (int i = 0; i < NO_OF_PLAYERS; i++) {
                if (players[i].die_roll < max) {
                players[i].play_order = TRUE;
                }
            }
        }

        printf("\n");
    }
}