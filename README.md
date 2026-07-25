# MONOPOLY-LK

A Sri Lankan-themed Monopoly board game simulation written in C. Four AI-controlled players compete to dominate the property market across Sri Lanka — from Pettah to Galle Face.

## Overview

MONOPOLY-LK simulates a full game of Monopoly with a Sri Lankan twist. The board features 40 cells including real Sri Lankan locations, railways, utilities, and special squares. Players follow predefined strategies to buy properties, collect rent, and construct houses and hotels.

## Features

- **40-cell Sri Lankan board** — Pettah, Bambalapitiya, Kandy City, Galle Fort, Jaffna Town, Nuwara Eliya, Galle Face, and more
- **4 AI players** with distinct strategies:
  - Aggressive Investor
  - Conservative Banker
  - Risk Taker
  - Opportunistic Trader
- **Property system** — buy, rent, and construct houses/hotels across 8 color groups
- **Railways** (4 stations) — rent scales with number of stations owned (250 / 500 / 1000 / 2000)
- **Utilities** (2 providers) — rent is 4x or 10x the dice roll
- **Construction** — build up to 4 houses, then upgrade to a hotel
- **Even-building rule** enforced within color groups
- **Round summaries** — cash, net worth, properties, and hotels after each round
- **Deterministic output** via seeded RNG (`srand(1)`)

## Board Layout

| # | Name | Type | Group |
|---|------|------|-------|
| 1 | GO | Start | — |
| 2 | Pettah | Property | Brown |
| 3 | Community Development Fund | Event | — |
| 4 | Maradana | Property | Brown |
| 5 | Income Tax | Tax | — |
| 6 | Colombo Fort Railway Station | Railway | — |
| 7 | Bambalapitiya | Property | Light Blue |
| 8 | National Event Cards | Event | — |
| 9 | Wellawatta | Property | Light Blue |
| 10 | Mount Lavinia | Property | Light Blue |
| 11 | Jail / Just Visiting | Special | — |
| 12 | Nugegoda | Property | Pink |
| 13 | Ceylon Electricity Board | Utility | — |
| 14 | Maharagama | Property | Pink |
| 15 | Kottawa | Property | Pink |
| 16 | Kandy Railway Station | Railway | — |
| 17 | Negombo | Property | Orange |
| 18 | Sri Lanka Insurance | Insurance | — |
| 19 | Katunayake | Property | Orange |
| 20 | Ja-Ela | Property | Orange |
| 21 | Free Parking | Special | — |
| 22 | Kandy City | Property | Red |
| 23 | National Event Card | Event | — |
| 24 | Peradeniya | Property | Red |
| 25 | Katugastota | Property | Red |
| 26 | Galle Railway Station | Railway | — |
| 27 | Galle Fort | Property | Yellow |
| 28 | Unawatuna | Property | Yellow |
| 29 | National Water Supply and Drainage Board | Utility | — |
| 30 | Hikkaduwa | Property | Yellow |
| 31 | Go To Jail | Special | — |
| 32 | Jaffna Town | Property | Green |
| 33 | Nallur | Property | Green |
| 34 | Ceylinco Insurance | Insurance | — |
| 35 | Trincomalee | Property | Green |
| 36 | Jaffna Railway Station | Railway | — |
| 37 | National Event Card | Event | — |
| 38 | Nuwara Eliya | Property | Dark Blue |
| 39 | Bank of Ceylon | Bank | — |
| 40 | Galle Face | Property | Dark Blue |

## Project Structure

```
MONOPOLY-LK/
├── main.c          # Entry point, game initialisation
├── game.c          # Game loop, dice, player ordering, round summaries
├── players.c       # Player init, buying, rent, construction, status
├── board.c         # Board generation with all 40 cells
├── types.h         # Structs, enums, and constants
├── functions.h     # Function prototypes
├── events.c        # Event cards (placeholder)
└── finance.c       # Banking, insurance, taxation (placeholder)

```

## Building & Running

### Prerequisites

- GCC or any C99-compatible compiler

### Compile

```bash
gcc *.c -o monopoly
```

### Run

```bash
./monopoly
```

### Generate Output to File

```bash
./monopoly > output.txt
```

## How the Game Works

1. **Player ordering** — Each player rolls the dice; highest roll goes first. Ties trigger re-rolls.
2. **Each turn** a player:
   - Rolls the dice (2-12)
   - Moves forward on the board
   - Collects LKR 2,000 if they pass GO
   - Buys unowned properties they land on (if affordable)
   - Constructs houses/hotels if they own all properties in a group
   - Pays rent to other players for owned properties, railways, and utilities
3. **Rounds** continue until 500 rounds or a winner is determined
4. **Net worth** = cash + property market prices + building values

## Property Groups

| Group | Properties | Value |
|-------|-----------|-------|
| Brown | Pettah, Maradana | LKR 1,500 |
| Light Blue | Bambalapitiya, Wellawatta, Mount Lavinia | LKR 2,500 |
| Pink | Nugegoda, Maharagama, Kottawa | LKR 3,500 |
| Orange | Negombo, Katunayake, Ja-Ela | LKR 4,500 |
| Red | Kandy City, Peradeniya, Katugastota | LKR 5,500 |
| Yellow | Galle Fort, Unawatuna, Hikkaduwa | LKR 6,500 |
| Green | Jaffna Town, Nallur, Trincomalee | LKR 8,000 |
| Dark Blue | Nuwara Eliya, Galle Face | LKR 10,000 |

## Tech Stack

- **Language:** C (C99)
- **RNG:** `rand()` with seeded randomness (`srand`)
- **Build:** GCC

## License

This project was developed as part of the SCS 1301 — Introduction to Computer Programming course.
