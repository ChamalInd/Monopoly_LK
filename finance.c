// Loans, banking, insurance, depreciation, taxation
#include "functions.h"

void obtain_loan(Player *player, Cell board[]) {
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

        printf("\nInterest Rate : %i%%.\n", player->loan_status.interest_rate);
        printf("Duration : %i.\n\n", player->loan_status.loan_duration);
    }
}

void accumulated_interest(Player *player) {
    if (player->loan_status.no_of_loans == 1 && player->loan_status.loan_duration > 0) {
        float interest = ((float) player->loan_status.total_payable) * (player->loan_status.interest_rate / 100.0);
        player->loan_status.total_payable += (int) interest;
    }
}

void check_for_loan_status(Player *player, Cell board[]) {
    if (player->loan_status.no_of_loans == 1 && player->loan_status.loan_duration > 0) {
        player->loan_status.loan_duration--;
        if (player->loan_status.loan_duration == 3) {
            printf("Loan of %s for LKR %i will overdue after 3 rounds.\n\n", player->name, player->loan_status.total_payable);
        }
        
    } else if (player->loan_status.no_of_loans == 1 && player->loan_status.loan_duration == 0) {
        player->loan_status.loan_duration = 0;
        player->loan_status.no_of_loans = 0;
        player->loan_status.total_payable = 0;
        
        destroy_property(*player, board);

        printf("%s has defaulted.\n", player->name);
        printf("Collateral has been foreclosed.\nOutstanding debt cleared.\n\n");
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

void increase_loan(Player *player, Cell board[]) {
    Status player_status = calculate_player_status(*player, board);
    if (player_status.unmortgaged_properties > 0) {
        player->loan_status.no_of_loans = 0;
        printf("%s decided to refinance existing loan of LKR %i.\n\n", player->name, player->loan_status.total_payable);
        obtain_loan(player, board);
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

    if (policy == BASIC) {
        premium = (int) ((float) place->value.market_price * (5.0 / 100.0));

    } else if (policy == COMPREHENSIVE) {
        premium = (int) ((float) place->value.market_price * (10.0 / 100.0));

    } else {
        premium = (int) ((float) place->value.market_price * (15.0 / 100.0));
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