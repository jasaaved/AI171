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
	int col = 0;
	int row = 0;

	while (time_left() - start_time <= move_deadline) {

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
		std::cout << "depth: " << d << std::endl;
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
			//horizontal check
			while (i + count < numCols && count < k)
			{
				if (gameState[i][j] == 1 && (gameState[i + count][j] == 1 || gameState[i + count][j] == 0))
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

					if (AI_row == k) 
					{
						if (AI_same == k)
						{
							AI_score == 1000;
							return;
						}
						AI_score += (AI_same * 5) + (AI_empty);
					}
				}

				else if (gameState[i][j] == -1 && (gameState[i + count][j] == -1 || gameState[i + count][j] == 0))
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

					if (Hum_row == k) 
					{
						if (hum_same == k)
						{
							Human_score == 1000;
							return;
						}
						Human_score += (hum_same * 5) + (hum_empty);
					}
				}

				++count;
			}



			count = 1;
			AI_row = 0;
			Hum_row = 0;
			AI_same = 0;
			AI_empty = 0;
			hum_same = 0;
			hum_empty = 0;
			//Upper-right diagnol check
			while (i + count < numCols && j + count < numRows && count < k) 
			{
				if (gameState[i][j] == 1 && (gameState[i + count][j + count] == 1 || gameState[i + count][j + count] == 0))
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

					if (AI_row == k)
					{
						if (AI_same == k)
						{
							AI_score == 1000;
							return;
						}
						AI_score += (AI_same * 5) + (AI_empty);
					}

				}

				if (gameState[i][j] == -1 && (gameState[i + count][j + count] == -1 || gameState[i + count][j + count] == 0))
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

					if (Hum_row == k)
					{
						if (hum_same == k)
						{
							Human_score == 1000;
							return;
						}
						Human_score += (hum_same * 5) + (hum_empty);
					}
				}

				++count;
			}


			count = 1;
			AI_row = 0;
			Hum_row = 0;
			AI_same = 0;
			AI_empty = 0;
			hum_same = 0;
			hum_empty = 0;
			//check lower right diagonals
			while (i + count < numCols && j - count >= 0 && count < k)
			{
				if (gameState[i][j] == 1 && (gameState[i + count][j - count] == 1 || gameState[i + count][j - count] == 0))
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

					if (AI_row == k)
					{
						if (AI_same == k)
						{
							AI_score == 1000;
							return;
						}
						AI_score += (AI_same * 5) + (AI_empty);
					}

				}

				if (gameState[i][j] == -1 && (gameState[i + count][j - count] == -1 || gameState[i + count][j - count] == 0))
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

					if (Hum_row == k)
					{
						if (hum_same == k)
						{
							Human_score == 1000;
							return;
						}
						Human_score += (hum_same * 5) + (hum_empty);
					}

				}
			
				++count;

			}

			count = 1;
			AI_row = 0;
			Hum_row = 0;
			AI_same = 0;
			AI_empty = 0;
			hum_same = 0;
			hum_empty = 0;

			while (j + count < numRows && count < k)
			{
				if (gameState[i][j] == 1 && (gameState[i][j + count] == 1 || gameState[i][j + count] == 0))
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

					if (AI_row == k)
					{
						if (AI_same == k)
						{
							AI_score == 1000;
							return;
						}
						AI_score += (AI_same * 5) + (AI_empty);
					}
				}

				if (gameState[i][j] == -1 && (gameState[i][j + count] == -1 || gameState[i][j + count] == 0))
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

					if (Hum_row == k)
					{
						if (hum_same == k)
						{
							Human_score == 1000;
							return;
						}
						Human_score += (hum_same * 5) + (hum_empty);
					}


				}

				++count;
			}

		}
	}
					

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
