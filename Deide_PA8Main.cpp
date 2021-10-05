/*  Name: Connor Deide
	Date: 11/20/2020
	Class: CPSC 121, Fall 2020
	Programming Assignment: PA8
	Description: This program simulates the popular game of Battleship in which the user plays against the computer. The user has the choice to place their ships manually or randomly and the inputs coordinates to attack the computers board. In turn, the computer makes random guesses of coordinates to attack the user's board. First player to sink all of the opponents ships wins. Program also sends info and data to the output file battleship.log.
*/

#include "Deide_PA8.h"


int main() {

	// variable declaration block
	int startPlayer = 0, intRow = 0, column = 0, i = 0;
	int numHits1 = 0, numHits2 = 0, numMiss1 = 0, numMiss2 = 0, shotTotal1 = 0, shotTotal2 = 0, shotRatio1 = 0, shotRatio2 = 0;
	bool positioning = 0, hit = 0, invalidGuess = 1, gameOver = 0;
	string fileName = "battleship.log", enter = "", trashBin = "", gameState = "play";
	char row = ' ';
	char p1Grid[NUM_ROWS][NUM_COLS]; // 10 x 10 char dimensional array
	char p2Grid[NUM_ROWS][NUM_COLS]; // 10 x 10 char dimensional array
	char p2DisplayGrid[NUM_ROWS][NUM_COLS]; // need this array to display hits and misses to the user
	ofstream outFile;

	// open the output file
	outFile.open(fileName);
	// check that the output file opened successfully
	if (!outFile.is_open()) {
		cout << "Failed to open file" << endl;
		return -1;
	}
	
	// while the user continues to input "play" at the end of the game keep looping =
	while (gameState == "play" ) {
		
		// reset all data values sent to the output file
		numHits1 = 0, numHits2 = 0, numMiss1 = 0, numMiss2 = 0, shotTotal1 = 0, shotTotal2 = 0, shotRatio1 = 0, shotRatio2 = 0;
		// clear screen if user plays again
		system("clear");
		// used in multiple functions
		srand(time(0)); 
		// output the welcome message and game rules
		welcomeScreen();

		cout << "You're Player1, the computer is Player2" << endl << endl;

		// fill the arrays before displaying
		fillArray(p1Grid, NUM_ROWS, NUM_COLS);
		fillArray(p2Grid, NUM_ROWS, NUM_COLS);
		fillArray(p2DisplayGrid, NUM_ROWS, NUM_COLS);

		// get whether the user want to place ships manually or randomly
		cout << "Would you like to place your ships manually or let the computer place them randomly? (Input 0 for manually and 1 for randomly): ";
		cin >> positioning;

		// if they chose manual then call that function, if else call the random placement function
		if (!positioning) {
			manuallyPlaceShipsOnBoard(p1Grid, shipSizes, shipSymbols, shipNames, rowLetters);
		}
		else if (positioning) {
			randomlyPlaceShipsOnBoard(p1Grid, shipSizes, shipSymbols);
		}

		// also need to randomly place the computers ships
		randomlyPlaceShipsOnBoard(p2Grid, shipSizes, shipSymbols);

		// display the game board
		displayBoard(p1Grid, rowLetters, p2DisplayGrid, NUM_ROWS, NUM_COLS);
		//printArray(p2Grid, NUM_ROWS, NUM_COLS);

		// function selects which player will start first
		startPlayer = selectWhoStartsFirst();

		cout << endl;
		cout << "Player" << startPlayer << " has been selected to go first." << endl << endl;

		if (startPlayer == 2) {
			getline(cin, trashBin);
		}

		// game loop for each turn until game is over
		while (!gameOver) {

			invalidGuess = 1; // reset invalidGuess to true every iteration to enter while loop
			hit = 0; //reset hit to false every iteration

			// loop to get user and computer guess, loop until the guess is valid
			while (invalidGuess) {

				invalidGuess = 0;
				// enter if player1 turn
				if (startPlayer == 1) {
					cout << endl;
					// get attack coordinates
					cout << "Enter attack coordinates, row then column (Ex. A 1): ";
					cin >> row;
					cin >> column;

					// loop to convert the char from the row input by the user to corresponding int
					for (i = 0; i < NUM_ROWS; ++i) {
						if (rowLetters[i] == row) {
							intRow = colNumbers[i];
						}
					}

					intRow -= 1;
					column -= 1;

					// check if user has already guessed the coordinate on player2's board
					if ((p2DisplayGrid[intRow][column] == '*') || (p2DisplayGrid[intRow][column] == 'm')) {
						cout << "Coordinate has already been guessed" << endl;
						invalidGuess = 1;
					}

					// check if coordinates were a hit or a miss
					hit = checkShot(p2Grid, intRow, column);
		
				}

				// enter if player2 turn
				else if (startPlayer == 2) {
					// generate random coordinate guess for computer (1 - 10 here instead of 0 - 9 because function checkShot denotes each value by one)
					intRow = (rand() % 10) + 1;
					column = (rand() % 10) + 1;

					// loop to convert the intRow value to its corresponding char value to be output to the console
					for (i = 0; i < NUM_ROWS; ++i) {
						if (intRow == colNumbers[i]) {
							row = rowLetters[i];
						}
					}
		
					cout << endl;
					cout << "Player2 (computer) guessed the coordinates " << row << " " << column << endl;
		
					intRow -= 1;
					column -= 1;
					// no need to convert char to corresponding int like with guess from the user
					// check if computer already guessed this coordinate on player1's board
					if ((p1Grid[intRow][column] == '*') || (p1Grid[intRow][column] == 'm')) {
						cout << "You already guessed that coordinate." << endl;
						invalidGuess = 1;
					}

					// check if coordinates were a hit or a miss
					hit = checkShot(p1Grid, intRow, column);
				
				}
			}

			// execute if guess is a hit
			if (hit) {
				cout << "Player" << startPlayer << "'s target was a hit!" << endl;
				cout << endl;
			}
			//execute if guess is a miss
			else {
				cout << "Player" << startPlayer << "'s target was a miss." << endl;
				cout << endl;
			}
			
			//if it is player1's turn execute all of this
			if (startPlayer == 1) {

				// check if each ship has been sunk
				checkIfSunkShip(p1Grid, shipNames, shipSymbols, 'c', 1);
				checkIfSunkShip(p1Grid, shipNames, shipSymbols, 'b', 1);
				checkIfSunkShip(p1Grid, shipNames, shipSymbols, 'r', 1);
				checkIfSunkShip(p1Grid, shipNames, shipSymbols, 's', 1);
				checkIfSunkShip(p1Grid, shipNames, shipSymbols, 'd', 1);			
				// check if there is a winner
				gameOver = isWinner(p1Grid);
				// increment startPlayer so it will be player2's turn next
				startPlayer++;
				getline(cin, trashBin);
				cout << "Press enter to continue: ";
				getline(cin, enter);
				
				// execute if guess is a hit
				if (hit) {
					outFile << "Player1: " << row << " " << column << " \"hit\"" << endl;			
					
					p2DisplayGrid[intRow][column] = '*';
					p2Grid[intRow][column] = '*';
					numHits1++; //used for the output file
				}
				//execute if guess is a miss
				else {
					outFile << "Player1: " << row << " " << column << " \"miss\"" << endl;	

					p2DisplayGrid[intRow][column] = 'm';
					p2Grid[intRow][column] = 'm';
					numMiss1++; //used for the output file
				}
			}
			//if it is player2's turn execute all of this
			else if (startPlayer == 2) {

				// check if each ship has been sunk
				checkIfSunkShip(p2Grid, shipNames, shipSymbols, 'c', 2);
				checkIfSunkShip(p2Grid, shipNames, shipSymbols, 'b', 2);
				checkIfSunkShip(p2Grid, shipNames, shipSymbols, 'r', 2);
				checkIfSunkShip(p2Grid, shipNames, shipSymbols, 's', 2);
				checkIfSunkShip(p2Grid, shipNames, shipSymbols, 'd', 2);
				// check if there is a winner
				gameOver = isWinner(p2Grid);	

				startPlayer--;
				cout << "Press enter to continue: ";
				getline(cin, enter);
				
				// execute if guess is a hit
				if (hit) {
					outFile << "Player2: " << row << " " << column << " \"hit\"" << endl;

					p1Grid[intRow][column] = '*';
					numHits2++; //used for the output file
				}
				//execute if guess is a miss
				else {
					outFile << "Player2: " << row << " " << column << " \"miss\"" << endl;		

					p1Grid[intRow][column] = 'm';
					numMiss2++; //used for the output file
				}
			}
		
			// clear screen before each turn
			system("clear");
			// display the game board
			displayBoard(p1Grid, rowLetters, p2DisplayGrid, NUM_ROWS, NUM_COLS);


			if (gameOver) {
				cout << "Player" << startPlayer << " has sunk all ships, the game is over!" << endl << endl;

				// add up hits and misses to get the total amount of shots
				shotTotal1 = numHits1 + numMiss1;
				shotTotal2 = numHits2 + numMiss2;
				// get the ration and then multiply by 100 to get it as a percentage
				shotRatio1 = (numHits1 / numMiss1) * 100;
				shotRatio2 = (numHits2 / numMiss2) * 100;

				// output file stats
				cout << endl;
				outFile << "Player" << startPlayer << " was the winner." << endl << endl;

				outFile << "*** Player1 Stats ***" << endl;
				outFile << "Number of Hits: " << numHits1 << endl;
				outFile << "Number of Misses: " << numMiss1 << endl;
				outFile << "Total Shots: " << shotTotal1 << endl;
				outFile << "Hit/Miss Ratio: " << shotRatio1 << "%" << endl;

				outFile << endl;

				outFile << "*** Player2 Stats ***" << endl;
				outFile << "Number of Hits: " << numHits2 << endl;
				outFile << "Number of Misses: " << numMiss2 << endl;
				outFile << "Total Shots: " << shotTotal2 << endl;
				outFile << "Hit/Miss Ratio: " << shotRatio2 << "%" << endl;

				outFile.close();				

				// get whether user would like to play again
				cout << "Type \"play\" to play again or anything else to end program: ";
				cin >> gameState;
			
			}
		}
	}
	return 0;
}
