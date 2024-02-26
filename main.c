#include <raylib.h>
#include <stdio.h>
#include "./GameGrid.h"
#include "./Button.h"

void checkForCollision(GameGrid *gameGrid) {
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    for (int i = 0; i < gameGrid->height; i++) {
 

        for (int j = 0; j < gameGrid->width; j++) {
         
            if (Cell_isWithin(gameGrid->grid[i][j], GetMouseX(), GetMouseY(), 3, 3)) {
                printf("Cell (%d, %d), Point (%d, %d)\n", gameGrid->grid[i][j]->worldX, gameGrid->grid[i][j]->worldY, mouseX, mouseY);
                if (IsKeyDown( KEY_LEFT_SHIFT)) {
                    GameGrid_flagSquare(gameGrid, j, i);
                    return;
                }

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


    Color Dark_Green = { 20, 160, 133, 255 };

    Button restartButton = {"restart"};
    Button_init(&restartButton, (Vector2) { 0, 0 }, (Vector2){40,40});

    const int screenWidth = 600;
    const int screenHeight = 600;
    int ball_x = 100;
    int ball_y = 100;
    int ball_speed_x = 5;
    int ball_speed_y = 5;
    int ball_radius = 15;

    GameGrid gameGrid = { 0, 9, 9, 12};

    gameStart(&gameGrid);

    printf("\n");
    printf("\n\n\n\nGRI\n\n\n");
    for (int i = 0; i < gameGrid.height; i++) {
        for (int j = 0; j < gameGrid.width; j++) {
            printf("%d", gameGrid.grid[i][j]->count);
        }
        printf("\n");
    }

    InitWindow(screenWidth, screenHeight, "MineSweeper :3");
    SetTargetFPS(60);


    double time_passed = 0;
    double delta_time = 0;



    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(Dark_Green);
        

        for (int i = 0; i < gameGrid.height; i++) {
            for (int j = 0; j < gameGrid.width; j++) {
 
                Cell_draw(gameGrid.grid[i][j]);
                
            }
        
        }

        

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

            

            if (Button_wasClicked(&restartButton, (Vector2) { GetMouseX(), GetMouseY() }, (Vector2) { 1, 1 })) {
                gameStart(&gameGrid);
            }

            if (gameGrid.isAlive) {
                checkForCollision(&gameGrid);

                if (GameGrid_checkWin(&gameGrid)) {
                    printf("\nWIN");
                }
                printf("\n(%d, %d)", GetMouseX(), GetMouseY());
            }
        }
        Button_draw(&restartButton);
        DrawCircle(GetMouseX(), GetMouseY(), 5, RED);

        EndDrawing();
    }

}