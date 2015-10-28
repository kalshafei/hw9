//Kyle Al-Shafei
//CS2110 HW9

#include "mylib.h"
#include <stdlib.h>

typedef struct {
	int row;
	int col;
	int speed;
	char direction;
	u16 color;
} ENEMY;

typedef struct {
	int row;
	int col;
	u16 color;
} PLAYER;

typedef struct {
	char direction;
	int length;
	int row;
	int col;
	u16 color;
} GATE;

typedef struct {
	int row;
	int col;
	u16 col;
	int size;
} SWITCH;


int main() {
	REG_DISPCTL = MODE_3 | BG2_EN;
	
	ENEMY enemy1;
	ENEMY enemy2;
	enemy1.row = //locaiton
	enemy1.col = //location
	enemy1.speed = 3;
	enemy1.direction = 'U';
	enemy2.row = //location
	enemy2.col = //location
	enemy1.direction = 'D';

	PLAYER player;
	player.row = 2;
	player.col = 2;
	player.color = GREEN;

	GATE gate1;
	GATE gate2;
	gate1.direction = 'U';
	gate1.length = 3; //PIXEL LENGTH OF GATE
	gate1.color = RED;
	gate1.row = //Location
	gate1.col = //Location
	gate2.direction = 'R';
	gate2.length = gate2.size; //PIXEL LENGTH OF GATE
	gate2.color = RED;
	gate2.row = //LOCATION
	gate2.col =	//LOCATION

	SWITCH tile1;
	SWITCH tile2;
	tile1.row = //LOCATION
	tile1.col = //LOCATION
	tile1.size = 5; //square
	tile1.color = BLUE;
	tile2.row = //LOCATION
	tile2.col = //LOCATION
	tile2.size = 5; //square
	tile2.color = BLUE;




	while(1) {
		if(KEY_DOWN_NOW(BUTTON_UP))
		{

		}
		if(KEY_DOWN_NOW(BUTTON_LEFT))
		{

		}
		if(KEY_DOWN_NOW(BUTTON_RIGHT))
		{

		}
		if(KEY_DOWN_NOW(BUTTON_DOWN))
		{

		}
		update(enemy1);
		update(enemy2);
		drawEnemy(enemy1);
		drawEnemy(enemy2);
		drawGate(gate1);
		drawGate(gate2);
		drawPlayer(player);
		checkGateCollision();
	}

	return 0;
}