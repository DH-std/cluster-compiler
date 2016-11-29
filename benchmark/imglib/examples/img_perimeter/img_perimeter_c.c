/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  IMGLIB  DSP Image/Video Processing Library                              */
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
/*          Copyright (C) 2002 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */


/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      IMG_perimeter                                                       */
/*                                                                          */
/*  REVISION DATE                                                           */
/*      09-Apr-2001                                                         */
/*                                                                          */
/*  USAGE                                                                   */
/*      This function is C callable, and has the following prototype:       */
/*                                                                          */
/*          int IMG_perimeter                                               */
/*          (                                                               */
/*              const unsigned char *restrict in,  // Input image    //     */
/*              int cols,                          // Width of input //     */
/*              unsigned char       *restrict out  // Output image   //     */
/*          );                                                              */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This function returns the boundary pixels of an image.              */
/*      Each call of IMG_perimeter() calculates one new line of output      */
/*      from a three line window of input.                                  */
/*                                                                          */
/*      The input pointer "in" points to the middle line of a three-line    */
/*      window of the image.  The IMG_perimeter function scans this window  */
/*      looking for pixels in the middle row which are on the IMG_perimeter */
/*      of the image.  A pixel is on the IMG_perimeter of the image if      */
/*      the pixel itself is non-zero, but one of its neighbors is zero.     */
/*      The total count of IMG_perimeter pixels is returned.                */
/*                                                                          */
/*      This particular implementation evaluates four neighbors for         */
/*      the IMG_perimeter test:  The neighbors to the left, right, top      */
/*      and bottom.                                                         */
/*                                                                          */
/*      Perimeter pixels retain their original grey level in the            */
/*      output.  Non-IMG_perimeter pixels are set to zero in the output.    */
/*      Pixels on the far left and right edges of a row are defined         */
/*      as *not* being on the IMG_perimeter, and are always forced to       */
/*      zero.                                                               */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      The optimized implementations assume that the input and output      */
/*      arrays are double-word aligned.  They also assume that the          */
/*      input is a multiple of 16 pixels long.                              */
/*                                                                          */
/*  BIBLIOGRAPHY                                                            */
/*      Image Processing by Gonzalez and Woods.                             */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2002 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */





int IMG_perimeter_c
(
    const unsigned char *restrict in,
    int cols,
    unsigned char       *restrict out
)
{
    int i, count = 0;
    unsigned char pix_lft, pix_rgt, pix_top, pix_bot, pix_mid;

    for(i = 0; i < cols; i++)
    {
        pix_lft = in[i - 1];
        pix_mid = in[i + 0];
        pix_rgt = in[i + 1];

        pix_top = in[i - cols];
        pix_bot = in[i + cols];

        if (((pix_lft == 0) || (pix_rgt == 0) ||
             (pix_top == 0) || (pix_bot == 0)) && (pix_mid > 0))
        {
            out[i] = pix_mid;
            count++;
        } else
        {
            out[i] = 0;
        }
    }
    if (out[cols-1]) count--;
    if (out[0])      count--;
    out[0] = out[cols-1] = 0;

    return count;
}

/* ======================================================================== */
/*  End of file:  img_perimeter.c                                           */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2002 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
