/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      IMG_sad_8x8_d.c -- Example file for IMG_sad_8x8                     */
/*                                                                          */
/*  USAGE                                                                   */
/*      This file contains code for demonstrating the C64x IMGLIB           */
/*      IMG_sad_8x8 function. All inputs to the function contain random     */
/*      data. The assembly version of IMG_sad_8x8 is called and the         */
/*      output is compared with the reference C code using mem_compare()    */
/*      in support.c.                                                       */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
    
#include <stdio.h>
#include <stdlib.h>

/* Header file for the memory compare function */
int mem_compare(const void *ptr1, const char *name1,
                const void *ptr2, const char *name2, int len);

/* Header file for the DSPLIB function */
#include "IMG_sad_8x8.h"

/* Header file for the C function */
unsigned IMG_sad_8x8_c(const unsigned char * src_data, const unsigned char * ref_data, int Pitch);

/* ======================================================================== */
/*  IMGLIB function-specific alignments. Refer to the                       */
/*  TMS320C64x IMG Library Programmer's Reference for details.              */
/* ======================================================================== */
#pragma DATA_ALIGN(src_data, 8);

/* ======================================================================== */
/*  Constant dataset.                                                       */
/* ======================================================================== */
#define pitch    (32)


/* ======================================================================== */
/*  Initialize arrays with random test data.                                */
/* ======================================================================== */
int     test = 0;
const unsigned char  src_data[64] = 
{
     0x7B,  0xA1,  0x70,  0x60,  0x9C,  0xAB,  0xF4,  0xB2,
     0xA9,  0x8D,  0x7B,  0xF0,  0xFA,  0xE2,  0xE0,  0xAE,
     0x21,  0x08,  0xC9,  0x74,  0x15,  0x4D,  0x3A,  0xEB,
     0x82,  0xAF,  0x28,  0x6E,  0x28,  0x7B,  0x4D,  0xCB,
     0x5E,  0x1E,  0x4F,  0xDE,  0x51,  0x8A,  0x3C,  0x19,
     0xCA,  0x21,  0xC6,  0x3E,  0x27,  0xFF,  0xF0,  0x91,
     0xB3,  0xA1,  0x5D,  0x36,  0xB5,  0x15,  0x16,  0x09,
     0xA9,  0x5D,  0xF2,  0xFC,  0x15,  0x82,  0xEE,  0x16
};

