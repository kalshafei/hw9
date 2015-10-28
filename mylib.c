//Kyle Al-Shafei
//CS2110 HW9

#include "mylib.h"

unsigned short *videoBuffer = (unsigned short *)0x6000000;
// A function to set pixel (r, c) to the color passed in
void setPixel(int r, int c, u16 color) {
	videoBuffer[OFFSET(row, col, 240)] = color;
}

// A function to draw a FILLED rectangle starting at (r, c)
void drawRect(int r, int c, int width, int height, u16 color)
{
	for (int row = 0; row < height; i++) {
		for (int col = 0; col < width; col++) {
			setPixel(row + r, col + c, color);
		}
	}
}


// A function to draw a HOLLOW rectangle starting at (r,c)
// NOTE: It has to run in O(w+h) time.
void drawHollowRect(int r, int c, int width, int height, u16 color)
{
	//paint left and right edges
	for (int row = 0; row < height; row++) {
		videoBuffer[row + r, c] = color;
		videoBuffer[row + r, c + width - 1] = color;
	}
	//Paint ceiling and floor
	for (int col = 0; col < width; col++) {
		videoBuffer[row, col + c] = color;
		videoBuffer[row + height - 1, col + c] = color;
	}
}
/* drawimage3
 * A function that will draw an arbitrary sized image
 * onto the screen
 * @param r row to draw the image
 * @param c column to draw the image
 * @param width width of the image
 * @param height height of the image
 * @param image Pointer to the first element of the image.
 */

void drawImage3(int r, int c, int width, int height, const u16* image) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			videoBuffer[c * 240 + r + row * 240 + col] = image[col + row * width];
		}
	}
}


void key_poll()
{
    __key_prev= __key_curr;
    __key_curr= ~REG_KEYINPUT & KEY_MASK;
}

u32 key_hit(u32 key)
{   return ( __key_curr &~ __key_prev) & key;  }

u32 key_released(u32 key)
{   return (~__key_curr &  __key_prev) & key;  }

void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

