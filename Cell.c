#include "./Cell.h"
#include <stdlib.h>
#include <raylib.h>

Cell* Cell_init(int x, int y, int width, int height, size_t isBomb) {
	Cell* cell = (Cell*)calloc(1, sizeof(Cell));
	//cell->count = 0;

	cell->x = x;
	cell->y = y;
	cell->width = width;
	cell->height = height;
	cell->color = DARKGRAY;
	cell->isBomb = isBomb;
	cell->isDiscoverd = 0;
	cell->isFlagged = 0;

	
	return cell;
}


void Cell_print(Cell* cell) {
	if (!cell)
		return;
	printf("\nPos (%d, %d), Size (%d, %d), IsBomb %d, IsFlagged %d", cell->x, cell->y, cell->width, cell->height, cell->isBomb, cell->isFlagged);

}

int Cell_isWithin(Cell *cell, int x, int y, int width, int height) {
	
	return cell->worldX + cell->width >= x &&     // r1 right edge past r2 left
		cell->worldX <= x + width &&       // r1 left edge past r2 right
		cell->worldY + cell->height >= y &&       // r1 top edge past r2 bottom
		cell->worldY <= y + height;   // r1 bottom edge past r2 top

}

void Cell_draw(Cell *cell) {

	DrawRectangle(cell->worldX, cell->worldY, cell->height, cell->width, cell->color);

	

	if (cell->isDiscoverd) {
		if (cell->isBomb) {
			DrawText("!", cell->worldX + (cell->width / 4), cell->worldY, 40, BLUE);
			return;
		}
		
		if (cell->count == 0)
			return;
		DrawText(TextFormat("%d", cell->count), cell->worldX + (cell->width/4), cell->worldY , 40, BLUE);
		return;
	}

	if (cell->isFlagged) {
		
		DrawRectangle(cell->worldX + cell->width/4, cell->worldY + cell->height/4, cell->height/2, cell->width/2, RED);

	}
}