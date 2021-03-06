#ifndef AISHELL_H
#define AISHELL_H

#pragma once
#include <sys/time.h>
#include <vector>

#include "Move.h"


// A new AIShell will be created for every move request.
class AIShell{

public:
	//these represent the values for each piece type.
	static const int AI_PIECE=1;
	static const int HUMAN_PIECE = -1;
	static const int NO_PIECE=0;
	static const int INF = 9999999;



private:
	//Do not alter the values of numRows or numcols.
	//they are used for deallocating the gameState variable.
	int numRows; //the total number of rows in the game state.
	int numCols; //the total number of columns in the game state.
	int **gameState; //a pointer to a two-dimensional array representing the game state.
	bool gravityOn; //this will be true if gravity is turned on. It will be false if gravity is turned off.
	Move lastMove; //this is the move made last by your opponent. If your opponent has not made a move yet (you move first) then this move will hold the value (-1, -1) instead.
	int AI_score;
	int Human_score;
	double start_time;
	std::vector<Move> best_path;
	std::vector<Move> temp_best;
	double move_deadline;
	int index;




public:
	int deadline; //this is how many milliseconds the AI has to make move.
	int k;        // k is the number of pieces a player must get in a row/column/diagonal to win the game. IE in connect 4, this variable would be 4
	int depth;
	bool first;

	AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove);
	~AIShell();
	Move makeMove();
	Move minimax(int d);
	int FindMax(int alpha, int beta, int depth);
	int FindMin(int alpha, int beta, int depth);
	int score();
	int score2();
	void winning_spaces();
	void winning_spaces2();
	inline double time_left();

};

#endif //AISHELL_H
