#include "./Button.h"
#include <raylib.h>
#include <string.h>
#include <stdlib.h>

void Button_init(Button *button, Vector2 pos, Vector2 size) {
	button->pos = pos;
	button->size = size;
	button->size.x = (20 * strlen(button->text));
}

int Button_wasClicked(Button* button, Vector2 pos, Vector2 size) {
	return button->pos.x + button->size.x >= pos.x &&     // r1 right edge past r2 left
		button->pos.x <= pos.x + size.x &&       // r1 left edge past r2 right
		button->pos.y + button->size.y >= pos.y &&       // r1 top edge past r2 bottom
		button->pos.y <= pos.y + size.y;   // r1 bottom edge past r2 top
}

void Button_draw(Button *button) {
	DrawRectangle(button->pos.x , button->pos.y, button->size.x, button->size.y, GRAY);
	DrawText(button->text, button->pos.x+8, button->pos.y, 30, BLACK);
}

void Button_preFree(Button* button) {
    if (button->text)
        free(button->text);
}
