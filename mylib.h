//Kyle Al-Shafei
//CS2110 HW9

#define OFFSET(row, col) ((row) *240 + (col))
#define RGB(r, g, b) (((b) << 10) | ((g) << 5) | (r))
#define REG_DISPCTL *(u16 *)0x4000000
#define MODE_3 3
#define BG2_EN (1 << 10)
typedef unsigned short u16;
typedef unsigned int u32;
u16 *videoBuffer= (u16*)(0x6000000);


//Function Prototypes
void setPixel(int r, int c, u16 color);
void drawRect(int r, int c, int width, int height, u16 color);
void drawHollowRect(int r, int c, int width, int height, u16 color);
void drawImage3(int r, int c, int width, int height, const u16* image);

