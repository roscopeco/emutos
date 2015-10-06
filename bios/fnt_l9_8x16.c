/*
 * fnt_l9_8x16.c - a font in standard format
 *
 * Copyright (c) 2015 The EmuTOS development team
 *
 * Automatically generated by fntconv.c
 *
 * This file is distributed under the GPL, version 2 or at your
 * option any later version.  See doc/license.txt for details.
 */

#include "config.h"
#include "portab.h"
#include "font.h"

static const UWORD off_table[] =
{
    0x0000, 0x0008, 0x0010, 0x0018, 0x0020, 0x0028, 0x0030, 0x0038,
    0x0040, 0x0048, 0x0050, 0x0058, 0x0060, 0x0068, 0x0070, 0x0078,
    0x0080, 0x0088, 0x0090, 0x0098, 0x00a0, 0x00a8, 0x00b0, 0x00b8,
    0x00c0, 0x00c8, 0x00d0, 0x00d8, 0x00e0, 0x00e8, 0x00f0, 0x00f8,
    0x0100, 0x0108, 0x0110, 0x0118, 0x0120, 0x0128, 0x0130, 0x0138,
    0x0140, 0x0148, 0x0150, 0x0158, 0x0160, 0x0168, 0x0170, 0x0178,
    0x0180, 0x0188, 0x0190, 0x0198, 0x01a0, 0x01a8, 0x01b0, 0x01b8,
    0x01c0, 0x01c8, 0x01d0, 0x01d8, 0x01e0, 0x01e8, 0x01f0, 0x01f8,
    0x0200, 0x0208, 0x0210, 0x0218, 0x0220, 0x0228, 0x0230, 0x0238,
    0x0240, 0x0248, 0x0250, 0x0258, 0x0260, 0x0268, 0x0270, 0x0278,
    0x0280, 0x0288, 0x0290, 0x0298, 0x02a0, 0x02a8, 0x02b0, 0x02b8,
    0x02c0, 0x02c8, 0x02d0, 0x02d8, 0x02e0, 0x02e8, 0x02f0, 0x02f8,
    0x0300, 0x0308, 0x0310, 0x0318, 0x0320, 0x0328, 0x0330, 0x0338,
    0x0340, 0x0348, 0x0350, 0x0358, 0x0360, 0x0368, 0x0370, 0x0378,
    0x0380, 0x0388, 0x0390, 0x0398, 0x03a0, 0x03a8, 0x03b0, 0x03b8,
    0x03c0, 0x03c8, 0x03d0, 0x03d8, 0x03e0, 0x03e8, 0x03f0, 0x03f8,
    0x0400, 0x0408, 0x0410, 0x0418, 0x0420, 0x0428, 0x0430, 0x0438,
    0x0440, 0x0448, 0x0450, 0x0458, 0x0460, 0x0468, 0x0470, 0x0478,
    0x0480, 0x0488, 0x0490, 0x0498, 0x04a0, 0x04a8, 0x04b0, 0x04b8,
    0x04c0, 0x04c8, 0x04d0, 0x04d8, 0x04e0, 0x04e8, 0x04f0, 0x04f8,
    0x0500, 0x0508, 0x0510, 0x0518, 0x0520, 0x0528, 0x0530, 0x0538,
    0x0540, 0x0548, 0x0550, 0x0558, 0x0560, 0x0568, 0x0570, 0x0578,
    0x0580, 0x0588, 0x0590, 0x0598, 0x05a0, 0x05a8, 0x05b0, 0x05b8,
    0x05c0, 0x05c8, 0x05d0, 0x05d8, 0x05e0, 0x05e8, 0x05f0, 0x05f8,
    0x0600, 0x0608, 0x0610, 0x0618, 0x0620, 0x0628, 0x0630, 0x0638,
    0x0640, 0x0648, 0x0650, 0x0658, 0x0660, 0x0668, 0x0670, 0x0678,
    0x0680, 0x0688, 0x0690, 0x0698, 0x06a0, 0x06a8, 0x06b0, 0x06b8,
    0x06c0, 0x06c8, 0x06d0, 0x06d8, 0x06e0, 0x06e8, 0x06f0, 0x06f8,
    0x0700, 0x0708, 0x0710, 0x0718, 0x0720, 0x0728, 0x0730, 0x0738,
    0x0740, 0x0748, 0x0750, 0x0758, 0x0760, 0x0768, 0x0770, 0x0778,
    0x0780, 0x0788, 0x0790, 0x0798, 0x07a0, 0x07a8, 0x07b0, 0x07b8,
    0x07c0, 0x07c8, 0x07d0, 0x07d8, 0x07e0, 0x07e8, 0x07f0, 0x07f8,
    0x0800,
};

