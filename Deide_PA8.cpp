/*  Name: Connor Deide
	Date: 11/20/2020
	Class: CPSC 121, Fall 2020
	Programming Assignment: PA8
	Description: This program simulates the popular game of Battleship in which the user plays against the computer. The user has the choice to place their ships manually or randomly and the inputs coordinates to attack the computers board. In turn, the computer makes random guesses of coordinates to attack the user's board. First player to sink all of the opponents ships wins. Program also sends info and data to the output file battleship.log.
*/

#include "Deide_PA8.h"

/*******************************************************************************************
* Function: welcomeScreen()
* Date Created: 11/17/2020
* Date Last Modified: 11/17/2020
* Description: This function outputs the welcome screen and instructions for how to play the game Battleship
* Input Parameters: none
* Returns: none, just outputs message
* Pre: needs function call
* Post: outputs message
*******************************************************************************************/

void welcomeScreen(void) {

	cout << "BATTLESHIP" << endl;
	cout << endl;
	
	cout << "Play against the computer in this game of BATTLESHIP. First place your ship's manually or randomly on the board." << endl;
	cout << "'c' indicates a Carrier, 'b' indicates a Battleship, 'r' indicates a Cruiser, 's' indicates a Submarine, and 'd' indicates a Destroyer." << endl;
	cout << "One player will then be decided to choose first. When it's your turn put in coordinates to target in terms of a row and a column. For example: A 1" << endl;
	cout << "A '*' character represents a hit and a 'm' character represents a miss. If a ship is sunk than all hit characters ('*') on that ship will change to their corresponding characters" << endl;
	cout << "First player to sink all opponents battleships wins." << endl;

}

/*******************************************************************************************
* Function: fillArray()
* Date Created: 11/17/2020
* Date Last Modified: 11/18/2020
* Description: This function fills the given two dimensional array with the char '~'.
* Returns: none, just fills the array
* Pre: needs function call
* Post: full array
*******************************************************************************************/

void fillArray(char arr[NUM_ROWS][NUM_COLS], int rows, int cols) {
	int i = 0, j = 0;
	
	// outer loop iterates over each row
	for (i = 0; i < rows; i++) {
		// inner loop iterates over int in arr[i] (row)
		for (j = 0; j < cols; j++) {
			arr[i][j] = '~';
		}
	}
}

/*******************************************************************************************
* Function: printArray()
* Date Created: 11/17/2020
* Date Last Modified: 11/20/2020
* Description: This function prints out the given array with a space in between each element. The purpose of the second array passed in is to output a letter before each row of the first array so the user can see the coordinates.
* Input Parameters: two const char 2 dimensional arrays and the value of rows and cols
* Returns: none, just outputs the arrays
* Pre: needs function call and arguments
* Post: outputs the arrays
*******************************************************************************************/

