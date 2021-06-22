#include "firebtn.h"

#define FIRE0 0x01
#define FIRE1 0x02

#define PORTE 0x10

void PortE_Init(void) {
    volatile unsigned long delay;
    SYSCTL_RCGC2_R |= PORTE;     // 1) activate clock for Port F
    delay = SYSCTL_RCGC2_R;           // allow time for clock to start
    GPIO_PORTE_AMSEL_R = 0x00;        // 3) disable analog on PF
    GPIO_PORTE_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
    GPIO_PORTE_DIR_R = 0x00;          // 5)
    GPIO_PORTE_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
    GPIO_PORTE_PUR_R = 0x00;
    GPIO_PORTE_DEN_R = 0x1F;
}

void Fire_Init(void) {
    PortE_Init();
}

int Fire_Pushed(void) {
    return (GPIO_PORTE_DATA_R & (FIRE0|FIRE1)) != 0;
}

int TwoFire_Pushed(void) {
    return (GPIO_PORTE_DATA_R & (FIRE0|FIRE1)) == (FIRE0|FIRE1);
}
