#pragma once
#ifndef CELL_H
#define CELL_H

#include <raylib.h>

typedef struct {
	int count;
	int x;
	int y;
	int worldX;
	int worldY;
	int width;
	int height;
	int isDiscoverd;
	int isFlagged;
	Color color;
	size_t isBomb;
}Cell;

Cell* Cell_init(int x, int y, int width, int height, size_t isBomb);

void Cell_print(Cell *cell);


int Cell_isWithin(Cell* cell, int x, int y, int width, int height);


void Cell_draw(Cell* cell);

#endif
