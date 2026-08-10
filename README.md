# MONOPOLY-LK

A Sri Lankan-themed simulation of Monopoly, written entirely in C for **SCS 1301 — Data Structures and Program Design using C** (University of Colombo School of Computing). Four autonomous, AI-controlled players — each with a distinct investment strategy — compete across a 40-square board modelled on real Sri Lankan locations, from Pettah to Galle Face, complete with banking, insurance, taxation, inflation, and a dynamic property market.

Once started, the simulation requires **no user interaction**. All buying, bidding, borrowing, insuring, building, and selling decisions are made programmatically by each player's assigned behavioral strategy.

---

## Overview

MONOPOLY-LK follows the traditional structure of Monopoly — roll dice, move around the board, buy properties, collect rent, build houses and hotels — but layers in systems meant to mirror the Sri Lankan economy:

- **Commercial banking** — secured loans against mortgaged collateral, interest accrual, refinancing, extensions, and foreclosure on default.
- **Insurance** — three policy tiers (Basic, Comprehensive, Business Interruption) covering fire, flood, riot, vandalism, earthquake, and lost rental income.
- **Taxation** — a flat Income Tax on net worth and a Community Development Fund levy on property holdings.
- **Inflation & dynamic markets** — periodic inflation/deflation cycles and rotating property-group booms/declines that shift purchase prices, rents, and construction costs.
- **Building depreciation & maintenance** — houses and hotels lose condition over time, cutting into rental income until the owner pays for upkeep.
- **Random events** — 20 National Event Cards, 12 Regional Development Cards, 8 Economic Events, and 8 Government Regulations, each with a defined effect and expiry.

The game runs for a maximum of **500 rounds**, or until only one player remains solvent — whichever comes first. The winner is whoever has the highest net worth at that point.

---

## Board Layout

The board contains 40 squares, indexed `0`–`39`, arranged clockwise.

| # | Name | Type | Group |
|---|------|------|-------|
| 1 | GO | Start | — |
| 2 | Pettah | Property | Brown |
| 3 | Community Development Fund | Event (Tax) | — |
| 4 | Maradana | Property | Brown |
| 5 | Income Tax | Tax | — |
| 6 | Colombo Fort Railway Station | Railway | — |
| 7 | Bambalapitiya | Property | Light Blue |
| 8 | National Event Card | Event | — |
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

---

## Property Groups & Values

Every property's mortgage value is fixed at exactly **50% of its purchase price**.

| Group | Property | Price (LKR) | Base Rent | Mortgage | House Cost | Hotel Cost |
|-------|----------|-------------:|----------:|---------:|-----------:|-----------:|
| Brown | Pettah | 1,500 | 100 | 750 | 500 | 2,000 |
| Brown | Maradana | 1,800 | 120 | 900 | 500 | 2,000 |
| Light Blue | Bambalapitiya | 2,500 | 180 | 1,250 | 750 | 3,000 |
| Light Blue | Wellawatta | 2,700 | 200 | 1,350 | 750 | 3,000 |
| Light Blue | Mount Lavinia | 3,000 | 220 | 1,500 | 750 | 3,000 |
| Pink | Nugegoda | 3,500 | 260 | 1,750 | 1,000 | 4,000 |
| Pink | Maharagama | 3,800 | 280 | 1,900 | 1,000 | 4,000 |
| Pink | Kottawa | 4,000 | 300 | 2,000 | 1,000 | 4,000 |
| Orange | Negombo | 4,500 | 350 | 2,250 | 1,250 | 5,000 |
| Orange | Katunayake | 4,700 | 370 | 2,350 | 1,250 | 5,000 |
| Orange | Ja-Ela | 5,000 | 400 | 2,500 | 1,250 | 5,000 |
| Red | Kandy City | 5,500 | 450 | 2,750 | 1,500 | 6,000 |
| Red | Peradeniya | 5,800 | 480 | 2,900 | 1,500 | 6,000 |
| Red | Katugastota | 6,000 | 500 | 3,000 | 1,500 | 6,000 |
| Yellow | Galle Fort | 6,500 | 600 | 3,250 | 2,000 | 8,000 |
| Yellow | Unawatuna | 6,800 | 620 | 3,400 | 2,000 | 8,000 |
| Yellow | Hikkaduwa | 7,000 | 650 | 3,500 | 2,000 | 8,000 |
| Green | Jaffna Town | 8,000 | 750 | 4,000 | 2,500 | 10,000 |
| Green | Nallur | 8,300 | 780 | 4,150 | 2,500 | 10,000 |
| Green | Trincomalee | 8,500 | 800 | 4,250 | 2,500 | 10,000 |
| Dark Blue | Nuwara Eliya | 10,000 | 1,000 | 5,000 | 3,000 | 12,000 |
| Dark Blue | Galle Face | 12,000 | 1,200 | 6,000 | 3,000 | 12,000 |