const unsigned char  ref_data[768] = 
{
     0x25,  0x9A,  0xB1,  0x28,  0x9F,  0xAF,  0x8B,  0xF3,
     0xC9,  0x35,  0x8D,  0x57,  0xD3,  0xD5,  0xD0,  0x3F,
     0x80,  0x7D,  0xCC,  0xF2,  0x23,  0x5C,  0x02,  0x75,
     0xC4,  0x23,  0xA4,  0x8D,  0xF2,  0xFB,  0xFB,  0x16,
     0xF5,  0x77,  0x7B,  0x77,  0x10,  0xF1,  0x23,  0x25,
     0x05,  0xD5,  0x2A,  0x82,  0x6A,  0xA3,  0x1A,  0xD8,
     0x72,  0xEC,  0xB8,  0x93,  0x85,  0x70,  0xA4,  0x92,
     0x02,  0xF4,  0x61,  0x41,  0xE8,  0x6E,  0xBC,  0x9C,
     0x5C,  0x76,  0x64,  0x90,  0x86,  0x25,  0x02,  0x9F,
     0x37,  0xB1,  0x08,  0xF9,  0xD7,  0xDF,  0x6C,  0xB1,
     0x9F,  0xD5,  0x78,  0xF8,  0x4F,  0x86,  0x2A,  0x74,
     0x53,  0x9A,  0x94,  0xC1,  0x7E,  0x40,  0xF1,  0x0D,
     0x38,  0xB2,  0xAA,  0x2E,  0x59,  0x32,  0x4C,  0x98,
     0x71,  0xBB,  0x07,  0xA6,  0xB9,  0xE3,  0x9E,  0x70,
     0x99,  0x1B,  0xB2,  0x6D,  0x53,  0xA7,  0x61,  0xCD,
     0x5D,  0x15,  0x41,  0xE4,  0x48,  0x7E,  0xBD,  0x0F,
     0x9F,  0x16,  0xA1,  0x33,  0x77,  0x78,  0x1F,  0xD3,
     0x2D,  0xE2,  0xCE,  0x42,  0xAB,  0x88,  0x89,  0xE6,
     0xF8,  0xC1,  0xFF,  0x2A,  0x0B,  0x28,  0x62,  0x2E,
     0xC2,  0x4B,  0x86,  0xEF,  0xF7,  0xDF,  0x56,  0x1F,
     0x26,  0xCA,  0x97,  0x13,  0xF7,  0xF5,  0x46,  0x7F,
     0xE8,  0x60,  0x9A,  0x5C,  0x3B,  0x22,  0xBF,  0x0A,
     0x89,  0x45,  0x2B,  0x50,  0xA4,  0x26,  0x6F,  0x21,
     0x31,  0x99,  0xCD,  0xF7,  0x44,  0x6A,  0xFE,  0xA4,
     0x18,  0x1E,  0x85,  0x02,  0xB7,  0xBE,  0x54,  0x1C,
     0xC7,  0x24,  0xFD,  0xB7,  0xEC,  0x71,  0xDB,  0xB2,
     0xAF,  0xB6,  0x82,  0xE8,  0x40,  0x93,  0x6D,  0x87,
     0xC3,  0xBA,  0x3B,  0xE4,  0x36,  0x40,  0xBB,  0xE1,
     0x1F,  0x67,  0x23,  0x66,  0x6E,  0x3A,  0xA8,  0xFE,
     0xD0,  0xD8,  0x13,  0x90,  0xE2,  0xEE,  0xCC,  0x74,
     0x6B,  0xFD,  0xBC,  0x66,  0xF9,  0x42,  0x88,  0xCD,
     0x27,  0x82,  0xCD,  0x98,  0x4C,  0x18,  0x56,  0x6C,
     0xD2,  0x5D,  0xC6,  0x04,  0xB9,  0xA7,  0xCC,  0xD7,
     0x27,  0xF8,  0xB1,  0x40,  0xA6,  0x0C,  0xA6,  0x40,
     0x99,  0xE9,  0xF5,  0x26,  0x23,  0x85,  0x7C,  0x77,
     0x17,  0xFB,  0xB1,  0xAD,  0xFD,  0xDE,  0x22,  0x86,
     0xB8,  0x68,  0x93,  0x76,  0xAE,  0x69,  0xC3,  0xD7,
     0xDD,  0x8E,  0xFC,  0xC8,  0x85,  0xD8,  0x7B,  0x25,
     0xD5,  0x68,  0x40,  0x6E,  0x47,  0xCF,  0xFC,  0x74,
     0xA3,  0x55,  0x4C,  0x66,  0x1A,  0xFB,  0x06,  0xEF,
     0x33,  0x72,  0x92,  0x58,  0x65,  0xA5,  0xB8,  0xDA,
     0xD0,  0xF9,  0x07,  0xB1,  0x0D,  0x8B,  0xB6,  0xC7,
     0x89,  0x84,  0x4C,  0x75,  0x5B,  0xE3,  0xCB,  0xC5,
     0xBD,  0x2F,  0x7D,  0x2C,  0x87,  0xCD,  0x46,  0xA2,
     0xD7,  0xA8,  0x07,  0xC0,  0xFE,  0x9B,  0x8F,  0x2C,
     0x0D,  0x56,  0xD7,  0xD7,  0x2D,  0x80,  0x7C,  0x0B,
     0xB4,  0x94,  0x9E,  0xE5,  0xB9,  0x03,  0xED,  0xF8,
     0x9B,  0xBD,  0x8C,  0x3F,  0xD6,  0xBA,  0xA1,  0x09,
     0xB5,  0xB7,  0xAC,  0x72,  0xA8,  0x59,  0xE0,  0x57,
     0x4D,  0x05,  0x62,  0x92,  0x69,  0x15,  0x95,  0x71,
     0xD3,  0x20,  0xE5,  0x5E,  0x55,  0xB6,  0x84,  0xF4,
     0x61,  0x42,  0x58,  0xF7,  0x41,  0x7D,  0x1E,  0x21,
     0x08,  0x08,  0x36,  0x54,  0x25,  0x25,  0xD7,  0x88,
     0xEE,  0xBA,  0x04,  0xBE,  0xB1,  0xF1,  0x51,  0x9C,
     0x77,  0x0F,  0xD7,  0x7E,  0xA8,  0x8B,  0xD1,  0x8E,
     0x9F,  0x68,  0x33,  0x35,  0x79,  0x0E,  0x34,  0x08,
     0xDB,  0x68,  0xBD,  0xA5,  0x42,  0x3F,  0x71,  0x02,
     0x0B,  0xB3,  0xE6,  0x2A,  0x51,  0x39,  0x01,  0x8E,
     0x15,  0x78,  0x33,  0xE9,  0xE4,  0x68,  0xD9,  0x7E,
     0x10,  0xED,  0xF4,  0x6C,  0xD8,  0xBC,  0xA6,  0x89,
     0x15,  0xB6,  0x68,  0x74,  0xD9,  0x63,  0xAB,  0x22,
     0x16,  0x87,  0xDF,  0xDD,  0x84,  0x2B,  0x63,  0x1B,
     0x72,  0xC0,  0x4A,  0xCF,  0xD8,  0xE7,  0x30,  0x12,
     0x33,  0x29,  0xC1,  0xCC,  0x71,  0xEA,  0xAB,  0x0A,
     0x6F,  0x04,  0xFA,  0xDA,  0xCB,  0x98,  0x08,  0x76,
     0x7F,  0x00,  0x42,  0xC8,  0x1C,  0xA1,  0xA3,  0xFD,
     0x45,  0x64,  0xA6,  0x77,  0x1D,  0x39,  0x65,  0x47,
     0x25,  0xF2,  0x0C,  0x11,  0x76,  0xFA,  0xE1,  0x76,
     0xE1,  0xB2,  0xAF,  0x73,  0x6E,  0xC6,  0x0B,  0x63,
     0xED,  0xA1,  0x29,  0x54,  0xCE,  0xFF,  0x57,  0x2C,
     0x88,  0xFE,  0x43,  0x46,  0xF6,  0x0B,  0x9E,  0x9E,
     0x56,  0x54,  0x42,  0x6F,  0x85,  0xDE,  0x77,  0x97,
     0xF4,  0xFE,  0xF2,  0x99,  0x08,  0x95,  0x04,  0xDB,
     0x81,  0x39,  0xAF,  0x4C,  0x96,  0x06,  0x04,  0xD9,
     0xF0,  0x0D,  0xDA,  0xCD,  0x73,  0x02,  0xC9,  0x54,
     0x7B,  0xA0,  0xB8,  0x25,  0x49,  0xCF,  0x27,  0x57,
     0x80,  0x96,  0x63,  0xDD,  0xBA,  0x1A,  0xD6,  0xA9,
     0xA6,  0x10,  0xA3,  0xB3,  0xBC,  0x1A,  0xA8,  0xA0,
     0x15,  0xE5,  0xC5,  0x55,  0x52,  0x33,  0xFF,  0x5E,
     0x5A,  0x5F,  0x41,  0x2A,  0xFD,  0xB6,  0x73,  0x82,
     0x62,  0x9C,  0xB5,  0x47,  0x71,  0xC3,  0x12,  0xC9,
     0xF0,  0x32,  0x2F,  0xF0,  0xF3,  0x62,  0xC6,  0x6A,
     0xC9,  0x67,  0xFA,  0x6A,  0x15,  0x2B,  0x87,  0xBD,
     0xDB,  0x8E,  0x01,  0x7F,  0x4A,  0xB6,  0xA3,  0x69,
     0x8D,  0xA1,  0xDD,  0xD1,  0x4A,  0x17,  0xFC,  0x52,
     0x83,  0x4F,  0xF3,  0xE1,  0x17,  0x5F,  0x7A,  0x80,
     0x17,  0xED,  0x92,  0xE9,  0xDE,  0x01,  0x00,  0xA4,
     0xEE,  0xC2,  0xF5,  0xA5,  0x02,  0x62,  0x0E,  0x05,
     0x1D,  0x22,  0x21,  0xA7,  0x00,  0xB6,  0xFB,  0x72,
     0x8F,  0xB2,  0x16,  0x50,  0x07,  0x64,  0x14,  0x4F,
     0x72,  0xE9,  0x71,  0x14,  0x85,  0xE9,  0x29,  0xE6,
     0xB1,  0x9B,  0xAD,  0xA8,  0x3A,  0x1B,  0x1F,  0xFA,
     0xC3,  0xF7,  0x6E,  0xA6,  0xCA,  0x29,  0xE6,  0xFB,
     0x52,  0xDA,  0xCA,  0x44,  0x19,  0x77,  0xB2,  0x5D,
     0x92,  0xC7,  0x77,  0x19,  0x68,  0xD9,  0xD9,  0x41,
     0x73,  0x15,  0xBB,  0x5C,  0x42,  0x18,  0xAC,  0x1D
};



/* ======================================================================== */
/*  Variables to catch return values from function.                         */
/* ======================================================================== */
unsigned ret_val_asm = 0;
unsigned ret_val_c = 0;

int main()
{   

/* ======================================================================== */
/*  Call hand-coded assembly version (located in IMG64x.lib library         */ 
/*  archive - see Project -> Build Options -> Linker -> Include Libraries)  */
/* ======================================================================== */   
    ret_val_asm = IMG_sad_8x8(src_data, ref_data, pitch);
    
/* ======================================================================== */
/*  Call natural-C version                                                  */
/* ======================================================================== */
    ret_val_c = IMG_sad_8x8_c(src_data, ref_data, pitch);

/* ======================================================================== */
/*  Compare outputs using mem_compare() in support.c.  If different,        */
/*  mem_compare() displays location of failures.                            */
/* ======================================================================== */

      printf("ret_val_asm vs. ret_val_c\n");
    if ((ret_val_c == ret_val_asm)) 
    {
      printf("Verification successful.\n");
    } else 
    {
      printf("Verification failure.\n");
    }

}

/* ======================================================================== */
/*  End of file:  img_sad_8x8_d.c                                           */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
