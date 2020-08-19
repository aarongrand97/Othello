#include <iostream>
#include "gameState.hpp"

using std::vector;
using std::pair;
using std::cout;
using std::endl;


gameState::gameState(char initBoard[8][8]){
	for(int row = 0; row != 8; row++){
		for(int col = 0; col != 8; col++){
			board[row][col] = initBoard[row][col];
		}
	}	
}

vector<pair<int,int>> gameState::getPossibleMoves(char tile){
	vector<pair<int,int>> possibles;
	for(int row = 0; row != 8; row++){
		for(int col = 0; col != 8; col++){
			if(checkMove(row, col, tile, false)){
				possibles.push_back(std::make_pair(row,col));
			}
		}
	}
	//cout << possibles.size() << endl;
	return possibles;
}

bool gameState::checkMove(int row, int col, char current, bool change) {
	bool valid = false;
	char oppositeCounter = current == 'w' ? 'b' : 'w';
	// check space is available
	if (board[row][col] != ' ')
		return false;

	if (col > 1) { // check left
		if (board[row][col - 1] == oppositeCounter)
			if (checkLeft(std::make_pair(row, col), current, change)) {
				valid = true;
			}
	}
	if (col < 6) { // check right
		if (board[row][col + 1] == oppositeCounter)
			if (checkRight(std::make_pair(row, col), current, change))
				valid = true;
	}
	if (row > 1) { // check up
		if (board[row - 1][col] == oppositeCounter)
			if (checkUp(std::make_pair(row, col), current, change))
				valid = true;
	}
	if (row < 6) { // check down
		if (board[row + 1][col] == oppositeCounter)
			if (checkDown(std::make_pair(row, col), current, change))
				valid = true;
	}
	if (col > 1 && row > 1) { // diag up left
		if (board[row - 1][col - 1] == oppositeCounter)
			if (checkUpLeft(std::make_pair(row, col), current, change))
				valid = true;
	}
	if (col > 0 && row < 7) { // diag down left
		if (board[row + 1][col - 1] == oppositeCounter)
			if (checkDownLeft(std::make_pair(row, col), current, change))
				valid = true;
	}
	if (col < 6 && row>1) { // diag up right
		if (board[row - 1][col + 1] == oppositeCounter)
			if (checkUpRight(std::make_pair(row, col), current, change))
				valid = true;
	}
	if (col < 6 && row < 6) { // diag down right
		if (board[row + 1][col + 1] == oppositeCounter)
			if (checkDownRight(std::make_pair(row, col), current, change))
				valid = true;
	}
	if (change) {
		board[row][col] = current;
	}
	return valid;
}

bool gameState::checkLeft(std::pair<int, int> coord, char current, bool change) {
	bool found = false;
	char oppositeCounter = current == 'w' ? 'b' : 'w';
	int y = coord.first;
	int x = coord.second;
	//cout << y << "," << x << endl;
	for (int i = x - 2; i >= 0; i--) {
		if (board[y][i] == current) {
			found = true;
			// Now go backwards and change the values
			if (change) {
				for (int p = x - 1; p != i; p--)
					board[y][p] = current;
			}
			break;
		}
		if (board[y][i] == ' ') {
			found = false;
			break;
		}
	}
	return found;
}
bool gameState::checkRight(std::pair<int, int> coord, char current, bool change) {
	bool found = false;
	char oppositeCounter = current == 'w' ? 'b' : 'w';
	int y = coord.first;
	int x = coord.second;
	for (int i = x + 2; i <= 7; i++) {
		if (board[y][i] == current) {
			found = true;
			if (change) {
				for (int p = x + 1; p != i; p++)
					board[y][p] = current;
			}
			break;
		}
		if (board[y][i] == ' ') {
			found = false;
			break;
		}
	}
	return found;
}

bool gameState::checkUp(std::pair<int, int> coord, char current, bool change) {
	bool found = false;
	char oppositeCounter = current == 'w' ? 'b' : 'w';
	int y = coord.first;
	int x = coord.second;
	for (int i = y - 2; i >= 0; i--) {
		if (board[i][x] == current) {
			found = true;
			if (change) {
				for (int p = y - 1; p != i; p--)
					board[p][x] = current;
			}
			break;
		}
		if (board[i][x] == ' ') {
			found = false;
			break;
		}
	}
	return found;
}

bool gameState::checkDown(std::pair<int, int> coord, char current, bool change) {
	bool found = false;
	char oppositeCounter = current == 'w' ? 'b' : 'w';
	int y = coord.first;
	int x = coord.second;
	for (int i = y + 2; i <= 7; i++) {
		if (board[i][x] == current) {
			found = true;
			if (change) {
				for (int p = y + 1; p != i; p++)
					board[p][x] = current;
			}
			break;
		}
		if (board[i][x] == ' ') {
			found = false;
			break;
		}
	}
	return found;
}

