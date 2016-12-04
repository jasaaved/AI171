#include "AIShell.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <stdlib.h>
#include <vector>


AIShell::AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove)
{
	this->numRows=numRows;
	this->numCols=numCols;
	this->gravityOn=gravityOn;
	this->gameState=gameState;
	this->lastMove=lastMove;
	this->start_time = time_left();
	this->index = 0;
	this->depth = 2;
	
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
	int alpha = -INF;
	int best_alpha = -INF;
	int beta = INF;
	int col;
	int row;

	for (int i = 0; i < numCols; i++)
	{
		for (int j = 0; j < numRows; j++)
		{
			if (gameState[i][j] == NO_PIECE)
			{

				gameState[i][j] = AI_PIECE;
				int possible = BestMove();
				if (possible == 1000)
				{
					gameState[i][j] == NO_PIECE;
					return Move(i, j);
				}
				gameState[i][j] == NO_PIECE;
			}
		}
	}



	while (time_left() - start_time <= move_deadline) {
		std::cout << "hello" << std::endl;
		for (int i = 0; i < numCols; i++)
		{
			for (int j = 0; j < numRows; j++)
			{

				if (gameState[i][j] == NO_PIECE)
				{

					gameState[i][j] = AI_PIECE;
					int possible = FindMin(alpha, beta, d - 1);
					if (possible > alpha && possible > best_alpha)
					{
						alpha = possible;
						best_alpha = alpha;
						col = i;
						row = j;
					}
					gameState[i][j] = NO_PIECE;

				}
			}
		}

		d++;
		index = 0;
		alpha = -INF;
		beta = INF;
	}

	return Move(col, row);
}

int AIShell::FindMin(int alpha, int beta, int d) {

	if (d == 1 || time_left() - start_time >= move_deadline)
	{
		for (int i = 0; i < numCols; i++)
		{
			for (int j = 0; j < numRows; j++) 
			{
				if (gameState[i][j] == NO_PIECE) 
				{
					gameState[i][j] = HUMAN_PIECE;
					int possible = score();
					
					gameState[i][j] = NO_PIECE;

					if (possible < beta) 
					{
						beta = possible;
					}
					
					if (alpha >= beta) 
					{
						return beta;
					}
				}
			}
		}
		return beta;
	}
	
	for (int i = 0; i < numCols; i++) 
	{
		for (int j = 0; j < numRows; j++) 
		{
			if (gameState[i][j] == NO_PIECE) 
			{
				gameState[i][j] = HUMAN_PIECE;
				int possible = FindMax(alpha, beta, d - 1);


				if (possible < beta) 
				{
					beta = possible;
				}

				gameState[i][j] = NO_PIECE;

				if (alpha >= beta || time_left() - start_time >= move_deadline)
				{
					return beta;
				}
			}
		}
	}

	return beta;
}

int AIShell::FindMax(int alpha, int beta, int d) 
{

	if (d == 1 || time_left() - start_time >= move_deadline) 
	{
		
		for (int i = 0; i < numCols; i++) 
		{
			for (int j = 0; j < numRows; j++) 
			{

				if (gameState[i][j] == NO_PIECE) 
				{
					gameState[i][j] = AI_PIECE;
					int possible = score();
					
					if (possible > alpha)
					{
						alpha = possible;
					}
					gameState[i][j] = NO_PIECE;
					if (alpha >= beta) 
					{
						return alpha;
					}
				}
			}
		}
		return alpha;
	}


	for (int i = 0; i < numCols; i++) 
	{
		for (int j = 0; j < numRows; j++)
		{
			if (gameState[i][j] == NO_PIECE) 
			{
				gameState[i][j] = AI_PIECE;
				int possible = FindMin(alpha, beta, d - 1);
				if (possible > alpha) 
				{
					alpha = possible;
				}
				gameState[i][j] = NO_PIECE;
			}

			if (alpha >= beta || time_left() - start_time >= move_deadline) 
			{
				return alpha;

			}
		}
	}

	return alpha;
}

