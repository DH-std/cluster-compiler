/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      IMG_dilate_bin_d.c -- Example file for IMG_dilate_bin               */
/*                                                                          */
/*  USAGE                                                                   */
/*      This file contains code for demonstrating the C64x IMGLIB           */
/*      IMG_dilate_bin function. All inputs to the function contain         */
/*      random data. The assembly version of IMG_dilate_bin is called and   */
/*      the output is compared with the reference C code using              */
/*      mem_compare() in support.c.                                         */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
    
#include <stdio.h>
#include <stdlib.h>


/* Header file for the DSPLIB function */
#include "IMG_dilate_bin.h"
#include "support.h"

/* Header file for the C function */
void IMG_dilate_bin_c(const unsigned char * in_data, unsigned char * out_data, const char * mask, int cols);


/* ======================================================================== */
/*  Constant dataset.                                                       */
/* ======================================================================== */
#define N    (2048)
#define COLS (N/8)


/* ======================================================================== */
/*  Initialize arrays with random test data.                                */
/* ======================================================================== */
int   test = 0;
const unsigned char  in_data[N] = 
{
     0x1D,  0x76,  0x8D,  0x59,  0x2F,  0x62,  0x58,  0x2B,
     0xCB,  0x41,  0x4C,  0xC0,  0x34,  0xD2,  0x7E,  0x47,
     0x16,  0x45,  0x28,  0x6F,  0xAF,  0x47,  0x1A,  0x64,
     0x2A,  0xA2,  0x90,  0x66,  0x05,  0x2E,  0xF2,  0x9F,
     0x43,  0x1E,  0xEC,  0x2E,  0xF1,  0x6D,  0x2B,  0x54,
     0x7B,  0x23,  0x80,  0x3A,  0x74,  0xA5,  0x5C,  0xA1,
     0x9A,  0xC3,  0x38,  0x33,  0x70,  0x35,  0xFE,  0xDA,
     0x95,  0xBB,  0xF6,  0x44,  0x17,  0xF5,  0xDD,  0xA9,
     0xD4,  0xBE,  0x99,  0x0D,  0x35,  0x99,  0x49,  0xB9,
     0xAD,  0x53,  0x81,  0xA3,  0x77,  0x49,  0x36,  0x77,
     0xF8,  0xC3,  0x66,  0x03,  0xCD,  0xA7,  0x3D,  0xCA,
     0x12,  0x5A,  0x7F,  0x4A,  0x41,  0xE9,  0x78,  0xC4,
     0x2E,  0x38,  0x8A,  0x6A,  0x92,  0x45,  0x64,  0xD8,
     0x3D,  0x8F,  0x1D,  0x55,  0x38,  0xFA,  0xB8,  0x94,
     0x5E,  0xFC,  0xA8,  0x31,  0x7E,  0xD9,  0xB2,  0xD9,
     0x57,  0x0B,  0x04,  0xD0,  0xC4,  0xFA,  0xE4,  0x17,
     0x26,  0x9B,  0x11,  0x9B,  0x04,  0x9E,  0x7A,  0x8B,
     0x6E,  0x0A,  0xC1,  0xEE,  0x40,  0xFB,  0x23,  0x4B,
     0x2F,  0x8A,  0x3A,  0x52,  0x9B,  0xC3,  0x57,  0xAA,
     0xE6,  0x03,  0x3D,  0x0D,  0x4E,  0xBF,  0x4F,  0xAB,
     0xF3,  0x1F,  0x9C,  0x3A,  0x0E,  0xB3,  0x3F,  0x41,
     0xF0,  0x08,  0xDC,  0x09,  0xDC,  0x41,  0x86,  0x90,
     0x61,  0x56,  0x3A,  0xB9,  0xA8,  0xFE,  0x4D,  0xD0,
     0x0C,  0x7B,  0x07,  0xB2,  0xAA,  0x49,  0xD6,  0x1C,
     0x15,  0x9E,  0x3B,  0x59,  0xD7,  0xDB,  0xF0,  0x47,
     0xEA,  0x99,  0x39,  0x65,  0x68,  0x10,  0x79,  0xD1,
     0xFB,  0x3B,  0x45,  0xF6,  0xE2,  0x3D,  0x97,  0x10,
     0x20,  0x65,  0xE8,  0x2F,  0xCE,  0x24,  0x3C,  0x2D,
     0x98,  0xFE,  0x89,  0xE9,  0xC2,  0xDE,  0x07,  0xA5,
     0x95,  0xEA,  0xC6,  0xE2,  0x3D,  0xFC,  0xE6,  0xF1,
     0x4C,  0x5B,  0xBB,  0xD1,  0x47,  0xCF,  0xED,  0x73,
     0x94,  0xF6,  0x44,  0x14,  0xC9,  0xFB,  0xDD,  0xD8,
     0x50,  0x1C,  0x5E,  0xF0,  0x08,  0x68,  0x59,  0x04,
     0xE3,  0xAC,  0x56,  0xE7,  0xBF,  0xCE,  0x49,  0x03,
     0x44,  0x3C,  0x11,  0x4B,  0xDC,  0xA5,  0x3C,  0xAA,
     0x57,  0x94,  0xCB,  0x15,  0x0A,  0x62,  0x6C,  0x48,
     0x80,  0xAD,  0xDF,  0xF1,  0xCA,  0x49,  0x11,  0x31,
     0xB7,  0x1A,  0xD8,  0xA3,  0x02,  0xDD,  0x06,  0x2B,
     0x89,  0x0E,  0xB2,  0x1E,  0xB0,  0x62,  0x48,  0x47,
     0xFA,  0x8E,  0x93,  0x2C,  0x88,  0x56,  0xEE,  0x45,
     0x67,  0x95,  0x5F,  0x21,  0x1F,  0xF6,  0x1C,  0xA7,
     0x1F,  0x15,  0x80,  0xB4,  0x8A,  0x46,  0x34,  0x37,
     0xA6,  0xB4,  0x01,  0x3C,  0x18,  0xF9,  0xF3,  0x3C,
     0x2F,  0x36,  0x73,  0x63,  0x3F,  0xD6,  0x80,  0x98,
     0x46,  0x3C,  0x91,  0xD8,  0xA9,  0xDC,  0x6B,  0xB0,
     0x2D,  0xD6,  0x67,  0xAD,  0xB4,  0x93,  0x79,  0x62,
     0xF6,  0x04,  0xE6,  0xD4,  0xAF,  0x4D,  0xAB,  0x39,
     0x08,  0xD8,  0x0B,  0xB5,  0x96,  0x2F,  0x65,  0xD3,
     0x46,  0x5A,  0x99,  0xC2,  0x1A,  0xF7,  0xA9,  0x90,
     0xC9,  0xC0,  0x22,  0xFA,  0x2F,  0x4A,  0x62,  0xCD,
     0xB7,  0xBE,  0x76,  0x54,  0x8D,  0x60,  0x78,  0x52,
     0x8D,  0xFC,  0x02,  0x97,  0x18,  0x73,  0xCF,  0x18,
     0xD5,  0xB9,  0x6A,  0x56,  0x3C,  0x32,  0xC9,  0x4D,
     0x1D,  0xC2,  0xC5,  0xAA,  0x16,  0xE2,  0xCA,  0x2B,
     0xC6,  0xBE,  0x2C,  0xEC,  0x42,  0x86,  0x36,  0x75,
     0x18,  0x91,  0xFB,  0xA3,  0x0F,  0x8D,  0xF4,  0x47,
     0xEB,  0x75,  0xFB,  0x04,  0xFA,  0x0F,  0x04,  0x7A,
     0x0D,  0xDD,  0xEA,  0x99,  0x2C,  0xA3,  0xBB,  0x18,
     0x90,  0xE3,  0x3B,  0x14,  0x00,  0x25,  0x6F,  0x3A,
     0x03,  0x64,  0xBD,  0xDE,  0x7A,  0x8C,  0xEC,  0x20,
     0xBD,  0x34,  0xD0,  0xB2,  0xDE,  0x1F,  0xB4,  0x9C,
     0x37,  0x37,  0x1D,  0x76,  0xAF,  0xF3,  0x5A,  0xA4,
     0xA9,  0x39,  0x70,  0x91,  0x97,  0x7C,  0x5C,  0x78,
     0x21,  0x79,  0x15,  0x24,  0xE1,  0x8B,  0xC5,  0xD9,
     0x5F,  0xD2,  0x5D,  0xEE,  0x93,  0xBA,  0x96,  0xA0,
     0x01,  0x53,  0x4B,  0x32,  0x4C,  0x81,  0x5A,  0x90,
     0x95,  0xD0,  0x30,  0x7E,  0x99,  0xF1,  0x89,  0x37,
     0x82,  0xB7,  0xE3,  0x31,  0x85,  0xCF,  0x70,  0x9F,
     0xCF,  0x0D,  0xB6,  0x67,  0xDC,  0x82,  0xF7,  0xDD,
     0x39,  0xD7,  0x9A,  0x47,  0xAB,  0xE9,  0x6D,  0xBA,
     0x3A,  0xD0,  0x00,  0xD3,  0x49,  0x70,  0xA1,  0x68,
     0x09,  0x73,  0xE8,  0xD2,  0x70,  0x7E,  0xE0,  0x8E,
     0xF0,  0xA4,  0x1D,  0x25,  0x94,  0x39,  0x3B,  0x28,
     0xBC,  0x70,  0x40,  0x6C,  0x1C,  0x30,  0x44,  0x3C,
     0x80,  0x4C,  0x32,  0xEC,  0xC2,  0x47,  0xDD,  0xF6,
     0x4A,  0x4A,  0xBE,  0xAC,  0xDA,  0x8E,  0xFD,  0x98,
     0xF2,  0x75,  0xDD,  0x03,  0x1D,  0x4C,  0x51,  0x81,
     0xAE,  0x54,  0xC8,  0x1A,  0xE4,  0xB5,  0x87,  0xBB,
     0xA2,  0x47,  0x15,  0x96,  0xD9,  0x16,  0x98,  0xA6,
     0x37,  0xE3,  0x8C,  0x31,  0x78,  0x54,  0xD3,  0xD9,
     0xA6,  0x0C,  0xFC,  0xEA,  0xD6,  0xBE,  0x8D,  0xC2,
     0xBC,  0xD3,  0x4F,  0x81,  0x9D,  0x07,  0x5F,  0x64,
     0xA4,  0x73,  0x49,  0x1B,  0x42,  0x40,  0x89,  0x44,
     0x1B,  0xFB,  0xF1,  0x2A,  0x1B,  0x3F,  0x87,  0xE3,
     0x3E,  0x37,  0x49,  0x4A,  0x0D,  0xCB,  0x5E,  0xF1,
     0xEE,  0x88,  0x36,  0x56,  0x3E,  0x25,  0xFE,  0x1F,
     0x81,  0x2D,  0x9F,  0xC9,  0x6C,  0x6B,  0x20,  0xA7,
     0x60,  0x52,  0x99,  0x69,  0x35,  0x3C,  0x97,  0x75,
     0xFE,  0x03,  0x33,  0x59,  0xE6,  0xD9,  0x76,  0x91,
     0x84,  0xA0,  0xC8,  0x03,  0x38,  0xA4,  0xAB,  0x75,
     0x7A,  0x2B,  0x0F,  0x84,  0x9D,  0x85,  0x8D,  0x03,
     0xA4,  0xF2,  0x12,  0x1A,  0xB5,  0x42,  0xD6,  0x28,
     0x54,  0xC1,  0x00,  0x93,  0xCD,  0x36,  0xCA,  0x92,
     0x60,  0xBE,  0x57,  0xBA,  0x36,  0x3F,  0xD5,  0x9A,
     0x1A,  0x6C,  0x4B,  0xD0,  0xC9,  0xD3,  0xE4,  0x09,
     0x9A,  0x48,  0x53,  0x38,  0xC5,  0x88,  0xB6,  0x86,
     0xE2,  0x7D,  0xD1,  0xF1,  0xD4,  0x1D,  0xFF,  0x4C,
     0x7E,  0xF0,  0x4B,  0xE8,  0xF5,  0x55,  0xB0,  0x39,
     0x66,  0xD9,  0x5A,  0xE5,  0xAA,  0x8A,  0xEE,  0x5F,
     0x35,  0xA0,  0x75,  0x9D,  0xE1,  0xE2,  0x50,  0x1B,
     0xF4,  0x6B,  0x00,  0x70,  0x9E,  0x7C,  0xBB,  0x0B,
     0xF8,  0x45,  0xA8,  0x86,  0xBB,  0xCA,  0xCD,  0x65,
     0xB6,  0x24,  0xD4,  0x3A,  0x92,  0x72,  0x18,  0xE4,
     0xA8,  0x6E,  0x24,  0x35,  0xCC,  0xCC,  0xB3,  0xF1,
     0xE0,  0xD5,  0x51,  0x4D,  0x3C,  0x12,  0x59,  0xAB,
     0x19,  0x7A,  0x88,  0xD3,  0xEE,  0xD4,  0x3E,  0x3E,
     0xC1,  0x5D,  0x2A,  0x19,  0x77,  0x0D,  0x10,  0x45,
     0xAC,  0xFD,  0x43,  0xDA,  0xE7,  0x98,  0xFE,  0xFD,
     0xD6,  0xFB,  0x7B,  0x89,  0x8D,  0x49,  0x83,  0xC9,
     0xF9,  0x3D,  0x0E,  0xE3,  0x3F,  0x2C,  0xBD,  0xCC,
     0x4F,  0xC1,  0x88,  0xB1,  0xC3,  0xCC,  0x7B,  0x64,
     0x92,  0xEC,  0x48,  0x43,  0x5A,  0x48,  0xB0,  0xFF,
     0xA1,  0x71,  0x7C,  0x2A,  0x95,  0x5D,  0x30,  0x03,
     0x2A,  0x8A,  0x44,  0x9C,  0x01,  0x33,  0x5B,  0x83,
     0x21,  0x45,  0xCE,  0x26,  0x5C,  0xCC,  0x59,  0x13,
     0xA9,  0x09,  0xCA,  0x9E,  0xA6,  0x91,  0xD2,  0x54,
     0xC6,  0x71,  0x52,  0xC1,  0x5C,  0x53,  0x8B,  0xC6,
     0xF2,  0xA5,  0x7B,  0x8B,  0x0B,  0x75,  0x2D,  0xFF,
     0x7A,  0x53,  0x15,  0x2B,  0x6C,  0x9A,  0x8D,  0x9B,
     0x6C,  0x08,  0xC4,  0x4B,  0x0D,  0x86,  0x52,  0x35,
     0xA5,  0xAA,  0x7B,  0xAA,  0xBC,  0x2C,  0x38,  0x32,
     0x8D,  0x2A,  0x96,  0x1C,  0xC8,  0x17,  0x81,  0x6A,
     0xE2,  0x47,  0x53,  0x8F,  0x61,  0x83,  0x08,  0x96,
     0xFC,  0x8B,  0x10,  0x2F,  0x56,  0x6E,  0x2F,  0xED,
     0xF6,  0x09,  0xCF,  0x95,  0xB5,  0xEB,  0x85,  0x8C,
     0x04,  0xB1,  0xCF,  0xB5,  0xD5,  0xB5,  0x22,  0x1A,
     0x8B,  0x23,  0x90,  0x5A,  0xB0,  0xE9,  0x17,  0x99,
     0x6D,  0x09,  0x94,  0x36,  0x77,  0x40,  0xE8,  0x76,
     0x3A,  0xF4,  0x35,  0xCF,  0xBF,  0xE1,  0xFA,  0xC1,
     0x06,  0x96,  0x6E,  0x32,  0xCA,  0x22,  0x0E,  0xDD,
     0xEB,  0xF7,  0x2C,  0xE2,  0xD2,  0x26,  0x5B,  0x35,
     0x58,  0x0E,  0xA5,  0x67,  0x8C,  0x4A,  0xAD,  0x16,
     0x9B,  0x88,  0x9F,  0xC1,  0x92,  0xC0,  0xD5,  0x7C,
     0x5D,  0x50,  0xFA,  0x3D,  0x94,  0x92,  0x40,  0x76,
     0x00,  0x8D,  0xC2,  0x62,  0xFE,  0x74,  0xE2,  0xBF,
     0x3E,  0x50,  0x1F,  0x27,  0xC1,  0x81,  0xD5,  0x5E,
     0xB2,  0x45,  0xEA,  0x43,  0xEE,  0xFB,  0xE4,  0x4A,
     0x5E,  0xE7,  0x58,  0x10,  0xF4,  0xAF,  0xFB,  0xC6,
     0xBC,  0xBF,  0x1B,  0x91,  0x21,  0x60,  0xE8,  0x70,
     0x3D,  0x22,  0xB4,  0x11,  0x7F,  0xFB,  0x1E,  0x20,
     0xC2,  0xBE,  0x0A,  0x1C,  0xE6,  0xEE,  0x46,  0x53,
     0xFA,  0x01,  0x61,  0x0D,  0x94,  0x17,  0x18,  0x34,
     0x29,  0x16,  0xB4,  0xC3,  0x90,  0x42,  0xB9,  0x55,
     0x87,  0xBD,  0xEB,  0xF5,  0x90,  0x0C,  0x2F,  0xDC,
     0xDC,  0xBB,  0x0C,  0x54,  0x20,  0x48,  0x96,  0x1F,
     0xC7,  0x06,  0x77,  0xC2,  0x45,  0xC0,  0xD7,  0xB3,
     0xAF,  0x14,  0x5F,  0xFC,  0xFD,  0x47,  0x3D,  0x8E,
     0x30,  0xDE,  0x59,  0x7B,  0x8C,  0x97,  0xD9,  0x14,
     0x6D,  0x52,  0x71,  0xBC,  0x93,  0x4B,  0xF2,  0xF0,
     0xA9,  0xE2,  0x7D,  0xC6,  0xC9,  0xC9,  0xC0,  0x0C,
     0x10,  0xC3,  0x75,  0x91,  0x25,  0x7C,  0xA6,  0x60,
     0xC2,  0x49,  0x8C,  0xE0,  0x2B,  0xFB,  0xAC,  0x17,
     0xC0,  0x84,  0x5A,  0x3A,  0x46,  0x48,  0x71,  0x2C,
     0x79,  0xDA,  0xD1,  0xFA,  0xCB,  0x31,  0xF8,  0xC8,
     0x88,  0xF2,  0x1B,  0xC4,  0xB6,  0x60,  0xC0,  0x96,
     0x25,  0x99,  0x2E,  0x57,  0xF9,  0x36,  0x3E,  0xB9,
     0xE6,  0xC4,  0x07,  0x58,  0x8B,  0xEE,  0x74,  0x57,
     0x46,  0xFE,  0xBC,  0xAB,  0x65,  0xFB,  0xAC,  0x5A,
     0xA2,  0xB2,  0x25,  0xE1,  0xFF,  0x8C,  0x70,  0xB6,
     0x4C,  0xEC,  0xD9,  0x8E,  0xDC,  0xA5,  0xC6,  0x83,
     0x91,  0x06,  0x37,  0x93,  0x34,  0xDD,  0x64,  0x1F,
     0x96,  0xB5,  0xCA,  0x15,  0xD1,  0x32,  0xF3,  0xEB,
     0x36,  0x8D,  0x01,  0x5F,  0xD0,  0xD3,  0xCA,  0x83,
     0x35,  0xEE,  0x23,  0xCF,  0xFE,  0xF6,  0x78,  0xCC,
     0x59,  0xBA,  0xCA,  0xE8,  0x46,  0x00,  0x54,  0xF7,
     0x3E,  0xDC,  0xA8,  0xC7,  0xAC,  0x61,  0xC1,  0x68,
     0x14,  0xEF,  0x43,  0x7D,  0x1F,  0x79,  0x5A,  0x54,
     0xB3,  0xB4,  0x5E,  0x45,  0x94,  0xBF,  0x20,  0x45,
     0xEB,  0x47,  0x4A,  0x28,  0xAC,  0x36,  0xFE,  0xCA,
     0x45,  0x06,  0xE9,  0x68,  0x59,  0xEF,  0x55,  0x31,
     0xE0,  0x4E,  0x3D,  0xE6,  0xE5,  0xEB,  0x07,  0xB9,
     0x88,  0xFA,  0x8C,  0xE1,  0x01,  0x3E,  0x8B,  0x7D,
     0xAD,  0x81,  0xBE,  0x87,  0x65,  0xC1,  0xB7,  0x32,
     0x4F,  0x4E,  0x48,  0x5B,  0x06,  0xE1,  0xAF,  0x02,
     0x91,  0x8B,  0x32,  0xD2,  0xC0,  0x80,  0x21,  0xF3,
     0x48,  0x2D,  0x0B,  0x60,  0xD4,  0xC2,  0x2E,  0xCC,
     0x48,  0x91,  0x55,  0xEE,  0xAE,  0xFA,  0xB6,  0xCE,
     0x19,  0x48,  0xDB,  0xC7,  0xC9,  0x8D,  0x93,  0x8C,
     0x2C,  0x07,  0x9D,  0x28,  0xC3,  0xCC,  0x13,  0xBC,
     0x8A,  0xDC,  0x73,  0xF5,  0x23,  0x40,  0x95,  0x32,
     0x9E,  0xDB,  0x67,  0x92,  0xA8,  0xD7,  0x4D,  0x1E,
     0x84,  0x83,  0xBF,  0x81,  0x59,  0xAB,  0x82,  0x3C,
     0x1D,  0xF6,  0x09,  0x24,  0x15,  0xEF,  0x3A,  0xDF,
     0xEC,  0xF7,  0x2A,  0x0D,  0xCB,  0x8D,  0x19,  0xAE,
     0xB8,  0x5C,  0x4D,  0x46,  0x00,  0xB0,  0x7F,  0x79,
     0xAA,  0x2F,  0xB3,  0x51,  0xE6,  0x59,  0x46,  0xB7,
     0xC7,  0x6A,  0x00,  0xFB,  0xC0,  0x76,  0x5D,  0x23,
     0x5A,  0x71,  0x2E,  0xBB,  0xFF,  0xC1,  0x55,  0x7B,
     0x10,  0x00,  0x85,  0x0F,  0x11,  0xD8,  0x7F,  0x8D,
     0x7D,  0x52,  0x30,  0x1D,  0x94,  0x86,  0x7C,  0x84,
     0xBE,  0x94,  0x96,  0xFF,  0x43,  0x42,  0x50,  0x07,
     0x27,  0xAF,  0x90,  0x42,  0xC1,  0x47,  0xE7,  0xC8,
     0xDB,  0x74,  0xB8,  0x7E,  0xFF,  0x71,  0x93,  0xF2,
     0x7B,  0x1B,  0x6E,  0x75,  0x05,  0x3D,  0xA0,  0x65,
     0x2D,  0xC2,  0xFC,  0xCB,  0x5F,  0xF8,  0x3C,  0xCE,
     0x78,  0x59,  0x2D,  0x40,  0xAF,  0x15,  0xF2,  0x59,
     0xAD,  0xEA,  0x0B,  0x46,  0x58,  0x17,  0xDC,  0x52,
     0xE8,  0xCD,  0xE3,  0xFE,  0x8D,  0x68,  0x2A,  0xEC,
     0xE9,  0x95,  0xB1,  0xE7,  0xA1,  0x7D,  0x04,  0x59,
     0x71,  0x04,  0x10,  0xFA,  0xB4,  0x85,  0xE3,  0x9C,
     0x1A,  0x61,  0x48,  0x94,  0xA7,  0xCC,  0x82,  0x99,
     0x18,  0xC3,  0xB5,  0x3F,  0x7E,  0x70,  0x21,  0xAE,
     0xB3,  0xEB,  0xC8,  0x71,  0x29,  0xF3,  0x58,  0x5C,
     0xB9,  0x30,  0x12,  0x4A,  0x11,  0x67,  0x01,  0xB4,
     0xB9,  0xDA,  0x5D,  0xA9,  0x91,  0xAE,  0xC8,  0xC4,
     0x45,  0x0E,  0xA2,  0x4D,  0x0F,  0x4A,  0xBD,  0xBB,
     0x24,  0x0B,  0xBE,  0x4A,  0x30,  0xC9,  0xE8,  0x54,
     0xC6,  0x20,  0x2B,  0xAC,  0x43,  0xAA,  0x3E,  0xEA,
     0x1B,  0x0F,  0xB0,  0x35,  0xE1,  0xF6,  0x81,  0xB0,
     0x75,  0x28,  0xDE,  0xDF,  0x64,  0x6D,  0x8D,  0xB9,
     0xCB,  0x85,  0x69,  0x3D,  0xC7,  0x4D,  0x40,  0xE0,
     0x75,  0x11,  0xFA,  0xF0,  0x4A,  0x3C,  0xCC,  0x1B,
     0x2C,  0x1F,  0xC6,  0xF2,  0x1D,  0xC6,  0x6D,  0x88,
     0xE7,  0x47,  0x61,  0x36,  0x30,  0x35,  0x9C,  0x37,
     0xF2,  0x46,  0x7D,  0xB1,  0x59,  0x4C,  0xC1,  0xDB,
     0x75,  0x41,  0x03,  0x05,  0xCC,  0x8C,  0xFB,  0x8E,
     0x7E,  0xB3,  0xC3,  0x00,  0x10,  0x34,  0xF9,  0x3D,
     0x91,  0xC2,  0x30,  0x74,  0x76,  0x24,  0x23,  0xAE,
     0x93,  0x70,  0x1D,  0x4E,  0x62,  0x34,  0x4B,  0xD5,
     0xF7,  0x56,  0x1A,  0x72,  0x8F,  0x36,  0xD8,  0xC2,
     0x0B,  0x1D,  0x38,  0x86,  0xD4,  0x29,  0xE5,  0x91,
     0x2F,  0x12,  0x1B,  0xCC,  0xE5,  0x9B,  0x3A,  0xB4,
     0xF9,  0x63,  0x10,  0x32,  0xEA,  0x48,  0x02,  0x4F,
     0x31,  0x9B,  0x90,  0xE0,  0xD7,  0x59,  0x12,  0xA3,
     0xD4,  0xF2,  0xCD,  0x09,  0xDC,  0x85,  0x51,  0x32,
     0x55,  0xEF,  0x66,  0x14,  0x55,  0x6F,  0x13,  0xE0,
     0x94,  0x81,  0xFF,  0x1C,  0x3B,  0x54,  0xB9,  0x55,
     0x2E,  0x94,  0x8A,  0x55,  0x20,  0x15,  0xA9,  0xBE,
     0xFF,  0x98,  0x3E,  0x14,  0x71,  0x09,  0xAA,  0x68,
     0x15,  0x00,  0xF7,  0x39,  0xD9,  0xEB,  0x33,  0xE0,
     0x6E,  0x2B,  0x4B,  0x1F,  0x52,  0x73,  0x8B,  0xE1,
     0x63,  0x73,  0x10,  0x82,  0xB3,  0xB6,  0xD7,  0xD9,
     0xD4,  0x4E,  0x2C,  0x93,  0x3D,  0x8F,  0x02,  0xD1,
     0xB2,  0xA5,  0x6C,  0x16,  0xF8,  0xC2,  0x37,  0x3C,
     0xD6,  0x79,  0xFA,  0x51,  0x8D,  0x55,  0x0D,  0x8E,
     0x9D,  0xDC,  0x57,  0xBC,  0x97,  0xFE,  0xCB,  0x83,
     0x2E,  0x35,  0x40,  0x78,  0x3F,  0x09,  0x45,  0xB1,
     0xDE,  0x64,  0xAB,  0x25,  0x7B,  0x5E,  0x9B,  0x52,
     0xB8,  0x26,  0x37,  0xFC,  0x1B,  0x95,  0xAC,  0x27,
     0xB5,  0x87,  0xB8,  0x10,  0x61,  0x26,  0x9E,  0x15,
     0xD7,  0xC5,  0x2C,  0x1B,  0xCC,  0xC9,  0xE0,  0x51,
     0x04,  0x5E,  0x68,  0x9A,  0x5E,  0x22,  0x04,  0xF7,
     0x1D,  0x3D,  0xEA,  0xD5,  0xA4,  0x95,  0xAD,  0x76,
     0x8D,  0x3B,  0xDC,  0xFD,  0x63,  0xFA,  0x17,  0xA0,
     0x52,  0x46,  0xF6,  0xDE,  0x05,  0x90,  0x3B,  0xF1,
     0x24,  0x6B,  0x1C,  0x5A,  0x59,  0x10,  0x96,  0x55,
     0x5C,  0xF4,  0xE1,  0xAB,  0xAC,  0x62,  0x59,  0xF4,
     0xE7,  0xA2,  0xA8,  0x4A,  0xB3,  0xAB,  0xA7,  0x50,
     0x90,  0xBD,  0x20,  0x92,  0x4B,  0xE9,  0xAC,  0xC5,
     0xB4,  0x49,  0xF8,  0x53,  0x88,  0x58,  0xC4,  0x75,
     0x77,  0x4C,  0x10,  0x20,  0x3B,  0x24,  0xC1,  0xC0,
     0x7A,  0x77,  0x4D,  0x81,  0x93,  0xBD,  0x3A,  0xBE,
     0x14,  0xD1,  0x23,  0x1D,  0x32,  0x4B,  0x3D,  0x90,
     0x16,  0x64,  0x43,  0xB7,  0xB1,  0x51,  0x30,  0xF8,
     0x25,  0xE2,  0x65,  0xDF,  0x3C,  0x94,  0xB4,  0x6B,
     0xDE,  0x86,  0x1D,  0x86,  0xB4,  0xAB,  0x3F,  0xB3
};

unsigned char  out_data_asm[COLS];
unsigned char  out_data_c[COLS];

const char  mask[9] = 
{
    -1, 1, -1,
     1, 1,  1,
    -1, 1, -1
};


int main()
{   

/* ======================================================================== */
/*  Call hand-coded assembly version (located in IMG64x.lib library         */ 
/*  archive - see Project -> Build Options -> Linker -> Include Libraries)  */
/* ======================================================================== */   
    settime();
    IMG_dilate_bin(in_data, out_data_asm, mask, COLS);
    gettime();
    
/* ======================================================================== */
/*  Call natural-C version                                                  */
/* ======================================================================== */
    IMG_dilate_bin_c(in_data, out_data_c, mask, COLS);

/* ======================================================================== */
/*  Compare outputs using mem_compare() in support.c.  If different,        */
/*  mem_compare() displays location of failures.                            */
/* ======================================================================== */
    test = mem_compare(out_data_asm, "out_data_asm", out_data_c, "out_data_c", sizeof(out_data_c));
    if (test == 0) 
    {
      printf("out_data_asm vs. out_data_c");
      printf("\nVerification successful.\n");
    }

}

/* ======================================================================== */
/*  End of file:  img_dilate_bin_d.c                                        */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
