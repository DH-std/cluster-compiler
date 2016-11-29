/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_mat_mul_d.c -- Example file for DSP_mat_mul                     */
/*                                                                          */
/*  USAGE                                                                   */
/*      This file contains code for demonstrating the C64x DSPLIB           */
/*      DSP_mat_mul function. All inputs to the function contain random     */
/*      data. The assembly version of DSP_mat_mul is called and the         */
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
#include "DSP_mat_mul.h"    

/* Header file for the C function */
void DSP_mat_mul_c(const short * x, int r1, int c1, const short * y, int c2, short * r, int qs);


/* ======================================================================== */
/*  Constant dataset.                                                       */
/* ======================================================================== */
#define C1   (14)
#define C2   (18)
#define R1   (12)
#define R1C1 (168)
#define R1C2 (216)
#define R2C2 (252)


/* ======================================================================== */
/*  Initialize arrays with random test data.                                */
/* ======================================================================== */
int     test = 0;
const short  x[R1C1] = 
{
    -0x2D03,  0x6085,  0x6267,  0x2C5E, -0x0691, -0x3F65,  0x2905, -0x37EA,
    -0x4335, -0x3AD4,  0x4672, -0x352D,  0x740C,  0x4E9A,  0x47B4, -0x3A21,
     0x3C73, -0x367A, -0x49C7,  0x12CD,  0x4360, -0x716C,  0x2E79, -0x2E8A,
     0x2952, -0x3E4E, -0x6A82, -0x1183,  0x5C2F,  0x1FA2, -0x059A, -0x65E7,
     0x6641,  0x4E28, -0x3F16, -0x4FE4, -0x4677,  0x2CA4,  0x6E1C, -0x5FB4,
    -0x47C8,  0x58C3,  0x1853,  0x005C, -0x6BBF, -0x1768,  0x6668, -0x6CE0,
     0x1943, -0x7D01, -0x0D81,  0x474C, -0x45B7,  0x419A,  0x30B3,  0x14B2,
     0x3A52,  0x2362, -0x7625, -0x7925,  0x4BAB, -0x30F3,  0x5E0E, -0x4DB8,
     0x5063,  0x0367, -0x5A00,  0x615D, -0x4292, -0x10D4, -0x2477, -0x1E10,
    -0x73B4,  0x3091,  0x5009, -0x4C5D,  0x6DA4, -0x76D8,  0x7113, -0x6C64,
     0x3A5B,  0x5C3E,  0x3C7C,  0x127C, -0x3AC9, -0x2FA5, -0x55B2,  0x4474,
    -0x3888,  0x16B7,  0x2009, -0x6148,  0x54C1, -0x745F,  0x16CE,  0x7D14,
    -0x6CC5,  0x0B64,  0x5E57, -0x34EF,  0x2F02,  0x36AE,  0x0C87,  0x5E45,
    -0x2146,  0x3C8E,  0x76F4,  0x1AAC,  0x39D7,  0x446D, -0x1A5D,  0x31E0,
    -0x4197, -0x37CE, -0x5228,  0x6962,  0x02F4,  0x56D2,  0x328D, -0x12A2,
    -0x639C,  0x6738, -0x3C0A, -0x04D5,  0x4785,  0x2534, -0x1930,  0x51CB,
     0x441F,  0x3D42,  0x2F06,  0x73B6,  0x441A,  0x1B44, -0x79C7,  0x6AB9,
     0x5C13,  0x009A,  0x5535, -0x3288,  0x6119,  0x50EC,  0x73DB,  0x7D1E,
    -0x617D, -0x43DD,  0x482E, -0x5AEA,  0x0EC3, -0x370B,  0x16B3, -0x4412,
    -0x0715, -0x52D4,  0x53E9,  0x5D94, -0x0054,  0x3B13,  0x3829, -0x7864,
     0x7FE7, -0x431B,  0x1ABC,  0x4920,  0x5323, -0x45E5,  0x250E,  0x0ABE
};



