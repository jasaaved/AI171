#include "AIShell.h"
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <vector>

AIShell::AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove)
{
	this->deadline=0;
	this->numRows=numRows;
	this->numCols=numCols;
	this->gravityOn=gravityOn;
	this->gameState=gameState;
	this->lastMove=lastMove;
}


AIShell::~AIShell()
{
	
	//delete the gameState variable.
	for (int i =0; i<numCols; i++){
		delete [] gameState[i];
	}
	delete [] gameState;

}

Move AIShell::minimax(int d) {
	int max = -100;
	int col = 0;
	int row = 0;

	for (int i = 0; i <= numCols; i++) {
		for (int j = 0; j <= numRows; j++) {
			if (gameState[i][j] == NO_PIECE) {
				gameState[i][j] = AI_PIECE;
				int possible = FindMin(d - 1);
				if (possible >= max) {
					max = possible;
					col = i;
					row = j;
				}
				gameState[i][j] = NO_PIECE;
			}
		}
	}

	return Move(col, row);
}

int AIShell::FindMin(int d) {
	int min = 100;
	if (d == 1) {
		for (int i = 0; i <= numCols; i++) {
			for (int j = 0; j <= numRows; j++) {
				if (gameState[i][j] == NO_PIECE) {
					gameState[i][j] = HUMAN_PIECE;
					int possible = score();
					if (possible <= min) {
						min = possible;
					}
					gameState[i][j] = NO_PIECE;
				}
			}
		}
		return min;
	}
	
	for (int i = 0; i <= numCols; i++) {
		for (int j = 0; j <= numRows; j++) {
			if (gameState[i][j] == NO_PIECE) {
				gameState[i][j] = HUMAN_PIECE;
				int possible = FindMax(d - 1);
				if (possible <= min) {
					min = possible;
				}
				gameState[i][j] = NO_PIECE;
			}
		}
	}

	return min;
}

int AIShell::FindMax(int d) {
	if (d == 0) {
		heuristic(1);
	}
}

int AIShell::heuristic(int m) {
	int max = -100;
	int min = 100;
	int col = 0;
	int row = 0;
	if (m = 1){
		for (int i = 0; i <= numCols; i++) {
			for (int j = 0; j <= numRows; j++) {
				if (gameState[i][j] == NO_PIECE) {
					gameState[i][j] = AI_PIECE;
					int possible = score();
					if (possible >= max) {
						max = possible;
						col = i;
						row = j;
					}
					gameState[i][j] = NO_PIECE;
				}
			}
		}
	}

	if (m = 0) {
		for (int i = 0; i <= numCols; i++) {
			for (int j = 0; j <= numRows; j++) {
				if (gameState[i][j] == NO_PIECE) {
					gameState[i][j] = HUMAN_PIECE;
					int possible = score();
					if (possible <= min) {
						 min = possible;
						col = i;
						row = j;
					}
					gameState[i][j] = NO_PIECE;
				}
			}
		}
	}	
}



Move AIShell::makeMove(){

	return minimax(depth);

	//int col = rand() % numCols;
	//int row = rand() % numRows;

	//while (gameState[col][row] != NO_PIECE){
	//	col = rand() % numCols;
	//	row = rand() % numRows;
	//}
	//Move m(col, row);
	//return m;
	 
}
