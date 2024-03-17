/*
	Braeden Treutel
	Minesweeper Project
*/


#include "Board.h"
#include <iostream>
using std::cout;
using std::endl;
using std::string;

// Function: add_mines
// Inputs: board, size, and difficulty (number of mines)
// Outputs: board is filled by reference with mines
void add_mines(int board[], int size, int difficulty) {
  for (int i = 0; i < difficulty; i++) {
    int mine = rand() % size;
    if (board[mine] == MINE) {
      i--;
    } else {
      board[mine] = MINE;
    }
  }
}

// Function: print_board
// Inputs: board, checked array, size (both are same size)
// Outputs: Prints the board out using the GRAPHICS string based on
//          the parallel array checked
void print_board(const int board[], const int checked[], int size) {
  cout << "   0 1 2 3 4 5 6 7 8 9" << endl << "-----------------------" << endl;

  int board_height;
  int board_width;
  if (size == 100) {
    board_height = 10;
    board_width = 10;
  }
  // This is how you can print a 1D array in 2D.
  // Iterate row by row
  for (int r = 0; r < board_height; r++) {
    // go across the row printing the value in the board
    cout << r << "| ";
    for (int c = 0; c < board_width; c++) {
      // row * maxWidth + col == current index
      int loc = r * board_width + c;
			if (checked[loc] == 0)
				cout << "+ ";
			else{
	  	cout << board[loc] << " ";} // print location value instead of graphic	
      /* if (checked[loc] != 0)
        cout << GRAPHICS[board[loc] + 1];
      else
        cout << GRAPHICS[UNCHECKED];*/
    }
    cout << endl;
  }
}

// Dig at a location (mark the correct spot in checked)
void dig_at_location(int x, int y, int checked[], int size) {
  int board_width;
  if (size == 100) {
    board_width = 10;
  }
  // Location in a 1D array based on 2D (x, y coords)
  int location = y * board_width + x;

  if (!isValidLocation(
          location, size)) { // if the location is invalid just leave/do nothing
    cout << "Invalid location..." << endl; // debugging
    return;
  }
  // check the spot
  checked[location] = 1;
}

// Make sure the location is between 0 and the size of the board inclusive
bool isValidLocation(int location, int size) {
  // if the location is less than 0 or greater than/equal to size
	if (location < 0 || location >= size){
		return false;
	}
	else{
		return true;
	}
  // return false
  // otherwise return true
}

// Determine if we've lost
bool isLoser(const int board[], const int checked[], int size) {
  // For Each spot that has been checked
	for (int x=0; x<size; x++){
		//If the checked spot has a mine
		if (checked[x] == 1 && board[x] == MINE){
			//return true (we've lost)
			return true;
		}	
	}
  //Otherwise return false
	return false;
}
bool isWinner(const int board[], const int checked[], int size) {
	int num_checked=0;
  // as long as no checked spot contains a mine in the board

	for (int x=0; x<size; x++){
		if (checked[x] == 1 && board[x] != MINE){
			num_checked++;
		}
		else if (checked[x] == 1 && board[x] == MINE) {
			return false;
		}
	}
	// and the total number of checked spots is equal to the
  // board size - mine count
	if (num_checked == size - EASY_M_COUNT){
		return true;
		// we've won
	}
	else {
		return false;
		// otherwise return false
	}
}

