//Gameboy

#define REG_DISPCTL *(unsigned short*)0x4000000
#define MODE3
#define SCANLINECOUNTER *(volatile unsigned short *)0x4000006
#define BG2_ENABLE (1<<10)
#define COLOR(r,g,b) r | g<<5 | b<<10//27		//cause little endian
#define RED COLOR(31,0,0)
#define GREEN COLOR(0,31,0)
#define BLUE COLOR(0,0,31)
#define MAGENTA COLOR(31,0,31)
#define CYAN COLOR(0,31,31)
#define YELLOW COLOR(31,31,0)
#define WHITE COLOR(31,31,31)
#define BLACK 0
#define OFFSET(r,c,numcols) ((r)*(numcols)+(c))

#define BUTTON_A 		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R 		(1<<8)
#define BUTTON_L 		(1<<9)

#define KEY_DOWN_NOW(key) (~(BUTTONS) & key)

#define BUTTONS *(volatile unsigned int *)0x4000130

unsigned short *videoBuffer = (unsigned short *)0x6000000;

//Prototypes
void setPixel(int row, int col, unsigned short color);
void drawRect(int row, into col, int height, int width, unsigned short color);
void delay(int n);
void limitCheck(int var, int delta, int limit, int size);

int main() {
	REG_DISPCTL = MODE3 | BG2_ENABLE;			//Location of REG_DISPCNT, set value to 1027 (Mode 3, BG2_Enabled)

		// *( videoBuffer + 19320 ) = 32767;	//Automatically multiplies the 19320 by 2 (short length), cause pointer arithmetic
		//19320[videoBuffer] = 32767;
	
	//setPixel(30,120,WHITE);

	int row = 80;
	int col = 120;
	int rdel = 1;
	int cdel = 1;
	int size = 5;
	int oldcol = col;
	int oldrow = row;
	int oldsize = size;

	while(1)  // The game loop
	{
		if (KEY_DOWN_NOW(BUTTON_UP)) {
			size++;
			if(size > 150)
				size = 150;
		}
		if (KEY_DOWN-NOW(BUTTON_DOWN)) {
			size--;
			if(size < 3) size = 3;
		}

		row += rdel;
		col += cdel;
		
		//makes square bounce off the screen when it hits the edge
		limitCheck(&row, &rdel, 159, size);
		limitCheck(&col, &cdel, 239, size);
		waitForVBlank();
		//Draw black over old spot using old size
		drawRect(oldrow, oldcol, oldsize, oldsize, BLACK);
		drawRect(row, col, size, size, RED);

		oldrow = row;
		oldcol = col;
		oldsize = size;
	}
}

void setPixel(int row, int col, unsigned short color) {
	videoBuffer[OFFSET(row, col, 240)] = color;
}

void drawRect(int row, into col, int height, int width, unsigned short color) {
	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++) {
			setPixel(row + r, col + c, color);
		}
	}
}

void delay(int n) {
	volatile int x = 0;				//Volatile forces the compiler to not ignore it
	for (int i = 0; i < n*5000; i++) {
		x = x + 1;
	}
}

void limitCheck(int *var, int *delta, int limit, int size) {	//pass in addresses so that can actually change values at address
	if (*var < 0) {
			*var = 0;
			*delta = -*delta;
		}
	if (*var > limit - size) {
		*var = limit - size;
		*delta = -*delta;
	}
}

void waitForVBlank() {
	while (SCANLINECOUNTER > 160);
	while (SCANLINECOUNTER < 160);
}