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
	check_rdiagonals();
	check_ldiagonals();

	return (AI_score - Human_score);

}

void AIShell::check_columns() {
	std::vector<int> in_a_row;
	int AI_counter;
	int current;
	int AI_row;
	int Hum_row;
	int human_counter;
	int p_AIscore;
	int p_Humscore;
	bool last_AI;
	bool last_hum;
	

	for (int i = 0; i < numCols; i++) {
		AI_counter = 0;
		human_counter = 0;
		p_AIscore = 0;
		p_Humscore = 0;
		AI_row = 0;
		Hum_row = 0;
		last_AI = false;
		last_hum = false;
		for (int j = 0; j < numRows; j++) {
			in_a_row.push_back(gameState[i][j]);
		}

		while (!in_a_row.empty()) {
			current = in_a_row.back();
			in_a_row.pop_back();
			if (current == 1) {
				AI_counter += 1;
				AI_row += 1;

				if (human_counter < k) {
					last_hum = false;
					human_counter = 0;
					p_Humscore = 0;
					Hum_row = 0;
				}

				if (AI_row != k) {
					p_AIscore += (5 * AI_row);
				}

				if (AI_row == k) {
					p_AIscore = 1000;
					break;
				}

				last_AI = true;

			}

			else if (current == -1) {
				human_counter += 1;
				Hum_row += 1;

				if (AI_counter < k) {
					last_AI = false;
					AI_counter = 0;
					p_AIscore = 0;
					AI_row = 0;

				}

				if (Hum_row != k) {
					p_Humscore += (5 * Hum_row);
				}

				if (Hum_row == k) {
					p_Humscore = 10000;
					break;
				}

				last_hum = true;
			}

			else {
				if (last_hum) {
					human_counter += 1;
					p_Humscore += 1;
					Hum_row = 0;
				}

				if (last_AI) {
					AI_counter += 1;
					p_AIscore += 1;
					AI_row = 0;
				}
			}
		}
		AI_score += p_AIscore;
		Human_score += p_Humscore;
	}
}




void AIShell::check_rows() {
	std::vector<int> in_a_row;
	int AI_counter;
	int current;
	int AI_row;
	int Hum_row;
	int human_counter;
	int p_AIscore;
	int p_Humscore;
	bool last_AI;
	bool last_hum;


	for (int i = 0; i < numRows; i++) {
		AI_counter = 0;
		human_counter = 0;
		p_AIscore = 0;
		p_Humscore = 0;
		AI_row = 0;
		Hum_row = 0;
		last_AI = false;
		last_hum = false;
		for (int j = 0; j < numCols; j++) {
			in_a_row.push_back(gameState[j][i]);
		}

		while (!in_a_row.empty()) {
			current = in_a_row.back();
			in_a_row.pop_back();
			if (current == 1) {
				AI_counter += 1;
				AI_row += 1;

				if (human_counter < k) {
					last_hum = false;
					human_counter = 0;
					p_Humscore = 0;
					Hum_row = 0;
				}

				if (AI_row != k) {
					p_AIscore += (5 * AI_row);
				}

				if (AI_row == k) {
					p_AIscore = 1000;
					break;
				}

				last_AI = true;

			}

			else if (current == -1) {
				human_counter += 1;
				Hum_row += 1;

				if (AI_counter < k) {
					last_AI = false;
					AI_counter = 0;
					p_AIscore = 0;
					AI_row = 0;

				}

				if (Hum_row != k) {
					p_Humscore += (5 * Hum_row);
				}

				if (Hum_row == k) {
					p_Humscore = 10000;
					break;
				}

				last_hum = true;
			}

			else {
				if (last_hum) {
					human_counter += 1;
					p_Humscore += 1;
					Hum_row = 0;
				}

				if (last_AI) {
					AI_counter += 1;
					p_AIscore += 1;
					AI_row = 0;
				}
			}
		}
		AI_score += p_AIscore;
		Human_score += p_Humscore;
	}
}



