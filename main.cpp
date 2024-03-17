#include "Board.h"
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(int argc, char **argv) {
  srand(333); // Ensure we have set mines for testing purposes

  int board[100] = {0}; // Create an easy board to test the gameplay loop
                              // and functions with
  int checked[100] = {0}; // Use a parallel array called checked to help
                                // determine win/lose initialized to all 0's
  int x, y;                     // variables for digging coordinates

  add_mines(board, 100, 10); // fill the board with mines
	count_touching(board, 100);
  while (!isLoser(board, checked, 100) &&
         !isWinner(board, checked, 100)) {
    print_board(
        board, checked,
        EASY_SIZE); // print the initial state of the board for debugging
    cout << "Enter x and y to dig: ";
    cin >> x >> y;
    dig_at_location(x, y, checked, 100);
		update_blanks((x+1)*(y+1), board, checked);
    cout << endl << endl; // spacing
  }
  print_board(board, checked, EASY_SIZE); // print the final state of theboard
  if (isLoser(board, checked, EASY_SIZE)) {
    cout << "You're a sucker and blew up !!!!" << endl;
  } else
    cout << "You won!!!! Congratulations" << endl;

  return 0;
}
