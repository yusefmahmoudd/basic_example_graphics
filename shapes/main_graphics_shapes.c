

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"


void Initialize(Graphics_Context* g_sContext_p);

int main(void) {

    // A structure that holds a large set of characteristics for graphics including foreground color, background color, fot of
    Graphics_Context g_sContext;

    Initialize(&g_sContext);

    Graphics_Rectangle R;
    R.xMin = 0;
    R.xMax = 63;
    R.yMin = 0;
    R.yMax = 127;

    Graphics_drawRectangle(&g_sContext, &R);
    Graphics_drawLine(&g_sContext, 0, 0, 127, 127);
    Graphics_fillCircle(&g_sContext, 63, 63, 30);

}

// This function initializes the fonts we can use
void InitFonts() {
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
}

// This function initializes the graphics
void InitGraphics(Graphics_Context *g_sContext_p) {

    Graphics_initContext(g_sContext_p,
                         &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_YELLOW);
    Graphics_setBackgroundColor(g_sContext_p, GRAPHICS_COLOR_BLACK);
    Graphics_setFont(g_sContext_p, &g_sFontCmtt16);

    InitFonts();

    Graphics_clearDisplay(g_sContext_p);
}




// The general initialization function
void Initialize(Graphics_Context* g_sContext_p) {
    WDT_A_hold(WDT_A_BASE);

    InitGraphics(g_sContext_p);
}