void AIShell::check_rdiagonals() {
	std::vector<int> in_a_row;
	int AI_counter;
	int current;
	int AI_row;
	int Hum_row;
	int human_counter;
	int p_AIscore;
	int p_Humscore;
	bool last_AI;
	bool last_hum;


	for (int i = 0; (i + (k-1)) <= numCols; i++) {
		AI_counter = 0;
		human_counter = 0;
		p_AIscore = 0;
		p_Humscore = 0;
		AI_row = 0;
		Hum_row = 0;
		last_AI = false;
		last_hum = false;
		for (int j = 0; j + (k - 1) <= numRows; j++) {
			for (int s = 1; (s + i) < numCols && (s + j) < numRows; s++)
				in_a_row.push_back(gameState[i + s][j + s]);
		}

		while (!in_a_row.empty()) {
			current = in_a_row.back();
			in_a_row.pop_back();
			if (current == 1) {
				AI_counter += 1;
				AI_row += 1;

				if (human_counter < k) {
					last_hum = false;
					human_counter = 0;
					p_Humscore = 0;
					Hum_row = 0;
				}

				if (AI_row != k) {
					p_AIscore += (5 * AI_row);
				}

				if (AI_row == k) {
					p_AIscore = 1000;
					break;
				}

				last_AI = true;

			}

			else if (current == -1) {
				human_counter += 1;
				Hum_row += 1;

				if (AI_counter < k) {
					last_AI = false;
					AI_counter = 0;
					p_AIscore = 0;
					AI_row = 0;

				}

				if (Hum_row != k) {
					p_Humscore += (5 * Hum_row);
				}

				if (Hum_row == k) {
					p_Humscore = 10000;
					break;
				}

				last_hum = true;
			}

			else {
				if (last_hum) {
					human_counter += 1;
					p_Humscore += 1;
					Hum_row = 0;
				}

				if (last_AI) {
					AI_counter += 1;
					p_AIscore += 1;
					AI_row = 0;
				}
			}
		}
		AI_score += p_AIscore;
		Human_score += p_Humscore;
	}
}

void AIShell::check_ldiagonals() {
	std::vector<int> in_a_row;
	int AI_counter;
	int current;
	int AI_row;
	int Hum_row;
	int human_counter;
	int p_AIscore;
	int p_Humscore;
	bool last_AI;
	bool last_hum;


	for (int i = numCols; i >= (numCols - k); i--) {
		AI_counter = 0;
		human_counter = 0;
		p_AIscore = 0;
		p_Humscore = 0;
		AI_row = 0;
		Hum_row = 0;
		last_AI = false;
		last_hum = false;
		for (int j = 0; j <= (numRows - k); j++) {
			for (int s = 1; (i - s) < numCols && (s + j) < numRows; s++)
				in_a_row.push_back(gameState[i - s][j + s]);
		}

		while (!in_a_row.empty()) {
			current = in_a_row.back();
			in_a_row.pop_back();
			if (current == 1) {
				AI_counter += 1;
				AI_row += 1;

				if (human_counter < k) {
					last_hum = false;
					human_counter = 0;
					p_Humscore = 0;
					Hum_row = 0;
				}

				if (AI_row != k) {
					p_AIscore += (5 * AI_row);
				}

				if (AI_row == k) {
					p_AIscore = 1000;
					break;
				}

				last_AI = true;

			}

			else if (current == -1) {
				human_counter += 1;
				Hum_row += 1;

				if (AI_counter < k) {
					last_AI = false;
					AI_counter = 0;
					p_AIscore = 0;
					AI_row = 0;

				}

				if (Hum_row != k) {
					p_Humscore += (5 * Hum_row);
				}

				if (Hum_row == k) {
					p_Humscore = 10000;
					break;
				}

				last_hum = true;
			}

			else {
				if (last_hum) {
					human_counter += 1;
					p_Humscore += 1;
					Hum_row = 0;
				}

				if (last_AI) {
					AI_counter += 1;
					p_AIscore += 1;
					AI_row = 0;
				}
			}
		}
		AI_score += p_AIscore;
		Human_score += p_Humscore;
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
