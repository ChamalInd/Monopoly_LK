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
        player->loan_status.total_payable = max_loan;
        player->loan_status.loan_duration = 20;

        printf("%s obtained a secured loan.\n", player->name);
        printf("Loan Amount : LKR %i.\n", (int) max_loan);
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
        float interest = (float) player->loan_status.total_payable * (player->loan_status.interest_rate / 100.0);
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
        
        for (int i = 0; i < NO_OF_CELLS; i++) {
            if (board[i].owner == player->id && board[i].mortgage.status == UNMORTGAGED) {
                if (board[i].type == PROPERTY) {
                    board[i].mortgage.status = UNMORTGAGED;
                    board[i].owner = BANK_OF_CEYLON;
                    board[i].ownerptr = NULL;
                    board[i].buildings.building_value = 0;
                    board[i].buildings.no_of_hotels = 0;
                    board[i].buildings.no_of_houses = 0;
                } else if (board[i].type == RAILWAY || board[i].type == UTILITY) {
                    board[i].mortgage.status = UNMORTGAGED;
                    board[i].owner = BANK_OF_CEYLON;
                    board[i].ownerptr = NULL;
                }
            }
        }

        printf("%s has defaulted.\n", player->name);
        printf("Collateral has been foreclosed.\nOutstanding debt cleared.\n\n");
    }
}

void repay_part_of_loan(Player *player) {
    // randomly decides the partial payment
    int amount = rand() % player->loan_status.total_payable + 1;
    player->cash -= amount;
    player->loan_status.total_payable -= amount;
    printf("%s repaid LKR %i.\n", player->name, amount);
    printf("Outstanding Balance : \n\tLKR %i.\n\n", player->loan_status.total_payable);
}

void repay_full_loan(Player *player, Cell board[]) {
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

void extend_loan(Player *player) {
    player->loan_status.loan_duration = 20;
    printf("%s extended the loan of LKR %i.\n", player->name, player->loan_status.total_payable);
    printf("Duration : %i.\n\n", player->loan_status.loan_duration);
}

void increase_loan(Player *player, Cell board[]) {
    Status player_status = calculate_player_status(*player, board);
    if (player_status.unmortgaged_properties > 0) {
        player->loan_status.no_of_loans = 0;
        obtain_loan(player, board);
    }
}