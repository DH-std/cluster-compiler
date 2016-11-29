/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_neg32_d.c -- Example file for DSP_neg32                         */
/*                                                                          */
/*  USAGE                                                                   */
/*      This file contains code for demonstrating the C64x DSPLIB           */
/*      DSP_neg32 function. All inputs to the function contain random       */
/*      data. The assembly version of DSP_neg32 is called and the output    */
/*      is compared with the reference C code using mem_compare() in        */
/*      support.c.                                                          */
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
#include "DSP_neg32.h"    

/* Header file for the C function */
void DSP_neg32_c(int * x, int * r, short nx);

/* ======================================================================== */
/*  DSPLIB function-specific alignments. Refer to the                       */
/*  TMS320C64x DSP Library Programmer's Reference for details.              */
/* ======================================================================== */
#pragma DATA_ALIGN(x_asm, 8);
#pragma DATA_ALIGN(x_c, 8);
#pragma DATA_ALIGN(r_asm, 8);
#pragma DATA_ALIGN(r_c, 8);

/* ======================================================================== */
/*  Constant dataset.                                                       */
/* ======================================================================== */
#define N    (256)


/* ======================================================================== */
/*  Initialize arrays with random test data.                                */
/* ======================================================================== */
int     test = 0;
int  x_asm[N] = 
{
     0x3104521E,  0x4B8AD6BF,  0x5B22DF04, -0x1CB3E263,
    -0x29CBF198, -0x59BB84A2,  0x69A21107, -0x77C3D2AC,
    -0x5FAE0476, -0x4964FB64,  0x4170AE36, -0x38CF2BE9,
    -0x66E180CD, -0x3407FF54,  0x3CC01B95,  0x598620BE,
     0x17DD1F86, -0x515F4FE5,  0x40B1B483,  0x29F23F7F,
     0x3DBC5B8A, -0x717F354D, -0x5273A0F9,  0x6742479A,
     0x7FBDE01E,  0x7B37E91F,  0x049AECAE, -0x75BF7D21,
     0x27B39148,  0x42B85805, -0x7B5D8D83, -0x6D3C9BC3,
     0x24308447, -0x3E56600B,  0x19EF2642, -0x05070664,
    -0x3E926933, -0x701C029E, -0x67E15F67, -0x14C7372C,
     0x47857F14, -0x597BEC57, -0x0E76BE66, -0x5A1A685C,
     0x4F3B8E6B,  0x7F7C9015,  0x1B5CBAD2,  0x0C192BE7,
    -0x05D52DAE,  0x3139DC61,  0x0199A7F1, -0x695953AA,
    -0x4BDADB1F,  0x7E6CFC1F, -0x7BC52569, -0x6471BAEC,
    -0x17BC8701, -0x0B6CC065, -0x4F6243D0, -0x4E06C164,
     0x50085EB7,  0x592BC591, -0x3E2D0D35, -0x3FCDEBF8,
     0x286037F7,  0x36793CE0,  0x31DEF547, -0x643A2D75,
    -0x0F8C5536,  0x21FF1919,  0x5420F64C,  0x5F13F8DB,
     0x7B9B47D3, -0x0965B6BF,  0x2A8B93B4, -0x14884DB2,
    -0x02A521B0, -0x7866BFFF, -0x44F485E7, -0x5402CA52,
    -0x0FBC7FD3,  0x3796C6E7, -0x22E31853,  0x0E8B55BE,
     0x0C5A326A, -0x1C85FE6A, -0x1CEF634B, -0x0C5591BE,
     0x35CB7566, -0x15E0EE4B, -0x13B17CD9,  0x335380EE,
     0x1EB6658A, -0x6CBDD4DE, -0x3FDCBB00, -0x5F552B87,
     0x65719291, -0x69F791F2,  0x3EF1B38B, -0x109BD2E7,
    -0x1A3EF1E1, -0x1E428B78,  0x297AC6AC,  0x017FADFE,
    -0x3BA85289, -0x3D61B174,  0x63960365, -0x6296071A,
    -0x507D2678, -0x27482740, -0x177FEA25, -0x295530B8,
     0x3970C54F, -0x5336026F, -0x09733814,  0x015E26AB,
    -0x4E27284F, -0x37FA1190, -0x7940F4D9, -0x65E0B80C,
     0x0E9F6C9D,  0x6F63648C, -0x384DF289,  0x79D5D866,
    -0x55AFBC59,  0x40D3E712, -0x35A3B37A,  0x12DC54EB,
     0x08EC657B,  0x4AD778C8,  0x49438246, -0x31FCF19B,
     0x17F92D2D,  0x7053A139, -0x026658E0,  0x18462D39,
    -0x5A78CC45, -0x14594246, -0x3BC683D6, -0x31DB6BBC,
    -0x6F79CE88, -0x43EC4E3E,  0x0FF4171A, -0x7FD4308B,
    -0x246C156C,  0x2CAF97BF, -0x3420865B, -0x0F1F4C50,
    -0x013CED8D,  0x3FD64BD5,  0x57ADCBB2, -0x74C0BD62,
     0x7D6B7AD0, -0x6EE9B57F,  0x38D9241E, -0x65BC3B70,
     0x08375326, -0x586736DC,  0x3EDF03FA, -0x55B6CD24,
     0x350FB731,  0x36940925, -0x79CCF276,  0x29147AAB,
     0x16800984, -0x5B88244B,  0x7CE4CD84,  0x5229F025,
    -0x63F535B6, -0x4894E830, -0x77D4CF20,  0x6522978A,
     0x1A5D3079, -0x7B5C75B2,  0x7B69411F,  0x1159FAED,
    -0x052A83F2,  0x76D4A619, -0x3C2585D5, -0x15618CA4,
     0x4C0D4FD9,  0x4F10F27F,  0x78811B9C,  0x7E8C4D0B,
    -0x1CC853CC, -0x5153D6B2,  0x70687ACD, -0x08A6AA0B,
    -0x052C2712, -0x22561CF3, -0x7F10DFE6,  0x5E9B9EDF,
    -0x1D488206,  0x3055CCB1, -0x22C34E07,  0x3440206E,
    -0x5B281DA3, -0x1618586B, -0x12DFCCD8,  0x0BF78338,
     0x2B5A73D3, -0x7CC7FDD8,  0x5253CCC4,  0x375E50F5,
     0x68C3E981,  0x1D3AF3F4,  0x12958841,  0x377D3FF2,
     0x6073566A, -0x7ADA7FD6, -0x21CC676A,  0x0A317548,
     0x3AA01FC5,  0x6A712145, -0x03001A2D,  0x2DA59B4A,
     0x3D29F3A7,  0x2FCB8905,  0x58C352EE, -0x7EF12B1C,
     0x0152591A, -0x4299DC0D, -0x57237D05,  0x1BA4CFF1,
     0x27B6119F,  0x67D9141F, -0x31067872, -0x29FB5573,
     0x502C2B67,  0x6A82F0BC, -0x1EA95041,  0x2663D584,
     0x7B1FB3CE,  0x1A023D19, -0x036054DD,  0x0C93E9D1,
     0x26C6D0D8,  0x1258C03D,  0x18E91229, -0x1738F778,
    -0x51C16857, -0x0E1B90B7, -0x15DCE26F,  0x7660F35D,
    -0x45077F36, -0x149CC9EA, -0x436B07C6,  0x68262260,
     0x348D3541,  0x1322DA81, -0x38CBA559,  0x18F2FD9F,
     0x42899293, -0x6CAFB395,  0x7688EA08, -0x2A89274D
};
int  x_c[N];

