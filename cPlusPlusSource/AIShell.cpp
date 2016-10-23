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

	for (int i = 0; i < numCols; i++) {
		for (int j = 0; j < numRows; j++) {
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
		for (int i = 0; i < numCols; i++) {
			for (int j = 0; j < numRows; j++) {
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
	
	for (int i = 0; i < numCols; i++) {
		for (int j = 0; j < numRows; j++) {
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
	int max = -100;
	if (d == 1) {
		for (int i = 0; i < numCols; i++) {
			for (int j = 0; j < numRows; j++) {
				if (gameState[i][j] == NO_PIECE) {
					gameState[i][j] = AI_PIECE;
					int possible = score();
					if (possible >= max) {
						max = possible;
					}
					gameState[i][j] = NO_PIECE;
				}
			}
		}
		return max;
	}

	for (int i = 0; i < numCols; i++) {
		for (int j = 0; j < numRows; j++) {
			if (gameState[i][j] == NO_PIECE) {
				gameState[i][j] = AI_PIECE;
				int possible = FindMax(d - 1);
				if (possible >= max) {
					max = possible;
				}
				gameState[i][j] = NO_PIECE;
			}
		}
	}

	return max;
}

int AIShell::score() {
	int AI_score = 0;
	int Human_score = 0;

	check_columns(&AI_score, &Human_score);
	check_rows(&AI_score, &Human_score);
	//check_diagonals(&AI_score, &Human_score);

	return (AI_score - Human_score);

}

void AIShell::check_columns(int* AI_score, int* Human_score) {
	int temp_AI = 0;
	int temp_Hum = 0;
	bool AI_control = false;
	bool Hum_control = false;

	for (int i = 0; i < numCols; i++) {
		for (int j = 0; j < numRows; j++) {

			if (gameState[i][j] == AI_PIECE){
				AI_control = true;
				temp_AI++;
				if (Hum_control == true) {
					Hum_control = 0;
					Hum_control = false;
				}
			}

			if (gameState[i][j] == HUMAN_PIECE) {
				Hum_control = true;
				temp_Hum++;
				if (AI_control == true) {
					AI_control = 0;
					AI_control = false;
				}
			}

			if (gameState[i][j] == NO_PIECE) {
				if (Hum_control) {
					temp_Hum++;
				}
				if (AI_control) {
					temp_AI++;
				}
			}
		}
		*AI_score += temp_AI;
		*Human_score += temp_Hum;
	}
}

void AIShell::check_rows(int* AI_score, int* Human_score) {
	int temp_AI = 0;
	int temp_Hum = 0;
	bool AI_control = false;
	bool Hum_control = false;

	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {

			if (gameState[j][i] == AI_PIECE) {
				AI_control = true;
				temp_AI++;
				if (Hum_control == true) {
					Hum_control = 0;
					Hum_control = false;
				}
			}

			if (gameState[j][i] == HUMAN_PIECE) {
				Hum_control = true;
				temp_Hum++;
				if (AI_control == true) {
					AI_control = 0;
					AI_control = false;
				}
			}

			if (gameState[j][i] == NO_PIECE) {
				if (Hum_control) {
					temp_Hum++;
				}
				if (AI_control) {
					temp_AI++;
				}
			}
		}
		*AI_score += temp_AI;
		*Human_score += temp_Hum;
	}
}

void AIShell::check_diagonals(int* AI_score, int* Human_score) {
	int temp_AI = 0;
	int temp_Hum = 0;
	return;
	bool AI_control = false;
	bool Hum_control = false;

	for (int i = 0; i < numCols; i++) {
		for (int j = 0; j < numRows; j++) {

			if (gameState[i][j] == AI_PIECE) {
				AI_control = true;
				temp_AI++;
				if (Hum_control == true) {
					Hum_control = 0;
					Hum_control = false;
				}
			}

			if (gameState[i][j] == HUMAN_PIECE) {
				Hum_control = true;
				temp_Hum++;
				if (AI_control == true) {
					AI_control = 0;
					AI_control = false;
				}
			}

			if (gameState[i][j] == NO_PIECE) {
				if (Hum_control) {
					temp_Hum++;
				}
				if (AI_control) {
					temp_AI++;
				}
			}
		}
		*AI_score += temp_AI;
		*Human_score += temp_Hum;
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
