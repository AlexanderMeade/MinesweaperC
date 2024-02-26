#include "./GameGrid.h"
#include <stdlib.h>



void GameGrid_init(GameGrid* gameGrid) {

	gameGrid->grid = (Cell***)calloc(1, sizeof(Cell**)*gameGrid->height);
	gameGrid->isAlive = 1;
	SetRandomSeed(time(NULL));

	for (int i = 0; i < gameGrid->width; i++) {
		gameGrid->grid[i] = (Cell**)calloc(1, gameGrid->width * sizeof(Cell*));
	}
	
}

void GameGrid_populateMatrix(GameGrid* gameGrid) {

	for (int i = 0; i < gameGrid->height; i++) {
		for (int j = 0; j < gameGrid->width; j++) {
			gameGrid->grid[i][j] = Cell_init( i, j, GridCellWidth, GridCellHeight, 0 );
		}
	}

}

void GameGrid_setWorldPos(GameGrid *gameGrid) {

	for (int i = 0; i < gameGrid->height; i++) {
		for (int j = 0; j < gameGrid->width; j++) {
			gameGrid->grid[i][j]->worldX = gameGrid->grid[i][j]->x + GridStartXOffset + (GridCellWidth * i);
			gameGrid->grid[i][j]->worldY = gameGrid->grid[i][j]->y + GridStartYOffset + (GridCellHeight * j);
		}
	}

}

void GameGrid_incrementAroundBomb(GameGrid *gameGrid, int x, int y) {
	for (int i = y-1; i <= y+1; i++) {
		for (int j = x-1; j <= x+1; j++) {

			
			if (i < 0 || j < 0 || i > gameGrid->height-1 || j > gameGrid->width-1) {
				continue;
			}
			gameGrid->grid[i][j]->count += 1;

			/*if (!gameGrid->grid[i][j]->isBomb)
				gameGrid->grid[i][j]->color = YELLOW;*/
			/*if ((i < 0 || i > gameGrid->height) || (j < 0 || j > gameGrid->height))
				continue;
			if (gameGrid->grid[i][j]->isBomb)
				continue;
			
			gameGrid->grid[i][j]->count += 1;
			*/
			
		}
	}
}

float GameGrid_generateBombChance() {
	
	return ((float)rand() / (float)(RAND_MAX)) * 75;

}

void GameGrid_generateBombs(GameGrid *gameGrid) {
	printf("\n\n\nBOOGIE");
	int times = 1;
	gameGrid->bombCount = 12;
	while (gameGrid->bombCount > 0 && times > 0) {
		for (int i = 0; i < gameGrid->height; i++) {
			for (int j = 0; j < gameGrid->width; j++) {
				if (gameGrid->grid[i][j]->isBomb)
					continue;
				if (gameGrid->bombCount <= 0)
					return;
				if (GetRandomValue(0, 100)<20) {
					gameGrid->grid[i][j]->isBomb = 1;
					gameGrid->bombCount -= 1;
					GameGrid_incrementAroundBomb(gameGrid, j, i);
					times--;
				}
			}
		}
	}
	
}

int GameGrid_checkWin(GameGrid *gameGrid) {
	
	for (int i = 0; i < gameGrid->height; i++) {
		for (int j = 0; j < gameGrid->width; j++) {
			Cell *cell = gameGrid->grid[i][j];
			if (!cell->isDiscoverd && !cell->isBomb) {
				return 0;
			}
		}
	}
	return 1;
}

void GameGrid_revealAllBombs(GameGrid *gameGrid) {
	for (int i = 0; i < gameGrid->height; i++) {
		for (int j = 0; j < gameGrid->width; j++) {
			if (gameGrid->grid[i][j]->isBomb)
				gameGrid->grid[i][j]->color = RED;
		}
	}
}

void GameGrid_onDeath(GameGrid *gameGrid) {
	GameGrid_revealAllBombs(gameGrid);
	gameGrid->isAlive = 0;
}


void GameGrid_flagSquare (GameGrid* gameGrid, int x, int y) {


	gameGrid->grid[y][x]->isFlagged = !gameGrid->grid[y][x]->isFlagged;
	
	Cell_print(gameGrid->grid[y][x]);

}


void GameGrid_revealSquares(GameGrid *gameGrid, int x, int y) {

	
	gameGrid->grid[y][x]->isDiscoverd = 1;
	gameGrid->grid[y][x]->color = GRAY;

	if (gameGrid->grid[y][x]->isBomb) {
		printf("DIE");
		GameGrid_onDeath(gameGrid);
		return;
	}

	if (gameGrid->grid[y][x]->count != 0)
		return;

	printf("\nPOINT (%d, %d)\n--------------------------\n", x, y);
	for (int i = y - 1; i <= y + 1; i++) {
		for (int j = x - 1; j <= x + 1; j++) {
			

			if (i < 0 || j < 0 || i > gameGrid->height - 1 || j > gameGrid->width - 1) 
				continue;

			Cell* cell = gameGrid->grid[i][j];

			if (cell->count == 0 && !cell->isDiscoverd) {
				GameGrid_revealSquares(gameGrid, j, i);

				continue;
			}

			if (!cell->isDiscoverd) {
				gameGrid->grid[i][j]->isDiscoverd = 1;
				gameGrid->grid[i][j]->color = GRAY;
			}
			

		}
	}
	
	
}