#include "AIShell.h"
#include <algorithm>
#include <iostream>
#include <numeric>
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
	int max = -100000000;
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
	int min = 100000000;
	if (d == 1) {
		for (int i = 0; i < numCols; i++) {
			for (int j = 0; j < numRows; j++) {
				if (gameState[i][j] == NO_PIECE) {
					gameState[i][j] = HUMAN_PIECE;
					int possible = score();
					if (possible < min) {
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
				if (possible < min) {
					min = possible;
				}
				gameState[i][j] = NO_PIECE;
			}
		}
	}

	return min;
}

int AIShell::FindMax(int d) {
	int max = -100000000;
	if (d == 1) {
		for (int i = 0; i < numCols; i++) {
			for (int j = 0; j < numRows; j++) {
				if (gameState[i][j] == NO_PIECE) {
					gameState[i][j] = AI_PIECE;
					int possible = score();
					if (possible > max) {
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
				int possible = FindMin(d - 1);
				if (possible > max) {
					max = possible;
				}
				gameState[i][j] = NO_PIECE;
			}
		}
	}

	return max;
}

int AIShell::score() {
	AI_score = 0;
	Human_score = 0;

	check_columns();
	check_rows();
	//check_diagonals(&AI_score, &Human_score);

	std::cout << AI_score << std::endl;
	std::cout << Human_score << std::endl;
	std::cout << std::endl;

	return (AI_score - Human_score);

}

void AIShell::check_columns() {
	std::vector<int> in_a_row;
	int size;
	int AI_counter;
	int current;
	int human_counter;
	int p_AIscore;
	int p_Humscore;
	bool last_AI = false;
	bool last_hum = false;
	

	for (int i = 0; i < numCols; i++) {
		for (int j = 0; j < numRows; j++) {
			in_a_row.push_back(gameState[i][j]);
		}
		while (!in_a_row.empty()) {
			current = in_a_row.back();
			in_a_row.pop_back();
			if (current == 1) {
				AI_counter += 1;
				p_AIscore += 2;

				if (human_counter < k) {
					last_hum = false;
					human_counter = 0;
					p_Humscore = 0;
				}

				if (last_AI) {
					p_AIscore += 2;
				}

				last_AI = true;
			}

			else if (current == -1) {
				human_counter += 1;
				p_Humscore += 2;

				if (AI_counter < k) {
					last_AI = false;
					AI_counter = 0;
					p_AIscore = 0;
				}

				if (last_hum) {
					p_Humscore += 2;
				}

				last_hum = true;
			}

			else {
				if (last_hum) {
					human_counter += 1;
					p_Humscore += 1;
				}

				if (last_AI) {
					AI_counter += 1;
					p_AIscore += 1;
				}
			}
		}
		AI_score += p_AIscore;
		Human_score += p_Humscore;
	}
}




void AIShell::check_rows() {
	std::vector<int> in_a_row;
	int size;
	int AI_counter;
	int current;
	int human_counter;
	int p_AIscore;
	int p_Humscore;
	bool last_AI = false;
	bool last_hum = false;


	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			in_a_row.push_back(gameState[j][i]);
		}
		while (!in_a_row.empty()) {
			current = in_a_row.back();
			in_a_row.pop_back();
			if (current == 1) {
				AI_counter += 1;
				p_AIscore += 2;

				if (human_counter < k) {
					last_hum = false;
					human_counter = 0;
					p_Humscore = 0;
				}

				if (last_AI) {
					p_AIscore += 2;
				}

				last_AI = true;
			}

			else if (current == -1) {
				human_counter += 1;
				p_Humscore += 2;

				if (AI_counter < k) {
					last_AI = false;
					AI_counter = 0;
					p_AIscore = 0;
				}

				if (last_hum) {
					p_Humscore += 2;
				}

				last_hum = true;
			}

			else {
				if (last_hum) {
					human_counter += 1;
					p_Humscore += 1;
				}

				if (last_AI) {
					AI_counter += 1;
					p_AIscore += 1;
				}
			}
		}
		AI_score += p_AIscore;
		Human_score += p_Humscore;
	}
}



void AIShell::check_diagonals() {

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
