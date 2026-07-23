// Program entry point
#include <stdio.h>
#include "functions.h"
#include "types.h"

int main(void) {
    Cell board[40];

    generate_board(board);
    // for (int i = 0; i < 40; i++) {
    //     printf("%i \tName: %s \n\tType: %i \n\tGroup: %i \n\tOwner: %i \n\tPurchased Price: %i \n\tMarket Price: %i \n\tBase Rent: %i \n\tNo of Houses: %i \n\tPrice of a House: %i \n\tNo og Hotels: %i \n\tPrice of a Hotel: %i \n\tMortgage Status: %i \n\tMortgage Value: %i\n\n", (i + 1), board[i].name, board[i].type, board[i].group, board[i].owner, board[i].value.purchase_price, board[i].value.market_price, board[i].value.base_rent, board[i].buildings.no_of_houses, board[i].buildings.price_of_house, board[i].buildings.no_of_hotels, board[i].buildings.price_of_hotel, board[i].mortgage.status, board[i].mortgage.value);
    // }
    return 0;
}