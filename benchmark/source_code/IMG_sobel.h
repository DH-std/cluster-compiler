/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  IMGLIB  DSP Image/Video Processing Library                              */
/*                                                                          */
/*      Release:        Revision 1.04b                                      */
/*      CVS Revision:   1.6     Fri Oct 10 16:01:13 2003 (UTC)              */
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
/* ======================================================================== */
/*  Assembler compatibility shim for assembling 4.30 and later code on      */
/*  tools prior to 4.30.                                                    */
/* ======================================================================== */
/* ======================================================================== */
/*  End of assembler compatibility shim.                                    */
/* ======================================================================== */
/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      IMG_sobel, Little Endian.                                           */
/*                                                                          */
/*  REVISION DATE                                                           */
/*      10-Oct-2003                                                         */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*      void IMG_sobel                                                      */
/*      (                                                                   */
/*          const unsigned char *in_data,      // Input image data  //      */
/*          unsigned char       *out_data,     // Output image data //      */
/*          short cols, short rows             // Image dimensions  //      */
/*      )                                                                   */
/*                                                                          */
/*      The IMG_sobel filter is applied to the input image. The input image */
/*      dimensions are given by the arguments 'cols' and 'rows'.  The       */
/*      output image is 'cols' pixels wide and 'rows - 2' pixels tall.      */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*                                                                          */
/*      To see how the implementation is going to work on the input         */
/*      buffer, lets imagine we have the following input buffer:            */
/*                                                                          */
/*              yyyyyyyyyyyyyyyy                                            */
/*              yxxxxxxxxxxxxxxy                                            */
/*              yxxxxxxxxxxxxxxy                                            */
/*              yxxxxxxxxxxxxxxy                                            */
/*              yxxxxxxxxxxxxxxy                                            */
/*              yyyyyyyyyyyyyyyy                                            */
/*                                                                          */
/*      The output buffer would be:                                         */
/*                                                                          */
/*              tXXXXXXXXXXXXXXz                                            */
/*              zXXXXXXXXXXXXXXz                                            */
/*              zXXXXXXXXXXXXXXz                                            */
/*              zXXXXXXXXXXXXXXt                                            */
/*                                                                          */
/*      Where:                                                              */
/*                                                                          */
/*          X = IMG_sobel(x)    The algorithm is applied to that pixel.     */
/*                          The correct output is obtained, the data        */
/*                          around the pixels we work on is used            */
/*                                                                          */
/*          t               Whatever was in the output buffer in that       */
/*                          position is kept there.                         */
/*                                                                          */
/*          z = IMG_sobel(y)    The algorithm is applied to that pixel.     */
/*                          The output is not meaningful, because the       */
/*                          necessary data to process the pixel is not      */
/*                          available.  This is because for each output     */
/*                          pixel we need input pixels from the right and   */
/*                          from the left of the output pixel.  But this    */
/*                          data doesn't exist.                             */
/*                                                                          */
/*      This means that we will only process (rows-2) lines.  Then, we      */
/*      will process all the pixels inside each line. Even though the       */
/*      results for the first and last pixels in each line will not         */
/*      be relevant, it makes the control much simpler and ends up          */
/*      saving cycles.                                                      */
/*                                                                          */
/*      Also the first pixel in the first processed line and the            */
/*      last pixel in the last processed line will not be computed.         */
/*      It is not necessary, since the results would be bogus.              */
/*                                                                          */
/*      The following horizontal and vertical masks that are                */
/*      applied to the input buffer to obtain one output pixel.             */
/*                                                                          */
/*          Horizontal:                                                     */
/*              -1 -2 -1                                                    */
/*               0  0  0                                                    */
/*               1  2  1                                                    */
/*                                                                          */
/*          Vertical:                                                       */
/*              -1  0  1                                                    */
/*              -2  0  2                                                    */
/*              -1  0  1                                                    */
/*                                                                          */
/*      This is a C model of the Sobel implementation.  This C code         */
/*      is functionally equivalent to the assembly code without             */
/*      restrictions.   The assembly code may impose additional             */
/*      restrictions.                                                       */
/*                                                                          */
/*          void IMG_sobel                                                  */
/*          (                                                               */
/*              const unsigned char *in,       // Input image data  //      */
/*              unsigned char       *out,      // Output image data //      */
/*              short cols, short rows         // Image dimensions  //      */
/*          )                                                               */
/*          {                                                               */
/*              // ------------------------------------------------ //      */
/*              //  Intermediate values.                            //      */
/*              // ------------------------------------------------ //      */
/*              int H;    // Horizontal mask result                 //      */
/*              int V;    // Vertical mask result                   //      */
/*              int O;    // Sum of horizontal and vertical masks   //      */
/*              int i;    // Input pixel offset                     //      */
/*              int o;    // Output pixel offset.                   //      */
/*              int xy;   // Loop counter.                          //      */
/*                                                                          */
/*              // ------------------------------------------------ //      */
/*              //  Input values.                                   //      */
/*              // ------------------------------------------------ //      */
/*              int i00, i01, i02;                                          */
/*              int i10,      i12;                                          */
/*              int i20, i21, i22;                                          */
/*                                                                          */
/*              // ------------------------------------------------ //      */
/*              //  Step through the entire image.  We step         //      */
/*              //  through 'rows - 2' rows in the output image,    //      */
/*              //  since those are the only rows that are fully    //      */
/*              //  defined for our filter.                         //      */
/*              // ------------------------------------------------ //      */
/*              for (xy = 0, i = cols + 1, o = 1;                           */
/*                   xy < cols*(rows-2) - 2;                                */
/*                   xy++, i++, o++)                                        */
/*              {                                                           */
/*                                                                          */
/*                  // -------------------------------------------- //      */
/*                  //  Read necessary data to process an input     //      */
/*                  //  pixel.  The following instructions are      //      */
/*                  //  written to reflect the position of the      //      */
/*                  //  input pixels in reference to the pixel      //      */
/*                  //  being processed, which would correspond     //      */
/*                  //  to the blank space left in the middle.      //      */
/*                  // -------------------------------------------- //      */
/*                  i00=in[i-cols-1]; i01=in[i-cols]; i02=in[i-cols+1];     */
/*                  i10=in[i     -1];                 i12=in[i     +1];     */
/*                  i20=in[i+cols-1]; i21=in[i+cols]; i22=in[i+cols+1];     */
/*                                                                          */
/*                  // -------------------------------------------- //      */
/*                  //  Apply the horizontal mask.                  //      */
/*                  // -------------------------------------------- //      */
/*                  H = -i00 - 2*i01 -   i02 +   i20 + 2*i21 + i22;         */
/*                                                                          */
/*                  // -------------------------------------------- //      */
/*                  //  Apply the vertical mask.                    //      */
/*                  // -------------------------------------------- //      */
/*                  V = -i00 +   i02 - 2*i10 + 2*i12 -   i20 + i22;         */
/*                                                                          */
/*                  O = abs(H) + abs(V);                                    */
/*                                                                          */
/*                  // -------------------------------------------- //      */
/*                  //  If the result is over 255 (largest valid    //      */
/*                  //  pixel value), saturate (clamp) to 255.      //      */
/*                  // -------------------------------------------- //      */
/*                  if (O > 255) O = 255;                                   */
/*                                                                          */
/*                  // -------------------------------------------- //      */
/*                  //  Store the result.                           //      */
/*                  // -------------------------------------------- //      */
/*                  out[o] = O;                                             */
/*              }                                                           */
/*          }                                                               */
/*                                                                          */
/*  TECHNIQUES                                                              */
/*      Eight output pixels are computed per iteration using loop unrolling */
/*      and packed operations.                                              */
/*      The prolog is only partially collapsed because use of predicate is  */
/*      not possible since there is no free instruction slot avaible in     */
/*      the kernel.                                                         */
/*      The last stage of the epilog is kept to accommodate for the         */
/*      exception of storing only 6 outputs in the last iteration.          */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      At least eight output pixels must be processed.                     */
/*      The input image width must be even (eg. 'cols' must be even).       */
/*                                                                          */
/*  MEMORY NOTE                                                             */
/*      No bank conflicts occur ever.                                       */
/*                                                                          */
/*  NOTES                                                                   */
/*      This is a LITTLE ENDIAN implementation.                             */
/*      The image arrays do not need to be aligned.                         */
/*                                                                          */
/*      The values of the left-most and right-most pixels on each line      */
/*      of the output are not well-defined.                                 */
/*                                                                          */
/*  CYCLES                                                                  */
/*      cycles = 11 * cols * (rows-2)/8 + 23                                */
/*      For cols = 128 and rows = 128, cycles = 22,199.                     */
/*                                                                          */
/*  CODESIZE                                                                */
/*      688 bytes.                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
#ifndef IMG_SOBEL_H_
#define IMG_SOBEL_H_ 1

void IMG_sobel
(
    const unsigned char *in_data,      /* Input image data  */
    unsigned char       *out_data,     /* Output image data */
    short cols, short rows             /* Image dimensions  */
);

#endif
/* ======================================================================== */
/*  End of file:  img_sobel.h                                               */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
