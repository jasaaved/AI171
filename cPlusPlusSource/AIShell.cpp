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
	int counter;
	int temp_counter;
	

	for (int i = 0; i < numCols; i++) {
		for (int j = 0; j < numRows; j++) {
			counter = 1;
			temp_counter = 1;
			in_a_row.clear();
			for (int s = 0; s < k; s++) {
				if ((s + j) >= numRows) {
					break;
				}

				in_a_row.push_back(gameState[i][j + s]);

				if (s <= (k - 1)) {
					int* num1 = &in_a_row[0];
					int* num2 = &in_a_row[1];

					size = in_a_row.size();
					if (std::find(in_a_row.begin(), in_a_row.end(), 1) != in_a_row.end() && std::find(in_a_row.begin(), in_a_row.end(), -1) != in_a_row.end()) {
						AI_score += 0;
						Human_score += 0;
					}

					else if (std::find(in_a_row.begin(), in_a_row.end(), 1) != in_a_row.end()) {

						for (int i = 0; i < size; i++){
							if (*num1 == *num2 && (*num1 == 1)) {
								temp_counter++;
								if (temp_counter > counter) {
									counter = temp_counter;
								}
							}
							else{
								temp_counter = 1;
							}
							num1++;
							num2++;

						}
						AI_score += (counter * 5);
					}


					else if (std::find(in_a_row.begin(), in_a_row.end(), -1) != in_a_row.end()) {
						for (int i = 0; i < size; i++) {
							if (*num1 == *num2 && (*num1 == -1)) {
								temp_counter++;
								if (temp_counter > counter) {
									counter = temp_counter;
								}
							}
							else {
								temp_counter = 1;
							}
							num1++;
							num2++;

						}
						Human_score += (counter * 5);
					}
					else {
						AI_score++;
						Human_score++;
					}
				}
			}
		}
	}
}




void AIShell::check_rows() {
	std::vector<int> in_a_row;
	int size;
	int counter;
	int temp_counter;

	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			counter = 1;
			temp_counter = 1;
			in_a_row.clear();
			for (int s = 0; s < k; s++) {
				if ((s + j) >= numCols) {
					break;
				}

				in_a_row.push_back(gameState[j + s][i]);

				if (s <= (k - 1)) {
					int* num1 = &in_a_row[0];
					int* num2 = &in_a_row[1];
					size = in_a_row.size();
					if (std::find(in_a_row.begin(), in_a_row.end(), 1) != in_a_row.end() && std::find(in_a_row.begin(), in_a_row.end(), -1) != in_a_row.end()) {
						AI_score += 0;
						Human_score += 0;
					}

					else if (std::find(in_a_row.begin(), in_a_row.end(), 1) != in_a_row.end()) {

						for (int i = 0; i < size; i++) {
							if (*num1 == *num2 && (*num1 == 1)) {
								temp_counter++;
								if (temp_counter > counter) {
									counter = temp_counter;
								}
							}
							else {
								temp_counter = 1;
							}
							num1++;
							num2++;

						}
						AI_score += (counter * 5);
					}

					else if (std::find(in_a_row.begin(), in_a_row.end(), -1) != in_a_row.end()) {
						for (int i = 0; i < size; i++) {
							if (*num1 == *num2 && (*num1 == 1)) {
								temp_counter++;
								if (temp_counter > counter) {
									counter = temp_counter;
								}
							}
							else {
								temp_counter = 1;
							}
							num1++;
							num2++;

						}
						Human_score += (counter * 5);
					}
					else {
						AI_score++;
						Human_score++;
					}
				}
			}
		}
	}
}


void AIShell::check_diagonals() {
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
		AI_score += temp_AI;
		Human_score += temp_Hum;
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
