# GIPF - game engine
### Algorithms and Data Structures project
## Author: Marek Szymański


## Project description
The project is a implementation of a game engine for generalized version of the GIPF board game. The game is played on a hexagonal board and 2 players take turns placing and pushing pieces on the board. The goal of the game is to capture all of the opponent's pieces by lining rows of 4 (the number can be customized) pieces. 
The engine works in a text-based environment and allows for playing the game in a console. 

This README assumes basic familiarity with the GIPF game rules, if you are not familiar with them you can find them [here](http://www.gipf.com/gipf/rules/rules.html)


### Board format
The board is represented as a hexagonal grid, with the following format:
- each field is represented by a single character:
    - 'W' - white player's piece
    - 'B' - black player's piece
    - '_' - empty field
    - '.' - 'dot' field, used for placing pieces before they move, hidden from the players, but used in the game rules
- the board is printed as a hexagonal grid, with the flat sides of the hexagon on the top and bottom
```
   W _ _ B
  _ _ _ _ _
 _ _ _ _ _ _
B _ _ _ _ _ W
 _ _ _ _ _ _
  _ _ _ _ _
   W _ _ B
```


### Coordinate system
The board is represented as a hexagonal grid, with the following coordinate system, borrowed from [Gipf for One (GF1)](https://gf1.sourceforge.net/#info):

Board like this (size 4), per the GIPF game rules also has a border of width 1 aroud the entire board - these fields are not printed here but are used for placing pieces before they move (these fields are often referred to as 'dot' fields or 'dots' in this implementation):
```
   W _ _ B
  _ _ _ _ _
 _ _ _ _ _ _
B _ _ _ _ _ W
 _ _ _ _ _ _
  _ _ _ _ _
   W _ _ B
```
with the 'dot' fields the board looks like this:
```
    . . . . . 
   . W _ _ B .
  . _ _ _ _ _ .
 . _ _ _ _ _ _ .
. B _ _ _ _ _ W .
 . _ _ _ _ _ _ .
  . _ _ _ _ _ .
   . W _ _ B .
    . . . . .
```

The coordinates are as follows:
```
    a5 b6 c7 d8 e9
   a4 b5 c6 d7 e8 f8
  a3 b4 c5 d6 e7 f7 g7
 a2 b3 c4 d5 e6 f6 g6 h6
a1 b2 c3 d4 e5 f5 g5 h5 i5
  b1 c2 d3 e4 f4 g4 h4 i4
    c1 d2 e3 f3 g3 h3 i3
      d1 e2 f2 g2 h2 i2
        e1 f1 g1 h1 i1
```
and the same board without 'dot' fields:
```
   b5 c6 d7 e8
  b4 c5 d6 e7 f7 
 b3 c4 d5 e6 f6 g6 
b2 c3 d4 e5 f5 g5 h5 
  c2 d3 e4 f4 g4 h4 
    d2 e3 f3 g3 h3 
      e2 f2 g2 h2 
```

As such each field, often referred to simply as hex, can be identified by a letter-number pair, for example `e5` or `c3`. The letters are always lowercase and the numbers are always integers.

> While the text examples may be a little bit unclear, due to the hexagonal shape of the board, [Gipf for One (GF1)](https://gf1.sourceforge.net/#info) provides more accesible visual representation of the board and the coordinate system


### Custom game rules
The engine allows for customizing the game rules, such as:
- size of the board
- number of pieces in row needed to capture it
- number of pieces each player has (it doesn't have to be equal)
This is done while creating a new game instance, by inputting the desired parameters in the following format:
```
<board_size: int> <pieces_in_row: int> <white_pieces: int> <black_pieecs: int> 
```
Example (board size 4, 4 pieces in a row needed to capture, 15 pieces for each player):
```
4 4 15 15
```


### Commands
The engine allows for the following commands:
- LOAD_GAME_BOARD - loads a new set of game paremeters and new board state from standard input 
                  - first line contain the game parameters: board size, pieces in row, number of white pieces, number of black pieces separated by spaces
                  - second line contains current state of the player's reserves: number of white pieces, number of black pieces and the current player ('W' or 'B')
                  - the rest of the lines contain the board state
                  - `BOARD_STATE_OK` will be printed if the board state is valid
Example:
```
LOAD_GAME_BOARD
4 4 15 15
12 12 W
   W _ _ B
  _ _ _ _ _
 _ _ _ _ _ _
B _ _ _ _ _ W
 _ _ _ _ _ _
  _ _ _ _ _
   W _ _ B
```
Here the new board is of size 4, 4 pieces in a row are required to capture and both players have 15 pieces
Both players have 12 pieces in reserve and it's white player's turn, with the board in initial state (as per GIPF rules)
> As it would be tedious to input the board state manually, it is recommended to just copy the board state from a file and paste it into the console
! If the provided game state is not valid the command will fail, currently saved game state will not change and error message will be printed

- PRINT_GAME_BOARD - prints the current state of the board in the same format as the LOAD_GAME_BOARD command
Example:
```
PRINT_GAME_BOARD
4 4 15 15
12 12 W
   W _ _ B
  _ _ _ _ _
 _ _ _ _ _ _
B _ _ _ _ _ W
 _ _ _ _ _ _
  _ _ _ _ _
   W _ _ B
```

- PRINT_GAME_STATE - prints the current state of the game
                   - possible states are:
                        - in_progress - game is still being played
                        - white_won - white player has won
                        - black_won - black player has won
                        - dead_lock <player_color> - current player cannot make a move
                        - bad_move <player_color> <move> - last move by the player was invalid
Example:
```
PRINT_GAME_STATE
in_progress
```

- DO_MOVE <xN> - <yM> - makes a move on the board
                  - xN and yM are coordinates of hexes on the board
                  - xN is the 'dot' field where th enew piece is placed at first
                  - yM is the field where the piece is pushed to from xN when the move is made
                  - if the move is not valid per GIPF rules the command will fail and error message will be printed
                  - if the move is valid `MOVE_COMITTED` will be printed
                  - if the game is already over the command will fail and `GAME_OVER <game_status>` will be printed 

- DO_MOVE <xN> - <yM> <w|b>: <x1> <xn> - makes a move on the board, but with additional information neccessary  to resolve ambiguity in some cases (when, per normal GIPF rules, moving player decides which pieces to remove)
                  - xN and yM are coordinates of hexes on the board
                  - xN is the 'dot' field where th enew piece is placed at first
                  - yM is the field where the piece is pushed to from xN when the move is made
                  - w|b is the color of the player that is making the move
                  - x1 and xn are coordinates of hexes on the board defining the row of pieces that are removed from the board
                  - if the move is not valid per GIPF rules the command will fail and error message will be printed
                  - if the move is valid `MOVE_COMITTED` will be printed 
                  - if the game is already over the command will fail and `GAME_OVER <game_status>` will be printed 
  

### List of error messages:
- illegal move - the move is invalid, the piece cannot be placed or pushed to the given hexes
- WRONG_WHITE_PAWNS_NUMBER - the number of white pieces on board + white pieces in the reserve is not equal to the total number of white pieces
- WRONG_BLACK_PAWNS_NUMBER - the number of black pieces on board + black pieces in the reserve is not equal to the total number of black pieces


--- 

#### Implementation details
The project was implemented in pure C++ without using any external libraries or frameworks. 
The implementation of hexagonal grid is based on the excellent article by [Red Blob Games](https://www.redblobgames.com/grids/hexagons/), which takes full credit for the system.
- the board (Board class) is implemented as unordered_map of hexes (Hex class) mapped to characters representing the pieces on the board. This way the board can be easily accessed and modified
- Hex class is used to represent a single field on a hexagonal grid and comes with methods for calculating the distance between hexes, performing basic hex grid arithmetic and operating on the grid's 6 directions (on 3 axes)
- the game engine itself (GIPF class) is implemented as a class that holds the board and the game parameters, provides methods for performing moves and validating the many game rules and conditions
- the constants.h holds all the constants, symbols and messages used by the engine - some used only interally, some for debugging and some for user interaction


As the program was checked by an automated testing system, the input and output format was strictly defined and had to be followed.