// Loans, banking, insurance, depreciation, taxation
#include "functions.h"

void obtain_loan(Player *player, Cell board[], Game game_status) {
    float max_loan = 0;
    int total_unmortgaged_property_value = 0;
    Status player_status = calculate_player_status(*player, board);

    if (player->loan_status.no_of_loans == 0 && player_status.unmortgaged_properties > 0) {
        for (int i = 0; i < NO_OF_CELLS; i++) {
            if (board[i].owner == player->id && board[i].mortgage.status == UNMORTGAGED) {
                total_unmortgaged_property_value += board[i].mortgage.value;
            }
        }

        max_loan = ((float) total_unmortgaged_property_value) * (75.0 / 100.0);

        player->cash += max_loan;
        player->loan_status.no_of_loans++;
        player->loan_status.total_payable += max_loan;
        player->loan_status.loan_duration = 20;
        player->loan_status.interest_rate = game_status.interest_rate;

        printf("%s obtained a secured loan.\n", player->name);
        printf("Loan Amount : LKR %i.\n", (int) max_loan);
        printf("Outstanding Loan Amount : LKR %i.\n", player->loan_status.total_payable);
        printf("\nCollateral : \n");

        for (int i = 0; i < NO_OF_CELLS; i++) {
            if (board[i].owner == player->id && board[i].mortgage.status == UNMORTGAGED) {
                printf("\t%s\n", board[i].name);
                board[i].mortgage.status = MORTGAGED;
            }
        }

        printf("\nInterest Rate : %.2f%%.\n", player->loan_status.interest_rate);
        printf("Duration : %i.\n\n", player->loan_status.loan_duration);
    }
}

void accumulated_interest(Player players[]) {
    for (int i = 0; i < NO_OF_PLAYERS; i++) {
        if (players[i].isBankrupt == FALSE && players[i].loan_status.no_of_loans == 1 && players[i].loan_status.loan_duration > 0) {
            float interest = ((float) players[i].loan_status.total_payable) * (players[i].loan_status.interest_rate / 100.0);
            players[i].loan_status.total_payable += (int) interest;
        }
    }
}

void check_for_loan_status(Player players[], Cell board[]) {
    for (int i = 0; i < NO_OF_PLAYERS; i++) {
        if (players[i].isBankrupt == FALSE) {
            if (players[i].loan_status.loan_duration > 0) {
                players[i].loan_status.loan_duration--;
                if (players[i].loan_status.loan_duration == 3) {
                    printf("Loan of %s for LKR %i will overdue after 3 rounds.\n\n", players[i].name, players[i].loan_status.total_payable);
                }
            } else if (players[i].loan_status.no_of_loans == 1 && players[i].loan_status.loan_duration == 0) {
                players[i].loan_status.loan_duration = 0;
                players[i].loan_status.no_of_loans = 0;
                players[i].loan_status.total_payable = 0;
                
                destroy_property(players[i], board);

                printf("%s has defaulted.\n", players[i].name);
                printf("Collateral has been foreclosed.\nOutstanding debt cleared.\n\n");

                check_for_bankruptcy(&players[i], board);
            }
        }
    }
}

void repay_part_of_loan(Player *player, Cell board[]) {
    // randomly decides the partial payment
    int amount = rand() % player->loan_status.total_payable + 1;
    if (player->cash >= amount) {
        player->cash -= amount;
        player->loan_status.total_payable -= amount;

        if (player->loan_status.total_payable == 0) {
            for (int i = 0; i < NO_OF_CELLS; i++) {
                if (board[i].owner == player->id && board[i].mortgage.status == MORTGAGED) {
                    board[i].mortgage.status = UNMORTGAGED;
                }
            }
        }
        
        printf("%s repaid LKR %i.\n", player->name, amount);
        printf("Outstanding Balance : \n\tLKR %i.\n\n", player->loan_status.total_payable);
    }
}

