/* 
 * Nikita Ermoshkin (ne75)
 * Eric Dai (emd88)
 *
 * September 2017
 *
 */

#include <stdint.h>
#include <stdbool.h>       
#include <plib.h> 

// Clock Configuration
#pragma config FNOSC = FRCPLL, POSCMOD = OFF
#pragma config FPLLIDIV = DIV_2, FPLLMUL = MUL_20 //40 MHz
#pragma config FPBDIV = DIV_1, FPLLODIV = DIV_2 // PB 40 MHz
#pragma config FWDTEN = OFF,  FSOSCEN = OFF, JTAGEN = OFF

#define SYS_FREQ     40000000
#define FCY          SYS_FREQ

/*
 * Delay function taken from http://www.microchip.com/forums/m523604.aspx
 *
 */
void delay_ms(unsigned int msec) {
	unsigned int tWait, tStart;
		
    tWait=(SYS_FREQ/2000)*msec;
    tStart=ReadCoreTimer();
    while((ReadCoreTimer()-tStart)<tWait);

}

int32_t main(void) {

    SYSTEMConfig(SYS_FREQ, SYS_CFG_ALL); 
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
   
    mPORTASetPinsDigitalOut(BIT_0);
    
    while(1)
    {
        mPORTAToggleBits(BIT_0);
        delay_ms(1000);
    }
}
