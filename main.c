#include <raylib.h>
#include <stdio.h>
#include "./GameGrid.c"
#include "./Button.c"
#include "./Cell.c"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

void checkForCollision(GameGrid *gameGrid) {
    //get mouse coords
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    //iterate through each cell in the gameGrid
    for (int i = 0; i < gameGrid->height; i++) {
        for (int j = 0; j < gameGrid->width; j++) {
            if (Cell_isWithin(gameGrid->grid[i][j], GetMouseX(), GetMouseY(), 3, 3)) {
                //on left shift key press call the flag squre function which will then check for collision detectin between the mouse click point and the rect of the cell.
                if (IsKeyDown( KEY_LEFT_SHIFT)) {
                    GameGrid_flagSquare(gameGrid, j, i);
                    return;
                }
                //if it's there's no addition keys being pressed then call the reveal squares function which will check for collision between the mouse click point and the rect of the cell.
                GameGrid_revealSquares(gameGrid, j, i);
                return;
            }
        }

    }
}

void gameStart(GameGrid *gameGrid) {

    GameGrid_init(gameGrid);
    GameGrid_populateMatrix(gameGrid);
    GameGrid_setWorldPos(gameGrid);
    GameGrid_generateBombs(gameGrid);
}

int main() {

    //creates a Color struct on the stack.
    Color Dark_Green = { 20, 160, 133, 255 };

    //creats our restart button on the stack.
    Button restartButton = {"restart"};
    //initilizes values like world position and size.
    Button_init(&restartButton, (Vector2) { 0, 0 }, (Vector2){40,40});
    
    int ball_x = 100;
    int ball_y = 100;
    int ball_speed_x = 5;
    int ball_speed_y = 5;
    int ball_radius = 15;

    GameGrid gameGrid = { 0, 9, 9, 12};

    gameStart(&gameGrid);

    InitWindow(SCREEN_WIDTH, SCREEN_WIDTH, "MineSweeper :3");
    SetTargetFPS(60);
 
    double time_passed = 0;
    double delta_time = 0;


    while (!WindowShouldClose()) {
        BeginDrawing(); //needed to render with raylib
        ClearBackground(Dark_Green); //
        

        GameGrid_draw(&gameGrid);
        

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

            

            if (Button_wasClicked(&restartButton, (Vector2) { GetMouseX(), GetMouseY() }, (Vector2) { 1, 1 })) {
                gameStart(&gameGrid);
            }

            if (gameGrid.isAlive) {
                checkForCollision(&gameGrid);

            }
        }
        Button_draw(&restartButton);
        DrawCircle(GetMouseX(), GetMouseY(), 5, RED);

        EndDrawing();
    }
    
    //free memory
    GameGrid_preFree(&gameGrid);
    //free((&restartButton)->text);// segfauts for some reason
}