void repay_full_loan(Player *player, Cell board[]) {
    if (player->cash >= player->loan_status.total_payable) {
        for (int i = 0; i < NO_OF_CELLS; i++) {
            if (board[i].owner == player->id && board[i].mortgage.status == MORTGAGED) {
                board[i].mortgage.status = UNMORTGAGED;
            }
        }

        printf("%s repaid LKR %i.\n", player->name, player->loan_status.total_payable);

        player->cash -= player->loan_status.total_payable;
        player->loan_status.total_payable = 0;
        player->loan_status.no_of_loans = 0;
        player->loan_status.loan_duration = 0;

        printf("Outstanding Balance : \n\tLKR %i.\n\n", player->loan_status.total_payable);
    }
}

void extend_loan(Player *player) {
    player->loan_status.loan_duration = 20;
    printf("%s extended the loan of LKR %i.\n", player->name, player->loan_status.total_payable);
    printf("Duration : %i.\n\n", player->loan_status.loan_duration);
}

void increase_loan(Player *player, Cell board[], Game game_status) {
    Status player_status = calculate_player_status(*player, board);
    if (player_status.unmortgaged_properties > 0) {
        player->loan_status.no_of_loans = 0;
        printf("%s decided to refinance existing loan of LKR %i.\n\n", player->name, player->loan_status.total_payable);
        obtain_loan(player, board, game_status);
    }
}

void obtain_insurance(Player *player, Cell *place, int provider) {
    char *insurance_policy_names[] = {"Basic Property Insurance", "Comprehensive Insurance", "Business Interruption Insurance"};

    int policy = rand() % 3;

    while (policy == BUSINESS_INTERRUPTION) {
        if (place->buildings.no_of_hotels == 0) {
            policy = rand() % 3;
        } else {
            break;
        }
    }

    int premium = 0;

    switch (policy) {
        case BASIC:
            premium = (int) ((float) place->value.market_price * (5.0 / 100.0));
            break;
        case COMPREHENSIVE:
            premium = (int) ((float) place->value.market_price * (10.0 / 100.0));
            break;
        case BUSINESS_INTERRUPTION:
            premium = (int) ((float) place->value.market_price * (15.0 / 100.0));
            break;
    }

    if (player->cash >= premium) {
        player->cash -= premium;
        place->insurance.policy = policy;
        place->insurance.provider = provider;
        place->insurance.duration = 20;

        printf("%s purchased.\n", insurance_policy_names[policy]);
        printf("Property : %s.\n", place->name);
        printf("Premium : LKR %i.\n\n", premium);
    } else {
        printf("Not enough money to purchase insurance premium.\n\n");
    }   
}

void check_for_insurance_status(Cell board[]) {
    for (int i = 0; i < NO_OF_CELLS; i++) {
        if (board[i].type == PROPERTY && board[i].insurance.policy != NO_INSURANCE && board[i].insurance.duration > 0) {
            board[i].insurance.duration--;
            if (board[i].insurance.duration == 3) {
                printf("Insurance policy on %s expires in 3 rounds.\n\n", board[i].name);
            }
        }
        if (board[i].type == PROPERTY && board[i].insurance.policy != NO_INSURANCE && board[i].insurance.duration == 0) {
            printf("Insurance policy on %s has expired.\n\n", board[i].name);
            board[i].insurance.duration = 0;
            board[i].insurance.policy = NO_INSURANCE;
            board[i].insurance.provider = NONE;
        }
    }
}

void renew_insurance(Player *player, Cell *board[], int length) {
    for (int i = 0; i < length; i++) {
        int premium = 0;

        switch (board[i]->insurance.policy) {
            case BASIC:
                premium = (int) ((float) board[i]->value.market_price * (5.0 / 100.0));
                break;
            case COMPREHENSIVE:
                premium = (int) ((float) board[i]->value.market_price * (10.0 / 100.0));
                break;
            case BUSINESS_INTERRUPTION:
                premium = (int) ((float) board[i]->value.market_price * (15.0 / 100.0));
                break;
            default :
                premium = -1;
                break;
        }

        if (premium < 0) {
            break;
        }

        if (player->cash >= premium) {
            player->cash -= premium;
            board[i]->insurance.duration = 20;
            printf("Insurance Policy renewed.\nProperty : %s\nPremium : %i\n\n", board[i]->name, premium);
        }
    }
}