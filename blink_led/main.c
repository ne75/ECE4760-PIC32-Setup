#include <stdint.h>         /* For uint32_t definition                        */
#include <stdbool.h>        /* For true/false definition                      */

#define _SUPPRESS_PLIB_WARNING 1
#include <plib.h>            /* Include to use PIC32 peripheral libraries     */

// Clock Configuration
#pragma config FNOSC = FRCPLL, POSCMOD = OFF
#pragma config FPLLIDIV = DIV_2, FPLLMUL = MUL_20 //40 MHz
#pragma config FPBDIV = DIV_1, FPLLODIV = DIV_2 // PB 40 MHz
#pragma config FWDTEN = OFF,  FSOSCEN = OFF, JTAGEN = OFF

#define SYS_FREQ     40000000
#define FCY          SYS_FREQ

void delay_ms(unsigned int msec) {
	unsigned int tWait, tStart;
		
    tWait=(SYS_FREQ/2000)*msec;
    tStart=ReadCoreTimer();
    while((ReadCoreTimer()-tStart)<tWait);		// wait for the time to pass

}

int32_t main(void) {

    /* TODO Add user clock/system configuration code if appropriate.  */
    SYSTEMConfig(SYS_FREQ, SYS_CFG_ALL); 
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
   
    mPORTASetPinsDigitalOut(BIT_0);
    
    while(1)
    {
        mPORTAToggleBits(BIT_0);
        delay_ms(100);
    }
}