int AIShell::score() {
	AI_score = 0;
	Human_score = 0;
	winning_spaces();
	if(Human_score == 1000) 
	{
		return -1000;
	}

	if (AI_score == 1000)
	{
		return 1000;
	}


	return (AI_score - Human_score);

}


void AIShell::winning_spaces() 
{

	int current;
	int AI_row;
	int Hum_row;
	int count;
	int AI_same;
	int AI_empty;
	int hum_same;
	int hum_empty;
	int zero_empty;
	bool AI_useless;
	bool Hum_useless;
	bool start_zero;


	for (int i = 0; i < numCols; ++i) {
		for (int j = 0; j < numRows; ++j) {

			if (gameState[i][j] == 0) {
				if (gravityOn)
					break;
				else
					continue;
			}
			count = 1;
			AI_row = 0;
			Hum_row = 0;
			AI_same = 0;
			AI_empty = 0;
			hum_same = 0;
			hum_empty = 0;
			AI_useless = false;

			//horizontal check
			while (i + count < numCols && count < k)
			{
				if (gameState[i][j] == 1)
				{
					if (gameState[i + count][j] == -1)
					{
						AI_useless = true;
						AI_row = 0;
						AI_same = 0;
						AI_empty = 0;
					}

					if (!AI_useless)
					{
						AI_row += 1;

						if (gameState[i + count][j] == 1)
						{
							AI_same += 1;
						}

						if (gameState[i + count][j] == 0)
						{
							AI_empty += 1;
						}
					}

				}

				else if (gameState[i][j] == -1)
				{
					if (gameState[i + count][j] == 1)
					{
						Hum_useless = true;
						Hum_row = 0;
						hum_same = 0;
						hum_empty = 0;
					}

					if (!Hum_useless)
					{

						Hum_row += 1;

						if (gameState[i + count][j] == -1)
						{
							hum_same += 1;
						}

						if (gameState[i + count][j] == 0)
						{
							hum_empty += 1;
						}
					}

				}

				++count;

				if (count >= k)
				{
					if (Hum_row == k)
					{
						Human_score == 1000;
						return;

					}

					if (AI_same == k)
					{
						AI_score == 1000;
						return;	
					}

					AI_score += (AI_same * 5) + (AI_empty);

					Human_score += (hum_same * 5) + (hum_empty);

				}
			}



			count = 1;
			AI_row = 0;
			Hum_row = 0;
			AI_same = 0;
			AI_empty = 0;
			hum_same = 0;
			hum_empty = 0;
			AI_useless = false;
			Hum_useless = false;

			//Upper-right diagnol check
			while (i + count < numCols && j + count < numRows && count < k) 
			{
				if (gameState[i][j] == 1)
				{
					if (gameState[i + count][j + count] == -1)
					{
						AI_useless = true;
						AI_row = 0;
						AI_same = 0;
						AI_empty = 0;
					}
					
					if (!AI_useless)
					{
						AI_row += 1;

						if (gameState[i + count][j + count] == 1)
						{
							AI_same += 1;
						}

						if (gameState[i + count][j + count] == 0)
						{
							AI_empty += 1;
						}
					}
				}

				if (gameState[i][j] == -1)
				{
					if (gameState[i + count][j + count] == 1)
					{
						Hum_useless = true;
						Hum_row = 0;
						hum_same = 0;
						hum_empty = 0;
					}

					if (!Hum_useless)
					{

						Hum_row += 1;

						if (gameState[i + count][j + count] == -1)
						{
							hum_same += 1;
						}

						if (gameState[i + count][j + count] == 0)
						{
							hum_empty += 1;
						}
					}

				}

				++count;

				if (count >= k)
				{
					if (hum_same == k)
					{
						Human_score == 1000;
						return;

					}

					if (AI_same == k)
					{
						AI_score == 1000;
						return;
					}

					AI_score += (AI_same * 5) + (AI_empty);

					Human_score += (hum_same * 5) + (hum_empty);

				}
			}


			count = 1;
			AI_row = 0;
			Hum_row = 0;
			AI_same = 0;
			AI_empty = 0;
			hum_same = 0;
			hum_empty = 0;
			AI_useless = false;
			Hum_useless = false;
			//check lower right diagonals
			while (i + count < numCols && j - count >= 0 && count < k)
			{
				if (gameState[i][j] == 1)
				{
					
					if (gameState[i + count][j - count] == -1)
					{
						AI_useless = true;
						AI_row = 0;
						AI_same = 0;
						AI_empty = 0;
					}

					if (!AI_useless)
					{
						AI_row += 1;

						if (gameState[i + count][j - count] == 1)
						{
							AI_same += 1;
						}

						if (gameState[i + count][j - count] == 0)
						{
							AI_empty += 1;
						}
					}


				}

				if (gameState[i][j] == -1)
				{
					if (gameState[i + count][j - count] == 1)
					{
						Hum_useless = true;
						Hum_row = 0;
						hum_same = 0;
						hum_empty = 0;
					}

					if (!Hum_useless)
					{

						Hum_row += 1;

						if (gameState[i + count][j - count] == -1)
						{
							hum_same += 1;
						}

						if (gameState[i + count][j - count] == 0)
						{
							hum_empty += 1;
						}
					}


				}
			
				++count;
				if (count >= k)
				{
					if (hum_same == k)
					{
						Human_score == 1000;
						return;

					}

					if (AI_same == k)
					{
						AI_score == 1000;
						return;
					}

					AI_score += (AI_same * 5) + (AI_empty);

					Human_score += (hum_same * 5) + (hum_empty);
				}

			}

			count = 1;
			AI_row = 0;
			Hum_row = 0;
			AI_same = 0;
			AI_empty = 0;
			hum_same = 0;
			hum_empty = 0;
			zero_empty = 0;
			AI_useless = false;
			Hum_useless = false;

			//check vertical
			while (j + count < numRows && count < k)
			{
				if (gameState[i][j] == 1)
				{
					if (gameState[i][j + count] == -1)
					{
						AI_useless = true;
						AI_row = 0;
						AI_same = 0;
						AI_empty = 0;
					}

					if (!AI_useless)
					{
						AI_row += 1;

						if (gameState[i][j + count] == 1)
						{
							AI_same += 1;
						}

						if (gameState[i][j + count] == 0)
						{
							AI_empty += 1;
						}
					}


				}

				if (gameState[i][j] == -1)
				{
					if (gameState[i][j + count] == 1)
					{
						Hum_useless = true;
						Hum_row = 0;
						hum_same = 0;
						hum_empty = 0;
					}

					if (!Hum_useless)
					{

						Hum_row += 1;

						if (gameState[i][j + count] == -1)
						{
							hum_same += 1;
						}

						if (gameState[i][j + count] == 0)
						{
							hum_empty += 1;
						}
					}

				}

				if (gameState[i][j] == 0)
				{
					if (gameState[i][j + count] == 0)
					{
						zero_empty += 1;
					}

					if (gameState[i][j + count] == 1)
					{
						Hum_useless = true;
						Hum_row = 0;
						hum_same = 0;
						hum_empty = 0;

						if (!AI_useless)
						{
							AI_same += 1;
							AI_empty = zero_empty;
						}
					}

					if (gameState[i][j + count] == -1)
					{
						AI_useless = true;
						AI_row = 0;
						AI_same = 0;
						AI_empty = 0;

						if (!Hum_useless)
						{
							hum_same += 1;
							hum_empty = zero_empty;
						}
					}

				}

				++count;

				if (count >= k)
				{
					if (hum_same == k)
					{
						Human_score == 1000;
						return;

					}

					if (AI_same == k)
					{
						AI_score == 1000;
						return;
					}

					AI_score += (AI_same * 5) + (AI_empty);

					Human_score += (hum_same * 5) + (hum_empty);
				}
			}

		}
	}
					

}

int AIShell::BestMove()
{
	return score();
}


inline double AIShell::time_left() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return((double)(tv.tv_sec + (double)tv.tv_usec / 1000000.0));
}



Move AIShell::makeMove()
{
	if (deadline == 0)
	{
		deadline = 50000;
	}


	move_deadline = deadline / 1000;
	move_deadline = move_deadline - 0.5;
	//std::cout << move_deadline << std::endl;
	
	return minimax(depth);	 
}
