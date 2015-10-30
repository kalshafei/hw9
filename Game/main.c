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
int horWallCollision(int x, int y, int size, int xD);
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


    //ENEMY enemy1 = {x, y, 3, 3, 'U', RED}; //Fill in row col start position
    //ENEMY enemy2 = {x, y, 3, 3, 'D', RED};
    PLAYER player = {100, 100, 1, 5, RED};
    //GATE gate1 = {x, y, length, direction, RED};
    //GATE gate2 = {x, y, length, direction, RED};
    //SWITCH tile1 = {x, y, 4, BLUE};
    //SWITCH tile2 = {x, y, 4, BLUE};
    
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
                if (getColor(y + j, x + i + size) == BLACK) {
                    return i - 1;
                }
            }
        }
    } else if (xD < 0) {
        for (int i = -1; i > xD; i--) {
            for (int j = 0; j < size + 1; j++) {
                if (getColor(y + j,x + i, videoBuffer)) {
                    return i + 1;
                }
            }
        }
    } 
    return xD;
}
