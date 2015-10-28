#include "myLib.h"

unsigned short *videoBuffer = (unsigned short *)0x6000000;


void setPixel(int r, int c, unsigned short color)
{
	videoBuffer[OFFSET(r,c, 240)] = color; 
}

void drawRect(int row, int col, int height, int width, unsigned short color)
{
	int r,c;
	for(r=0; r<height; r++)
	{
		for(c=0; c<width; c++)
		{
			setPixel(r+row, c+col, color);
		}
	}
}


void drawChar(int row, int col, char ch, unsigned short color)
{
	int r,c;
	for(r=0; r<8; r++)
	{
		for(c=0; c<6; c++)
		{
			if(fontdata_6x8[OFFSET(r, c, 6)+ch*48])
			{
				setPixel(row+r, col+c, color);
			}
		}
	}
}

void drawString(int row, int col, char *str, unsigned short color)
{
	while(*str)
	{
		drawChar(row, col, *str++, color);
		col += 6;
	}
}
				
void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

