/*
 * screen.c - low-level screen routines
 *
 * Copyright (c) 2001-2011 The EmuTOS development team
 *
 * Authors:
 *  MAD   Martin Doering
 *  THH   Thomas Huth
 *  LVL   Laurent Vogel
 *  joy   Petr Stehlik
 *
 * This file is distributed under the GPL, version 2 or at your
 * option any later version.  See doc/license.txt for details.
 */

#include "config.h"  
#include "machine.h"
#include "screen.h"
#include "asm.h"
#include "tosvars.h"
#include "lineavars.h"
#include "nvram.h"
#include "kprint.h"
#include "font.h"
#include "vt52.h"

#define DBG_SCREEN 0

#define VIDEOBASE_ADDR_HI   0xffff8201L
#define VIDEOBASE_ADDR_MID  0xffff8203L
#define VIDEOBASE_ADDR_LOW  0xffff820dL

#define ST_SHIFTER          0xffff8260L
#define TT_SHIFTER          0xffff8262L
#define SPSHIFT             0xffff8266L

#define ST_PALETTE_REGS     0xffff8240L
#define FALCON_PALETTE_REGS 0xffff9800L

#define ST_VRAM_SIZE        32000UL

/* determine monitor type, ... */

/* Define palette */

static const WORD dflt_palette[] = {
    RGB_WHITE, RGB_RED, RGB_GREEN, RGB_YELLOW,
    RGB_BLUE, RGB_MAGENTA, RGB_CYAN, RGB_LTGRAY,
    RGB_GRAY, RGB_LTRED, RGB_LTGREEN, RGB_LTYELLOW,
    RGB_LTBLUE, RGB_LTMAGENTA, RGB_LTCYAN, RGB_BLACK
};

#if CONF_WITH_VIDEL
static const LONG videl_dflt_palette[] = {
    FRGB_WHITE, FRGB_RED, FRGB_GREEN, FRGB_YELLOW,
    FRGB_BLUE, FRGB_MAGENTA, FRGB_CYAN, FRGB_LTGRAY,
    FRGB_GRAY, FRGB_LTRED, FRGB_LTGREEN, FRGB_LTYELLOW,
    FRGB_LTBLUE, FRGB_LTMAGENTA, FRGB_LTCYAN, FRGB_BLACK
};

static LONG falcon_shadow_palette[256];   /* real Falcon does this */
#endif

#if CONF_WITH_VIDEL
typedef struct {
    LONG vmode;         /* video mode (-1 => end marker) */
    UWORD hht;          /* H hold timer */
    UWORD hbb;          /* H border begin */
    UWORD hbe;          /* H border end */
    UWORD hdb;          /* H display begin */
    UWORD hde;          /* H display end */
    UWORD hss;          /* H SS */
    UWORD vft;          /* V freq timer */
    UWORD vbb;          /* V border begin */
    UWORD vbe;          /* V border end */
    UWORD vdb;          /* V display begin */
    UWORD vde;          /* V display end */
    UWORD vss;          /* V SS */
    UWORD width;        /* scanline width */
    UWORD ctl;          /* video control */
} VMODE_ENTRY;

/*
 * a list of all(?) valid Falcon modes
 * note:
 *  . 256-colour and Truecolor modes are not currently supported by the VDI
 */
