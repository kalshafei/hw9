#include "myLib.h"
#include <stdlib.h>
#define HEIGHTMAX 149

#define NUMOBJS 7

typedef struct
{
	int row;
	int col;
	int rd;
	int cd;
	int size;
	u16 color;
} MOVOBJ;

void bouncecheck(int cond, 
			int *var1, int set1, 
			int *var2, int set2,
			int *var3, int set3);


int main()
{
	int i;
	char buffer[15];
	int size = 5;
	int oldsize = size;
	int dels[] = {-3, -2, -1, 1, 2, 3};
	int numdels = sizeof(dels)/ sizeof(dels[0]);
	u16 colors[] = {RED, GREEN, BLUE, MAGENTA, 
		        CYAN, YELLOW, WHITE};
	int numcolors = sizeof(colors)/sizeof(colors[0]);
	MOVOBJ objs[NUMOBJS];
	MOVOBJ oldobjs[NUMOBJS];
	MOVOBJ *cur;
	
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	for(i=0; i<NUMOBJS; i++)
	{
		objs[i].row = 70 + rand()%20;
		objs[i].col = 110 + rand()%20;
		objs[i].rd =  dels[rand()%numdels];
		objs[i].cd =  dels[rand()%numdels];
		objs[i].color = colors[i%numcolors];
		oldobjs[i] = objs[i];
	}
	
	int score = 0;
	drawString(150, 5, "Score:", RED);
	while(1) // Game Loop
	{
		if(KEY_DOWN_NOW(BUTTON_UP))
		{
			size++;
			if(size>150)
				size = 150;
		}
		if(KEY_DOWN_NOW(BUTTON_DOWN))
		{
			size--;
			if(size<3)
				size = 3;
		}
		for(i=0; i<NUMOBJS; i++)
		{
			//cur = &objs[i];
			cur = objs + i;		
			cur->row =  cur->row + cur->rd;
			cur->col = cur->col + cur->cd;
			bouncecheck(cur->row < 0, 
			&(cur->row), 0,
			&(cur->rd), -cur->rd,
			&(score), score+1);
			
			if( cur->row < 0)
			{
				cur->row = 0;
				cur->rd = -cur->rd;
				score++;
			}
			
			
			if( cur->row > HEIGHTMAX-size+1)
			{
				cur->row = HEIGHTMAX-size+1;
				cur->rd = -cur->rd;
			}
			if(cur->col < 0)
			{
				cur->col = 0;
				cur->cd = -cur->cd;
			}
			if(cur->col > 239-size+1)
			{
				cur->col = 239-size+1;
				cur->cd = -cur->cd;
			}
		}
		waitForVblank();
		for(i=0; i<NUMOBJS; i++)
		{
				
			drawRect(oldobjs[i].row, oldobjs[i].col, oldsize, oldsize, BLACK);
		}
		for(i=0; i<NUMOBJS; i++)
		{
			cur = objs+i;				
			drawRect( cur->row, cur->col, size, size, cur->color);
			oldobjs[i] = objs[i];
			
			
		} // for loop
		drawRect(150,42, 10, 24, BLACK);
		sprintf(buffer, "%d", score);
		drawString(150, 42, buffer, RED);
		oldsize = size;
	} // Game Loop
	return 0;
}

void bouncecheck(int cond, 
			int *var1, int set1, 
			int *var2, int set2,
			int *var3, int set3)
{
	if(cond)
	{
		*var1 = set1;
		*var2 = set2;
		*var3 = set3;
	}
}		