bool gameState::checkUpRight(std::pair<int, int> coord, char current, bool change) {
	bool found = false;
	char oppositeCounter = current == 'w' ? 'b' : 'w';
	int y = coord.first;
	int x = coord.second;
	int i = x + 2;
	int j = y - 2;
	while (i <= 7 && j >= 0) {
		if (board[j][i] == current) {
			found = true;
			int p = x + 1;
			int k = y - 1;
			if (change) {
				while (p != i) {
					board[k][p] = current;
					p++;
					k--;
				}
			}
			break;
		}
		if (board[j][i] == ' ') {
			found = false;
			break;
		}
		i++;
		j--;
	}
	return found;
}

bool gameState::checkUpLeft(std::pair<int, int> coord, char current, bool change) {
	bool found = false;
	char oppositeCounter = current == 'w' ? 'b' : 'w';
	int y = coord.first;
	int x = coord.second;
	int i = x - 2;
	int j = y - 2;
	while (i >= 0 && j >= 0) {
		if (board[j][i] == current) {
			found = true;
			int p = x - 1;
			int k = y - 1;
			if (change) {
				while (p != i) {
					board[k][p] = current;
					p--;
					k--;
				}
			}
			break;
		}
		if (board[j][i] == ' ') {
			found = false;
			break;
		}
		i--;
		j--;
	}
	return found;
}

bool gameState::checkDownRight(std::pair<int, int> coord, char current, bool change) {
	bool found = false;
	char oppositeCounter = current == 'w' ? 'b' : 'w';
	int y = coord.first;
	int x = coord.second;
	int i = x + 2;
	int j = y + 2;
	while (i <= 7 && j <= 7) {
		if (board[j][i] == current) {
			found = true;
			int p = x + 1;
			int k = y + 1;
			if (change) {
				while (p != i) {
					board[k][p] = current;
					p++;
					k++;
				}
			}
			break;
		}
		if (board[j][i] == ' ') {
			found = false;
			break;
		}
		i++;
		j++;
	}
	return found;
}

bool gameState::checkDownLeft(std::pair<int, int> coord, char current, bool change) {
	bool found = false;
	char oppositeCounter = current == 'w' ? 'b' : 'w';
	int y = coord.first;
	int x = coord.second;
	int i = x - 2;
	int j = y + 2;
	while (i >= 0 && j <= 7) {
		if (board[j][i] == current) {
			found = true;
			int p = x - 1;
			int k = y + 1;
			if (change) {
				while (p != i) {
					board[k][p] = current;
					p--;
					k++;
				}
			}
			break;
		}
		if (board[j][i] == ' ') {
			found = false;
			break;
		}
		i--;
		j++;
	}
	return found;
}

void gameState::printBoard(){
	cout<< " +-0-+-1-+-2-+-3-+-4-+-5-+-6-+-7-+"<<endl;
	for(int i = 0; i != 8; i++){
		cout<< " +---+---+---+---+---+---+---+---+"<<endl;
		cout<< " | ";
		for(int j = 0; j != 8; j++){
			cout<<board[i][j] << " | ";
		}
		cout << i;
		cout<<endl;
	}
	cout<< " +---+---+---+---+---+---+---+---+ "<<endl;
}

int gameState::getScore(char tile){
	int score = 0;
	for(int row = 0; row != 8; row++){
		for(int col = 0; col != 8; col++){
			if(board[row][col] == tile)
				score++;
		}
	}
	return score;
}

double gameState::getWeightedScores(char letter) {
	
	double weights[8][8];

	double corner_default[4][4] = {
		{50.00, -3.03, 0.99, 0.43},
		{-4.12, -1.81, -0.08, -0.27},
		{1.33, -0.04, 0.51, 0.07},
		{0.63, -0.18, -0.04, -0.01}
	};

	double corner_captured[4][4] = {
		{50.00, 25.00, 10.00, 6.00},
		{25.00, 5.00, -0.08, -0.27},
		{10.00, -0.04, 0.51, 0.07},
		{6.00, -0.18, -0.04, -0.01}
	};
	// top left
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			if (board[0][0] == letter)
				weights[row][col] = corner_captured[row][col];
			else
				weights[row][col] = corner_default[row][col];
		}
	}
	// top right
	for (int row = 0; row < 4; row++) {
		for (int col = 4; col < 8; col++) {
			if (board[0][7] == letter)
				weights[row][col] = corner_captured[row][7-col];
			else
				weights[row][col] = corner_default[row][7-col];
		}
	}
	//bottom left
	for (int row = 4; row < 8; row++) {
		for (int col = 0; col < 4; col++) {
			if (board[7][0] == letter)
				weights[row][col] = corner_captured[7-row][col];
			else
				weights[row][col] = corner_default[7-row][col];
		}
	}
	//bottom right
	for (int row = 4; row < 8; row++) {
		for (int col = 4; col < 8; col++) {
			if (board[7][7] == letter)
				weights[row][col] = corner_captured[7 - row][7 - col];
			else
				weights[row][col] = corner_default[7 - row][7 - col];
		}
	}

	double weightedScore = 0;
	for (int i = 0; i != 8; i++) {
		for (int j = 0; j != 8; j++) {
			if (board[i][j] == letter)
				weightedScore +=weights[i][j];
		}
	}
	return weightedScore;
}
	


