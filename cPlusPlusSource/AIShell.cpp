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

	std::cout << AI_score << std::endl;
	std::cout << Human_score << std::endl;
	std::cout << std::endl;

	return (AI_score - Human_score);

}

void AIShell::check_columns(int* AI_score, int* Human_score) {
	int temp_AI = 0;
	int temp_Hum = 0;
	bool AI_control = false;
	bool Hum_control = false;
	int sum_of_elems = 0;
	std::vector<int> current;

	for (int i = 0; i < numCols; i++) {
		for (int j = 0; j < numRows; j++) {
			for (int s = 0; s < k; s++) {
				if (s + j >= numRows) {
					current.clear();
					break;
				}
				current.push_back(gameState[i][j + s]);
				if (s = (k - 1)) {
					if (std::find(current.begin(), current.end(), 1) != current.end() && std::find(current.begin(), current.end(), -1) != current.end()) {
						break;
					}
					for (std::vector<int>::iterator it = current.begin(); it != current.end(); ++it) {
						sum_of_elems += *it;
					}
					current.clear();
					if (sum_of_elems == 0) {
						temp_AI++;
						temp_Hum++;
					}
						
					else if (sum_of_elems >= 1) {
							
						if (sum_of_elems == k) {
								temp_AI = 100;
						}
							
						else {
								temp_AI++;
						}
					}

					else {
							
						if (sum_of_elems <= -1) {
								
							if (sum_of_elems == -k) {
									temp_AI = 100;
							}
								
							else {
									temp_AI++;
							}
						}
					}
				}
			}
		}
	}
		*AI_score += temp_AI;
		*Human_score += temp_Hum;
}


void AIShell::check_rows(int* AI_score, int* Human_score) {
	int temp_AI = 0;
	int temp_Hum = 0;
	bool AI_control = false;
	bool Hum_control = false;
	int sum_of_elems = 0;
	std::vector<int> current;

	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			for (int s = 0; s < k; s++) {
				if (s + j >= numCols) {
					current.clear();
					break;
				}
				current.push_back(gameState[i][j + s]);
				if (s = (k - 1)) {
					if (std::find(current.begin(), current.end(), 1) != current.end() && std::find(current.begin(), current.end(), -1) != current.end()) {
						break;
					}
					for (std::vector<int>::iterator it = current.begin(); it != current.end(); ++it) {
						sum_of_elems += *it;
					}
					current.clear();
					if (sum_of_elems == 0) {
						temp_AI++;
						temp_Hum++;
					}

					else if (sum_of_elems >= 1) {

						if (sum_of_elems == k) {
							temp_AI = 100;
						}

						else {
							temp_AI++;
						}
					}

					else {

						if (sum_of_elems <= -1) {

							if (sum_of_elems == -k) {
								temp_AI = 100;
							}

							else {
								temp_AI++;
							}
						}
					}
				}
			}
		}
	}
	*AI_score += temp_AI;
	*Human_score += temp_Hum;
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
