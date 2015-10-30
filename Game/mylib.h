//Kyle Al-Shafei
//CS2110 HW9

typedef unsigned short u16;
typedef unsigned int u32;

#define OFFSET(row, col) ((row) *240 + (col))
#define RGB(r, g, b) (((b) << 10) | ((g) << 5) | (r))
#define REG_DISPCTL *(u16 *)0x4000000
#define MODE_3 3
#define BG2_EN (1 << 10)
#define SCANLINECOUNTER *(volatile u16 *)0x4000006

extern u16 *videoBuffer;
extern const unsigned char fontdata_6x8[12288];

#define RED RGB(31,0,0)
#define GREEN RGB(0,31,0)
#define BLUE RGB(0,0,31)
#define MAGENTA RGB(31,0,31)
#define CYAN RGB(0,31,31)
#define YELLOW RGB(31,31,0)
#define WHITE RGB(31,31,31)
#define BLACK 0

#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)
#define BUTTON_MASK     (0x03FF)


#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)
#define BUTTONS *(volatile unsigned int *)0x4000130


//Function Prototypes
void setPixel(int r, int c, u16 color);
void drawRect(int r, int c, int width, int height, u16 color);
void drawHollowRect(int r, int c, int width, int height, u16 color);
void drawImage3(int r, int c, int width, int height, const u16* image);
void key_poll();
void waitForVblank();
u32 key_hit(u32 key);
u32 key_released(u32 key);
