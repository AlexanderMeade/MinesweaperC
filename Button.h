#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <raylib.h>

typedef struct {
	char* text;
	Vector2 pos;
	Vector2 size;
}Button;

void Button_init(Button *button, Vector2 pos, Vector2 size);

int Button_wasClicked(Button *button, Vector2 pos, Vector2 size);

void Button_draw(Button* button);

#endif