/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      IMG_idct_8x8_12q4_d.c -- Example file for IMG_idct_8x8_12q4         */
/*                                                                          */
/*  USAGE                                                                   */
/*      This file contains code for demonstrating the C64x IMGLIB           */
/*      IMG_idct_8x8_12q4 function. All inputs to the function contain      */
/*      random data. The assembly version of IMG_idct_8x8_12q4 is called    */
/*      and the output is compared with the reference C code using          */
/*      mem_compare() in support.c.                                         */
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
#include "IMG_idct_8x8_12q4.h"

/* Header file for the C function */
void IMG_idct_8x8_12q4_c(short * idct_data, unsigned NUM_IDCTS);

/* ======================================================================== */
/*  IMGLIB function-specific alignments. Refer to the                       */
/*  TMS320C64x IMG Library Programmer's Reference for details.              */
/* ======================================================================== */
#pragma DATA_ALIGN(idct_data_asm, 8);
#pragma DATA_ALIGN(idct_data_c, 8);

/* ======================================================================== */
/*  Constant dataset.                                                       */
/* ======================================================================== */
#define num_idcts    (6)


/* ======================================================================== */
/*  Initialize arrays with random test data.                                */
/* ======================================================================== */
int     test = 0;
short  idct_data_asm[384] = 
{
     0x5F3D,  0x4D16, -0x3F33, -0x5476,  0x16FC,  0x5217, -0x7253, -0x7F51,
    -0x3992, -0x3E5D,  0x2243,  0x1C0B,  0x2FE9,  0x7698,  0x6C99,  0x0810,
     0x1BB4, -0x7339,  0x2277,  0x0F09,  0x1EEA, -0x57FB,  0x3B0B, -0x21C0,
    -0x019F, -0x232C, -0x0506, -0x1B12,  0x50AE,  0x7097,  0x6D4B,  0x3474,
    -0x0462,  0x2FE1,  0x08BD,  0x6284, -0x2F43, -0x772B,  0x1118,  0x6BF3,
    -0x495D, -0x3889, -0x2016,  0x1440, -0x5614,  0x376D,  0x2E3A,  0x3F14,
     0x4F0F,  0x5E38,  0x7AEF, -0x2246,  0x3979, -0x5A82, -0x496A,  0x1936,
    -0x3E2B,  0x1F6E,  0x3949, -0x3C79, -0x5982,  0x25C9, -0x304E,  0x530F,
     0x3D43,  0x19D9, -0x362D, -0x5C2D,  0x531A,  0x6C02, -0x03CE,  0x4641,
     0x006C, -0x6197, -0x2157,  0x364F, -0x5489,  0x3C76, -0x6758, -0x58CF,
    -0x7BDD, -0x2A83,  0x6967, -0x3DB7,  0x3B59, -0x4579,  0x571C,  0x29C8,
     0x5D3D, -0x09F1,  0x6EEA, -0x26FB, -0x7E8B,  0x1C09, -0x1251,  0x4CEC,
    -0x627B,  0x47D4, -0x070C, -0x3348, -0x3FE4, -0x1DA4,  0x0041, -0x0CD4,
     0x1F2A, -0x2E5B, -0x6F59, -0x2617, -0x7BC2, -0x06AA,  0x3E2B, -0x3BA1,
    -0x740B,  0x68B3, -0x55A9, -0x5EBD,  0x70D7, -0x6EAB,  0x4103,  0x419F,
    -0x5243,  0x23E8, -0x1FDA,  0x2560,  0x7C11,  0x62A3,  0x1ADD,  0x247B,
     0x1CEA, -0x1163,  0x77A1,  0x6B73, -0x4D8F,  0x6633, -0x5359, -0x0020,
     0x05C9,  0x2E29, -0x6909, -0x17D5,  0x1E44, -0x4BFE, -0x2AF0, -0x0F57,
     0x79A5, -0x3CC3, -0x2BA6, -0x0F46, -0x6BA0,  0x570A,  0x45E5, -0x2253,
     0x6A60, -0x2027,  0x41D0, -0x2FB1, -0x53DD,  0x7C4D,  0x3EF3,  0x137E,
     0x2C2D,  0x40AB, -0x2DE2, -0x5AFA,  0x570C,  0x2CD4, -0x29BF, -0x2103,
     0x20C3,  0x6617,  0x2356, -0x6241,  0x3429,  0x3BAA,  0x72F0,  0x776A,
     0x0618,  0x30B1, -0x16A7,  0x340C, -0x1F49, -0x4C5F, -0x0DDF, -0x4169,
     0x280B,  0x36FE, -0x042B, -0x2C04,  0x55FD,  0x3B97, -0x3AF6,  0x3461,
    -0x69DA, -0x21A4, -0x35B6,  0x632C, -0x6B86,  0x7C17,  0x6DC9,  0x2EB3,
     0x66B0, -0x3A5C,  0x552E, -0x5EB0, -0x5C28,  0x77D8,  0x4495,  0x6AED,
     0x0CC9, -0x4779,  0x00AF,  0x7D23,  0x5510,  0x3032,  0x42AC,  0x209D,
    -0x6BBF, -0x41DA, -0x51A4,  0x3352, -0x08C6, -0x4728,  0x50C6,  0x1A37,
    -0x3ED8,  0x463A,  0x3AA7, -0x3E0D, -0x6789, -0x208C,  0x2DBD, -0x6568,
    -0x1129, -0x7CD5, -0x028D,  0x14CC,  0x570C,  0x7147,  0x5703, -0x571F,
    -0x43BB,  0x7F07, -0x7D45,  0x6597, -0x384B, -0x3601,  0x77AB, -0x2485,
    -0x78D6,  0x23AA,  0x6CF5,  0x644F,  0x3AA0, -0x04F3, -0x5622, -0x212F,
    -0x12C4, -0x4245, -0x36EB,  0x3C8E,  0x7836, -0x6ACB, -0x44BF, -0x3F48,
    -0x64B3,  0x2FF1,  0x63CC, -0x1716,  0x5327,  0x39E6, -0x1EDB, -0x76CA,
    -0x042E, -0x25F8,  0x785D,  0x0D41,  0x1F99, -0x1719, -0x66BD, -0x462F,
     0x666B,  0x0C2D,  0x1E61,  0x4FE9,  0x3492, -0x36D7,  0x7F86,  0x1876,
    -0x2935,  0x3112, -0x0445,  0x21CD,  0x41E4, -0x31C7, -0x5977, -0x5095,
     0x4B21, -0x5004,  0x788C,  0x2A89,  0x5BEB,  0x3D9E, -0x766E, -0x3635,
     0x6FB8, -0x6515,  0x77F2, -0x5F41,  0x5F69,  0x7AA1,  0x1333, -0x4982,
     0x4A3C, -0x2346, -0x58A0,  0x74FE, -0x6C56,  0x1962,  0x6439,  0x52B2,
     0x4733, -0x7184,  0x13A6, -0x403E,  0x0AE6,  0x33D0, -0x35C6,  0x755D,
     0x1E05,  0x5F9E,  0x0601, -0x59B1, -0x4A77,  0x7F3D,  0x3CFA,  0x1B83,
    -0x4941,  0x115D, -0x67D0, -0x2CA5, -0x1C6A, -0x73B0,  0x03AB, -0x7D82,
     0x7A51, -0x322D,  0x3B1A, -0x4D34,  0x20DF, -0x4317, -0x699A,  0x63C7,
     0x1AC0,  0x1496,  0x4493, -0x29E8,  0x7E4D,  0x332A, -0x63A7,  0x3E5C,
     0x420E, -0x38E0,  0x4991,  0x6A25, -0x7179,  0x3F24,  0x05B4, -0x0CD0,
     0x4F45,  0x575F,  0x0D80, -0x1914,  0x59D1, -0x1213, -0x601E, -0x283F,
    -0x4FFB, -0x2529,  0x6293,  0x277F,  0x17CD, -0x645D,  0x037D,  0x3C39
};
short  idct_data_c[384];


int main()
{   
/* ------------------------------------------------------------------------ */
/*  Duplicate input for natural-C function call.                            */
/* ------------------------------------------------------------------------ */
    memcpy(idct_data_c, idct_data_asm, sizeof(idct_data_asm));

/* ======================================================================== */
/*  Call hand-coded assembly version (located in IMG64x.lib library         */ 
/*  archive - see Project -> Build Options -> Linker -> Include Libraries)  */
/* ======================================================================== */   
    IMG_idct_8x8_12q4(idct_data_asm, num_idcts);
    
/* ======================================================================== */
/*  Call natural-C version                                                  */
/* ======================================================================== */
    IMG_idct_8x8_12q4_c(idct_data_c, num_idcts);

/* ======================================================================== */
/*  Compare outputs using mem_compare() in support.c.  If different,        */
/*  mem_compare() displays location of failures.                            */
/* ======================================================================== */
    test = mem_compare(idct_data_asm, "idct_data_asm", idct_data_c, "idct_data_c", sizeof(idct_data_c));
    if (test == 0) 
    {
      printf("idct_data_asm vs. idct_data_c");
      printf("\nVerification successful.\n");
    }

}

/* ======================================================================== */
/*  End of file:  img_idct_8x8_12q4_d.c                                     */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