void printArray(const char arr[NUM_ROWS][NUM_COLS], const char arr2[NUM_ROWS], int rows, int cols) {
	int i = 0, j = 0;

	cout << endl;
	for (i = 0; i < rows; i++) {
		cout << arr2[i] << " ";
		for (j = 0; j < cols; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

/*******************************************************************************************
* Function: selectWhoStartsFirst()
* Date Created: 11/20/2020
* Date Last Modified: 11/20/2020
* Description: This function selects which player will start first. Its very simple and just chooses a random number
* Input Parameters: none
* Returns: the integer for the startPlayer, either 1 or 2
* Pre: needs function call
* Post: outputs the integer startPlayer
*******************************************************************************************/

int selectWhoStartsFirst() {
	int startPlayer = 0;

	//get random number of either 1 or 2 to decide who goes first
	startPlayer = (rand() % 2) + 1;
	return startPlayer;
}

/*******************************************************************************************
* Function: manuallyPlaceShipsOnBoard()
* Date Created: 11/17/2020
* Date Last Modified: 11/18/2020
* Description: This function lets the user choose how they want to place their ships on the board. It asks whether they want to place it vertically or horizontally and where they want the start point to be.
* Input Parameters: the const arrays shipSizes, shipSymbols, and shipNames and two other two dimensional arrays
* Returns: none, places the ships on the board
* Pre: needs function call and arguments
* Post: ships will be placed on the board
*******************************************************************************************/

void manuallyPlaceShipsOnBoard(char arr[NUM_ROWS][NUM_COLS], const int shipSizes[], const char shipSymbols[], const string shipNames[], const char arr2[NUM_ROWS]) {
	
	int column = 0, intRow = 0, checkRow = 0, checkColumn = 0, i = 0, j = 0 , k = 0, l = 0; 
	char row = ' ';
	bool VorH = 0, invalidPoint = 1;

	// loop 5 times for the 5 ships
	for (i = 0; i < 5; ++i){
		
		cout << endl;
		cout << "Your Board:" << endl;
		printArray(arr, arr2, NUM_ROWS, NUM_COLS);
	
		// reset invalidPoint to true every loop
		invalidPoint = 1;
		while (invalidPoint) {

			cout << endl;
			cout << "Ship: " << shipNames[i] << endl;
			// get information from the user about the ship placement
			cout << "Please enter whether you want to place the ship vertically or horizontally (input a 0 for vertical or a 1 for horizontal): ";
			cin >> VorH;  
			cout << endl;
			cout << "Now please enter the coordinates of the starting position of your ship starting with the row and ending with the column with a space in-between (Ex. A 1): ";
			cin >> row;
			cin >> column;
			cout << endl;

			// loop to convert the char from the row input by the user to corresponding int
			for (j = 0; j < NUM_ROWS; ++j) {
				if (rowLetters[j] == row) {
					intRow = colNumbers[j];
				}
			}

			//lower user coordinates by one value to access the proper array index
			intRow -= 1;
			column -= 1;
		
			// assign to another variable so we can alter the check variables
			checkRow = intRow;
			checkColumn = column;

			// check start position is valid
			if ((((checkRow + shipSizes[i]) < 10) || ((checkColumn + shipSizes[i]) < 10)) && (arr[checkRow][checkColumn] == '~')){
				invalidPoint = 0;
				// if the ship won't go out of the array and doesn't start on another ship then continue to check it wont overlap other ships
				for (k = 0; k < shipSizes[i]; ++k) {
					// if the coordinate does not have a tild then it must be a ship
					if (arr[checkRow][checkColumn] != '~') {
						cout << "ERROR: invalid coordinates, please make sure that your ships don't overlap and stay on the board" << endl;
						invalidPoint = 1;
						break;
					}
					else {
						// add 1 to randRow or randColumn depending on which was picked randomly
						if (!VorH) {
							checkRow += 1;
						}
						else if (VorH) {
							checkColumn += 1;
						}
					}
				}	
			}
			else {
				cout << "ERROR: invalid coordinates, please make sure that your ships don't overlap and stay on the board" << endl;
			}
		}
		// loop until all cells of the ship have been placed
		for (l = 0; l < shipSizes[i]; ++l) { 
			
			arr[intRow][column] = shipSymbols[i];
			// add 1 to randRow or randColumn depending on which was picked randomly
			if (!VorH) {
				intRow += 1;
			}
			else if (VorH) {
				column += 1;
			}
		}
	}

	cout << "Ships have been placed." << endl;
}

/*******************************************************************************************
* Function: randomlyPlaceShipsOnBoard()
* Date Created: 11/17/2020
* Date Last Modified: 11/18/2020
* Description: This function randomly places the ships on the board, either for the user or the computer.It randomly chooses vertical or horizontal direction and the start point. 
* Input Parameters: one two dimensional char array and the const arrays shipSizes and shipSymbols
* Returns: none, places the ships
* Pre: needs function call and arguments
* Post: ships will be placed on the board
*******************************************************************************************/

void randomlyPlaceShipsOnBoard(char arr[NUM_ROWS][NUM_COLS], const int shipSizes[], const char shipSymbols[]) {
	
	int column = 0, row = 0, checkRow = 0, checkColumn = 0, i = 0, j = 0 , k = 0, l = 0; 
	bool VorH = 0, invalidPoint = 1;

	// loop 5 times for the 5 ships
	for (i = 0; i < 5; ++i){
		
		// reset invalidPoint to true every loop
		invalidPoint = 1;
		while (invalidPoint) {

			// get random numbers ranging from 0 - 9
			row = rand() % 10;
			column = rand() % 10;

			// get random number, either 0 or 1, for boolean VorH
			VorH = rand() % 2;
		
			// assign to another variable so we can alter the check variables
			checkRow = row;
			checkColumn = column;

			// check start position is valid
			if ((((checkRow + shipSizes[i]) < 10) || ((checkColumn + shipSizes[i]) < 10)) && (arr[checkRow][checkColumn] == '~')){
				invalidPoint = 0;
				// if the ship won't go out of the array and doesn't start on another ship then continue to check it wont overlap other ships
				for (k = 0; k < shipSizes[i]; ++k) {
					// if the coordinate does not have a tild then it must be a ship
					if (arr[checkRow][checkColumn] != '~') {
						invalidPoint = 1;
						break;
					}
					else {
						// add 1 to randRow or randColumn depending on which was picked randomly
						if (!VorH) {
							checkRow += 1;
						}
						else if (VorH) {
							checkColumn += 1;
						}
					}
				}	
			}
		}
		// loop until all cells of the ship have been placed
		for (l = 0; l < shipSizes[i]; ++l) { 
			
			arr[row][column] = shipSymbols[i];
			// add 1 to randRow or randColumn depending on which was picked randomly
			if (!VorH) {
				row += 1;
			}
			else if (VorH) {
				column += 1;
			}
		}
	}
}

/*******************************************************************************************
* Function: displayBoard()
* Date Created: 11/18/2020
* Date Last Modified: 11/20/2020
* Description: This function displays the game board for the user. It uses the function printArray() to print out the users board and a modified version of the computers board.
* Input Parameters: two const char two dimensional arrays, one const char array and the int value of rows and columns
* Returns: none, just displays the game board
* Pre: needs function call and arguments
* Post: gameBoard is displayed each turn
*******************************************************************************************/

void displayBoard(const char arr1[NUM_ROWS][NUM_COLS], const char arrchar[NUM_ROWS],  char arr2[NUM_ROWS][NUM_COLS], int rows, int columns) {
	
	cout << endl;
	cout << "Your Board:" << endl;
	cout << "  1 2 3 4 5 6 7 8 9 10";
	printArray(arr1, arrchar, NUM_ROWS, NUM_COLS);

	cout << endl;
	cout << "Player2's Board:" << endl;
	cout << "  1 2 3 4 5 6 7 8 9 10";
	printArray(arr2, arrchar, NUM_ROWS, NUM_COLS);
}

/*******************************************************************************************
* Function: checkShot()
* Date Created: 11/19/2020
* Date Last Modified: 11/20/2020
* Description: This function checks the passed in guess to see if it was a hit or a miss 
* Input Parameters: a single two dimensional array and the int values row and column
* Returns: the boolean variable hit as true or false
* Pre: needs function call and arguments
* Post: will know it it was a hit or a miss
*******************************************************************************************/

bool checkShot(char arr[NUM_ROWS][NUM_COLS], int row, int column) {

	int i = 0;
	bool hit = 0, miss = 0;

	// if the coordinates dont find water or a hit or a miss then it must have hit a ship
	if ((arr[row][column] == 'c') || (arr[row][column] == 'b') || (arr[row][column] == 'r') || (arr[row][column] == 's') || (arr[row][column] == 'd')) {
		hit = 1;
	}
	// if the coordinates do find water then its a miss
	else if (arr[row][column] == '~') {
		// set coordinates equal to miss
		miss = 1;
	}
	
	return hit;	
}

/*******************************************************************************************
* Function: isWinner()
* Date Created: 11/19/2020
* Date Last Modified: 11/20/2020
* Description: This function checks if someone has won the game by checking if there are any ship cells left in the two dimensional array
* Input Parameters: a single two dimensional array
* Returns: the boolean value of winner as either true or false
* Pre: needs function call and arguments
* Post: will know if there is a winner or not
*******************************************************************************************/

bool isWinner(char arr[NUM_ROWS][NUM_COLS]) {

	int shipCells = 0, i = 0, j = 0;
	bool winner = 0;
	
	// iterate through the entire two demensional array
	for (i = 0; i < NUM_ROWS; ++i) {
		for (j = 0; j < NUM_COLS; ++j) {
			// if a coordinate holds one of the chars indicating a ship then the game has not been won
			if ((arr[i][j] == 'c') || (arr[i][j] == 'b') || (arr[i][j] == 'r') || (arr[i][j] == 's') || (arr[i][j] == 'd')) {
				shipCells += 1;
			}
			
		}
	}
	// if no ship cells were found in the entire array then the player must have won
	if (shipCells == 0) {
		winner = 1;
	}

	return winner;
}
	
/*******************************************************************************************
* Function: updateBoard()
* Date Created: 11/19/2020
* Date Last Modified: 11/20/2020
* Description: This function updates the gameBoard by either putting a '*' or a 'm' in the previous guess whether or not it was a hit or a miss
* Input Parameters: a single two dimensional array, the boolean value of hit and the int values of row and column
* Returns: none, just modifies the game board
* Pre: needs function call and arguments
* Post: will know where the hit or miss was on the board
*******************************************************************************************/

void updateBoard(char arr[NUM_ROWS][NUM_COLS], bool hit, int row, int column) {

	if (hit) {
		arr[row][column] == '*';
	}
	else {
		arr[row][column] == 'm';
	}

}

/*******************************************************************************************
* Function: checkIfSunkShip()
* Date Created: 11/19/2020
* Date Last Modified: 11/20/2020
* Description: This function checks if the passed in ship char has been sunk by seeing if that char is left anywhere on the board
* Input Parameters: a single two dimensional array, the const arrays shipNames and shipSymbols, the char letter of cell and the int value of player
* Returns: none, just outputs a message if a ship was sunk
* Pre: needs function call and arguments
* Post: message will tell you that you sunk a ship
*******************************************************************************************/

void checkIfSunkShip(char arr[NUM_ROWS][NUM_COLS], const string shipNames[], const char shipSymbols[], char cell, int player) {

	int shipCells = 0, i = 0, j = 0, k = 0;
	string shipName = "";
	bool shipSunk = 0;
	
	// iterate through the entire two demensional array
	for (i = 0; i < NUM_ROWS; ++i) {
		for (j = 0; j < NUM_COLS; ++j) {
			// if a coordinate holds one of the chars indicating a ship then that ship has not been sunk
			if (arr[i][j] == cell) {
				shipCells += 1;
			}
			
		}
	}
	// loop to get the name of the correct ship that has been sunk
	for (k = 0; k < 5; ++k) {
		if (cell == shipSymbols[k]) {
			shipName = shipNames[k];
		}
	}

	// if no ship cells were found for a certain ship then it must be sunk
	if (shipCells == 0) {
		shipSunk = 1;
	}
	
	// output this sunk ship message if a ship was sunk
	if (shipSunk) {
		cout << "Player" << player << "'s " << shipName << " is sunk." << endl;
	}

	//return shipSunk;
}