int  r_asm[N];
int  r_c[N];


int main()
{   
/* ------------------------------------------------------------------------ */
/*  Duplicate input for natural-C function call.                            */
/* ------------------------------------------------------------------------ */
    memcpy(x_c, x_asm, sizeof(x_asm));

/* ======================================================================== */
/*  Call hand-coded assembly version (located in DSP64x.lib library         */ 
/*  archive - see Project -> Build Options -> Linker -> Include Libraries)  */
/* ======================================================================== */   
    DSP_neg32(x_asm, r_asm, N);
    
/* ======================================================================== */
/*  Call natural-C version                                                  */
/* ======================================================================== */
    DSP_neg32_c(x_c, r_c, N);

/* ======================================================================== */
/*  Compare outputs using mem_compare() in support.c.  If different,        */
/*  mem_compare() displays location of failures.                            */
/* ======================================================================== */
    test = mem_compare(x_asm, "x_asm", x_c, "x_c", sizeof(x_c));
    if (test == 0) 
    {
      printf("x_asm vs. x_c");
      printf("\nVerification successful.\n");
    }

    test = mem_compare(r_asm, "r_asm", r_c, "r_c", sizeof(r_c));
    if (test == 0) 
    {
      printf("r_asm vs. r_c");
      printf("\nVerification successful.\n");
    }

}

/* ======================================================================== */
/*  End of file:  dsp_neg32_d.c                                             */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
