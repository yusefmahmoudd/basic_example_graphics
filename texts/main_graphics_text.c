#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"


void Initialize(Graphics_Context* g_sContext_p);


int main(void) {

    Graphics_Context g_sContext;

    Initialize(&g_sContext);

    Graphics_setFont(&g_sContext, &g_sFontCm14);
    Graphics_drawString(&g_sContext, (int8_t *)"1234567890abcdefghijklmnopqrstuvwx", -1, 0, 0, false);
    unsigned char h = Graphics_getStringHeight(&g_sContext);
    Graphics_drawString(&g_sContext, (int8_t *)"123456789012345678901234567890", -1, 0, 14, false);


    Graphics_setFont(&g_sContext, &g_sFontCmss18b);
    Graphics_drawString(&g_sContext, (int8_t *)"GO HOKIES", -1, 10, 70, false);

    h = Graphics_getStringHeight(&g_sContext);
    Graphics_setFont(&g_sContext, &g_sFontCmss20b);
    Graphics_drawString(&g_sContext, (int8_t *)"GO HOKIES", -1, 10, 90, true);

    while (1) ;
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