void update_blanks(int location, int board[], int checked[]){
	if (isValidLocation(location, 10)){
		if (checked[location] == 0){
			checked[location] = 1;
			/*   __________________________
  *  |topleft |  top  | topright|
  *  |--------|-------|---------|
  *  |   left |  MINE |    right|
  *  |--------|-------|---------|
  *  |botleft |  bot  | botright|
  *   --------------------------
  */

	int board_width=10;

		//flags to make it easier to do corners
		bool bottom_flag = false;
		bool top_flag = false;
		bool right_flag = false;
		bool left_flag = false;

		//defining the spots on the board
		int top = location-board_width;
		int bottom = location+board_width;
		int left = location-1;
		int right = location+1;
		int topleft = top-1;
		int topright = top+1;
		int bottomleft = bottom-1;
		int bottomright = bottom+1;

		//if the spot has no mines
		if (board[location] == 0){
			
			if (isValidLocation(top, 100) && board[top] != MINE){ // TOP
				checked[top] = 1;
				top_flag = true;
				update_blanks(board[top], board, checked);
			}

			if (isValidLocation(bottom, 100) && board[bottom] != MINE){ // BOTTOM
				checked[bottom] = 1;
				bottom_flag = true;
				update_blanks(board[bottom], board, checked);
			}
			
			if (isValidLocation(right, 100) && board[right] != MINE && (right%board_width) != 0){ // RIGHT
				checked[right] = 1;
				right_flag = true;
				update_blanks(board[right], board, checked);
			}
			

			if (isValidLocation(left, 100) && board[left] != MINE && ((location%board_width) != 0)){ // LEFT
				checked[left] = 1;
				left_flag = true;
				update_blanks(board[left], board, checked);
			}

			if (left_flag && top_flag && board[topleft]!=MINE){//TOPLEFT
				checked[topleft] = 1;
				update_blanks(board[topleft], board, checked);
			}

			if (left_flag && bottom_flag && board[bottomleft]!=MINE){//BOTTOMLEFT
				checked[bottomleft] = 1;
				update_blanks(board[bottomleft], board, checked);
			}

			if (right_flag && top_flag && board[topright]!=MINE){//TOPRIGHT
				checked[topright] = 1;
				update_blanks(board[topright], board, checked);
			}

			if (right_flag && bottom_flag && board[bottomright]!=MINE){//BOTTOMRIGHT
				checked[bottomright] = 1;
				update_blanks(board[bottomright], board, checked);
			}
		}
	}
	}
}

void count_touching(int board[], int size){
  /*   __________________________
  *  |topleft |  top  | topright|
  *  |--------|-------|---------|
  *  |   left |  MINE |    right|
  *  |--------|-------|---------|
  *  |botleft |  bot  | botright|
  *   --------------------------
  */

	int board_width=10;

	//Making sure I have the right width for the difficulty
	
	int location;

	
	for (location=0; location<size; location++){

		//flags to make it easier to do corners
		bool bottom_flag = false;
		bool top_flag = false;
		bool right_flag = false;
		bool left_flag = false;

		//defining the spots on the board
		int top = location-board_width;
		int bottom = location+board_width;
		int left = location-1;
		int right = location+1;
		int topleft = top-1;
		int topright = top+1;
		int bottomleft = bottom-1;
		int bottomright = bottom+1;

		//if the spot has a mine
		if (board[location] == MINE){
			
			if (isValidLocation(top, size) && board[top] != MINE){ // TOP
				board[top]++;
				top_flag = true;
			}

			if (isValidLocation(bottom, size) && board[bottom] != MINE){ // BOTTOM
				board[bottom]++;
				bottom_flag = true;
			}
			
			if (isValidLocation(right, size) && board[right] != MINE && (right%board_width) != 0){ // RIGHT
				board[right]++;
				right_flag = true;
			}
			

			if (isValidLocation(left, size) && board[left] != MINE && ((location%board_width) != 0)){ // LEFT
				board[left]++;
				left_flag = true;
			}

			if (left_flag && top_flag && board[topleft]!=MINE){//TOPLEFT
				board[topleft]++;
			}

			if (left_flag && bottom_flag && board[bottomleft]!=MINE){//BOTTOMLEFT
				board[bottomleft]++;
			}

			if (right_flag && top_flag && board[topright]!=MINE){//TOPRIGHT
				board[topright]++;
			}

			if (right_flag && bottom_flag && board[bottomright]!=MINE){//BOTTOMRIGHT
				board[bottomright]++;
			}
		}
	}
}