static const VMODE_ENTRY vmode_init_table[] = {
    /* the first entries are for VGA, since we expect to access them most frequently */
    { 0x0011, 0x0017, 0x0012, 0x0001, 0x020a, 0x0009, 0x0011, 0x0419, 0x03ff, 0x003f, 0x003f, 0x03ff, 0x0415, 0x0028, 0x0004 },
    { 0x0012, 0x00c6, 0x008d, 0x0015, 0x028a, 0x006b, 0x0096, 0x0419, 0x03ff, 0x003f, 0x003f, 0x03ff, 0x0415, 0x0050, 0x0004 },
    { 0x0013, 0x00c6, 0x008d, 0x0015, 0x029a, 0x007b, 0x0096, 0x0419, 0x03ff, 0x003f, 0x003f, 0x03ff, 0x0415, 0x00a0, 0x0004 },
    { 0x0014, 0x00c6, 0x008d, 0x0015, 0x02ac, 0x0091, 0x0096, 0x0419, 0x03ff, 0x003f, 0x003f, 0x03ff, 0x0415, 0x0140, 0x0004 },
    { 0x0018, 0x00c6, 0x008d, 0x0015, 0x0273, 0x0050, 0x0096, 0x0419, 0x03ff, 0x003f, 0x003f, 0x03ff, 0x0415, 0x0028, 0x0008 },
    { 0x0019, 0x0017, 0x0012, 0x0001, 0x020e, 0x000d, 0x0011, 0x0419, 0x03ff, 0x003f, 0x003f, 0x03ff, 0x0415, 0x0050, 0x0008 },
    { 0x001a, 0x00c6, 0x008d, 0x0015, 0x02a3, 0x007c, 0x0096, 0x0419, 0x03ff, 0x003f, 0x003f, 0x03ff, 0x0415, 0x00a0, 0x0008 },
    { 0x001b, 0x00c6, 0x008d, 0x0015, 0x02ab, 0x0084, 0x0096, 0x0419, 0x03ff, 0x003f, 0x003f, 0x03ff, 0x0415, 0x0140, 0x0008 },
    { 0x0098, 0x00c6, 0x008d, 0x0015, 0x0273, 0x0050, 0x0096, 0x0419, 0x03af, 0x008f, 0x008f, 0x03af, 0x0415, 0x0028, 0x0008 },
    { 0x0111, 0x0017, 0x0012, 0x0001, 0x020a, 0x0009, 0x0011, 0x0419, 0x03ff, 0x003f, 0x003f, 0x03ff, 0x0415, 0x0028, 0x0005 },
    { 0x0112, 0x00c6, 0x008d, 0x0015, 0x028a, 0x006b, 0x0096, 0x0419, 0x03ff, 0x003f, 0x003f, 0x03ff, 0x0415, 0x0050, 0x0005 },
    { 0x0113, 0x00c6, 0x008d, 0x0015, 0x029a, 0x007b, 0x0096, 0x0419, 0x03ff, 0x003f, 0x003f, 0x03ff, 0x0415, 0x00a0, 0x0005 },
    { 0x0114, 0x00c6, 0x008d, 0x0015, 0x02ac, 0x0091, 0x0096, 0x0419, 0x03ff, 0x003f, 0x003f, 0x03ff, 0x0415, 0x0140, 0x0005 },
    { 0x0118, 0x00c6, 0x008d, 0x0015, 0x0273, 0x0050, 0x0096, 0x0419, 0x03ff, 0x003f, 0x003f, 0x03ff, 0x0415, 0x0028, 0x0009 },
    { 0x0119, 0x0017, 0x0012, 0x0001, 0x020e, 0x000d, 0x0011, 0x0419, 0x03ff, 0x003f, 0x003f, 0x03ff, 0x0415, 0x0050, 0x0009 },
    { 0x011a, 0x00c6, 0x008d, 0x0015, 0x02a3, 0x007c, 0x0096, 0x0419, 0x03ff, 0x003f, 0x003f, 0x03ff, 0x0415, 0x00a0, 0x0009 },
    { 0x011b, 0x00c6, 0x008d, 0x0015, 0x02ab, 0x0084, 0x0096, 0x0419, 0x03ff, 0x003f, 0x003f, 0x03ff, 0x0415, 0x0140, 0x0009 },
    { 0x0192, 0x0017, 0x0012, 0x0001, 0x020e, 0x000d, 0x0011, 0x0419, 0x03af, 0x008f, 0x008f, 0x03af, 0x0415, 0x0050, 0x0005 },
    { 0x0199, 0x0017, 0x0012, 0x0001, 0x020e, 0x000d, 0x0011, 0x0419, 0x03af, 0x008f, 0x008f, 0x03af, 0x0415, 0x0050, 0x0009 },

    /* the remaining entries are for TV+NTSC, TV+PAL, TV+NTSC+overscan, TV+PAL+overscan */
    { 0x0001, 0x003e, 0x0030, 0x0008, 0x0239, 0x0012, 0x0034, 0x020d, 0x0201, 0x0016, 0x004d, 0x01dd, 0x0207, 0x0028, 0x0000 },
    { 0x0002, 0x00fe, 0x00c9, 0x0027, 0x000c, 0x006d, 0x00d8, 0x020d, 0x0201, 0x0016, 0x004d, 0x01dd, 0x0207, 0x0050, 0x0000 },
    { 0x0003, 0x00fe, 0x00c9, 0x0027, 0x001c, 0x007d, 0x00d8, 0x020d, 0x0201, 0x0016, 0x004d, 0x01dd, 0x0207, 0x00a0, 0x0000 },
    { 0x0004, 0x00fe, 0x00c9, 0x0027, 0x002e, 0x008f, 0x00d8, 0x020d, 0x0201, 0x0016, 0x004d, 0x01dd, 0x0207, 0x0140, 0x0000 },
    { 0x0008, 0x01ff, 0x0197, 0x0050, 0x03f0, 0x009f, 0x01b4, 0x020d, 0x0201, 0x0016, 0x004d, 0x01dd, 0x0207, 0x0028, 0x0004 },
    { 0x0009, 0x003e, 0x0030, 0x0008, 0x0002, 0x0020, 0x0034, 0x020d, 0x0201, 0x0016, 0x004d, 0x01dd, 0x0207, 0x0050, 0x0004 },
    { 0x000a, 0x01ff, 0x0197, 0x0050, 0x004d, 0x00fd, 0x01b4, 0x020d, 0x0201, 0x0016, 0x004d, 0x01dd, 0x0207, 0x00a0, 0x0004 },
    { 0x000b, 0x01ff, 0x0197, 0x0050, 0x005d, 0x010d, 0x01b4, 0x020d, 0x0201, 0x0016, 0x004d, 0x01dd, 0x0207, 0x0140, 0x0004 },
    { 0x0021, 0x003e, 0x0030, 0x0008, 0x0239, 0x0012, 0x0034, 0x0271, 0x0265, 0x002f, 0x007f, 0x020f, 0x026b, 0x0028, 0x0000 },
    { 0x0022, 0x00fe, 0x00cb, 0x0027, 0x000c, 0x006d, 0x00d8, 0x0271, 0x0265, 0x002f, 0x007f, 0x020f, 0x026b, 0x0050, 0x0000 },
    { 0x0023, 0x00fe, 0x00cb, 0x0027, 0x001c, 0x007d, 0x00d8, 0x0271, 0x0265, 0x002f, 0x007f, 0x020f, 0x026b, 0x00a0, 0x0000 },
    { 0x0024, 0x00fe, 0x00cb, 0x0027, 0x002e, 0x008f, 0x00d8, 0x0271, 0x0265, 0x002f, 0x007f, 0x020f, 0x026b, 0x0140, 0x0000 },
    { 0x0028, 0x01fe, 0x0199, 0x0050, 0x03ef, 0x00a0, 0x01b2, 0x0271, 0x0265, 0x002f, 0x007f, 0x020f, 0x026b, 0x0028, 0x0004 },
    { 0x0029, 0x003e, 0x0030, 0x0008, 0x0002, 0x0020, 0x0034, 0x0271, 0x0265, 0x002f, 0x007f, 0x020f, 0x026b, 0x0050, 0x0004 },
    { 0x002a, 0x01fe, 0x0199, 0x0050, 0x004d, 0x00fe, 0x01b2, 0x0271, 0x0265, 0x002f, 0x007f, 0x020f, 0x026b, 0x00a0, 0x0004 },
    { 0x002b, 0x01fe, 0x0199, 0x0050, 0x005d, 0x010e, 0x01b2, 0x0271, 0x0265, 0x002f, 0x007f, 0x020f, 0x026b, 0x0140, 0x0004 },
    { 0x0041, 0x003e, 0x0030, 0x0008, 0x0239, 0x0012, 0x0034, 0x020d, 0x0201, 0x0016, 0x0025, 0x0205, 0x0207, 0x0030, 0x0000 },
    { 0x0042, 0x00fe, 0x00c9, 0x0027, 0x000c, 0x006d, 0x00d8, 0x020d, 0x0201, 0x0016, 0x0025, 0x0205, 0x0207, 0x0060, 0x0000 },
    { 0x0043, 0x00fe, 0x00c9, 0x0027, 0x001c, 0x007d, 0x00d8, 0x020d, 0x0201, 0x0016, 0x0025, 0x0205, 0x0207, 0x00c0, 0x0000 },
    { 0x0044, 0x00fe, 0x00c9, 0x0027, 0x002e, 0x008f, 0x00d8, 0x020d, 0x0201, 0x0016, 0x0025, 0x0205, 0x0207, 0x0180, 0x0000 },
    { 0x0048, 0x01ff, 0x0197, 0x0050, 0x03f0, 0x009f, 0x01b4, 0x020d, 0x0201, 0x0016, 0x0025, 0x0205, 0x0207, 0x0030, 0x0004 },
    { 0x0049, 0x003e, 0x0030, 0x0008, 0x023b, 0x001c, 0x0034, 0x020d, 0x0201, 0x0016, 0x0025, 0x0205, 0x0207, 0x0060, 0x0004 },
    { 0x004a, 0x01ff, 0x0197, 0x0050, 0x004d, 0x00fd, 0x01b4, 0x020d, 0x0201, 0x0016, 0x0025, 0x0205, 0x0207, 0x00c0, 0x0004 },
    { 0x004b, 0x01ff, 0x0197, 0x0050, 0x005d, 0x010d, 0x01b4, 0x020d, 0x0201, 0x0016, 0x0025, 0x0205, 0x0207, 0x0180, 0x0004 },
    { 0x0061, 0x003e, 0x0030, 0x0008, 0x0239, 0x0012, 0x0034, 0x0271, 0x0265, 0x002f, 0x0057, 0x0237, 0x026b, 0x0030, 0x0000 },
    { 0x0062, 0x00fe, 0x00cb, 0x0027, 0x000c, 0x006d, 0x00d8, 0x0271, 0x0265, 0x002f, 0x0057, 0x0237, 0x026b, 0x0060, 0x0000 },
    { 0x0063, 0x00fe, 0x00cb, 0x0027, 0x001c, 0x007d, 0x00d8, 0x0271, 0x0265, 0x002f, 0x0057, 0x0237, 0x026b, 0x00c0, 0x0000 },
    { 0x0064, 0x00fe, 0x00cb, 0x0027, 0x002e, 0x008f, 0x00d8, 0x0271, 0x0265, 0x002f, 0x0057, 0x0237, 0x026b, 0x0180, 0x0000 },
    { 0x0068, 0x01fe, 0x0199, 0x0050, 0x03ef, 0x00a0, 0x01b2, 0x0271, 0x0265, 0x002f, 0x0057, 0x0237, 0x026b, 0x0030, 0x0004 },
    { 0x0069, 0x003e, 0x0030, 0x0008, 0x023b, 0x001c, 0x0034, 0x0271, 0x0265, 0x002f, 0x0057, 0x0237, 0x026b, 0x0060, 0x0004 },
    { 0x006a, 0x01fe, 0x0199, 0x0050, 0x004d, 0x00fe, 0x01b2, 0x0271, 0x0265, 0x002f, 0x0057, 0x0237, 0x026b, 0x00c0, 0x0004 },
    { 0x006b, 0x01fe, 0x0199, 0x0050, 0x005d, 0x010e, 0x01b2, 0x0271, 0x0265, 0x002f, 0x0057, 0x0237, 0x026b, 0x0180, 0x0004 },
    { 0x0088, 0x01ff, 0x0197, 0x0050, 0x03f0, 0x009f, 0x01b4, 0x020d, 0x0201, 0x0016, 0x004d, 0x01dd, 0x0207, 0x0028, 0x0004 },
    { 0x00a8, 0x01fe, 0x0199, 0x0050, 0x03ef, 0x00a0, 0x01b2, 0x0271, 0x0265, 0x002f, 0x007f, 0x020f, 0x026b, 0x0028, 0x0004 },
    { 0x00c8, 0x01ff, 0x0197, 0x0050, 0x03f0, 0x009f, 0x01b4, 0x020d, 0x0201, 0x0016, 0x0025, 0x0205, 0x0207, 0x0030, 0x0004 },
    { 0x00e8, 0x01fe, 0x0199, 0x0050, 0x03ef, 0x00a0, 0x01b2, 0x0271, 0x0265, 0x002f, 0x0057, 0x0237, 0x026b, 0x0030, 0x0004 },
    { 0x0101, 0x003e, 0x0030, 0x0008, 0x0239, 0x0012, 0x0034, 0x020c, 0x0201, 0x0016, 0x004c, 0x01dc, 0x0207, 0x0028, 0x0002 },
    { 0x0102, 0x00fe, 0x00c9, 0x0027, 0x000c, 0x006d, 0x00d8, 0x020c, 0x0201, 0x0016, 0x004c, 0x01dc, 0x0207, 0x0050, 0x0002 },
    { 0x0103, 0x00fe, 0x00c9, 0x0027, 0x001c, 0x007d, 0x00d8, 0x020c, 0x0201, 0x0016, 0x004c, 0x01dc, 0x0207, 0x00a0, 0x0002 },
    { 0x0104, 0x00fe, 0x00c9, 0x0027, 0x002e, 0x008f, 0x00d8, 0x020c, 0x0201, 0x0016, 0x004c, 0x01dc, 0x0207, 0x0140, 0x0002 },
    { 0x0108, 0x01ff, 0x0197, 0x0050, 0x03f0, 0x009f, 0x01b4, 0x020c, 0x0201, 0x0016, 0x004c, 0x01dc, 0x0207, 0x0028, 0x0006 },
    { 0x0109, 0x003e, 0x0030, 0x0008, 0x0002, 0x0020, 0x0034, 0x020c, 0x0201, 0x0016, 0x004c, 0x01dc, 0x0207, 0x0050, 0x0006 },
    { 0x010a, 0x01ff, 0x0197, 0x0050, 0x004d, 0x00fd, 0x01b4, 0x020c, 0x0201, 0x0016, 0x004c, 0x01dc, 0x0207, 0x00a0, 0x0006 },
    { 0x010b, 0x01ff, 0x0197, 0x0050, 0x005d, 0x010d, 0x01b4, 0x020c, 0x0201, 0x0016, 0x004c, 0x01dc, 0x0207, 0x0140, 0x0006 },
    { 0x0121, 0x003e, 0x0030, 0x0008, 0x0239, 0x0012, 0x0034, 0x0270, 0x0265, 0x002f, 0x007e, 0x020e, 0x026b, 0x0028, 0x0002 },
    { 0x0122, 0x00fe, 0x00cb, 0x0027, 0x000c, 0x006d, 0x00d8, 0x0270, 0x0265, 0x002f, 0x007e, 0x020e, 0x026b, 0x0050, 0x0002 },
    { 0x0123, 0x00fe, 0x00cb, 0x0027, 0x001c, 0x007d, 0x00d8, 0x0270, 0x0265, 0x002f, 0x007e, 0x020e, 0x026b, 0x00a0, 0x0002 },
    { 0x0124, 0x00fe, 0x00cb, 0x0027, 0x002e, 0x008f, 0x00d8, 0x0270, 0x0265, 0x002f, 0x007e, 0x020e, 0x026b, 0x0140, 0x0002 },
    { 0x0128, 0x01fe, 0x0199, 0x0050, 0x03ef, 0x00a0, 0x01b2, 0x0270, 0x0265, 0x002f, 0x007e, 0x020e, 0x026b, 0x0028, 0x0006 },
    { 0x0129, 0x003e, 0x0030, 0x0008, 0x0002, 0x0020, 0x0034, 0x0270, 0x0265, 0x002f, 0x007e, 0x020e, 0x026b, 0x0050, 0x0006 },
    { 0x012a, 0x01fe, 0x0199, 0x0050, 0x004d, 0x00fe, 0x01b2, 0x0270, 0x0265, 0x002f, 0x007e, 0x020e, 0x026b, 0x00a0, 0x0006 },
    { 0x012b, 0x01fe, 0x0199, 0x0050, 0x005d, 0x010e, 0x01b2, 0x0270, 0x0265, 0x002f, 0x007e, 0x020e, 0x026b, 0x0140, 0x0006 },
    { 0x0141, 0x003e, 0x0030, 0x0008, 0x0239, 0x0012, 0x0034, 0x020c, 0x0201, 0x0016, 0x0024, 0x0204, 0x0207, 0x0030, 0x0002 },
    { 0x0142, 0x00fe, 0x00c9, 0x0027, 0x000c, 0x006d, 0x00d8, 0x020c, 0x0201, 0x0016, 0x0024, 0x0204, 0x0207, 0x0060, 0x0002 },
    { 0x0143, 0x00fe, 0x00c9, 0x0027, 0x001c, 0x007d, 0x00d8, 0x020c, 0x0201, 0x0016, 0x0024, 0x0204, 0x0207, 0x00c0, 0x0002 },
    { 0x0144, 0x00fe, 0x00c9, 0x0027, 0x002e, 0x008f, 0x00d8, 0x020c, 0x0201, 0x0016, 0x0024, 0x0204, 0x0207, 0x0180, 0x0002 },
    { 0x0148, 0x01ff, 0x0197, 0x0050, 0x03f0, 0x009f, 0x01b4, 0x020c, 0x0201, 0x0016, 0x0024, 0x0204, 0x0207, 0x0030, 0x0006 },
    { 0x0149, 0x003e, 0x0030, 0x0008, 0x023b, 0x001c, 0x0034, 0x020c, 0x0201, 0x0016, 0x0024, 0x0204, 0x0207, 0x0060, 0x0006 },
    { 0x014a, 0x01ff, 0x0197, 0x0050, 0x004d, 0x00fd, 0x01b4, 0x020c, 0x0201, 0x0016, 0x0024, 0x0204, 0x0207, 0x00c0, 0x0006 },
    { 0x014b, 0x01ff, 0x0197, 0x0050, 0x005d, 0x010d, 0x01b4, 0x020c, 0x0201, 0x0016, 0x0024, 0x0204, 0x0207, 0x0180, 0x0006 },
    { 0x0161, 0x003e, 0x0030, 0x0008, 0x0239, 0x0012, 0x0034, 0x0270, 0x0265, 0x002f, 0x0056, 0x0236, 0x026b, 0x0030, 0x0002 },
    { 0x0162, 0x00fe, 0x00cb, 0x0027, 0x000c, 0x006d, 0x00d8, 0x0270, 0x0265, 0x002f, 0x0056, 0x0236, 0x026b, 0x0060, 0x0002 },
    { 0x0163, 0x00fe, 0x00cb, 0x0027, 0x001c, 0x007d, 0x00d8, 0x0270, 0x0265, 0x002f, 0x0056, 0x0236, 0x026b, 0x00c0, 0x0002 },
    { 0x0164, 0x00fe, 0x00cb, 0x0027, 0x002e, 0x008f, 0x00d8, 0x0270, 0x0265, 0x002f, 0x0056, 0x0236, 0x026b, 0x0180, 0x0002 },
    { 0x0168, 0x01fe, 0x0199, 0x0050, 0x03ef, 0x00a0, 0x01b2, 0x0270, 0x0265, 0x002f, 0x0056, 0x0236, 0x026b, 0x0030, 0x0006 },
    { 0x0169, 0x003e, 0x0030, 0x0008, 0x023b, 0x001c, 0x0034, 0x0270, 0x0265, 0x002f, 0x0056, 0x0236, 0x026b, 0x0060, 0x0006 },
    { 0x016a, 0x01fe, 0x0199, 0x0050, 0x004d, 0x00fe, 0x01b2, 0x0270, 0x0265, 0x002f, 0x0056, 0x0236, 0x026b, 0x00c0, 0x0006 },
    { 0x016b, 0x01fe, 0x0199, 0x0050, 0x005d, 0x010e, 0x01b2, 0x0270, 0x0265, 0x002f, 0x0056, 0x0236, 0x026b, 0x0180, 0x0006 },
    { 0x0182, 0x003e, 0x0032, 0x0009, 0x023f, 0x001c, 0x0034, 0x020d, 0x0201, 0x0016, 0x004d, 0x01dd, 0x0207, 0x0050, 0x0000 },
    { 0x0189, 0x003e, 0x0032, 0x0009, 0x023f, 0x001c, 0x0034, 0x020d, 0x0201, 0x0016, 0x004d, 0x01dd, 0x0207, 0x0050, 0x0004 },
    { 0x01a2, 0x003e, 0x0032, 0x0009, 0x023f, 0x001c, 0x0034, 0x0271, 0x0265, 0x002f, 0x006f, 0x01ff, 0x026b, 0x0050, 0x0000 },
    { 0x01a9, 0x003e, 0x0032, 0x0009, 0x023f, 0x001c, 0x0034, 0x0271, 0x0265, 0x002f, 0x006f, 0x01ff, 0x026b, 0x0050, 0x0004 },
    { 0x01c2, 0x003e, 0x0032, 0x0009, 0x023f, 0x001c, 0x0034, 0x020d, 0x0201, 0x0016, 0x004d, 0x01dd, 0x0207, 0x0050, 0x0000 },
    { 0x01c9, 0x003e, 0x0032, 0x0009, 0x023f, 0x001c, 0x0034, 0x020d, 0x0201, 0x0016, 0x004d, 0x01dd, 0x0207, 0x0060, 0x0004 },
    { 0x01e2, 0x003e, 0x0032, 0x0009, 0x023f, 0x001c, 0x0034, 0x0271, 0x0265, 0x002f, 0x006f, 0x01ff, 0x026b, 0x0050, 0x0000 },
    { 0x01e9, 0x003e, 0x0032, 0x0009, 0x023f, 0x001c, 0x0034, 0x0271, 0x0265, 0x002f, 0x006f, 0x01ff, 0x026b, 0x0060, 0x0004 },
	{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
#endif


/* calculate VRAM size for current video mode */

static unsigned long vram_size()
{
#if CONF_WITH_VIDEL
    if (has_videl) {
        return get_videl_width() / 8L * get_videl_height() * get_videl_bpp();
    }
    else
#endif
    return ST_VRAM_SIZE;
}


/* get monitor type (same encoding as VgetMonitor()) */
static WORD get_monitor_type()
{
#if CONF_WITH_VIDEL
    if (has_videl) {
        return vmontype();
    }
    else
#endif
    {
        volatile UBYTE *gpip = (UBYTE *)0xfffffa01;

        if (*gpip & 0x80)       /* colour monitor */
            return 1;

        return 0;               /* monochrome monitor */
    }
}


/* Set physical screen address */

static void setphys(LONG addr,int checkaddr)
{
    if (checkaddr) {
        if (addr > ((ULONG)phystop - vram_size())) {
            panic("VideoRAM covers ROM area!!\n");
        }
    }

    *(volatile UBYTE *) VIDEOBASE_ADDR_HI = ((ULONG) addr) >> 16;
    *(volatile UBYTE *) VIDEOBASE_ADDR_MID = ((ULONG) addr) >> 8;
#if CONF_WITH_VIDEL
    if (has_videl) {
        *(volatile UBYTE *) VIDEOBASE_ADDR_LOW = ((ULONG) addr);
    }
    else
#endif
#if CONF_WITH_STE_SHIFTER
    if (has_ste_shifter) {
        *(volatile UBYTE *) VIDEOBASE_ADDR_LOW = ((ULONG) addr);
    }
#endif
}


/*
 * In the original TOS there used to be an early screen init, 
 * before memory configuration. This is not used here, and all is
 * done at the same time from C.
 */

void screen_init(void)
{
    volatile BYTE *rez_reg = (BYTE *) ST_SHIFTER;
    volatile WORD *col_regs = (WORD *) ST_PALETTE_REGS;
#if CONF_WITH_VIDEL
    volatile LONG *fcol_regs = (LONG *) FALCON_PALETTE_REGS;
    UWORD boot_resolution;
#endif
    WORD monitor_type, mask, sync_mode;
    WORD rez = 0;   /* avoid 'may be uninitialized' warning */
    WORD i;
    ULONG screen_start;

/*
 * first, see what we're connected to, and set the
 * resolution / video mode appropriately
 */
    monitor_type = get_monitor_type();

#if CONF_WITH_VIDEL
    if (has_videl) {
        int ret = 1;

        /* reset VIDEL on boot-up */
        /* first set the physbase to a safe memory */
        setphys(0x10000L,0);

#if CONF_WITH_NVRAM && !defined(MACHINE_FIREBEE)
        /* get boot resolution from NVRAM */
        ret = nvmaccess(0, 14, 2, (PTR)&boot_resolution);
#endif // CONF_WITH_NVRAM
        if (ret != 0)
        {
            boot_resolution = FALCON_DEFAULT_BOOT; /* invalid nvram, default is TV/NTSC */
        }
        switch(monitor_type) {                  /* override if necessary */
        case 0:     /* monochrome */
            boot_resolution = FALCON_ST_HIGH;
            break;
        case 1:     /* colour */
            boot_resolution = FALCON_ST_MEDIUM;
            break;
        case 2:     /* VGA */
            boot_resolution |= VIDEL_VGA;
            break;
        case 3:     /* TV */
            boot_resolution &= ~VIDEL_VGA;
            break;
        }
        vsetmode(boot_resolution);
        rez = 3;        /* fake value indicates Falcon/Videl */
        mask = 0x0fff;  /* STe-compatible palette */
    }
    else
#endif // CONF_WITH_VIDEL
#if CONF_WITH_STE_SHIFTER
    if (has_ste_shifter) {
        rez = monitor_type?ST_MEDIUM:ST_HIGH;
        *rez_reg = rez;
        mask = 0x0fff;  /* STe-compatible palette */
    }
    else
#endif
    {
        rez = monitor_type?ST_MEDIUM:ST_HIGH;
        *rez_reg = rez;
        mask = 0x0777;  /* ST-compatible palette */
    }

#if CONF_WITH_VIDEL
    if (rez == 3) {     /* detected a Falcon */
        sync_mode = (boot_resolution&VIDEL_PAL)?0x02:0x00;
    }
    else
#endif
    {
        sync_mode = (os_pal&0x01)?0x02:0x00;
    }
    *(volatile BYTE *) 0xffff820a = sync_mode;

/*
 * next, set up the palette(s)
 */
    for (i = 0; i < 16; i++) {
        col_regs[i] = dflt_palette[i] & mask;
    }

#if CONF_WITH_VIDEL
    if (has_videl) {
        for(i = 0; i < 256; i++) {
            fcol_regs[i] = videl_dflt_palette[i%16]; /* hackish way of getting all 256 colors from first 16 - incorrect, FIXME */
        }
        switch(boot_resolution&VIDEL_BPPMASK) {
        case VIDEL_1BPP:        /* 2-colour mode */
            fcol_regs[1] = fcol_regs[15];
            col_regs[1] = col_regs[15];
            break;
        case VIDEL_2BPP:        /* 4-colour mode */
            fcol_regs[3] = fcol_regs[15];
            col_regs[3] = col_regs[15];
            break;
        }
    }
    else
#endif
    {
        
    }
    sshiftmod = rez;

    if (rez == ST_MEDIUM) {
        col_regs[3] = col_regs[15];
    }
    else if (rez == ST_HIGH) {
        col_regs[1] = col_regs[15];
    }

    /* videoram is placed just below the phystop */
    screen_start = (ULONG)phystop - vram_size();
    /* round down to 256 byte boundary */
    screen_start &= 0x00ffff00;
    /* Original TOS leaves a gap of 768 bytes between screen ram and phys_top...
     * ... we normally don't need that, but some old software relies on that fact,
     * so we use this gap, too. */
#if CONF_WITH_VIDEL
    if (has_videl)
        ;
    else
#endif
    {
        screen_start -= 0x300;
    }
    /* set new v_bas_ad */
    v_bas_ad = (UBYTE *)screen_start;
    /* correct physical address */
    setphys(screen_start,1);
}


/* xbios routines */

LONG physbase(void)
{
    LONG addr;

    addr = *(volatile UBYTE *) VIDEOBASE_ADDR_HI;
    addr <<= 8;
    addr += *(volatile UBYTE *) VIDEOBASE_ADDR_MID;
    addr <<= 8;
#if CONF_WITH_VIDEL
    if (has_videl) {
        addr += *(volatile UBYTE *) VIDEOBASE_ADDR_LOW;
    }
    else
#endif
#if CONF_WITH_STE_SHIFTER
    if (has_ste_shifter) {
        addr += *(volatile UBYTE *) VIDEOBASE_ADDR_LOW;
    }
#endif

    return (addr);
}

LONG logbase(void)
{
    return ((ULONG) v_bas_ad);
}

WORD getrez(void)
{
    UBYTE rez;

#if CONF_WITH_VIDEL
    if (has_videl) {
        /* Get the video mode for Falcon-hardware */
        WORD vmode = vsetmode(-1);
        if (vmode & VIDEL_COMPAT) {
            switch(vmode&VIDEL_BPPMASK) {
            case VIDEL_1BPP:
                rez = 2;
                break;
            case VIDEL_2BPP:
                rez = 1;
                break;
            case VIDEL_4BPP:
                rez = 0;
                break;
            default:
                kprintf("Problem - unsupported video mode\n");
                rez = 0;
            }
        } else
            rez = 2;
    }
    else
#endif
#if CONF_WITH_TT_SHIFTER
    if (has_tt_shifter) {
        /* Get the video mode for TT-hardware */
        rez = *(volatile UBYTE *)TT_SHIFTER & 0x07;
    }
    else
#endif
    {
        rez = *(volatile UBYTE *)ST_SHIFTER & 0x03;
    }

    return rez;
}


void setscreen(LONG logLoc, LONG physLoc, WORD rez, WORD videlmode)
{
    if (logLoc >= 0) {
        v_bas_ad = (UBYTE *) logLoc;
    }
    if (physLoc >= 0) {
        setphys(physLoc,1);
    }
    if (rez >= 0 && rez < 8) {
#if CONF_WITH_VIDEL
        if (has_videl) {
            if (rez == 3) {
                vsetmode(videlmode);
                sshiftmod = rez;
            } else if (rez < 3) {   /* ST compatible resolution */
                *(volatile UWORD *)SPSHIFT = 0;
                *(volatile UBYTE *)ST_SHIFTER = sshiftmod = rez;
            }
        }
        else
#endif
#if CONF_WITH_TT_SHIFTER
        if (has_tt_shifter) {
            if ((rez != 3) && (rez != 5))
                *(volatile UBYTE *)TT_SHIFTER = sshiftmod = rez;
        }
        else
#endif
        if (rez < 3) {      /* ST resolution */
            *(volatile UBYTE *)ST_SHIFTER = sshiftmod = rez;
        }

        /* Re-initialize line-a, VT52 etc: */
        linea_init();
        font_set_default();
        vt52_init();
    }
}

void setpalette(LONG palettePtr)
{
#if DBG_SCREEN
    int i, max;
    WORD *p = (WORD *)palettePtr;
    max = getrez() == 0 ? 15 : getrez() == 1 ? 3 : 1;
    kprintf("Setpalette(");
    for(i = 0 ; i <= max ; i++) {
        kprintf("%03x", p[i]);
        if(i < 15) kprintf(" ");
    }
    kprintf(")\n");
#endif
    /* next VBL will do this */
    colorptr = (WORD *) palettePtr;
}

WORD setcolor(WORD colorNum, WORD color)
{
    WORD oldcolor;
    WORD mask;
    volatile WORD *palette = (WORD *) ST_PALETTE_REGS;

#if DBG_SCREEN
    kprintf("Setcolor(0x%04x, 0x%04x)\n", colorNum, color);
#endif

    colorNum &= 0x000f;         /* just like real TOS */

#if CONF_WITH_VIDEL
    if (has_videl) {
        mask = 0xfff;
    } else
#endif
#if CONF_WITH_STE_SHIFTER
    if (has_ste_shifter) {
        mask = 0xfff;
    } else
#endif
    {
        mask = 0x777;
    }

    oldcolor = palette[colorNum] & mask;
    if (color == -1)
        return oldcolor;

    palette[colorNum] = color;          /* update ST(e)-compatible palette */
    return oldcolor;
}


void vsync(void)
{
    WORD old_sr;
    LONG a;

    old_sr = set_sr(0x2300);    /* allow VBL interrupt */
    a = frclock;
    while (frclock == a) {
#if USE_STOP_INSN_TO_FREE_HOST_CPU
        stop2300();
#else
        ;
#endif
    }
    set_sr(old_sr);
}


#if CONF_WITH_TT_SHIFTER

/*
 * TT shifter functions
 */

/*
 * Set TT shifter mode
 */
WORD esetshift(WORD mode)
{
    volatile WORD *resreg = (WORD *)TT_SHIFTER;
    WORD oldmode;

    if (!has_tt_shifter)
        return -32;

    oldmode = *resreg;
    *resreg = mode;

    return oldmode;
}


/*
 * Get TT shifter mode
 */
WORD egetshift(void)
{
    if (!has_tt_shifter)
        return -32;

    return *(volatile WORD *)TT_SHIFTER;
}

#endif /* CONF_WITH_TT_SHIFTER */


#if CONF_WITH_VIDEL

/*
 * functions for VIDEL programming
 */

UWORD get_videl_bpp(void)
{
    UWORD f_shift = *(volatile UWORD *)SPSHIFT;
    UBYTE st_shift = *(volatile UBYTE *)ST_SHIFTER;
    /* to get bpp, we must examine f_shift and st_shift.
     * f_shift is valid if any of bits no. 10, 8 or 4
     * is set. Priority in f_shift is: 10 ">" 8 ">" 4, i.e.
     * if bit 10 set then bit 8 and bit 4 don't care...
     * If all these bits are 0 get display depth from st_shift
     * (as for ST and STE)
     */
    int bits_per_pixel = 1;
    if (f_shift & 0x400)         /* 2 colors */
        bits_per_pixel = 1;
    else if (f_shift & 0x100)    /* hicolor */
        bits_per_pixel = 16;
    else if (f_shift & 0x010)    /* 8 bitplanes */
        bits_per_pixel = 8;
    else if (st_shift == 0)
        bits_per_pixel = 4;
    else if (st_shift == 0x1)
        bits_per_pixel = 2;
    else /* if (st_shift == 0x2) */
        bits_per_pixel = 1;

    return bits_per_pixel;
}

UWORD get_videl_width(void)
{
    return (*(volatile UWORD *)0xffff8210) * 16 / get_videl_bpp();
}

UWORD get_videl_height(void)
{
    UWORD vdb = *(volatile UWORD *)0xffff82a8;
    UWORD vde = *(volatile UWORD *)0xffff82aa;
    UWORD vmode = *(volatile UWORD *)0xffff82c2;

    /* visible y resolution:
     * Graphics display starts at line VDB and ends at line
     * VDE. If interlace mode off unit of VC-registers is
     * half lines, else lines.
     */
    UWORD yres = vde - vdb;
    if (!(vmode & 0x02))        /* interlace */
        yres >>= 1;
    if (vmode & 0x01)           /* double */
        yres >>= 1;

    return yres;
}


/*
 * lookup videl initialisation data for specified mode
 * returns NULL if mode is invalid
 */
static const VMODE_ENTRY *lookup_videl_mode(WORD mode)
{
    const VMODE_ENTRY *p;

    for (p = vmode_init_table; p->vmode >= 0; p++)
        if (p->vmode == mode)
            return p;

    return NULL;
}


/*
 * this routine can set VIDEL to 1,2,4 or 8 bitplanes mode on VGA
 */
static int set_videl_vga(WORD mode)
{
    volatile char *videlregs = (char *)0xffff8200;
#define videlword(n) (*(volatile UWORD *)(videlregs+(n)))
    const VMODE_ENTRY *p;

    p = lookup_videl_mode(mode);        /* validate mode */
    if (!p)
        return -1;

    videlregs[0x0a] = (mode&0x0020) ? 2 : 0;    /* video sync */

    videlword(0x82) = p->hht;           /* H hold timer */
    videlword(0x84) = p->hbb;           /* H border begin */
    videlword(0x86) = p->hbe;           /* H border end */
    videlword(0x88) = p->hdb;           /* H display begin */
    videlword(0x8a) = p->hde;           /* H display end */
    videlword(0x8c) = p->hss;           /* H SS */

    videlword(0xa2) = p->vft;           /* V freq timer */
    videlword(0xa4) = p->vbb;           /* V border begin */
    videlword(0xa6) = p->vbe;           /* V border end */
    videlword(0xa8) = p->vdb;           /* V display begin */
    videlword(0xaa) = p->vde;           /* V display end */
    videlword(0xac) = p->vss;           /* V SS */

    videlword(0x0e) = 0x0000;           /* offset */
    videlword(0x10) = p->width;         /* scanline width */

    videlword(0xc2) = p->ctl;           /* video control */

    if (mode&0x0010)
        videlword(0xc0) = 0x0186;       /* for VGA */
    else if ((mode&0x0180) == 0x180)
        videlword(0xc0) = 0x0081;       /* for ST low/medium compatibility */
    else videlword(0xc0) = 0x0181;

    switch(mode&0x07) {                 /* set SPSHIFT / ST shift */
    case 0:                                 /* 1 bpp (mono) */
        videlword(0x66) = 0x0400;
        break;
    case 1:                                 /* 2 bpp (4 colours) */
        videlword(0x66) = 0x0000;
        videlregs[0x60] = 0x01;
        break;
    case 2:                                 /* 4 bpp (16 colours) */
        videlword(0x66) = 0x0000;
        videlregs[0x60] = 0x00;
        break;
    case 3:                                 /* 8 bpp (256 colours) */
        videlword(0x66) = 0x0010;
        videlregs[0x60] = 0x00;
        break;
    case 4:                                 /* 16 bpp (Truecolor) */
        videlword(0x66) = 0x0100;
        videlregs[0x60] = 0x00;
        break;
    }

    return 0;
}


/*
 * Set Falcon video mode
 */
WORD vsetmode(WORD mode)
{
    static WORD oldmode;
    WORD ret;

    if (!has_videl)
        return -32;

    if (mode == -1)
        return oldmode;

#if DBG_SCREEN
    kprintf("vsetmode(0x%04x)\n", mode);
#endif

    if (set_videl_vga(mode) < 0)    /* invalid mode */
        return oldmode;

    ret = oldmode;
    oldmode = mode;

    return ret;
}

/*
 * Get Videl monitor type
 */
WORD vmontype(void)
{
    if (!has_videl)
        return -32;

    return ((*(volatile UBYTE *)0xffff8006) >> 6) & 3;
}

/*
 * get video ram size according to mode
 */
LONG vgetsize(WORD mode)
{
    const VMODE_ENTRY *p;
    int height;

    if (!has_videl)
        return -32;

    p = lookup_videl_mode(mode);
    if (!p)                     /* invalid mode, */
        return 32000L;          /* so make something up */

    height = p->vde - p->vdb;
    if (!(p->ctl&0x02))
        height >>= 1;
    if (p->ctl&0x01)
        height >>= 1;

    return (LONG)p->width * 2 * height;
}

/*
 * set palette registers
 */
void vsetrgb(WORD index,WORD count,LONG *rgb)
{
    volatile LONG *colour;
    LONG *shadow;
    union {
		LONG l;
        UBYTE b[4];
    } u;
    WORD limit;

    if (!has_videl)
        return;

    if ((index < 0) || (count <= 0))
        return;

    limit = (get_videl_bpp()<=4) ? 16 : 256;
    if ((index+count) > limit)
        return;

    colour = (LONG *)FALCON_PALETTE_REGS + index;
    shadow = falcon_shadow_palette + index;
    while(count--) {
        u.l = *rgb++;
        *shadow++ = u.l;
        u.b[0] = u.b[1];                 /* shift R & G */
        u.b[1] = u.b[2];
        *colour++ = u.l & 0xfcfc00fcL;   /* eliminate unused bits */
    }
}

/*
 * get palette registers
 */
void vgetrgb(WORD index,WORD count,LONG *rgb)
{
    LONG *shadow;
    WORD limit;

    if (!has_videl)
        return;

    if ((index < 0) || (count <= 0))
        return;

    limit = (get_videl_bpp()<=4) ? 16 : 256;
    if ((index+count) > limit)
        return;

    shadow = falcon_shadow_palette + index;
    while(count--)
        *rgb++ = *shadow++;      /* just what was set */
}

#endif /* CONF_WITH_VIDEL */
