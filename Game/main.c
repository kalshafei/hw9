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
    MAZE2,
    MAZE2_NODRAW,
    LOSE,
    LOSE_NODRAW,
    WIN,
    WIN_NODRAW
};


int game();
void buildMaze1(PLAYER p, SWITCH tile1, GATE gate1, SWITCH winTile);
void buildMaze2(PLAYER p, SWITCH tile1, SWITCH tile2, SWITCH tile3, GATE gate1, GATE gate2, GATE gate3, SWITCH winTile);
int vertWallCollision(int x, int y, int size, int xD);
int horWallCollision(int x, int y, int size, int yD);
int yEdgeCollision(int y, int height, int yD);
int xEdgeCollision(int x, int width, int xD);
int tileCollision(int px1, int py1, int psize, SWITCH g);
int enemyCollision(int px1, int py1, int psize, ENEMY g);

int main() {
    REG_DISPCTL = MODE_3 | BG2_EN;
    enum GBAState state = START;
    int gameState;
    int alpha;
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
            alpha = 1;
            gameState = game(alpha);
            if (gameState == 0) {
                state = START;
            } else  {
                state = MAZE2;
                alpha = 2;
            }
            break;
        case MAZE2:
            drawImage3(0, 0, 240, 160, maze2);
            state = MAZE2_NODRAW;
            waitForVblank();
            break;
        case MAZE2_NODRAW:
            alpha = 2;
            gameState = game(alpha);
            if (gameState == 0) {
                state = START;
            } else  if (gameState == 1) {
                state = WIN;
            } else {
                state = LOSE;
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
    ENEMY enemy1 = {0,0,0,0,CYAN};
    ENEMY enemy2 = {0,0,0,0,CYAN};
    ENEMY enemy3 = {0,0,0,0,CYAN};
    ENEMY enemy4 = {0,0,0,0,CYAN};
    PLAYER player;
    GATE gate1;
    SWITCH tile1;
    SWITCH winTile;
    GATE gate2 = {0,0,0,0,RED};
    GATE gate3 = {0,0,0,0,RED};
    SWITCH tile2 = {0,0,0,BLUE};
    SWITCH tile3 = {0,0,0,BLUE};

    player.x = 0;
    player.y = 70;
    player.speed = 1;
    player.size = 5;
    player.color = RED;
    winTile.x = 200;
    winTile.y = 70;
    winTile.size = 20;
    winTile.color = GREEN;
    gate1.x = 49;
    gate1.y = 97;
    gate1.length = 40;
    gate1.direction = 1;
    gate1.color = RED;
    tile1.x = 10;
    tile1.y = 10;
    tile1.size = 10;
    tile1.color = BLUE;
    if (maze == 2) {
        player.x = 0;
        player.y = 75;
        player.speed = 1;
        player.size = 5;
        player.color = RED;
        winTile.x = 75;
        winTile.y = 75;
        winTile.size = 15;
        winTile.color = GREEN;
        gate1.x = 66;
        gate1.y = 65;
        gate1.length = 9;
        gate1.direction = 1;
        gate1.color = RED;
        tile1.x = 10;
        tile1.y = 143;
        tile1.size = 8;
        tile1.color = BLUE;
        gate2.x = 38;
        gate2.y = 46;
        gate2.length = 10;
        gate2.direction = 0;
        gate2.color = RED;
        tile2.x = 10;
        tile2.y = 10;
        tile2.size = 10;
        tile2.color = BLUE;
        gate3.x = 122;
        gate3.y = 148;
        gate3.length = 10;
        gate3.direction = 1;
        gate3.color = RED;
        tile3.x = 66;
        tile3.y = 143;
        tile3.size = 8;
        tile3.color = BLUE;
        enemy1.x = 100;
        enemy1.y = 75;
        enemy1.speed = -1;
        enemy1.size = 5;
        enemy1.color = CYAN;
        enemy2.x = 120;
        enemy2.y = 75;
        enemy2.speed = 2;
        enemy2.size = 5;
        enemy2.color = CYAN;
        enemy3.x = 121;
        enemy3.y = 100;
        enemy3.speed = 2;
        enemy3.size = 5;
        enemy3.color = CYAN;
        enemy4.x = 120;
        enemy4.y = 60;
        enemy4.speed = -1;
        enemy4.size = 5;
        enemy4.color = CYAN;

    }
    drawRect(winTile.y, winTile.x, winTile.size, winTile.size, winTile.color);
    waitForVblank();

    int oldPlayerX = player.x;
    int oldPlayerY = player.y;
    int newPlayerX = oldPlayerX;
    int newPlayerY = oldPlayerY;


    while(1) {
        drawRect(oldPlayerY, oldPlayerX , player.size, player.size, WHITE);
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
        // drawRect(tile1.x, tile1.y, tile1.size, tile1.size, tile1.color);    //Redraw Tile
        drawLine(gate1.x, gate1.y, gate1.length, gate1.direction, RED);     //Draw Line
        if(tileCollision(oldPlayerX,oldPlayerY , player.size, tile1)) {     //Check collision with tile
            drawLine(gate1.x, gate1.y, gate1.length, gate1.direction, WHITE);//Erase and redraw gate with new direction
            gate1.direction = 0;
            drawLine(gate1.x, gate1.y, gate1.length, gate1.direction, RED);
        }
        drawRect(tile1.y, tile1.x, tile1.size, tile1.size, tile1.color);
        drawRect(tile2.y, tile2.x, tile2.size, tile2.size, tile2.color);
        drawRect(tile3.y, tile3.x, tile3.size, tile3.size, tile3.color);
        drawLine(gate1.x, gate1.y, gate1.length, gate1.direction, RED);
        drawLine(gate2.x, gate2.y, gate2.length, gate2.direction, RED);
        drawLine(gate3.x, gate3.y, gate3.length, gate3.direction, RED);
        if(tileCollision(oldPlayerX,oldPlayerY , player.size, tile1)) {     //Check collision with tile
            drawLine(gate1.x, gate1.y, gate1.length, gate1.direction, WHITE);//Erase and redraw gate with new direction
            gate1.direction = 0;
            drawLine(gate1.x, gate1.y, gate1.length, gate1.direction, RED);
        }
        if(tileCollision(oldPlayerX,oldPlayerY , player.size, tile3)) {     //Check collision with tile
            drawLine(gate2.x, gate2.y, gate2.length, gate2.direction, WHITE);//Erase and redraw gate with new direction
            gate2.direction = 1;
            drawLine(gate2.x, gate2.y, gate2.length, gate2.direction, RED);
        }
        if(tileCollision(oldPlayerX,oldPlayerY , player.size, tile2)) {     //Check collision with tile
            drawLine(gate3.x, gate3.y, gate3.length, gate3.direction, WHITE);//Erase and redraw gate with new direction
            gate3.direction = 0;
            drawLine(gate3.x, gate3.y, gate3.length, gate3.direction, RED);
            drawLine(gate1.x, gate1.y, gate1.length, gate1.direction, BLACK);//Erase and redraw gate with new direction
            gate1.direction = 1;
            drawLine(gate1.x, gate1.y, gate1.length, gate1.direction, RED);
        }

        drawRect(enemy1.y, enemy1.x, enemy1.size, enemy1.size, WHITE);
        if(horWallCollision(enemy1.x, enemy1.y, enemy1.size, enemy1.speed) == 0) {
            enemy1.speed *= -1;
        }
        enemy1.y += enemy1.speed;
        drawRect(enemy1.y, enemy1.x, enemy1.size, enemy1.size, enemy1.color);

        drawRect(enemy2.y, enemy2.x, enemy2.size, enemy2.size, WHITE);
        if(horWallCollision(enemy2.x, enemy2.y, enemy2.size, enemy2.speed) == 0) {
            enemy2.speed *= -1;
        }
        enemy2.y += enemy2.speed;
        drawRect(enemy2.y, enemy2.x, enemy2.size, enemy2.size, enemy2.color);


        drawRect(enemy3.y, enemy3.x, enemy3.size, enemy3.size, WHITE);
        if(vertWallCollision(enemy3.x, enemy3.y, enemy3.size, enemy3.speed) == 0) {
            enemy3.speed *= -1;
        }
        enemy3.x += enemy3.speed;
        drawRect(enemy3.y, enemy3.x, enemy3.size, enemy3.size, enemy3.color);

        drawRect(enemy4.y, enemy4.x, enemy4.size, enemy4.size, WHITE);
        if(vertWallCollision(enemy4.x, enemy4.y, enemy4.size, enemy4.speed) == 0) {
            enemy4.speed *= -1;
        }
        enemy4.x += enemy4.speed;
        drawRect(enemy4.y, enemy4.x, enemy4.size, enemy4.size, enemy4.color);

        if(enemyCollision(newPlayerX, newPlayerY, player.size, enemy1)) {
            return 2;
        }

        if(enemyCollision(newPlayerX, newPlayerY, player.size, enemy2)) {
            return 2;
        }
        if(enemyCollision(newPlayerX, newPlayerY, player.size, enemy3)) {
            return 2;
        }
        if(enemyCollision(newPlayerX, newPlayerY, player.size, enemy4)) {
            return 2;
        }

        if (KEY_DOWN_NOW(BUTTON_SELECT)) {
            return 0;
        }
        if (tileCollision(newPlayerX, newPlayerY, player.size, winTile)) {
            return 1;
        }

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

int enemyCollision(int px1, int py1, int psize, ENEMY g) {
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





