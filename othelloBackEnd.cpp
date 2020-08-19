#include <boost/python.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/to_python_converter.hpp>
#include <iostream>
#include "gameState.hpp"

using std::pair;
using std::vector;
using std::cout;
using std::endl;

// Check  if a move is on the corner of the board
bool checkCorner(pair<int, int> move){
	int row = move.first;
	int col = move.second;
	if(row == 0){
		if(col == 0 || col == 7){
			return true;
		}
	}
	else if(row == 7){
		if(col == 0 || col == 7){
			return true;
		}		
	}
	return false;
}


boost::python::object makeMove(boost::python::list& py_board, std::string comp_tile){
	char orig_board[8][8]= {};
	
	char comp_char = comp_tile == "WHITE_TILE" ? 'w' : 'b';
	char plyr_char = comp_tile == "WHITE_TILE" ? 'b' : 'w';
	
	
	// Create the original board as it is passed in from the python game 
	for(int col = 0; col != len(py_board); col++){
		for(int row = 0; row != len(py_board[col]); row++){
			std::string tile = boost::python::extract<std::string>(py_board[col][row]);
			if(tile == "WHITE_TILE"){
				orig_board[row][col] = 'w';
			}
			else if(tile == "BLACK_TILE"){
				orig_board[row][col] = 'b';
			}
			else
				orig_board[row][col] = ' ';
		}	
	}
		
	
	// Store the best move to return
	pair<int,int> bestMove = std::make_pair(-1, -1);
	
	// Get all possible computer moves 
	gameState originalState = gameState(orig_board);
	vector<pair<int,int>> compPossMoves = originalState.getPossibleMoves(comp_char);
	// if theres only one possible move, do it
	if((int)compPossMoves.size() == 1){
		pair<int, int> move = compPossMoves[0];	
		return boost::python::make_tuple(move.second,move.first);
	}
	
	vector<float> compScoresMax = {}; // store the maximum score the player can get after each computer move
	
	// Now go through each move and apply it to a duplicate
	for(vector<pair<int,int>>::iterator iter = compPossMoves.begin(); iter != compPossMoves.end(); iter++){
		// if can take corner, do
		if(checkCorner(*iter) == true){
			return boost::python::make_tuple((*iter).second,(*iter).first);
		}
		gameState dupState = gameState(orig_board);
		dupState.checkMove((*iter).first, (*iter).second, comp_char, true);
		// Get the possible player moves following this computer move
		vector<pair<int,int>> plyrPossMoves = dupState.getPossibleMoves(plyr_char);
		// if player cant go, is the ideal move, do it
		if((int)plyrPossMoves.size() == 0){
			bestMove.first = (*iter).first;
			bestMove.second= (*iter).second;
			return boost::python::make_tuple(bestMove.second,bestMove.first);
		}
		vector<float> compScores = {}; // store the player scores
		// Go through the moves and see what the player score is. If minimised, update the bestMove.
		for(vector<pair<int,int>>::iterator plyr_iter = plyrPossMoves.begin(); plyr_iter != plyrPossMoves.end(); plyr_iter++){
			gameState dupdupState = gameState(dupState.board);
			dupdupState.checkMove((*plyr_iter).first, (*plyr_iter).second, plyr_char, true);
			compScores.push_back(dupdupState.getWeightedScores(plyr_char));
		}
		compScoresMax.push_back(*max_element(compScores.begin(), compScores.end())); // store the maximum possible
	}	
	
	// find which computer move results in the minimum maximum player score
	int indexOfMin = std::min_element(compScoresMax.begin(), compScoresMax.end()) - compScoresMax.begin();
	bestMove = compPossMoves.at(indexOfMin);
	// stupid order in python game so .second goes 1st
	return boost::python::make_tuple(bestMove.second,bestMove.first);
}


