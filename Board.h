#ifndef _MINES_H
#define _MINES_H
#include <string>

// Constants for use in our Minesweeper program
// to aid in readability
const std::string GRAPHICS[11] = {
    "+", "0", "1", // Array of characters to index into
    "2",          "3",          "4", // when we print our board
    "5",          "6",          "7", "8", "9"};
const int UNCHECKED = 0; // use UNCHECKED instead of magic number

const int EASY_M_COUNT = 10;
const int INTER_M_COUNT = 40;
const int EXPERT_M_COUNT = 99;
const int MINE = 9;
const int EASY_SIZE = 64;
const int INTER_SIZE = 256;
const int EXPERT_SIZE = 480;

// Function Prototypes
void add_mines(int board[], int size, int difficulty); // add mines to the board
void print_board(const int board[], const int checked[],
                 int size); // print the board based on what is checked
void dig_at_location(int x, int y, int checked[], int size); // dig at a spot
bool isLoser(const int board[], const int checked[],
             int size); // check for loser
bool isWinner(const int board[], const int checked[],
              int size);                      // check for winner
bool isValidLocation(int location, int size); // ensure the location is valid
void count_touching(int board[], int size);
void update_blanks(int location, int board[], int checked[]);
#endif
