/*  Name: Connor Deide
	Date: 11/20/2020
	Class: CPSC 121, Fall 2020
	Programming Assignment: PA8
	Description:This program simulates the popular game of Battleship in which the user plays against the computer. The user has the choice to place their ships manually or randomly and the inputs coordinates to attack the computers board. In turn, the computer makes random guesses of coordinates to attack the user's board. First player to sink all of the opponents ships wins. Program also sends info and data to the output file battleship.log.
*/

#ifndef Deide_PA8_H
#define Deide_PA8_H

#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

// constant variables
const int NUM_ROWS = 10;
const int NUM_COLS = 10;
const int colNumbers[NUM_COLS] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const char rowLetters[NUM_ROWS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

// lets store ship info in 3 parallel arrays
const string shipNames[] = {"Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer"};
const char shipSymbols[] = {'c', 'b', 'r', 's', 'd'};
const int shipSizes[] = {5, 4, 3, 3, 2};

// function prototypes
void welcomeScreen(void);
void fillArray(char[NUM_ROWS][NUM_COLS], int, int);
void printArray(const char[NUM_ROWS][NUM_COLS], const char[NUM_ROWS], int, int);
int selectWhoStartsFirst();
void manuallyPlaceShipsOnBoard(char[NUM_ROWS][NUM_COLS], const int[], const char[], const string[], const char[NUM_ROWS]);
void randomlyPlaceShipsOnBoard(char[NUM_ROWS][NUM_COLS], const int[], const char[]);
void displayBoard(const char[NUM_ROWS][NUM_COLS], const char[NUM_ROWS], char[NUM_ROWS][NUM_COLS], int, int);
bool checkShot(char[NUM_ROWS][NUM_COLS], int, int);
bool isWinner(char[NUM_ROWS][NUM_COLS]);
void updateBoard(char[NUM_ROWS][NUM_COLS], bool, int, int);
void checkIfSunkShip(char[NUM_ROWS][NUM_COLS], const string[], const char[], char, int);

#endif