const short  y[R2C2] = 
{
    -0x3E3D,  0x31C5,  0x5865, -0x7BDC, -0x5168, -0x478A,  0x3B99,  0x4D67,
    -0x012C,  0x1A99, -0x72C8, -0x046F, -0x6B7D, -0x245C,  0x7299,  0x68E0,
    -0x7EF3, -0x5DDB,  0x7C13,  0x2158,  0x15BD,  0x0578,  0x0C20,  0x2BF0,
     0x44DD,  0x6925,  0x648E, -0x2F98, -0x048C, -0x670A, -0x11DE,  0x45E6,
    -0x225C,  0x713F, -0x1965,  0x3760, -0x65E2, -0x0ABA, -0x7A41,  0x0C49,
    -0x4690, -0x2BF4,  0x1DF2,  0x00E1, -0x6723, -0x7F15, -0x1E81, -0x01E2,
    -0x7747, -0x2786,  0x2EAF, -0x7BD1, -0x1026,  0x5173, -0x5AA8, -0x7197,
    -0x3DEE,  0x5415,  0x7C07, -0x7073, -0x4A1F, -0x35B7, -0x3ADB, -0x0948,
     0x3390, -0x6389,  0x2846,  0x23AB,  0x3E8F, -0x1029, -0x76C9, -0x42B5,
    -0x7036,  0x48DA, -0x00D8, -0x62A9,  0x7EDC,  0x6412,  0x53A3, -0x0F61,
     0x1BD2,  0x471A, -0x23CF, -0x008C, -0x5566,  0x31C7, -0x7FAB,  0x59F5,
    -0x6F63, -0x5A39, -0x5122,  0x3D41,  0x7006,  0x696B, -0x7AC1, -0x3F3E,
    -0x5E7E,  0x37CD, -0x30A7,  0x28E3,  0x5CCD, -0x1916, -0x485F, -0x4D3F,
    -0x79A1,  0x54FB, -0x1603,  0x1814,  0x5282, -0x0BF5, -0x72EB,  0x75CB,
     0x6007,  0x354D, -0x21F1,  0x5306,  0x628A, -0x40BD,  0x0EE9, -0x7977,
     0x5248,  0x7719,  0x34E4,  0x3163, -0x5D36, -0x2EA7,  0x0373, -0x7892,
    -0x6D46,  0x6E77,  0x4543,  0x1397,  0x0467, -0x3ABA,  0x001A,  0x7081,
    -0x0E00, -0x5EFD,  0x2CDC, -0x7273, -0x3921,  0x72B3, -0x34B3, -0x3A24,
    -0x3913, -0x0C29, -0x6574, -0x5BC1,  0x5CB6, -0x64FE, -0x4902, -0x3012,
     0x4B1F,  0x3A02,  0x149C, -0x6B5A,  0x5B9B,  0x268F,  0x730A, -0x02F7,
     0x416E,  0x3105, -0x23C0,  0x3DB4,  0x5BA9,  0x5FAD, -0x5257,  0x41F3,
    -0x4CB6, -0x531F, -0x50A4,  0x7274,  0x7912, -0x72A0,  0x0905, -0x6449,
     0x77E1, -0x0A01, -0x2CDB,  0x486A, -0x7B24, -0x75CF, -0x6ABF,  0x0934,
     0x5C6D, -0x0015,  0x570D, -0x2F1E, -0x2E1E, -0x5C88, -0x5085, -0x3D6D,
    -0x787B, -0x12F1,  0x686F,  0x11F5, -0x0378,  0x147F,  0x34CB,  0x0100,
     0x15C3,  0x04EA,  0x7F97, -0x6568, -0x152E,  0x0551,  0x6BD0, -0x703B,
    -0x5EC6, -0x3904, -0x4CFE, -0x5BB1, -0x3155, -0x3F44, -0x72D0, -0x08C4,
    -0x0D63,  0x4685,  0x143B, -0x3A65, -0x13CB,  0x2FF4, -0x15AF, -0x6B3D,
    -0x4726,  0x537F, -0x26BA, -0x055E,  0x71DC,  0x5E9C, -0x6C60, -0x6EA8,
    -0x18DA,  0x43A4,  0x736E,  0x3527, -0x461F, -0x2597,  0x52F2, -0x46B5,
     0x033E,  0x5248,  0x0EFC, -0x45B7, -0x0C5F,  0x5278,  0x1206,  0x0BE3,
     0x5C8C, -0x3C52, -0x2C29,  0x3B26
};


short  r_asm[R1C2];
short  r_c[R1C2];

int qs =  0x0000000C;

int main()
{   

/* ======================================================================== */
/*  Call hand-coded assembly version (located in DSP64x.lib library         */ 
/*  archive - see Project -> Build Options -> Linker -> Include Libraries)  */
/* ======================================================================== */   
    DSP_mat_mul(x, R1, C1, y, C2, r_asm, qs);
    
/* ======================================================================== */
/*  Call natural-C version                                                  */
/* ======================================================================== */
    DSP_mat_mul_c(x, R1, C1, y, C2, r_c, qs);

/* ======================================================================== */
/*  Compare outputs using mem_compare() in support.c.  If different,        */
/*  mem_compare() displays location of failures.                            */
/* ======================================================================== */
    test = mem_compare(r_asm, "r_asm", r_c, "r_c", sizeof(r_c));
    if (test == 0) 
    {
      printf("r_asm vs. r_c");
      printf("\nVerification successful.\n");
    }

}

/* ======================================================================== */
/*  End of file:  dsp_mat_mul_d.c                                           */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