**Rent multipliers by development:** No buildings = 1×, 1 house = 2×, 2 houses = 3×, 3 houses = 5×, 4 houses = 7×, hotel = 10× base rent (before market/event/condition modifiers).

## Railways & Utilities

| Type | Purchase Price | Mortgage Value |
|------|----------------:|----------------:|
| Railway (×4) | LKR 1,500 | LKR 750 |
| Utility (×2) | LKR 1,500 | LKR 750 |

- **Railway rent** scales with stations owned by the same player: 1 → LKR 250, 2 → LKR 500, 3 → LKR 1,000, 4 → LKR 2,000.
- **Utility rent** is dice-based: 4× the roll with one utility owned, 10× the roll with both.

---

## Player Strategies

| Player | Core Behaviour |
|--------|-----------------|
| **Aggressive Investor** | Expands rapidly, prioritises completing monopolies and premium properties (Galle Face, Nuwara Eliya), builds houses/hotels the moment it's legal, borrows to fund construction, rarely sells. |
| **Conservative Banker** | Buys only when cash reserves stay healthy, avoids loans unless facing bankruptcy, always insures developed property comprehensively, prefers railways/utilities for stable income, pulls back during recessions. |
| **Risk Taker** | Buys aggressively, always maximises loans and refinances often, bids until cash runs out, builds hotels early, sells weaker assets to fund premium developments, ignores depreciation until forced to repair. |
| **Opportunistic Trader** | Evaluates projected appreciation vs. cost before every purchase, favours discounted auctions, adapts construction and insurance decisions to current inflation/regulation conditions, maintains a balanced portfolio. |

---

## Core Systems

