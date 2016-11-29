/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  DSPLIB  DSP Signal Processing Library                                   */
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


/* ======================================================================== */
/*  NAME                                                                    */
/*      DSP_blk_eswap16 -- Endian-swap a block of 16-bit values             */
/*                                                                          */
/*  REVISION DATE                                                           */
/*      12-Aug-2001                                                         */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine has the following C prototype:                         */
/*                                                                          */
/*          void DSP_blk_eswap16                                            */
/*          (                                                               */
/*              void *restrict src,     // Source data                  //  */
/*              void *restrict dst,     // Destination array            //  */
/*              int  n_hwords           // Number of half-words to swap //  */
/*          );                                                              */
/*                                                                          */
/*      This function performs an endian-swap on the data in the "src"      */
/*      array, writing the results to "dst".  If NULL is passed in for      */
/*      the destination, then the endian-swap is performed in-place.        */
/*      The "n_hwords" argument gives the total length of the array, in     */
/*      half-words.                                                         */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      The data in the "src" array is endian swapped, meaning that the     */
/*      byte-order of the bytes within each word of the src[] array is      */
/*      reversed.  This is meant to facilitate moving big-endian data       */
/*      to a little-endian system or vice-versa.                            */
/*                                                                          */
/*      When the "dst" pointer is non-NULL, the endian-swap occurs          */
/*      out-of-place, similar to a block move.  When the "dst" pointer      */
/*      is NULL, the endian-swap occurs in-place, allowing the swap to      */
/*      occur without using any additional storage.                         */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      Input and output arrays do not overlap, except in the very          */
/*      specific case that "dst == NULL" so that the operation occurs       */
/*      in-place.                                                           */
/*                                                                          */
/*  NOTES                                                                   */
/*      n/a                                                                 */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

void DSP_blk_eswap16_c
(
    void *restrict src,
    void *restrict dst,
    int  n_hwords
)
{
    int i;
    char *_src, *_dst;

    if (dst)
    {
        _src = (char *)src;
        _dst = (char *)dst;
    } else
    {
        _src = (char *)src;
        _dst = (char *)src;
    }

    for (i = 0; i < n_hwords; i++)
    {
        char t0, t1;
        t0 = _src[i*2 + 1];
        t1 = _src[i*2 + 0];
        _dst[i*2 + 0] = t0;
        _dst[i*2 + 1] = t1;
    }
}

/* ======================================================================== */
/*  End of file:  dsp_blk_eswap16.c                                         */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
