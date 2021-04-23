#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"


#define PRESSED 0

void Initialize(Graphics_Context* g_sContext_p);
void TurnOn_Launchpad_LED1();
void TurnOff_Launchpad_LED1();
char SwitchStatus_Launchpad_Button1();


unsigned colormix(unsigned r,unsigned g,unsigned b) {
    return ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
}

int main(void) {
    Graphics_Context g_sContext;

    unsigned i, j, r, g, b;

    Initialize(&g_sContext);

    while (1)
    {
        // If the button is not pressed, keep the LED off
        if (SwitchStatus_Launchpad_Button1() != PRESSED)
            TurnOff_Launchpad_LED1();
        else
            TurnOn_Launchpad_LED1();

        for (j=0; j<128; j++)
        {
            for (i=0; i<128; i++)
            {
                r = 25;
                g = i*2;
                b = 256 - i*2;
                Graphics_setForegroundColor(&g_sContext, colormix(r,g,b));
                Graphics_drawLineH(&g_sContext, 0, 127, (i+j)%127);
            }
        }

    }

}

void initializeButtonLED()
{
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN1);
}

void TurnOn_Launchpad_LED1()
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
}
void TurnOff_Launchpad_LED1()
{
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
}
char SwitchStatus_Launchpad_Button1()
{
    return (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1));
}

// This function initializes the the LCD screen including setting up the SPI connection
void Init_LCD() {
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

    Init_LCD();

    Graphics_clearDisplay(g_sContext_p);
}




// The general initialization function
void Initialize(Graphics_Context* g_sContext_p) {
    WDT_A_hold(WDT_A_BASE);

    InitGraphics(g_sContext_p);
}
