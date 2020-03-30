#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"

Graphics_Context g_sContext;

#define PRESSED 0

void Initialize();
void TurnOn_Launchpad_LED1();
void TurnOff_Launchpad_LED1();
char SwitchStatus_Launchpad_Button1();


unsigned colormix(unsigned r,unsigned g,unsigned b) {
    return ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
}

int main(void) {
    unsigned i, j, r, g, b;

    Initialize();

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

// Initialization part is always device dependent and therefore does not change much with HAL
void initializeButtonLED()
{



    // step 2: Initializing LED1, which is on Pin 0 of Port P1 (from page 37 of the Launchpad User Guide)
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    // step 3: Initializing S1 (switch 1 or button 1),
    // which is on Pin1 of Port 1 (from page 37 of the Launchpad User Guide)
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

void InitFonts() {
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
}

void InitGraphics() {

    Graphics_initContext(&g_sContext,
                         &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_YELLOW);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
    Graphics_setFont(&g_sContext, &g_sFontCmtt16);
    Graphics_clearDisplay(&g_sContext);

    InitFonts();
}




void LCDClearDisplay() {
    Graphics_clearDisplay(&g_sContext);
}

void Initialize() {
    WDT_A_hold(WDT_A_BASE);

    InitGraphics();
    LCDClearDisplay();
    initializeButtonLED();

}
