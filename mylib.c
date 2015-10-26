//Kyle Al-Shafei
//CS2110 HW9

#define OFFSET(row, col) ((row) *240 + (col))
#define toRGB(r, g, b) (((b) << 10) | ((g) << 5) | (r))



typedef unsigned short u16;
typedef unsigned int u32;

u16 *videoBuffer= (u16*)(0x6000000);

//Function Prototypes
void setPixel(int r, int c, u16 color);
void drawRect(int r, int c, int width, int height, u16 color);
void drawHollowRect(int r, int c, int width, int height, u16 color);
void drawImage3(int r, int c, int width, int height, const u16* image);

// A function to set pixel (r, c) to the color passed in
void setPixel(int r, int c, u16 color) {
	videoBuffer[OFFSET(r, c)] = color;
}

// A function to draw a FILLED rectangle starting at (r, c)
void drawRect(int r, int c, int width, int height, u16 color)
{
	for (int row = 0; row < height; i++) {
		for (int col = 0; col < width; col++) {
			videoBuffer[OFFSET(row + r, col + c)] = color;
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

}