static const UWORD dat_table[] =
{
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1104,
    0x0000, 0x0000, 0x1800, 0x3800, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x4000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x003c,
    0x0600, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x6600, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x6600, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x6006, 0x1832, 0x003c, 0x0000, 0x6006, 0x1800, 0x6006, 0x1800,
    0x0032, 0x6006, 0x1832, 0x0000, 0x0060, 0x0618, 0x0006, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x05a0,
    0x7c00, 0x7c7c, 0x007c, 0x7c7c, 0x7c7c, 0x0000, 0x0000, 0x0b28,
    0x0000, 0x0000, 0x1800, 0x7c00, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1000,
    0x6000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x000e, 0x18e0, 0x0000,
    0x0000, 0x0618, 0x0060, 0x1c00, 0x1800, 0x6000, 0x1860, 0x6666,
    0x0c00, 0x3e18, 0x0060, 0x1860, 0x0066, 0x6600, 0x0e00, 0x0000,
    0x0600, 0x000e, 0x0000, 0x3c00, 0x0000, 0x0000, 0x0000, 0x00fe,
    0x3800, 0x0000, 0x3c00, 0x0000, 0x0000, 0x0000, 0x0000, 0x6600,
    0x300c, 0x3c7a, 0x6666, 0x3e00, 0x300c, 0x3c66, 0x300c, 0x3c66,
    0x007a, 0x300c, 0x3c7a, 0x6600, 0x0130, 0x0c3c, 0x660c, 0x0000,
    0x6006, 0x1832, 0x001c, 0x0000, 0x6006, 0x1800, 0x6006, 0x1800,
    0x0032, 0x6006, 0x1832, 0x0000, 0x0060, 0x0618, 0x0006, 0x0000,
    0x0000, 0x0030, 0x0c7c, 0xfeee, 0x0100, 0x0008, 0x7838, 0x05a0,
    0xba02, 0x3a3a, 0x82b8, 0xb8ba, 0xbaba, 0x0078, 0x0000, 0x0dd8,
    0x0018, 0x6666, 0x3e66, 0x6c18, 0x0660, 0x6600, 0x0000, 0x0006,
    0x3c18, 0x3c7e, 0x0c7e, 0x1c7e, 0x3c3c, 0x0000, 0x0000, 0x003c,
    0x3818, 0x7c3c, 0x787e, 0x7e3e, 0x667e, 0x06cc, 0x60c6, 0x663c,
    0x7c3c, 0xf83e, 0x7e66, 0x66c6, 0x6666, 0x7e1e, 0x6078, 0x1000,
    0x7000, 0x6000, 0x0600, 0x0e00, 0x6018, 0x0cc0, 0x3800, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0018, 0x1830, 0x0000,
    0x3c66, 0x0c3c, 0x6630, 0x3600, 0x3c66, 0x3066, 0x3c30, 0x663c,
    0x1800, 0x7e3c, 0x6630, 0x3c30, 0x6666, 0x6618, 0x1e66, 0x180e,
    0x0c00, 0x181e, 0x1c66, 0x181c, 0x667c, 0x0000, 0x0000, 0x7cfe,
    0x6c00, 0x3078, 0x1800, 0x7a00, 0x6618, 0x3c00, 0x7e00, 0x6618,
    0x1818, 0x664c, 0x663c, 0x7e3c, 0x1818, 0x6666, 0x1818, 0x6666,
    0x784c, 0x1818, 0x664c, 0x6600, 0x3d18, 0x1866, 0x6618, 0x6018,
    0x300c, 0x3c7a, 0x6636, 0x0000, 0x300c, 0x3c66, 0x300c, 0x3c66,
    0x667a, 0x300c, 0x3c7a, 0x6600, 0x0030, 0x0c3c, 0x660c, 0x0066,
    0x0018, 0x3c38, 0x1c38, 0xfec6, 0x013c, 0x000e, 0x4040, 0x05a0,
    0xc606, 0x0606, 0xc6c0, 0xc0c6, 0xc6c6, 0x0040, 0x0000, 0x0628,
    0x0018, 0x6666, 0x7e66, 0x6c18, 0x0c30, 0x6618, 0x0000, 0x0006,
    0x7e18, 0x7e7e, 0x0c7e, 0x3c7e, 0x7e7e, 0x0000, 0x0e00, 0xe07e,
    0x7c3c, 0x7e7e, 0x7c7e, 0x7e7e, 0x667e, 0x06cc, 0x60c6, 0x667e,
    0x7e7e, 0xfc7e, 0x7e66, 0x66c6, 0x6666, 0x7e1e, 0x6078, 0x3800,
    0x3800, 0x6000, 0x0600, 0x1e00, 0x6018, 0x0cc0, 0x3800, 0x0000,
    0x0000, 0x0000, 0x1800, 0x0000, 0x0000, 0x0018, 0x1830, 0x0000,
    0x7e66, 0x1866, 0x6618, 0x1c00, 0x6666, 0x1866, 0x6618, 0x1818,
    0x7e00, 0xf866, 0x6618, 0x6618, 0x6600, 0x0018, 0x3866, 0x3c1e,
    0x1818, 0x1838, 0x3e66, 0x3e36, 0x3cc6, 0x0000, 0x0000, 0xc600,
    0x4418, 0x4818, 0x7e00, 0xca00, 0x3c78, 0x6600, 0xfe00, 0x0018,
    0x0000, 0x0000, 0x1818, 0xf87e, 0x7e7e, 0x0000, 0x7e7e, 0x0000,
    0x7c00, 0x0000, 0x0000, 0x0000, 0x7e00, 0x0000, 0x0000, 0x603c,
    0x1818, 0x664c, 0x661c, 0x0000, 0x1818, 0x6666, 0x1818, 0x6666,
    0x184c, 0x1818, 0x664c, 0x6618, 0x0018, 0x1866, 0x6618, 0x6066,
    0x003c, 0x242c, 0x34ba, 0xfed6, 0x0366, 0x180f, 0x7040, 0x05a0,
    0xc606, 0x0606, 0xc6c0, 0xc0c6, 0xc6c6, 0x0070, 0x0000, 0x07d0,
    0x0018, 0x66ff, 0x606c, 0x3818, 0x1c38, 0x3c18, 0x0000, 0x0006,
    0x6638, 0x660c, 0x1c60, 0x7006, 0x6666, 0x1818, 0x1c7e, 0x7066,
    0xe67e, 0x6666, 0x6e60, 0x6060, 0x6618, 0x06d8, 0x60ee, 0x6666,
    0x6666, 0xcc60, 0x1866, 0x66c6, 0x6666, 0x0c18, 0x6018, 0x3800,
    0x1c00, 0x6000, 0x0600, 0x1800, 0x6000, 0x00c0, 0x1800, 0x0000,
    0x0000, 0x0000, 0x1800, 0x0000, 0x0000, 0x0018, 0x1830, 0x0000,
    0x6600, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3c3c,
    0x7e00, 0xd800, 0x0000, 0x0000, 0x003c, 0x663c, 0x3066, 0x6618,
    0x0018, 0x3c30, 0x6666, 0x7e32, 0x1882, 0x3c00, 0x0000, 0x8200,
    0x6c18, 0x1830, 0x7e00, 0xca00, 0x1818, 0x6600, 0xd800, 0x6600,
    0x3c3c, 0x3c3c, 0x3c3c, 0xd866, 0x7e7e, 0x7e7e, 0x7e7e, 0x7e7e,
    0x6e66, 0x3c3c, 0x3c3c, 0x3cc3, 0x6666, 0x6666, 0x6666, 0x6066,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x6c00, 0x0000, 0x0000, 0x0018, 0x0100, 0x0000, 0x0000, 0x6000,
    0x0066, 0x24e6, 0x6792, 0xfc92, 0x03c3, 0x3c09, 0x4040, 0x0db0,
    0xc606, 0x0606, 0xc6c0, 0xc0c6, 0xc6c6, 0x7c40, 0x0000, 0x2e10,
    0x0018, 0x66ff, 0x600c, 0x3818, 0x1818, 0x3c18, 0x0000, 0x000c,
    0x6638, 0x660c, 0x1c60, 0x6006, 0x6666, 0x1818, 0x387e, 0x3866,
    0xc266, 0x6666, 0x6660, 0x6060, 0x6618, 0x06d8, 0x60ee, 0x7666,
    0x6666, 0xcc60, 0x1866, 0x66c6, 0x3c66, 0x0c18, 0x3018, 0x6c00,
    0x0c3c, 0x7c3c, 0x3e3c, 0x183e, 0x7c38, 0x0ccc, 0x186c, 0x3c3c,
    0x7c3e, 0x7c3e, 0x7e66, 0x66c6, 0x6666, 0x7e18, 0x1830, 0x6218,
    0x6666, 0x3c3c, 0x3c3c, 0x3c3c, 0x3c3c, 0x3c38, 0x3838, 0x7e7e,
    0x6076, 0xd83c, 0x3c3c, 0x6666, 0x667e, 0x667e, 0x3066, 0x6618,
    0x3c00, 0x7e30, 0x6066, 0x6018, 0x3eba, 0x3e00, 0x0000, 0xba00,
    0x3818, 0x3018, 0x0c66, 0xca00, 0x7e18, 0x6600, 0xd87e, 0x6618,
    0x7e7e, 0x7e7e, 0x7e7e, 0xd866, 0x6060, 0x7e7e, 0x1818, 0x7e7e,
    0x6666, 0x7e7e, 0x7e7e, 0x7e66, 0x6666, 0x6666, 0x6666, 0x7c66,
    0x3c3c, 0x3c3c, 0x3c3c, 0x763c, 0x3c3c, 0x3c3c, 0x3838, 0x3838,
    0x063c, 0x3c3c, 0x3c3c, 0x3c00, 0x3d66, 0x6666, 0x6666, 0x7c66,
    0x00c3, 0x2483, 0xc1d6, 0xfcba, 0x0691, 0x3c08, 0x4038, 0x0db0,
    0x8202, 0x3a3a, 0xbab8, 0xb882, 0xbaba, 0x7e78, 0x0000, 0x39e0,
    0x0018, 0x6666, 0x7c18, 0x7018, 0x1818, 0xff7e, 0x007e, 0x000c,
    0x6618, 0x0c18, 0x3c7c, 0x600c, 0x3c7e, 0x1818, 0x7000, 0x1c0c,
    0xda66, 0x7e60, 0x667c, 0x7c6e, 0x7e18, 0x06f0, 0x60fe, 0x7666,
    0x6666, 0xcc70, 0x1866, 0x66c6, 0x3c3c, 0x1818, 0x3018, 0x6c00,
    0x043e, 0x7e7c, 0x7e7e, 0x7e7e, 0x7e38, 0x0cdc, 0x18fe, 0x7e7e,
    0x7e7e, 0x7e7e, 0x7e66, 0x66c6, 0x6666, 0x7e38, 0x1838, 0xf218,
    0x6066, 0x7e3e, 0x3e3e, 0x3e7c, 0x7e7e, 0x7e38, 0x3838, 0x6666,
    0x607f, 0xde7e, 0x7e7e, 0x6666, 0x6666, 0x6666, 0x307e, 0x6618,
    0x3e18, 0x6630, 0xfc7e, 0x703c, 0x7ea2, 0x061a, 0x003c, 0xaa00,
    0x007e, 0x6048, 0x0c66, 0xca00, 0x7e18, 0x66b0, 0xdeff, 0x6618,
    0x6666, 0x6666, 0x6666, 0xde60, 0x6060, 0x6060, 0x1818, 0x1818,
    0x7676, 0x6666, 0x6666, 0x663c, 0x6e66, 0x6666, 0x6666, 0x7e66,
    0x3e3e, 0x3e3e, 0x3e3e, 0x7f7c, 0x7e7e, 0x7e7e, 0x3838, 0x3838,
    0x1e7e, 0x7e7e, 0x7e7e, 0x7e7e, 0x7e66, 0x6666, 0x6666, 0x7e66,
    0x0081, 0xe783, 0xc1c6, 0xf838, 0x0691, 0x3c08, 0x0000, 0x1db8,
    0x0000, 0x7c7c, 0x7c7c, 0x7c00, 0x7c7c, 0x0600, 0x0000, 0x3800,
    0x0018, 0x6666, 0x3e18, 0x7018, 0x1818, 0xff7e, 0x007e, 0x0018,
    0x6e18, 0x0c18, 0x3c7e, 0x7c0c, 0x3c3e, 0x1818, 0xe000, 0x0e0c,
    0xd666, 0x7c60, 0x667c, 0x7c6e, 0x7e18, 0x06f0, 0x60d6, 0x7e66,
    0x6666, 0xfc38, 0x1866, 0x66d6, 0x183c, 0x1818, 0x1818, 0xc600,
    0x0006, 0x6660, 0x6666, 0x7e66, 0x6618, 0x0cf8, 0x18fe, 0x6666,
    0x6666, 0x6660, 0x1866, 0x66d6, 0x3c66, 0x0cf0, 0x181e, 0xbe3c,
    0x6066, 0x6606, 0x0606, 0x0660, 0x6666, 0x6618, 0x1818, 0x6666,
    0x7c1b, 0xde66, 0x6666, 0x6666, 0x6666, 0x6660, 0x303c, 0x7c7e,
    0x0618, 0x6030, 0x603c, 0x3866, 0x60a2, 0x3e36, 0x003c, 0xb200,
    0x007e, 0x7830, 0x1866, 0xca18, 0x0c7c, 0x3cd8, 0xdedb, 0x6618,
    0x6666, 0x6666, 0x6666, 0xde60, 0x7c7c, 0x6060, 0x1818, 0x1818,
    0xf676, 0x6666, 0x6666, 0x6618, 0x6e66, 0x6666, 0x6666, 0x667c,
    0x0606, 0x0606, 0x0606, 0x1b60, 0x6666, 0x6666, 0x1818, 0x1818,
    0x3e66, 0x6666, 0x6666, 0x667e, 0x6666, 0x6666, 0x6666, 0x6666,
    0x00e7, 0x81e6, 0x67d6, 0xfaba, 0x8c9d, 0x3c78, 0x1e1c, 0x399c,
    0x8202, 0xb83a, 0x3a3a, 0xba02, 0xba3a, 0x060e, 0x07f0, 0x0000,
    0x0018, 0x00ff, 0x0630, 0xde00, 0x1818, 0x3c18, 0x0000, 0x0018,
    0x7618, 0x180c, 0x6c06, 0x7e18, 0x6606, 0x0000, 0x707e, 0x1c18,
    0xd67e, 0x6660, 0x6660, 0x6066, 0x6618, 0x06d8, 0x60d6, 0x7e66,
    0x7e66, 0xf81c, 0x1866, 0x66d6, 0x1818, 0x3018, 0x1818, 0xc600,
    0x003e, 0x6660, 0x6666, 0x1866, 0x6618, 0x0cf0, 0x18d6, 0x6666,
    0x6666, 0x6070, 0x1866, 0x66d6, 0x3c66, 0x18f0, 0x181e, 0x9c24,
    0x6066, 0x663e, 0x3e3e, 0x3e60, 0x6666, 0x6618, 0x1818, 0x7e7e,
    0x7c7b, 0xf866, 0x6666, 0x6666, 0x6666, 0x6660, 0xfe18, 0x6618,
    0x3e18, 0x60fe, 0xf818, 0x1c66, 0x70a2, 0x7e6c, 0x0000, 0xba00,
    0x0018, 0x0000, 0x1866, 0x7a18, 0x1800, 0x006c, 0xd8db, 0x3c30,
    0x7e7e, 0x7e7e, 0x7e7e, 0xf860, 0x7c7c, 0x7c7c, 0x1818, 0x1818,
    0xe67e, 0x6666, 0x6666, 0x663c, 0x7666, 0x6666, 0x663c, 0x667c,
    0x3e3e, 0x3e3e, 0x3e3e, 0x7b60, 0x6666, 0x6666, 0x1818, 0x1818,
    0x6666, 0x6666, 0x6666, 0x6600, 0x6e66, 0x6666, 0x6666, 0x6666,
    0x0024, 0xc32c, 0x3492, 0xf292, 0x8c81, 0x3cf8, 0x1012, 0x799e,
    0xc606, 0xc006, 0x0606, 0xc606, 0xc606, 0x7e10, 0x0ff8, 0x0000,
    0x0018, 0x00ff, 0x0636, 0xde00, 0x1818, 0x3c18, 0x0000, 0x0030,
    0x6618, 0x180c, 0x6c06, 0x6618, 0x6606, 0x0000, 0x387e, 0x3818,
    0xdc7e, 0x6660, 0x6660, 0x6066, 0x6618, 0x06d8, 0x60c6, 0x6e66,
    0x7c66, 0xd80e, 0x1866, 0x66fe, 0x3c18, 0x3018, 0x0c18, 0x0000,
    0x007e, 0x6660, 0x667e, 0x1866, 0x6618, 0x0cf8, 0x18d6, 0x6666,
    0x6666, 0x603c, 0x1866, 0x66fe, 0x1866, 0x1838, 0x1838, 0x0066,
    0x6066, 0x7e7e, 0x7e7e, 0x7e60, 0x7e7e, 0x7e18, 0x1818, 0x7e7e,
    0x60ff, 0xf866, 0x6666, 0x6666, 0x6666, 0x6666, 0x307e, 0x6618,
    0x7e18, 0x6630, 0x607e, 0x0e3c, 0x3cba, 0x66d8, 0x7e00, 0xaa00,
    0x0018, 0x0000, 0x3066, 0x0a00, 0x1800, 0x0036, 0xd8df, 0x3c30,
    0x7e7e, 0x7e7e, 0x7e7e, 0xf860, 0x6060, 0x7c7c, 0x1818, 0x1818,
    0x666e, 0x6666, 0x6666, 0x6666, 0x7666, 0x6666, 0x663c, 0x7e66,
    0x7e7e, 0x7e7e, 0x7e7e, 0xff60, 0x7e7e, 0x7e7e, 0x1818, 0x1818,
    0x6666, 0x6666, 0x6666, 0x6618, 0x7e66, 0x6666, 0x6666, 0x6666,
    0x0024, 0x6638, 0x1cba, 0xf6d6, 0xd8c3, 0x7e70, 0x1c1c, 0x718e,
    0xc606, 0xc006, 0x0606, 0xc606, 0xc606, 0x660c, 0x1fec, 0x0000,
    0x0000, 0x0066, 0x7e66, 0xcc00, 0x1818, 0x6618, 0x1800, 0x1830,
    0x6618, 0x3066, 0x7e06, 0x6630, 0x6606, 0x1818, 0x1c00, 0x7018,
    0xc066, 0x6666, 0x6660, 0x6066, 0x6618, 0x66cc, 0x60c6, 0x6e66,
    0x6066, 0xcc06, 0x1866, 0x3cfe, 0x3c18, 0x6018, 0x0c18, 0x0000,
    0x0066, 0x6660, 0x6660, 0x1866, 0x6618, 0x0cd8, 0x18d6, 0x6666,
    0x6666, 0x600e, 0x1866, 0x3cfe, 0x3c66, 0x3018, 0x1830, 0x0042,
    0x6666, 0x6066, 0x6666, 0x6660, 0x6060, 0x6018, 0x1818, 0x6666,
    0x60d8, 0xd866, 0x6666, 0x6666, 0x6666, 0x667e, 0x3018, 0x6618,
    0x6618, 0x7e30, 0x6018, 0x0618, 0x0e82, 0x666c, 0x7e00, 0x8200,
    0x0018, 0x0000, 0x3066, 0x0a00, 0x3000, 0x006c, 0xd8d8, 0x1866,
    0x6666, 0x6666, 0x6666, 0xd866, 0x6060, 0x6060, 0x1818, 0x1818,
    0x666e, 0x6666, 0x6666, 0x66c3, 0x6666, 0x6666, 0x6618, 0x7c66,
    0x6666, 0x6666, 0x6666, 0xd860, 0x6060, 0x6060, 0x1818, 0x1818,
    0x6666, 0x6666, 0x6666, 0x6618, 0x7666, 0x6666, 0x6666, 0x6666,
    0x0024, 0x3c30, 0x0c38, 0xe6c6, 0x5866, 0xff00, 0x1014, 0x718e,
    0xc606, 0xc006, 0x0606, 0xc606, 0xc606, 0x6602, 0x1804, 0x0000,
    0x0000, 0x0066, 0x7c66, 0xcc00, 0x1c38, 0x6600, 0x1800, 0x1860,
    0x6618, 0x3066, 0x7e66, 0x6630, 0x660e, 0x1818, 0x0e00, 0xe000,
    0xe266, 0x6666, 0x6e60, 0x6066, 0x6618, 0x66cc, 0x60c6, 0x6666,
    0x606a, 0xcc06, 0x1866, 0x3cee, 0x6618, 0x6018, 0x0618, 0x0000,
    0x0066, 0x6660, 0x6660, 0x187e, 0x6618, 0x0ccc, 0x18c6, 0x6666,
    0x6666, 0x6006, 0x1866, 0x3cee, 0x3c7e, 0x3018, 0x1830, 0x00c3,
    0x6666, 0x6066, 0x6666, 0x6660, 0x6060, 0x6018, 0x1818, 0x6666,
    0x60d8, 0xd866, 0x6666, 0x6666, 0x7e66, 0x663c, 0x3018, 0x7c18,
    0x6618, 0x3c30, 0x6618, 0x064c, 0x06c6, 0x7e36, 0x0600, 0xc600,
    0x0000, 0x0000, 0x607f, 0x0a00, 0x3000, 0x00d8, 0xd8d8, 0x1866,
    0x6666, 0x6666, 0x6666, 0xd866, 0x6060, 0x6060, 0x1818, 0x1818,
    0x6e66, 0x6666, 0x6666, 0x6600, 0x6666, 0x6666, 0x6618, 0x6066,
    0x6666, 0x6666, 0x6666, 0xd860, 0x6060, 0x6060, 0x1818, 0x1818,
    0x6666, 0x6666, 0x6666, 0x6600, 0x6666, 0x6666, 0x667e, 0x667e,
    0x003c, 0x1800, 0x007c, 0xeeee, 0x703c, 0x1000, 0x1012, 0x6186,
    0xba02, 0xb83a, 0x023a, 0xba02, 0xba3a, 0x7e1c, 0x1804, 0x0000,
    0x0018, 0x0000, 0x1800, 0xfe00, 0x0c30, 0x0000, 0x1800, 0x1860,
    0x7e7e, 0x7e7e, 0x0c7e, 0x7e30, 0x7e3c, 0x1818, 0x0000, 0x0018,
    0x7e66, 0x7e7e, 0x7c7e, 0x607e, 0x667e, 0x7ec6, 0x7ec6, 0x667e,
    0x607c, 0xc67e, 0x187e, 0x18c6, 0x6618, 0x7e1e, 0x0678, 0x00fe,
    0x007e, 0x7e7e, 0x7e7e, 0x183e, 0x663c, 0x0cce, 0x3cc6, 0x667e,
    0x7e7e, 0x607e, 0x1e7e, 0x18c6, 0x663e, 0x7e18, 0x1830, 0x00ff,
    0x7e7e, 0x7e7e, 0x7e7e, 0x7e7e, 0x7e7e, 0x7e3c, 0x3c3c, 0x6666,
    0x7eff, 0xde7e, 0x7e7e, 0x7e7e, 0x3e7e, 0x7e18, 0x7f18, 0x6c18,
    0x7e18, 0x187f, 0x3e18, 0x7e6c, 0x7e7c, 0x3e1a, 0x0600, 0x7c00,
    0x007e, 0x0000, 0x7e5d, 0x0a00, 0x7e00, 0x00b0, 0xfeff, 0x187e,
    0x6666, 0x6666, 0x6666, 0xde7e, 0x7e7e, 0x7e7e, 0x7e7e, 0x7e7e,
    0x7c66, 0x7e7e, 0x7e7e, 0x7e00, 0x7e7e, 0x7e7e, 0x7e18, 0x6066,
    0x7e7e, 0x7e7e, 0x7e7e, 0xff7e, 0x7e7e, 0x7e7e, 0x3c3c, 0x3c3c,
    0x7e66, 0x7e7e, 0x7e7e, 0x7e00, 0x7e7e, 0x7e7e, 0x7e3e, 0x7e3e,
    0x0000, 0x0000, 0x0000, 0x0000, 0x3000, 0x3800, 0x0000, 0x4182,
    0x7c00, 0x7c7c, 0x007c, 0x7c00, 0x7c7c, 0x3c00, 0x1004, 0x0000,
    0x0018, 0x0000, 0x1800, 0x7600, 0x0660, 0x0000, 0x1800, 0x1860,
    0x3c7e, 0x7e3c, 0x0c3c, 0x3c30, 0x3c38, 0x1818, 0x0000, 0x0018,
    0x3c66, 0x7c3c, 0x787e, 0x603c, 0x667e, 0x3cc6, 0x7ec6, 0x663c,
    0x6036, 0xc67c, 0x183c, 0x1882, 0x6618, 0x7e1e, 0x0678, 0x00fe,
    0x003e, 0x7c3e, 0x3e3e, 0x1806, 0x663c, 0x0cc6, 0x3cc6, 0x663c,
    0x7c3e, 0x607c, 0x0e3e, 0x1882, 0x6606, 0x7e18, 0x1830, 0x0000,
    0x3c3e, 0x3e3e, 0x3e3e, 0x3e3e, 0x3e3e, 0x3e3c, 0x3c3c, 0x6666,
    0x7e7f, 0xde3c, 0x3c3c, 0x3e3e, 0x063c, 0x3c18, 0xff18, 0x6070,
    0x3e18, 0x18ff, 0x1c18, 0x7c38, 0x7c00, 0x0000, 0x0600, 0x0000,
    0x007e, 0x0000, 0x7ec0, 0x0a00, 0x7e00, 0x0000, 0x7e7f, 0x183c,
    0x6666, 0x6666, 0x6666, 0xde3c, 0x7e7e, 0x7e7e, 0x7e7e, 0x7e7e,
    0x7866, 0x3c3c, 0x3c3c, 0x3c00, 0xbc3c, 0x3c3c, 0x3c18, 0x606c,
    0x3e3e, 0x3e3e, 0x3e3e, 0x7f3e, 0x3e3e, 0x3e3e, 0x3c3c, 0x3c3c,
    0x3c66, 0x3c3c, 0x3c3c, 0x3c00, 0xbc3e, 0x3e3e, 0x3e06, 0x7c06,
    0x0000, 0x0000, 0x0000, 0x0000, 0x2000, 0x1000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1e3c, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0030, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x007e, 0x0000, 0x7c00, 0x0000, 0x0000,
    0x6006, 0x0000, 0x0000, 0x0000, 0x007e, 0x000e, 0x18e0, 0x0000,
    0x0c00, 0x0000, 0x0000, 0x000c, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x7e00, 0x0000, 0x0000, 0x4060,
    0x0018, 0x0000, 0x0000, 0x0000, 0x0000, 0x7e00, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0080, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x000c, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x8000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x000c, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x8000, 0x0000, 0x007e, 0x607e,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1754, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x007c, 0x0000, 0x7800, 0x0000, 0x0000,
    0x6006, 0x0000, 0x0000, 0x0000, 0x007c, 0x0000, 0x0000, 0x0000,
    0x3800, 0x0000, 0x0000, 0x0038, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x7c00, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0038, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0038, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x007c, 0x607c,
};

const Fonthead fnt_l9_8x16 =
{
    1,  /* font_id */
    10,  /* point */
    "8x16 system font",  /* BYTE name[32] */
    0,  /* first_ade */
    255,  /* last_ade */
    13,  /* top */
    11,  /* ascent */
    8,  /* half */
    2,  /* descent */
    2,  /* bottom */
    7,  /* max_char_width */
    8,  /* max_cell_width */
    1,  /* left_offset */
    7,  /* right_offset */
    1,  /* thicken */
    1,  /* ul_size */
    0x5555,  /* lighten */
    0x5555,  /* skew */
    F_STDFORM | F_MONOSPACE | F_DEFAULT,  /* flags */
    0,  /* hor_table */
    off_table,  /* off_table */
    dat_table,  /* dat_table */
    256,  /* form_width */
    16,  /* form_height */
    0    /* Fonthead * next_font */
};
