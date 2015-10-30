//Kyle Al-Shafei
//CS2110 HW9

#include "mylib.h"
#include <stdlib.h>

#define min(a,b) 
   ({ __typeof__ (a) _a = (a); 
       __typeof__ (b) _b = (b); 
     _a > _b ? _b : _a; })

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

int yEdgeCollision(int x, int y, int height, int yD);
int xEdgeCollision(int x, int y, int width, int xD);


int main() {

    REG_DISPCTL = MODE_3 | BG2_EN;
    drawRect(0, 0, 240, 160, WHITE);

    //ENEMY enemy1 = {x, y, 3, 3, 'U', RED}; //Fill in row col start position
    //ENEMY enemy2 = {x, y, 3, 3, 'D', RED};

    PLAYER player = {100, 100, 1, 5, RED};

    //GATE gate1 = {x, y, length, direction, RED};
    //GATE gate2 = {x, y, length, direction, RED};

    //SWITCH tile1 = {x, y, 4, BLUE};
    //SWITCH tile2 = {x, y, 4, BLUE};

    int oldPlayerX = player.x;
    int oldPlayerY = player.y;
    int newPlayerX = oldPlayerX;
    int newPlayerY = oldPlayerY;

    drawRect(50, 50, 50, 1, BLACK);
    //drawRect(100, 100, 1, 50, BLACK);

    while(1) {
        int neg = -1 * player.speed;
        if(KEY_DOWN_NOW(BUTTON_UP))
        {
            newPlayerY += yEdgeCollision(oldPlayerX, oldPlayerY, player.size, neg);

        }
        if(KEY_DOWN_NOW(BUTTON_LEFT))
        {
            int wall = horWallCollision(oldPlayerX, oldPlayerY, player.size, neg);
            int edge = yEdgeCollision(oldPlayerX, oldPlayerY, player.size, neg);
            newPlayerX += min(edge, wall);
        }
        if(KEY_DOWN_NOW(BUTTON_RIGHT))
        {
            int wall = horWallCollision(oldPlayerX, oldPlayerY, player.size, player.speed);
            int edge = xEdgeCollision(oldPlayerX, oldPlayerY, player.size,  player.speed);
            newPlayerX += min(edge, wall);
        }
        if(KEY_DOWN_NOW(BUTTON_DOWN))
        {
            newPlayerY += yEdgeCollision(oldPlayerX, oldPlayerY, player.size,  player.speed);
        }

        drawRect(oldPlayerY, oldPlayerX , player.size, player.size, WHITE);
        drawRect(newPlayerY, newPlayerX, player.size, player.size, player.color);
        oldPlayerX = newPlayerX;
        oldPlayerY = newPlayerY;
        // update(enemy1);
        // update(enemy2);
        // drawEnemy(enemy1);
        // drawEnemy(enemy2);
        // drawGate(gate1);
        // drawGate(gate2);
        // drawPlayer(player);
        // checkGateCollision();
        waitForVblank();
    }

    return 0;
}

int xEdgeCollision(int x, int y, int width, int xD) {
    if (xD > 0) {
        if (x + width + xD > 240) {
            //return 240 - x - width;
            return 0;
        } else if (xWallCollision(x, y, width, xD)) {
            return 0;
        }
    } else if (xD < 0) {
        if (x + xD < 0) {
            return 0;
        } 
    }
    return xD;
}

int yEdgeCollision(int x, int y, int height, int yD) {
    if (yD > 0) {
        if (y + height + yD > 160) {
            //return 240 - x - width;
            return 0;
        }
    } else if (yD < 0) {
        if (y + yD < 0) {
            //return -x;
            return 0;
        } 
    }
    return yD;
}


int horWallCollision(int x, int y, int size, int xD) {
    if (xD > 0) {
        for (int i = 1; i < xD; i++) {
            for (int j = 0; j < size + 1; j++) {
                if (getPixel(x + j + size, y + i) == BLACK) {
                    return i;
                }
            }
        }
    } else if (xD < 0) {
        for (int i = -1; i > xD; i--) {
            for (int j = 0; j < size + 1; j++) {
                if (getPixel(x + j + size, y + i) == BLACK) {
                    return i;
                }
            }
        }
    } else {
        return xD;
    }
}