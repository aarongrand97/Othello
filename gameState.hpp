#include <vector>

class gameState {
	public:
		gameState(char initBoard[8][8]);
		std::vector<std::pair<int,int>> getPossibleMoves(char tile);
		
		bool checkMove(int row, int col, char opp, bool change);

		bool checkLeft(std::pair<int, int> coord, char current, bool change);
		bool checkRight(std::pair<int, int> coord, char current, bool change);
		bool checkUp(std::pair<int, int> coord, char current, bool change);
		bool checkDown(std::pair<int, int> coord, char current, bool change);
		bool checkUpLeft(std::pair<int, int> coord, char current, bool change);
		bool checkDownLeft(std::pair<int, int> coord, char current, bool change);
		bool checkUpRight(std::pair<int, int> coord, char current, bool change);
		bool checkDownRight(std::pair<int, int> coord, char current, bool change);
		
		void printBoard();
		int getScore(char tile);
		double getWeightedScores(char letter);

		
		char board[8][8];
		
		
	
};
