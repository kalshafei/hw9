//Kyle Al-Shafei
//CS2110 HW9

#include "mylib.h"

unsigned short *videoBuffer = (unsigned short *)0x6000000;
// A function to set pixel (r, c) to the color passed in
void setPixel(int row, int col, u16 color) {
	videoBuffer[OFFSET(row, col, 240)] = color;
}

// A function to draw a FILLED rectangle starting at (r, c)
void drawRect(int r, int c, int width, int height, u16 color)
{
	for (int row = 0; row < height; row++) {
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
		videoBuffer[OFFSET(row + r, c, 240)] = color;
		videoBuffer[OFFSET(row + r, c + width - 1, 240)] = color;
	}
	//Paint ceiling and floor
	for (int col = 0; col < width; col++) {
		videoBuffer[OFFSET(r, col + c, 240)] = color;
		videoBuffer[OFFSET(r + height - 1, col + c, 240)] = color;
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


void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

void drawLine(int r, int c, int length, int direction, u16 color) {
	if (direction == 1) {
		for (int row = 0; row < length; row++) {
			setPixel(row + r, c, color);
		}
	} else {
		for (int col = 0; col < length; col++) {
			setPixel(r, c + col, color);
		}
	}
}

u16 getColor(int row, int col) {
	u16 color = videoBuffer[row*240 + col];
	return color;
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