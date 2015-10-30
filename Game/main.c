//Kyle Al-Shafei
//CS2110 HW9

#include "mylib.h"
#include <stdlib.h>

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

int yEdgeCollision(int y, int height, int yD);
int xEdgeCollision(int x, int width, int xD);
int checkOutOfBound(int x, int y, u16* mask);


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
    drawLine(100, 100, 10, 1, BLACK);
    drawLine(100, 100, 10, 0, BLACK);
    //drawRect(100, 100, 1, 50, BLACK);

    while(1) {
        int neg = -1 * player.speed;
        if(KEY_DOWN_NOW(BUTTON_UP))
        {
            newPlayerY += yEdgeCollision(oldPlayerY, player.size, neg);

        }
        if(KEY_DOWN_NOW(BUTTON_LEFT))
        {
            int wall = horWallCollision(oldPlayerX, oldPlayerY, player.size, neg);
            int edge = xEdgeCollision(oldPlayerX, player.size, neg);
            newPlayerX += MAX(edge, wall);
        }
        if(KEY_DOWN_NOW(BUTTON_RIGHT))
        {
            int wall = horWallCollision(oldPlayerX, oldPlayerY, player.size, player.speed);
            int edge = xEdgeCollision(oldPlayerX, player.size,  player.speed);
            newPlayerX += MIN(edge, wall);
        }
        if(KEY_DOWN_NOW(BUTTON_DOWN))
        {
            newPlayerY += yEdgeCollision(oldPlayerY, player.size,  player.speed);
        }

        drawRect(oldPlayerY, oldPlayerX , player.size, player.size, WHITE);
        drawRect(newPlayerY, newPlayerX, player.size, player.size, player.color);
        oldPlayerX = newPlayerX;
        oldPlayerY = newPlayerY;

        waitForVblank();
    }

    return 0;
}

int xEdgeCollision(int x, int width, int xD) {
    if (xD > 0) {
        if (x + width + xD > 240) {
            return 0;
        } 
    } else if (xD < 0) {
        if (x + xD < 0) {
            return 0;
        } 
    }
    return xD;
}

int yEdgeCollision(int y, int height, int yD) {
    if (yD > 0) {
        if (y + height + yD > 160) {
            return 0;
        }
    } else if (yD < 0) {
        if (y + yD < 0) {
            return 0;
        } 
    }
    return yD;
}


int horWallCollision(int x, int y, int size, int xD) {
    if (xD > 0) {
        for (int i = 1; i < xD; i++) {
            for (int j = 0; j < size + 1; j++) {
                if (checkOutOfBound(y + j, x + i + size, videoBuffer)) {
                    return i - 1;
                }
            }
        }
    } else if (xD < 0) {
        for (int i = -1; i > xD; i--) {
            for (int j = 0; j < size + 1; j++) {
                if (checkOutOfBound(y + j,x + i, videoBuffer)) {
                    return i + 1;
                }
            }
        }
    } else {
        return xD;
    }
}

int checkOutOfBound(int x, int y, u16* mask) {
    if (mask[OFFSET(x, y, 240)] == BLACK) {
        return 1;
    } else {
        return 0;
    }
}