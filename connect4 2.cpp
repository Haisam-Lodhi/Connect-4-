#include <iostream>
#include <string>
#include <iomanip> // For better formatting
using namespace std;

const int ROWS = 6;
const int COLS = 7;

char board[ROWS][COLS];

// Function to print colored text
void printColoredText(string text, string color) {
	if (color == "red") {
		cout << "\033[31m" << text << "\033[0m"; // Red text
	}
	else if (color == "yellow") {
		cout << "\033[33m" << text << "\033[0m"; // Yellow text
	}
	else if (color == "green") {
		cout << "\033[32m" << text << "\033[0m"; // Green text
	}
	else if (color == "cyan") {
		cout << "\033[36m" << text << "\033[0m"; // Cyan text
	}
	else {
		cout << text; // Default text
	}
}

void initializeBoard() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			board[i][j] = ' ';
		}
	}
}

void printBoard() {
	system("CLS");
	cout << "<===================GAME=====================>\n";
	printColoredText("..............CONNECT  FOUR(4)..........\n", "cyan");
	cout << " 2 Players (Game)\n\n";
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			cout << "| ";
			if (board[i][j] == 'X') {
				printColoredText(string(1, board[i][j]), "red");
			}
			else if (board[i][j] == 'O') {
				printColoredText(string(1, board[i][j]), "yellow");
			}
			else {
				cout << board[i][j];
			}
			cout << " ";
		}
		cout << "|\n";
		for (int j = 0; j < COLS; j++) {
			cout << "-----";
		}
		cout << "\n";
	}
}

bool isColumnFull(int col) {
	return board[0][col] != ' ';
}

bool isValidMove(int col) {
	return col >= 0 && col < COLS && !isColumnFull(col);
}

void makeMove(int col, char playerSymbol) {
	for (int i = ROWS - 1; i >= 0; i--) {
		if (board[i][col] == ' ') {
			board[i][col] = playerSymbol;
			break;
		}
	}
}

bool checkForWin(char playerSymbol) {
	// Check horizontally
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS - 3; j++) {
			if (board[i][j] == playerSymbol &&
				board[i][j + 1] == playerSymbol &&
				board[i][j + 2] == playerSymbol &&
				board[i][j + 3] == playerSymbol) {
				return true;
			}
		}
	}

	// Check vertically
	for (int i = 0; i < ROWS - 3; i++) {
		for (int j = 0; j < COLS; j++) {
			if (board[i][j] == playerSymbol &&
				board[i + 1][j] == playerSymbol &&
				board[i + 2][j] == playerSymbol &&
				board[i + 3][j] == playerSymbol) {
				return true;
			}
		}
	}

	// Check diagonally (positive slope)
	for (int i = 0; i < ROWS - 3; i++) {
		for (int j = 0; j < COLS - 3; j++) {
			if (board[i][j] == playerSymbol &&
				board[i + 1][j + 1] == playerSymbol &&
				board[i + 2][j + 2] == playerSymbol &&
				board[i + 3][j + 3] == playerSymbol) {
				return true;
			}
		}
	}

	// Check diagonally (negative slope)
	for (int i = 3; i < ROWS; i++) {
		for (int j = 0; j < COLS - 3; j++) {
			if (board[i][j] == playerSymbol &&
				board[i - 1][j + 1] == playerSymbol &&
				board[i - 2][j + 2] == playerSymbol &&
				board[i - 3][j + 3] == playerSymbol) {
				return true;
			}
		}
	}

	return false;
}

bool isBoardFull() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (board[i][j] == ' ') {
				return false;
			}
		}
	}
	return true;
}

int main() {
	string player1, player2;
	char currplayerSymbol = 'X';
	string currplayerName;
	int column;

	// Get player names
	cout << "Enter name for Player 1 (X): ";
	getline(cin, player1);
	cout << "Enter name for Player 2 (O): ";
	getline(cin, player2);

	// Welcome screen
	system("CLS");
	printColoredText("<===================CONNECT FOUR=====================>\n\n", "cyan");
	cout << "Get ready!\n";
	printColoredText(player1 + " (X)", "red");
	cout << " vs ";
	printColoredText(player2 + " (O)\n\n", "yellow");
	system("pause");

	initializeBoard();

	do {
		printBoard();

		currplayerName = (currplayerSymbol == 'X') ? player1 : player2;

		cout << currplayerName << "'s turn ("
			<< (currplayerSymbol == 'X' ? "\033[31mX\033[0m" : "\033[33mO\033[0m")
			<< "). Enter column (0-6): ";
		cin >> column;

		if (isValidMove(column)) {
			makeMove(column, currplayerSymbol);

			if (checkForWin(currplayerSymbol)) {
				printBoard();
				printColoredText(currplayerName + " wins!\n", "green");
				break;
			}
			else if (isBoardFull()) {
				printBoard();
				printColoredText("It's a draw!\n", "cyan");
				break;
			}

			// Switch to the other player
			currplayerSymbol = (currplayerSymbol == 'X') ? 'O' : 'X';
		}
		else {
			printColoredText("Invalid move. Try again.\n", "red");
		}

	} while (true);

	system("pause");
	return 0;
}
