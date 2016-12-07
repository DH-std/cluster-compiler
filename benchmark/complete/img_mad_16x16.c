/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  IMGLIB  DSP Image/Video Processing Library                              */
/*                                                                          */
/*      Release:        Revision 1.04b                                      */
/*      CVS Revision:   1.8     Mon Jan 14 18:41:30 2002 (UTC)              */
/*      Snapshot date:  23-Oct-2003                                         */
/*                                                                          */
/*  This library contains proprietary intellectual property of Texas        */
/*  Instruments, Inc.  The library and its source code are protected by     */
/*  various copyrights, and portions may also be protected by patents or    */
/*  other legal protections.                                                */
/*                                                                          */
/*  This software is licensed for use with Texas Instruments TMS320         */
/*  family DSPs.  This license was provided to you prior to installing      */
/*  the software.  You may review this license by consulting the file       */
/*  TI_license.PDF which accompanies the files in this library.             */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */


/* ======================================================================= */
/*                                                                         */
/*  TEXAS INSTRUMENTS, INC.                                                */
/*                                                                         */
/*  NAME                                                                   */
/*      IMG_mad_16x16                                                      */
/*                                                                         */
/*  REVISION DATE                                                          */
/*      05-Jul-2001                                                        */
/*                                                                         */
/*  USAGE                                                                  */
/*      This routine is C-callable and can be called as:                   */
/*                                                                         */
/*      void IMG_mad_16x16                                                 */
/*      (                                                                  */
/*          const unsigned char *restrict refImg,                          */
/*          const unsigned char *restrict srcImg,                          */
/*          int pitch,                                                     */
/*          int                 h,                                         */
/*          int                 v,                                         */
/*          unsigned            *restrict match                            */
/*      )                                                                  */
/*                                                                         */
/*      refImg          Reference image.                                   */
/*      srcImg[256]     16x16 block image to look for.                     */
/*      pitch           Width of reference image.                          */
/*      h               Horiz. size of search area.                        */
/*      v               Vert.  size of search area. Must be multiple of 2. */
/*      match[2]        Result:                                            */
/*                          match[0] is packed x, y.                       */
/*                          match[1] is MAD value.                         */
/*                                                                         */
/*  DESCRIPTION                                                            */
/*      This routine returns the location of the minimum absolute          */
/*      difference between a 16x16 search block and some block in a        */
/*      (h + 16) x (v + 16) search area. h and v are the sizes of the      */
/*      search space for the top left coordinate of the search block.      */
/*      refImg points to the top left pixel of the search area.            */
/*                                                                         */
/*           (0,0)          (h,0)      (h+16,0)                            */
/*             ;--------------+--------;                                   */
/*             ;    search    |        ;                                   */
/*             ;    space     |        ;                                   */
/*             ;              |        ;        search area                */
/*             ;--------------+        ;        within reference image     */
/*           (0,v)          (h,v)      ;                                   */
/*             ;                       ;                                   */
/*             ;-----------------------;                                   */
/*           (0, v+16)                 (v+16,h+16)                         */
/*                                                                         */
/*      The location is returned relative to the above coordinate system   */
/*      as x and y packed in two 16-bit quantities in a 32-bit word:       */
/*                                                                         */
/*                  31             16 15             0                     */
/*                  +----------------+----------------+                    */
/*       match[0]:  |       x        |       y        |                    */
/*                  +----------------+----------------+                    */
/*                                                                         */
/*                  31                               0                     */
/*                  +---------------------------------+                    */
/*       match[1]:  |   SAD value at location x, y    |                    */
/*                  +---------------------------------+                    */
/*                                                                         */
/*  ASSUMPTIONS                                                            */
/*      srcImg and refImg do not alias in memory.                          */
/*      The routine is written for Little Endian configuration.            */
/*                                                                         */
/*  MEMORY NOTE                                                            */
/*      None.                                                              */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================= */

#include "IMG_mad_16x16.h"

void IMG_mad_16x16
(
    const unsigned char *restrict refImg,
    const unsigned char *restrict srcImg,
    int pitch,
    int h, int v,
    unsigned int *restrict match
)
{
    int i, j, x, y, matx, maty;
    unsigned matpos, matval;

    matval = ~0U;
    matx   = maty = 0;

    for (x = 0; x < h; x++)
        for (y = 0; y < v; y++)
        {
            unsigned acc = 0;

            for (i = 0; i < 16; i++)
                for (j = 0; j < 16; j++)
                    acc += abs(srcImg[i*16 + j] - refImg[(i+y)*pitch + x + j]);

            if (acc < matval)
            {
                matval = acc;
                matx   = x;
                maty   = y;
            }
        }

    matpos    = (0xffff0000 & (matx << 16)) | (0x0000ffff & maty);
    match[0] = matpos;
    match[1] = matval;
}

/* ======================================================================= */
/*  End of file:  img_mad_16x16.c                                          */
