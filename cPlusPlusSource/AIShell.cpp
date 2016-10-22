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
	this->depth=3;
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
	

	//int col = rand() % numCols;
	//int row = rand() % numRows;

	//while (gameState[col][row] != NO_PIECE){
	//	col = rand() % numCols;
	//	row = rand() % numRows;
	//}
	//Move m(col, row);
	//return m;
	 
}
