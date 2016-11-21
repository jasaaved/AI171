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
	int alpha = -INF;
	int beta = INF;
	int col = 0;
	int row = 0;

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
					col = i;
					row = j;
				}
				gameState[i][j] = NO_PIECE;
			}
		}
	}

	return Move(col, row);
}

int AIShell::FindMin(int alpha, int beta, int d) {
	if (d == 1) {
		for (int i = 0; i < numCols; i++) {
			for (int j = 0; j < numRows; j++) {
				if (gameState[i][j] == NO_PIECE) {
					gameState[i][j] = HUMAN_PIECE;
					int possible = score();
					
					gameState[i][j] = NO_PIECE;

					if (possible < beta) {
						beta = possible;
					}
					
					if (alpha >= beta) {
						return beta;
					}
				}
			}
		}
		return beta;
	}
	
	for (int i = 0; i < numCols; i++) {
		for (int j = 0; j < numRows; j++) {
			if (gameState[i][j] == NO_PIECE) {
				gameState[i][j] = HUMAN_PIECE;
				int possible = FindMax(alpha, beta, d - 1);


				if (possible < beta) {
					beta = possible;
				}

				gameState[i][j] = NO_PIECE;

				if (alpha >= beta) {
					return beta;
				}
			}
		}
	}

	return beta;
}

int AIShell::FindMax(int alpha, int beta, int d) {
	if (d == 1) {
		for (int i = 0; i < numCols; i++) {
			for (int j = 0; j < numRows; j++) {
				if (gameState[i][j] == NO_PIECE) {
					gameState[i][j] = AI_PIECE;
					int possible = score();
					
					if (possible > alpha) {
						alpha = possible;
					}
					gameState[i][j] = NO_PIECE;
					if (alpha >= beta) {						
						return alpha;
					}
				}
			}
		}
		return alpha;
	}

	for (int i = 0; i < numCols; i++) {
		for (int j = 0; j < numRows; j++) {
			if (gameState[i][j] == NO_PIECE) {
				gameState[i][j] = AI_PIECE;
				int possible = FindMin(alpha, beta, d - 1);
				if (possible > alpha) {
					alpha = possible;
				}
				gameState[i][j] = NO_PIECE;
			}

			if (alpha >= beta) {
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
	//std::cout << "score:  " << AI_score - Human_score << std::endl;

	return (AI_score - Human_score);

}


void AIShell::winning_spaces() 
{

	int current;
	int AI_row;
	int Hum_row;
	int p_AIscore;
	int p_Humscore;
	int count;

	for (int i = 0; i < numCols; ++i) {
		for (int j = 0; j < numRows; ++j) {

			if (gameState[i][j] == 0) {
				if (gravityOn)
					break;
				else
					continue;
			}
			count = 0;
			p_AIscore = 0;
			p_Humscore = 0;
			AI_row = 0;
			Hum_row = 0;

			while (i + count < numCols)
			{
				if (gameState[i + count][j] == 0)
				{
					AI_row = 0;
					Hum_row = 0;
					p_AIscore = 0;
					p_Humscore = 0;
				}

				if (gameState[i + count][j] == 1)
				{
					AI_row += 1;
					p_Humscore = 0;
					Hum_row = 0;

					p_AIscore += (5 * AI_row);

					if (AI_row == k) 
					{
						AI_score = 1000;
						return;
					}

				}

				if (gameState[i + count][j] == -1)
				{

					Hum_row += 1;
					p_AIscore = 0;
					AI_row = 0;

					p_Humscore += (5 * Hum_row);

					if (Hum_row == k) 
					{
						Human_score = 1000;
						return;
					}
					/*
					if (Hum_row == k - 1)
					{
						Human_score = 1000;
						return;
					}
					*/

				}

				++count;
			}

			AI_score += p_AIscore;
			Human_score += p_Humscore;

			count = 0;
			p_AIscore = 0;
			p_Humscore = 0;
			AI_row = 0;
			Hum_row = 0;

			while (i + count < numCols && j + count < numRows) 
			{
				if (gameState[i + count][j + count] == 0)
				{
					
						AI_row = 0;
						Hum_row = 0;
						p_AIscore = 0;
						p_Humscore = 0;

				}

				if (gameState[i + count][j + count] == 1)
				{
					AI_row += 1;
					p_Humscore = 0;
					Hum_row = 0;

					p_AIscore += (5 * AI_row);

					if (AI_row == k)
					{
						AI_score = 1000;
						return;
					}

				}

				if (gameState[i + count][j + count] == -1)
				{
					Hum_row += 1;;
					p_AIscore = 0;
					AI_row = 0;

					p_Humscore += (5 * Hum_row);

					if (Hum_row == k)
					{
						Human_score = 1000;
						return;
					}
					/*
					if (Hum_row == k - 1)
					{
						Human_score = 1000;
						AI_score += p_AIscore;
						return;
					}
					*/

				}

				++count;
			}

			AI_score += p_AIscore;
			Human_score += p_Humscore;

			count = 0;
			p_AIscore = 0;
			p_Humscore = 0;
			AI_row = 0;
			Hum_row = 0;

			while (i + count < numCols && j - count >= 0)
			{
				if (gameState[i + count][j - count] == 0)
				{
					
						AI_row = 0;
						Hum_row = 0;
						p_AIscore = 0;
						p_Humscore = 0;

				}

				if (gameState[i + count][j - count] == 1)
				{
					AI_row += 1;
					p_Humscore = 0;
					Hum_row = 0;


					p_AIscore += (5 * AI_row);


					if (AI_row == k)
					{
						AI_score = 1000;
						return;
					}

				}

				if (gameState[i + count][j - count] == -1)
				{

					Hum_row += 1;
					p_AIscore = 0;
					AI_row = 0;


					p_Humscore += (5 * Hum_row);

					if (Hum_row == k)
					{
						Human_score = 1000;
						return;
					}
					/*
					if (Hum_row == k - 1)
					{
						Human_score = 1000;
						AI_score += p_AIscore;
						return;
					}
					*/

				}

				++count;

			}

			AI_score += p_AIscore;
			Human_score += p_Humscore;

			count = 0;
			p_AIscore = 0;
			p_Humscore = 0;
			AI_row = 0;
			Hum_row = 0;

			while (j + count < numRows)
			{
				if (gameState[i][j + count] == 0)
				{
						AI_row = 0;
						Hum_row = 0;
						p_AIscore = 0;
						p_Humscore = 0;
				}

				if (gameState[i][j + count] == 1)
				{
					
					AI_row += 1;
					p_Humscore = 0;
					Hum_row = 0;
					

					p_AIscore += (5 * AI_row);
			

					if (AI_row == k)
					{
						AI_score = 1000;
						return;
					}

				}

				if (gameState[i][j + count] == -1)
				{
					Hum_row += 1;
					p_AIscore = 0;
					AI_row = 0;

					p_Humscore += (5 * Hum_row);

					if (Hum_row == k)
					{
						Human_score = 1000;
						return;
					}
					/*
					if (Hum_row == k - 1)
					{
						Human_score = 1000;
						AI_score += p_AIscore;
						return;
					}
					*/
				}

				++count;
			}

			AI_score += p_AIscore;
			Human_score += p_Humscore;

		}
	}
					

}


int AIShell::time_left() {
	timeval curTime;
	gettimeofday(&curTime, NULL);
	int milli = curTime.tv_usec / 1000;
	return milli;
}



Move AIShell::makeMove()
{
	return minimax(depth);	 
}
