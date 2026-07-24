// Definitions of structures, enumerations, constants, and data types
#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>

#define NO_OF_PLAYERS 4
#define NO_OF_CELLS  40
#define TRUE          1
#define FALSE         0

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
    Values value;
    Building buildings; 
    Mortgage mortgage;
} Cell;

typedef struct {
    char *name;
    int id;
    int play_order;
    int die_roll;
    int cash;
    int place;
    int properties[8][3];
    int property_owned[8];
    int railways[4];
    int railway_owned;
    int utilities[2];
    int utilities_owned;
} Player;


#endif