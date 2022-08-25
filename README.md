# Battleships-cpp

Problem Description:
Implementing the game of BattleShip. The game starts with each player secretly placing their ships on their board. A ship can be placed either horizontally or vertically on their board. Once the players have finished placing their ships, they take turns guessing locations on their opponent's board to fire. Their opponent announces whether the shot hits or misses their ship and if it is the final hit on their ship, the fact that that shot destroyed their ship.  

Requirements:
All code must be in a namespace named BattleShip
must have at least 3 user defined classes and used them in your solution
Must appropriately use public and private. You should NOT make everything public because it “makes things easier”

Input:
Input will come from 3 locations: the command line, files, and standard input
Command Line
Argument 1
Required
The path to the configuration file for this game
This value will always be valid
Configuration File
The configuration file specifies
The size of the board
The number of ships to be placed on the board
The character used to represent each ship
The size of each ship

The format of the file looks like
Number of rows on the board
Number of columns on the board
Number of ships to be placed
Ship1_Character Ship1_Size
Ship2_Character Ship2_Size
…
For example, the configuration file of a traditional game of Battleship that is played on 10 X 10 board with a Carrier that is 5 long, a Battleship that is 4 long, a Destroyer that is 3 long, a Submarine that is 3 long, and a Patrol Boat that is 2 long looks like 
10
10
5
C 5
B 4
D 3
S 3
P 2

The contents of this file will always be valid.

Standard Input (Keyboard)
This is how the user will specify where to place their ships and what location on the board to fire at. Input will NOT  always be valid. If invalid input is entered the user should be prompted for input 

Setting Up The Game
The player will first be asked for their name and then will be asked to place their ships. Ships are placed in ASCII order based on the character used to represent the ship.

For each ship
The player’s board should be displayed
The player should be asked if they want to place the ship horizontally or vertically
H or h represents horizontal and V or v represents vertical
Repeatedly prompt for valid input if invalid input is entered
They will then be asked for the starting coordinate they want to place the ship at
This will be the leftmost point if the ship is placed horizontally
This will be the topmost point if the ship is placed vertically
If invalid input is entered go back to step 2
If the ship can be legally placed at the location it should be placed there but if it can’t go back to step 2
A placement is legal if 
The ship can fit there without going off the board
The ship does not overlap with any of the ships that have already been placed
