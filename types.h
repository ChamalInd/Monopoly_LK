// Definitions of structures, enumerations, constants, and data types
#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO_OF_PLAYERS 4
#define NO_OF_CELLS  40
#define TRUE          1
#define FALSE         0
#define NONE         -1 

// Declaring data structures required for players
typedef struct{
    int total_properties;
    int total_railways;
    int total_utilities;
    int unmortgaged_properties;
    int hotels_built;
    int net_worth;
} Status;

typedef struct {
    int isJailed;
    int no_of_rounds;
} Jail;

typedef struct {
    int no_of_loans;
    int loan_duration;
    int total_payable;
    int interest_rate;
} Loan;

typedef struct {
    char *name;
    int id;
    int isBankrupt;
    Jail jail_status;
    Loan loan_status;
    int play_order;
    int die_roll;
    int cash;
    int place;
} Player;

// Declaring data structures required to build the board.
typedef enum {
    START, PROPERTY, RAILWAY, UTILITY, EVENT, SPECIAL, TAX, BANK, INSURANCE
} Type;

typedef enum {
    NO_COLOR = -1, BROWN, LIGHT_BLUE, PINK, ORANGE, RED, YELLOW, GREEN, DARK_BLUE
} Color;

typedef enum {
    NO_OWNER = -1, BANK_OF_CEYLON, AGGRESSIVE_INVESTOR, CONSERVATIVE_BANKER, RISK_TAKER, OPPORTUNISTIC_TRADER
} Ownership;

typedef enum {
    CANNOT_MORTGAGED = -1, MORTGAGED, UNMORTGAGED
} Mortgage_Status;

typedef struct {
    int purchase_price;
    int market_price;
    int base_rent; 
} Values;

typedef struct {
    int no_of_houses;
    int price_of_house;
    int no_of_hotels;
    int price_of_hotel;
    int building_value;
} Building;

typedef struct {
    Mortgage_Status status;
    int value;
} Mortgage;

typedef struct {
    char *name;
    Type type;
    Color group;
    Ownership owner;
    Player *ownerptr;
    Values value;
    Building buildings; 
    Mortgage mortgage;
} Cell;


#endif