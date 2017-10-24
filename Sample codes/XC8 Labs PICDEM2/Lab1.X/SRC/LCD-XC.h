// set up the timing for the LCD delays
#if _XTAL_FREQ | FCY    // This is a default to stop linker errors
#else
#define _XTAL_FREQ 4000000  // device clock frequency (_XTAL_FREQ) used by XC8 for __delay_ms()
#define FCY _XTAL_FREQ/2    // device instruction frequency (FCY) used by XC16 for __delay_ms()
#endif         

#define	LCD_delay           5           //  ~5mS
#define	LCD_Startup         15          //  ~15mS

// Command set for Hitachi 44780U LCD display controller
#define LCD_CLEAR           0x01
#define LCD_HOME            0x02
#define LCD_CURSOR_BACK     0x10
#define LCD_CURSOR_FWD      0x14
#define LCD_PAN_LEFT        0x18
#define LCD_PAN_RIGHT       0x1C
#define LCD_CURSOR_OFF      0x0C
#define LCD_CURSOR_ON       0x0E
#define LCD_CURSOR_BLINK    0x0F
#define LCD_CURSOR_LINE2    0xC0

// Macros Recomended for new labs
#define mOPEN_LCD           LCDInit()
#define mLCD_PAN_RIGHT      LCDPutCmd (LCD_PAN_RIGHT)
#define mLCD_PAN_LEFT       LCDPutCmd (LCD_PAN_LEFT)
#define mLCD_CURSOR_BLINK   LCDPutCmd (LCD_CURSOR_BLINK)
#define mLCD_HOME           LCDPutCmd (LCD_HOME)
#define mLCD_CLEAR          LCDPutCmd (LCD_CLEAR)
#define mCURSOR_ON          LCDPutCmd (LCD_CURSOR_ON)
#define mCURSOR_OFF         LCDPutCmd (LCD_CURSOR_OFF)
#define mCURSOR_FWD         LCDPutCmd (LCD_CURSOR_FWD)
#define mCURSOR_BACK        LCDPutCmd (LCD_CURSOR_BACK)

// Common Function Prototypes for XC8 & XC16
void LCDInit(void);
void LCDPutChar(unsigned char ch);
void LCDPutCmd(unsigned char cmd);

// Common legecy Macros
#define LCDHome()           LCDPutCmd (LCD_HOME)         // legacy support
#define LCDClr()            LCDPutCmd (LCD_CLEAR)        // legacy support
#define LCDwrite            LCDPutChar                   // legacy support


#if __XC16
//----------------------------------------------------------------------
// Below are definitions specific to XC16 compiler
//----------------------------------------------------------------------

// display controller set up commands from page 46 of Hitachi datasheet
#define FUNCTION_SET        0x3C        // 8 bit interface, 2 lines, 5x8 font
#define ENTRY_MODE          0x06        // increment Mode
#define DISPLAY_SETUP       0x0C        // display on, cursor off, blink off

// Macro Definitions (not recomended for new code)
#define LCDCurFwd()         LCDPutCmd(LCD_CURSOR_FWD)   // legacy support
#define LCDCurBack()        LCDPutCmd(LCD_CURSOR_BACK)  // legacy support
#define LCDPanLeft()        LCDPutCmd(LCD_PAN_LEFT)     // legacy support
#define LCDPanRight()       LCDPutCmd(LCD_PAN_RIGHT)    // legacy support
#define LCDClear()          LCDPutCmd (LCD_CLEAR)       // legacy support
#define LCDPut              LCDPutChar                  // legacy support
#define LCDL1Home()         LCDPutCur(0,0)              // legacy support
#define LCDL2Home()         LCDPutCur(1,0)              // legacy support

// Specific Function Prototypes for XC16
void LCDPutStr(char *str);
void LCDPutCur(char row, char col);
void LCDPutInt(long num, char radix);
void LCDPutUInt(unsigned long num, char radix);
void LCDPutFloat(float fnum, char precision);
 
//----------------------------------------------------------------------
// Below are definitions specific to the Explorer 16
//----------------------------------------------------------------------

// NOTE: To use the macros below, YOU must have previously defined _XTAL_FREQ
#define __delay_ms(x) Wait((unsigned long)((x)*(_XTAL_FREQ/22000.0)))
inline static void Wait(unsigned long count) {while(count) count--;}   // 11 cycles per iteration + 17 overhead

#define MAX_DIGITS          6
#define BIN                 2
#define OCT                 8
#define DEC                 10
#define HEX                 16
#endif


#if __XC8
//----------------------------------------------------------------------
// Below are definitions specific to the XC8 compiler
//----------------------------------------------------------------------

// display controller set up commands from page 46 of Hitachi datasheet
#define FUNCTION_SET        0x28        // 4 bit interface, 2 lines, 5x8 font
#define ENTRY_MODE          0x06        // increment Mode
#define DISPLAY_SETUP       0x0C        // display on, cursor off, blink off

// Macro Definitions specific to XC8 (not reconended for new code)
#define text_display        LCDPutStr                    // legacy support
#define LCDLine1()          LCDPutCmd (LCD_HOME)         // legacy support
#define LCDLine2()          LCDPutCmd (LCD_CURSOR_LINE2) // legacy support
#define shift_cursor()      LCDPutCmd (LCD_CURSOR_FWD)   // legacy support
#define cursor_on()         LCDPutCmd (LCD_CURSOR_ON)    // legacy support

// Function prototypes
void LCDInit(void );                    // nitialize the LCD module
void LCDPutChar(unsigned char);         // display an ASCii character in data mode
void LCDPutCmd(unsigned char);          // sends an ASCii character command to the LCD in instruction mode
void LCDPutStr(unsigned char *);        // display a string
void LCDWriteNibble(unsigned char,unsigned char);

//----------------------------------------------------------------------
// Below are definitions specific to the PICDEM 2 +
// These apply to thre Red, Green and Black versions
//----------------------------------------------------------------------
//  single bit for selecting command register or data register
#define instr               0
#define data                1

// These #defines create the pin connections to the LCD in case they are changed on a future demo board
#define LCD_PORT     PORTD

#define	LCD_PWR      PORTDbits.RD7       // LCD power pin
#define	LCD_EN       PORTDbits.RD6       // LCD enable
#define	LCD_RW       PORTDbits.RD5       // LCD read/write line
#define	LCD_RS       PORTDbits.RD4       // LCD register select line

#define	LCD_PWR_DIR  TRISDbits.TRISD7
#define	LCD_EN_DIR   TRISDbits.TRISD6
#define	LCD_RW_DIR   TRISDbits.TRISD5
#define	LCD_RS_DIR   TRISDbits.TRISD4
#endif