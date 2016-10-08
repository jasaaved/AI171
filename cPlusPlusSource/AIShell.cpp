#include "AIShell.h"
#include <iostream>
#include <stdlib.h>

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

Move AIShell::makeMove(){
	int col = rand() % numCols + 1;
	int row = rand() % numRows + 1;

	if (gameState[col][row] != NO_PIECE){
		col = rand() % numCols + 1;
		row = rand() % numRows + 1;
	}
	Move m(col, row);
	return m;
	 
}
