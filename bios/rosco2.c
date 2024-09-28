#include "rosco2.h"
#include "duart68681.h"
#include "serport.h"
#include "kprint.h"
#include "delay.h"
#include "asm.h"

#define CMD_LED_POWRED      0x1
#define CMD_LED_POWGRN      0x2
#define CMD_LED_POWBLU      0x3
#define CMD_LED_DISK        0x5
#define CMD_MODE_SET        0x10
#define CMD_MOUSE_DETECT    0x20
#define CMD_MOUSE_STRM_ON   0x21

static void duart_out(UBYTE byte){
	while(!(read_duart(DUART_SRB) & DUART_SR_TXRDY)){}
	write_duart(DUART_THRB, byte);
}

void rosco2_ikbd_init(void){
#ifndef DANODUS_KEYBOARD
    duart_out(CMD_LED_POWRED);
    duart_out(0xff);
    duart_out(CMD_LED_POWGRN);
    duart_out(0x2);
    duart_out(CMD_LED_POWBLU);
    duart_out(0xcf);
    duart_out(CMD_LED_DISK);
    duart_out(0xff);
    duart_out(CMD_MODE_SET);
    duart_out(0x0);
    duart_out(CMD_MOUSE_DETECT);
    duart_out(CMD_MOUSE_STRM_ON);
#endif

	return;
}

// 0 no -1 yes
UBYTE rosco2_ikbd_cinRdy(void){
	return bconstatDUARTB();
}

void rosco2_ikbd_writeb(UBYTE byte){
	duart_out(byte);
} 

UBYTE rosco2_ikbd_readb(WORD timeout){
	WORD i;
	for (i = 0; i < timeout; i++)
    	{
        	if (rosco2_ikbd_cinRdy())
            		return bconinDUARTB();

        	delay_loop(loopcount_1_msec);
    	}
	return 0;
}
