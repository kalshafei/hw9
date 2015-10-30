//Kyle Al-Shafei
//CS2110 HW9

#include "mylib.h"
#include <stdlib.h>
#include "Start.h"
#include "maze1.h"
#include "maze2.h"
#include "Lost.h"
#include "Won.h"


#define MIN(a,b) (((a) > (b) ? (b):(a)))
#define MAX(a,b) (((a) < (b) ? (b):(a)))

typedef struct {
    int x;
    int y;
    int speed;
    int size;
    char direction;
    u16 color;
} ENEMY;

typedef struct  {
    int x;
    int y;
    int speed;
    int size;
    u16 color;
} PLAYER;

typedef struct {
    int x;
    int y;
    int length;
    char direction;
    u16 color;
} GATE;

typedef struct {
    int x;
    int y;
    int size;
    u16 color;
} SWITCH;

enum GBAState {
    START,
    START_NODRAW,
    MAZE1,
    MAZE1_NODRAW,
//    MAZE2,
//    MAZE2_NODRAW,
    LOSE,
    LOSE_NODRAW,
    WIN,
    WIN_NODRAW
};


int game();

int main() {
    REG_DISPCTL = MODE_3 | BG2_EN;
    enum GBAState state = START;
    int gameState;

    while(1) {
        switch(state) {

        case START:
            drawImage3(0, 0, START_WIDTH, START_HEIGHT, Start);
            state = START_NODRAW;
            waitForVblank();
            break;
        case START_NODRAW:
            if(KEY_DOWN_NOW(BUTTON_A)) {
                state = MAZE1;
            }
            break;
        case MAZE1:
            drawImage3(0, 0, 240, 160, maze1);
            state = MAZE1_NODRAW;
            waitForVblank();
            break;
        case MAZE1_NODRAW:
            gameState = game();
            if (gameState == 0) {
                state = START;
            } else  if (gameState == 1) {
                state = LOSE;
            } else {
                state = WIN;
            }
            break;
        case MAZE2:
            drawImage3(0, 0, 240, 160, maze2);
            state = MAZE2_NODRAW;
            waitForVblank();
            break;
        case MAZE2_NODRAW:
            gameState = game();
            if (gameState == 0) {
                state = START;
            } else  if (gameState == 1) {
                state = LOSE;
            } else {
                state = WIN;
            }
            break;
        case LOSE:
            drawImage3(30, 30, LOST_WIDTH, LOST_HEIGHT, Lost);
            state = LOSE_NODRAW;
            waitForVblank();
            break;
        case LOSE_NODRAW:
            if(KEY_DOWN_NOW(BUTTON_SELECT)) {
                state = START;
            }
            break;
        case WIN:
            drawImage3(30, 30, WON_WIDTH, WON_HEIGHT, Won);
            state = WIN_NODRAW;
            waitForVblank();
            break;
        case WIN_NODRAW:
            if(KEY_DOWN_NOW(BUTTON_SELECT)) {
                state = START;
            }
            break;
        }
    }
    return 0;
}

