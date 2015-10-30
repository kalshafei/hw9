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


int yEdgeCollision(int y, int height, int yD);
int xEdgeCollision(int x, int width, int xD);
int checkOutOfBound(int x, int y, u16* mask);
int vertWallCollision(int x, int y, int size, int xD);
int horWallCollision(int x, int y, int size, int yD);
int game();
int tileCollision(int px1, int py1, int psize, SWITCH g);

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

int game() {

    PLAYER player = {100, 100, 1, 5, RED};
    GATE gate1 = {10, 10, 5, 1, RED};
    SWITCH tile1 = {0, 0, 5, BLUE};

    // int won = 0;
    // int lost = 0;
    int oldPlayerX = player.x;
    int oldPlayerY = player.y;
    int newPlayerX = oldPlayerX;
    int newPlayerY = oldPlayerY;

    while(1) {
        if(KEY_DOWN_NOW(BUTTON_SELECT)) {
            return 0;
        }
        // if(won) {
        //     return 2;
        // }
        // if(lost) {
        //     return 1;
        // }      
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
        //ERASE
        drawRect(tile1.y, tile1.x, tile1.size, tile1.size, tile1.color);
        drawRect(oldPlayerY, oldPlayerX , player.size, player.size, WHITE);

        //DRAW NEW
        drawRect(tile1.x, tile1.y, tile1.size, tile1.size, tile1.color);    //Draw Tile
        drawLine(gate1.x, gate1.y, gate1.length, gate1.direction, RED);
        if(tileCollision(oldPlayerX,oldPlayerY , player.size, tile1)) {
            drawLine(gate1.x, gate1.y, gate1.length, gate1.direction, WHITE);
            gate1.direction = 0; 
            drawLine(gate1.x, gate1.y, gate1.length, gate1.direction, RED);
        }

        drawLine(20, 20, 5, 0, RED);

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


int vertWallCollision(int x, int y, int size, int xD) {
    if (xD > 0) {
        for (int j = 0; j < size; j++) {
            if (getColor(y + j, x + size) == BLACK || getColor(y + j, x + size) == RED) {
                return 0;
            }
        }
    } else if (xD < 0) {
        for (int j = 0; j < size; j++) {
            if (getColor(y + j, x - 1) == BLACK || getColor(y + j, x - 1) == RED) {
                return 0;
            }
        }
    }
    return xD;
}

int horWallCollision(int x, int y, int size, int yD) {
    if (yD > 0) {
        for (int i = 0; i < size; i++) {
            if (getColor(y + size, x + i) == BLACK || getColor(y + size, x + i) == RED) {
                return 0;
            }
        }
    } else if (yD < 0) {
        for (int i = 0; i < size; i++) {
            if (getColor(y - 1, x + i) == BLACK || getColor(y - 1, x + i) == RED) {
                return 0;
            }
        }
    }
    return yD;
}

int tileCollision(int px1, int py1, int psize, SWITCH g) {
    int px2 = px1 + psize - 1;
    int py2 = py1 + psize - 1;
    int sx1 = g.x;
    int sy1 = g.y;
    int sx2 = sx1 + g.size - 1;
    int sy2 = sy1 + g.size - 1;
    if (px1 <= sx2 && px2 >= sx1 &&
    py1 <= sy2 && py2 >= sy1) {
        return 1;
    } else {
        return 0;
    }
}