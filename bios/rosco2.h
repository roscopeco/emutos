#ifndef ROSCO2_H
#define ROSCO2_H
#include "emutos.h"
void rosco2_ikbd_init(void);
UBYTE rosco2_ikbd_cinRdy(void);
UBYTE rosco2_ikbd_conin(UBYTE* isAscii);
void rosco2_ikbd_writeb(UBYTE byte);
UBYTE rosco2_ikbd_readb(WORD timeout);
#endif