int game(int maze) {
    PLAYER player;
    GATE gate1;
    SWITCH tile1;
    SWITCH winTile;
    if (maze == 1) {
        buildMaze1(player, tile1, gate1, winTile);
    } else {
        GATE gate2, gate3;
        SWITCH tile2, tile3;
        buildMaze2(player, tile1, tile2, tile3, gate1, gate2, gate3, winTile);
    } 

    int oldPlayerX = player.x;
    int oldPlayerY = player.y;
    int newPlayerX = oldPlayerX;
    int newPlayerY = oldPlayerY;

    while(1) {
        if(KEY_DOWN_NOW(BUTTON_SELECT)) {
            return 0;
        }   
        int neg = -1 * player.speed;
        if(KEY_DOWN_NOW(BUTTON_UP))
        {
            int wall = horWallCollision(oldPlayerX, oldPlayerY, player.size, neg);
            int edge = yEdgeCollision(oldPlayerY, player.size, neg);
            newPlayerY += MAX(edge, wall);

        }
        if(KEY_DOWN_NOW(BUTTON_LEFT))
        {
            int wall = vertWallCollision(oldPlayerX, oldPlayerY, player.size, neg);
            int edge = xEdgeCollision(oldPlayerX, player.size, neg);
            newPlayerX += MAX(edge, wall);
        }
        if(KEY_DOWN_NOW(BUTTON_RIGHT))
        {
            int wall = vertWallCollision(oldPlayerX, oldPlayerY, player.size, player.speed);
            int edge = xEdgeCollision(oldPlayerX, player.size,  player.speed);
            newPlayerX += MIN(edge, wall);
        }
        if(KEY_DOWN_NOW(BUTTON_DOWN))
        {
            int wall = horWallCollision(oldPlayerX, oldPlayerY, player.size, player.speed);
            int edge = yEdgeCollision(oldPlayerY, player.size,  player.speed);
            newPlayerY += MIN(wall, edge);
        }
        //Update 
        drawRect(oldPlayerY, oldPlayerX , player.size, player.size, WHITE); //Erase old Player Location

        if (maze == 1) {
            drawRect(tile1.x, tile1.y, tile1.size, tile1.size, tile1.color);    //Redraw Tile  
            drawLine(gate1.x, gate1.y, gate1.length, gate1.direction, RED);     //Draw Line
            if(tileCollision(oldPlayerX,oldPlayerY , player.size, tile1)) {     //Check collision with tile
                drawLine(gate1.x, gate1.y, gate1.length, gate1.direction, WHITE);//Erase and redraw gate with new direction
                gate1.direction = 0; 
                drawLine(gate1.x, gate1.y, gate1.length, gate1.direction, RED);
            }
        } else {
            drawRect(tile1.x, tile1.y, tile1.size, tile1.size, tile1.color);
            drawRect(tile2.x, tile2.y, tile2.size, tile2.size, tile2.color);
            drawRect(tile3.x, tile3.y, tile3.size, tile3.size, tile3.color);
            drawLine(gate1.x, gate1.y, gate1.length, gate1.direction, RED);
            drawLine(gate2.x, gate2.y, gate2.length, gate2.direction, RED);
            drawLine(gate3.x, gate3.y, gate3.length, gate3.direction, RED);
            if(tileCollision(oldPlayerX,oldPlayerY , player.size, tile1)) {     //Check collision with tile
                drawLine(gate1.x, gate1.y, gate1.length, gate1.direction, WHITE);//Erase and redraw gate with new direction
                gate1.direction = 0; 
                drawLine(gate1.x, gate1.y, gate1.length, gate1.direction, RED);
            }
            if(tileCollision(oldPlayerX,oldPlayerY , player.size, tile2)) {     //Check collision with tile
                drawLine(gate2.x, gate2.y, gate2.length, gate2.direction, WHITE);//Erase and redraw gate with new direction
                gate1.direction = 0; 
                drawLine(gate2.x, gate2.y, gate2.length, gate2.direction, RED);
            }
            if(tileCollision(oldPlayerX,oldPlayerY , player.size, tile3)) {     //Check collision with tile
                drawLine(gate3.x, gate3.y, gate3.length, gate3.direction, WHITE);//Erase and redraw gate with new direction
                gate1.direction = 0; 
                drawLine(gate3.x, gate3.y, gate3.length, gate3.direction, RED);
            }
        }

        if (tileCollision(oldPlayerX, oldPlayerY, player.size winTile)) {
            return 1;
        }
        if (KEY_DOWN_NOW(BUTTON_SELECT)) {
            return 0;
        }
        drawRect(oldPlayerY, oldPlayerX , player.size, player.size, WHITE);
        drawRect(newPlayerY, newPlayerX, player.size, player.size, player.color);
        oldPlayerX = newPlayerX;
        oldPlayerY = newPlayerY;
        waitForVblank();
    }
    return 0;
}


void buildMaze1(PLAYER p, SWITCH tile1, GATE gate1, SWITCH winTile) {
    p = {0, 70, 1, 5, RED };
    winTile = {70, 200, 20, 20};
    gate1 = {49, 97, 40, 1, RED};
    tile1 = {10, 10, 10, BLUE};
}

void buildMaze2(Player p, SWITCH tile1, SWITCH tile2, SWITCH tile3, GATE gate1, GATE gate2, GATE gate3, SWITCH winTile) {
    p = {78, 0, 5, 5, RED};
    winTile = {75, 75, 15, 15, GREEN};
    gate1 = {66, 65, 9, 0, RED};
    tile1 = {141, 10, 10, GREEN};
    gate2 = {56, 54, 10, 0, RED};
    tile2 = {10, 10, 10, GREEN};
    gate3 = {122, 148, 10, 1, RED};
    tile3 = {143, 66, 8, GREEN};
}









