//Kyle Al-Shafei
//CS2110 HW9

#define OFFSET(row, col) ((row) *240 + (col))
#define RGB(r, g, b) (((b) << 10) | ((g) << 5) | (r))
#define REG_DISPCTL *(u16 *)0x4000000
#define MODE_3 3
#define BG2_EN (1 << 10)

#define KEY_A        0x0001
#define KEY_B        0x0002
#define KEY_SELECT   0x0004
#define KEY_START    0x0008
#define KEY_RIGHT    0x0010
#define KEY_LEFT     0x0020
#define KEY_UP       0x0040
#define KEY_DOWN     0x0080
#define KEY_R        0x0100
#define KEY_L        0x0200
#define KEY_MASK     0x03FF

typedef unsigned short u16;
typedef unsigned int u32;

u16 *videoBuffer= (u16*)(0x6000000);
//extern u16 *videoBuffer;
//Function Prototypes
void setPixel(int r, int c, u16 color);
void drawRect(int r, int c, int width, int height, u16 color);
void drawHollowRect(int r, int c, int width, int height, u16 color);
void drawImage3(int r, int c, int width, int height, const u16* image);
void key_poll();
u32 key_hit(u32 key);
u32 key_released(u32 key);