**Banking & Loans** — Each player may hold at most one active loan at a time. The maximum loan is 75% of the total mortgage value of unmortgaged collateral (properties, railways, utilities — buildings don't count). Loans run for 20 rounds, accrue interest every complete round, and can be repaid, extended, or refinanced from the Bank of Ceylon square. Failure to repay in time triggers foreclosure: collateral reverts to the bank, buildings are demolished, and insurance on those properties is cancelled.

**Insurance** — Landing on Sri Lanka Insurance or Ceylinco Insurance lets a player buy or renew a policy on any uninsured property they own. Basic Insurance (5% premium) covers fire/flood at 80% compensation; Comprehensive (10%) covers fire/flood/riot/vandalism/earthquake at 100%; Business Interruption (15%) covers hotels, including five rounds of lost rent. Policies last 20 rounds with a reminder at 3 rounds remaining.

**Taxation** — Income Tax (starting at 15%) is charged on net worth when landing on the Income Tax square. The Community Development Fund square levies 10% on the market value of owned properties.

**Inflation & Dynamic Market** — Every 10 rounds, an inflation/deflation rate (-3% to +12%) is applied to prices, rents, and construction costs, and one property group enters a Market Boom while another enters a Market Decline, each lasting 10 rounds.

**Depreciation & Maintenance** — Properties older than 50 rounds lose up to 30% of their value over time unless renovated. Buildings lose 2% condition per round; once condition drops below 25% the building stops earning rent until the owner pays for maintenance.

**Random Events** — National Event Cards (drawn on Event squares), Regional Development Cards, Economic Events, and Government Regulations fire on fixed intervals (every turn, 15, and 20 rounds respectively) and expire automatically, reversing their effects.

---

## File-by-File Breakdown

| File | Purpose |
|------|---------|
| **`main.c`** | Program entry point. Seeds the RNG and hands off to `initialize_game()`. |
| **`types.h`** | All shared data types: `Player`, `Cell`, `Game`, `Status`, and the enums for property colours, ownership, insurance policies, national/regional/economic events, and government regulations. Also defines global constants (`STARTUP_CASH`, `MAX_ROUNDS`, `GO_REWARD`, etc.). |
| **`functions.h`** | Prototypes for every function across the project, grouped by the source file that implements them. |
| **`board.c`** | Builds the 40-square board (names, types, colour groups, prices, rents, construction costs, mortgage values), initialises the four players' starting state, generates the National Event/Regional Development card decks, and determines turn order via dice roll-off. |
| **`game.c`** | The simulation's outer loop: prints the game-start banner, drives the per-turn/per-round cycle (movement, GO payouts, periodic triggers for inflation/market reviews/events/regulations), prints round summaries and current market conditions, decides the winner, and prints the end-of-game report. |
| **`players.c`** | Core turn logic and AI decision-making: dispatches the correct action for whatever square a player lands on, purchase decisions and auctions per strategy, rent calculation (including all market/event/depreciation modifiers), raising cash by selling/auctioning property, house/hotel construction per strategy, and property/building renovation logic. |
| **`finance.c`** | The banking and insurance subsystem: obtaining, extending, refinancing, and repaying loans; interest accrual and default/foreclosure handling; purchasing/renewing insurance and calculating premiums; processing insurance claims and disaster compensation; Income Tax and Community Development Fund collection; and settling any outstanding penalties (e.g. Luxury Property Tax). |
| **`events.c`** | All time-based and random systems: property and building depreciation, inflation, the rotating dynamic property market (boom/decline), disaster occurrence and resolution, drawing and expiring National Event Cards, Economic Events, Government Regulations, and Regional Development Cards. |
| **`helper.c`** | Shared utility functions: rounding, resetting a property back to bank ownership, unmortgaging a player's properties, rolling dice, deciding the winner by net worth, jail entry/release logic, bankruptcy detection and processing, and computing a player's full financial `Status` (cash, properties, railways, utilities, hotels, unmortgaged count, net worth). |

---

## Building & Running

**Requirements:** GCC or any C99-compatible compiler.

```bash
gcc *.c -o monopoly
./monopoly
```

To capture the full simulation log to a file:

```bash
./monopoly > output.txt
```

---

## Sample Output

```
========================================================
                 MONOPOLY-LK Simulation
========================================================

Player 1 : Aggressive Investor
Player 2 : Conservative Banker
Player 3 : Risk Taker
Player 4 : Opportunistic Trader

Each player begins with LKR 30000.

Risk Taker rolled 6.
Risk Taker moves from Square 1 to Square 7.

Risk Taker Landed on Bambalapitiya.

Risk Taker purchased Bambalapitiya for LKR 2500.
Remaining Balance : LKR 27500.
```

```
=================== Round 36 Summary ===================

Player : Aggressive Investor
	 Cash             : LKR   46373
	 Net Worth        : LKR   96220
	 Properties       :          11
	 Hotels           :           0
	 Outstanding Loan : LKR   25941
...
========================================================
                       GAME OVER
========================================================

Winner               : Aggressive Investor
Total Cash           : LKR  46373
Total Property Value : LKR  67098
Outstanding Loans    : LKR  25941
Net Worth            : LKR  96220
```

---

## Tech Stack

- **Language:** C (C99, no external dependencies beyond the standard library)
- **RNG:** `rand()` with a fixed seed for deterministic, reproducible runs
- **Build:** GCC (`gcc *.c -o monopoly`)
