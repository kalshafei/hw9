//Kyle Al-Shafei
//CS2110 HW9

#include "mylib.h"
#include <stdlib.h>

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


int main() {

	REG_DISPCTL = MODE_3 | BG2_EN;
	drawRect(0, 0, 240, 160, WHITE);

	//ENEMY enemy1 = {x, y, 3, 3, 'U', RED}; //Fill in row col start position
	//ENEMY enemy2 = {x, y, 3, 3, 'D', RED};

	PLAYER player = {2, 2, 1, 2, GREEN};

	//GATE gate1 = {x, y, length, direction, RED};
	//GATE gate2 = {x, y, length, direction, RED};

	//SWITCH tile1 = {x, y, 4, BLUE};
	//SWITCH tile2 = {x, y, 4, BLUE};

	int oldPlayerX = player.x;
	int oldPlayerY = player.y;
	int newPlayerX = oldPlayerX;
	int newPlayerY = oldPlayerY;

	//drawRect(50, 50, 50, 1, BLACK);
	//drawRect(100, 100, 1, 50, BLACK);

	while(1) {
		if(KEY_DOWN_NOW(BUTTON_UP))
		{
			if (!yEdgeCollision(player.y, player.size, -1 * player.speed)) {
				newPlayerY += player.speed * -1;
			}
		}
		if(KEY_DOWN_NOW(BUTTON_LEFT))
		{
			if (!xEdgeCollision(player.x, player.size,  -1 * player.speed)) {
				newPlayerX += -1 * player.speed;
			}
		}
		if(KEY_DOWN_NOW(BUTTON_RIGHT))
		{
			if (!xEdgeCollision(player.x, player.size,  player.speed)) {
				newPlayerX += player.speed;
			}
		}
		if(KEY_DOWN_NOW(BUTTON_DOWN))
		{
			newPlayerY += yEdgeCollision(player.y, player.size,  player.speed);
		}

		drawRect(oldPlayerY, oldPlayerX , player.size, player.size, WHITE);
		drawRect(newPlayerY, newPlayerX, player.size, player.size, BLUE);
		// update(enemy1);
		// update(enemy2);
		// drawEnemy(enemy1);
		// drawEnemy(enemy2);
		// drawGate(gate1);
		// drawGate(gate2);
		// drawPlayer(player);
		// checkGateCollision();
	}

	return 0;
}

int xEdgeCollision(int x, int width, int xD) {
	if (xD > 0) {
		if (x + width + xD > 240) {
			return 240 - x - width;
		}
	} else if (xD < 0) {
		if (x + xD < 0) {
			return -x;
		}
	}
	return xD;
}

int yEdgeCollision(int y, int height, int yD) {
	if (yD > 0) {
		if (y + yD < 0) {
			return -y;
		}
	} else if (yD < 0) {
		if (y + yD + height > 160) {
			return 160 - y - height;
		}
	}
	return yD;
}

// int xWallCollision(int x, int y, int width, int xD) {

// 	for (int row = 0; row < width; row++) {
// 		if (getPixel(row + x, y) + )
// 	}
// }

// int yWallCollision(int x, int y, int height, int yD) {

// }