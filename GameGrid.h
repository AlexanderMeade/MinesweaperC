#pragma once
#ifndef GAMEGRID_H 
#define GAMEGRID_H
#include "./Cell.h"

#define GridStartXOffset 100
#define GridStartYOffset 100
#define GridCellWidth 40
#define GridCellHeight 40


typedef struct {
	
	Cell ***grid;
	int width;
	int height;
	int bombCount;
	int cellWidth;
	int cellHeight;
	int isAlive;

}GameGrid;

void GameGrid_init(GameGrid* gameGrid);

void GameGrid_populateMatrix(GameGrid* gameGrid);

void GameGrid_setWorldPos(GameGrid* gameGrid);

void GameGrid_incrementAroundBomb(GameGrid* gameGrid, int x, int y);

void GameGrid_revealAllBombs(GameGrid* gameGrid);

void GameGrid_onDeath(GameGrid* gameGrid);

float GameGrid_generateBombChance();

void GameGrid_generateBombs(GameGrid* gameGrid);

int GameGrid_checkWin(GameGrid* gameGrid);

void GameGrid_flagSquare(GameGrid* gameGrid, int x, int y);

void GameGrid_revealSquares(GameGrid* gameGrid, int x, int y);

#endif