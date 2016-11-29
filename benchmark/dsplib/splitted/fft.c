fft.c/          1066929505  0     0     0       41222     `
/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  DSPLIB  DSP Signal Processing Library                                   */
/*                                                                          */
/*      Release:        Revision 1.04b                                      */
/*      CVS Revision:   1.7     Sun Mar 10 01:10:45 2002 (UTC)              */
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
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*     DSP_fft                                                              */
/*                                                                          */
/*                                                                          */
/*  REVISION DATE                                                           */
/*      15-Oct-2000                                                         */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This code performs a Radix-4 FFT with digit reversal.  The code     */
/*      uses a special ordering of twiddle factors and memory accesses      */
/*      to improve performance in the presence of cache.  It operates       */
/*      largely in-place, but the final digit-reversed output is written    */
/*      out-of-place.                                                       */
/*                                                                          */
/*      This code requires a special sequence of twiddle factors stored     */
/*      in 1Q15 fixed-point format.  The following C code illustrates       */
/*      one way to generate the desired twiddle-factor array:               */
/*                                                                          */
/*      #include <math.h>                                                   */
/*                                                                          */
/*      #ifndef PI                                                          */
/*      # define PI (3.14159265358979323846)                                */
/*      #endif                                                              */
/*                                                                          */
/*      short d2s(double d)                                                 */
/*      {                                                                   */
/*          d = floor(0.5 + d);  // Explicit rounding to integer //         */
/*          if (d >=  32767.0) return  32767;                               */
/*          if (d <= -32768.0) return -32768;                               */
/*          return (short)d;                                                */
/*      }                                                                   */
/*                                                                          */
/*      void gen_twiddle(short *w, int n)                                   */
/*      {                                                                   */
/*          double M = 32767.5;                                             */
/*          int i, j, k;                                                    */
/*                                                                          */
/*          for (j = 1, k = 0; j < n >> 2; j = j << 2)                      */
/*          {                                                               */
/*              for (i = 0; i < n >> 2; i += j << 1)                        */
/*              {                                                           */
/*                  w[k + 11] = d2s(M * cos(6.0 * PI * (i + j) / n));       */
/*                  w[k + 10] = d2s(M * sin(6.0 * PI * (i + j) / n));       */
/*                  w[k +  9] = d2s(M * cos(6.0 * PI * (i    ) / n));       */
/*                  w[k +  8] = d2s(M * sin(6.0 * PI * (i    ) / n));       */
/*                                                                          */
/*                  w[k +  7] = d2s(M * cos(4.0 * PI * (i + j) / n));       */
/*                  w[k +  6] = d2s(M * sin(4.0 * PI * (i + j) / n));       */
/*                  w[k +  5] = d2s(M * cos(4.0 * PI * (i    ) / n));       */
/*                  w[k +  4] = d2s(M * sin(4.0 * PI * (i    ) / n));       */
/*                                                                          */
/*                  w[k +  3] = d2s(M * cos(2.0 * PI * (i + j) / n));       */
/*                  w[k +  2] = d2s(M * sin(2.0 * PI * (i + j) / n));       */
/*                  w[k +  1] = d2s(M * cos(2.0 * PI * (i    ) / n));       */
/*                  w[k +  0] = d2s(M * sin(2.0 * PI * (i    ) / n));       */
/*                                                                          */
/*                  k += 12;                                                */
/*              }                                                           */
/*          }                                                               */
/*          w[2*n - 1] = w[2*n - 3] = w[2*n - 5] = 32767;                   */
/*          w[2*n - 2] = w[2*n - 4] = w[2*n - 6] = 0;                       */
/*      }                                                                   */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      The size of the FFT, n, must be a power of 4 and greater than       */
/*      or equal to 16 and less than 32768.                                 */
/*                                                                          */
/*      The arrays 'x[]', 'y[]', and 'w[]' all must be aligned on a         */
/*      double-word boundary for the "optimized" implementations.           */
/*                                                                          */
/*      The input and output data are complex, with the real/imaginary      */
/*      components stored in adjacent locations in the array.  The real     */
/*      components are stored at even array indices, and the imaginary      */
/*      components are stored at odd array indices.                         */
/*                                                                          */
/*  TECHNIQUES                                                              */
/*      The following C code represents an implementation of the Cooley     */
/*      Tukey radix 4 DIF FFT. It accepts the inputs in normal order and    */
/*      produces the outputs in digit reversed order. The natural C code    */
/*      shown in this file on the other hand, accepts the inputs in nor-    */
/*      mal order and produces the outputs in normal order.                 */
/*                                                                          */
/*      Several transformations have been applied to the original Cooley    */
/*      Tukey code to produce the natural C code description shown here.    */
/*      In order to understand these it would first be educational to       */
/*      understand some of the issues involved in the conventional Cooley   */
/*      Tukey FFT code.                                                     */
/*                                                                          */
/*      void radix4(int n, short x[], short wn[])                           */
/*      {                                                                   */
/*          int    n1,  n2,  ie,   ia1,  ia2, ia3;                          */
/*          int    i0,  i1,  i2,    i3,    i, j,     k;                     */
/*          short  co1, co2, co3,  si1,  si2, si3;                          */
/*          short  xt0, yt0, xt1,  yt1,  xt2, yt2;                          */
/*          short  xh0, xh1, xh20, xh21, xl0, xl1,xl20,xl21;                */
/*                                                                          */
/*          n2 = n;                                                         */
/*          ie = 1;                                                         */
/*          for (k = n; k > 1; k >>= 2)                                     */
/*          {                                                               */
/*              n1 = n2;                                                    */
/*              n2 >>= 2;                                                   */
/*              ia1 = 0;                                                    */
/*                                                                          */
/*              for (j = 0; j < n2; j++)                                    */
/*              {                                                           */
/*                   ia2 = ia1 + ia1;                                       */
/*                   ia3 = ia2 + ia1;                                       */
/*                                                                          */
/*                   co1 = wn[2 * ia1    ];                                 */
/*                   si1 = wn[2 * ia1 + 1];                                 */
/*                   co2 = wn[2 * ia2    ];                                 */
/*                   si2 = wn[2 * ia2 + 1];                                 */
/*                   co3 = wn[2 * ia3    ];                                 */
/*                   si3 = wn[2 * ia3 + 1];                                 */
/*                   ia1 = ia1 + ie;                                        */
/*                                                                          */
/*                   for (i0 = j; i0< n; i0 += n1)                          */
/*                   {                                                      */
/*                       i1 = i0 + n2;                                      */
/*                       i2 = i1 + n2;                                      */
/*                       i3 = i2 + n2;                                      */
/*                                                                          */
/*                                                                          */
/*                       xh0  = x[2 * i0    ] + x[2 * i2    ];              */
/*                       xh1  = x[2 * i0 + 1] + x[2 * i2 + 1];              */
/*                       xl0  = x[2 * i0    ] - x[2 * i2    ];              */
/*                       xl1  = x[2 * i0 + 1] - x[2 * i2 + 1];              */
/*                                                                          */
/*                       xh20 = x[2 * i1    ] + x[2 * i3    ];              */
/*                       xh21 = x[2 * i1 + 1] + x[2 * i3 + 1];              */
/*                       xl20 = x[2 * i1    ] - x[2 * i3    ];              */
/*                       xl21 = x[2 * i1 + 1] - x[2 * i3 + 1];              */
/*                                                                          */
/*                       x[2 * i0    ] = xh0 + xh20;                        */
/*                       x[2 * i0 + 1] = xh1 + xh21;                        */
/*                                                                          */
/*                       xt0  = xh0 - xh20;                                 */
/*                       yt0  = xh1 - xh21;                                 */
/*                       xt1  = xl0 + xl21;                                 */
/*                       yt2  = xl1 + xl20;                                 */
/*                       xt2  = xl0 - xl21;                                 */
/*                       yt1  = xl1 - xl20;                                 */
/*                                                                          */
/*                       x[2 * i1    ] = (xt1 * co1 + yt1 * si1) >> 15;     */
/*                       x[2 * i1 + 1] = (yt1 * co1 - xt1 * si1) >> 15;     */
/*                       x[2 * i2    ] = (xt0 * co2 + yt0 * si2) >> 15;     */
/*                       x[2 * i2 + 1] = (yt0 * co2 - xt0 * si2) >> 15;     */
/*                       x[2 * i3    ] = (xt2 * co3 + yt2 * si3) >> 15;     */
/*                       x[2 * i3 + 1] = (yt2 * co3 - xt2 * si3) >> 15;     */
/*                   }                                                      */
/*             }                                                            */
/*                                                                          */
/*             ie <<= 2;                                                    */
/*         }                                                                */
/*     }                                                                    */
/*                                                                          */
/*      The conventional Cooley Tukey FFT, is written using three loops.    */
/*      The outermost loop "k" cycles through the stages. There are log     */
/*      N to the base 4 stages in all. The loop "j" cycles through the      */
/*      groups of butterflies with different twiddle factors, loop "i"      */
/*      reuses the twiddle factors for the different butterflies within     */
/*      a stage. It is interesting to note the following:                   */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*      Stage#     #Groups     # Butterflies with common     #Groups*Bflys  */
/*                               twiddle factors                            */
/*--------------------------------------------------------------------------*/
/*       1         N/4          1                            N/4            */
/*       2         N/16         4                            N/4            */
/*       ..                                                                 */
/*       logN      1            N/4                          N/4            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*      The following statements can be made based on above observations:   */
/*                                                                          */
/*      a) Inner loop "i0" iterates a veriable number of times. In          */
/*      particular the number of iterations quadruples every time from      */
/*      1..N/4. Hence software pipelining a loop that iterates a vraiable   */
/*      number of times is not profitable.                                  */
/*                                                                          */
/*      b) Outer loop "j" iterates a variable number of times as well.      */
/*      However the number of iterations is quartered every time from       */
/*      N/4 ..1. Hence the behaviour in (a) and (b) are exactly opposite    */
/*      to each other.                                                      */
/*                                                                          */
/*      c) If the two loops "i" and "j" are colaesced together then they    */
/*      will iterate for a fixed number of times namely N/4. This allows    */
/*      us to combine the "i" and "j" loops into 1 loop. Optimized impl-    */
/*      ementations will make use of this fact.                             */
/*                                                                          */
/*      In addition the Cooley Tukey FFT accesses three twiddle factors     */
/*      per iteration of the inner loop, as the butterflies that re-use     */
/*      twiddle factors are lumped together. This leads to accessing the    */
/*      twiddle factor array at three points each sepearted by "ie". Note   */
/*      that "ie" is initially 1, and is quadrupled with every iteration.   */
/*      Therfore these three twiddle factors are not even contiguous in     */
/*      the array.                                                          */
/*                                                                          */
/*      In order to vectorize the FFT, it is desirable to access twiddle    */
/*      factor array using double word wide loads and fetch the twiddle     */
/*      factors needed. In order to do this a modified twiddle factor       */
/*      array is created, in which the factors WN/4, WN/2, W3N/4 are        */
/*      arranged to be contiguous. This eliminates the seperation between   */
/*      twiddle factors within a butterfly. However this implies that as    */
/*      the loop is traversed from one stage to another, that we maintain   */
/*      a redundant version of the twiddle factor array. Hence the size     */
/*      of the twiddle factor array increases as compared to the normal     */
/*      Cooley Tukey FFT.  The modified twiddle factor array is of size     */
/*      "2 * N" where the conventional Cooley Tukey FFT is of size"3N/4"    */
/*      where N is the number of complex points to be transformed. The      */
/*      routine that generates the modified twiddle factor array was        */
/*      presented earlier. With the above transformation of the FFT,        */
/*      both the input data and the twiddle factor array can be accessed    */
/*      using double-word wide loads to enable packed data processing.      */
/*                                                                          */
/*      The final stage is optimised to remove the multiplication as        */
/*      w0 = 1.  This stage also performs digit reversal on the data,       */
/*      so the final output is in natural order.                            */
/*                                                                          */
/*      The DSP_fft() code shown here performs the bulk of the computation  */
/*      in place. However, because digit-reversal cannot be performed       */
/*      in-place, the final result is written to a separate array, y[].     */
/*                                                                          */
/*      There is one slight break in the flow of packed processing that     */
/*      needs to be comprehended. The real part of the complex number is    */
/*      in the lower half, and the imaginary part is in the upper half.     */
/*      The flow breaks in case of "xl0" and "xl1" because in this case     */
/*      the real part needs to be combined with the imaginary part because  */
/*      of the multiplication by "j". This requires a packed quantity like  */
/*      "xl21xl20" to be rotated as "xl20xl21" so that it can be combined   */
/*       using add2's and sub2's. Hence the natural version of C code       */
/*      shown below is transformed using packed data processing as shown:   */
/*                                                                          */
/*                       xl0  = x[2 * i0    ] - x[2 * i2    ];              */
/*                       xl1  = x[2 * i0 + 1] - x[2 * i2 + 1];              */
/*                       xl20 = x[2 * i1    ] - x[2 * i3    ];              */
/*                       xl21 = x[2 * i1 + 1] - x[2 * i3 + 1];              */
/*                                                                          */
/*                       xt1  = xl0 + xl21;                                 */
/*                       yt2  = xl1 + xl20;                                 */
/*                       xt2  = xl0 - xl21;                                 */
/*                       yt1  = xl1 - xl20;                                 */
/*                                                                          */
/*                       xl1_xl0   = _sub2(x21_x20, x21_x20)                */
/*                       xl21_xl20 = _sub2(x32_x22, x23_x22)                */
/*                       xl20_xl21 = _rotl(xl21_xl20, 16)                   */
/*                                                                          */
/*                       yt2_xt1   = _add2(xl1_xl0, xl20_xl21)              */
/*                       yt1_xt2   = _sub2(xl1_xl0, xl20_xl21)              */
/*                                                                          */
/*      Also notice that xt1, yt1 endup on seperate words, these need to    */
/*      be packed together to take advantage of the packed twiddle fact     */
/*      ors that have been loaded. In order for this to be achieved they    */
/*      are re-aligned as follows:                                          */
/*                                                                          */
/*      yt1_xt1 = _packhl2(yt1_xt2, yt2_xt1)                                */
/*      yt2_xt2 = _packhl2(yt2_xt1, yt1_xt2)                                */
/*                                                                          */
/*      The packed words "yt1_xt1" allows the loaded"sc" twiddle factor     */
/*      to be used for the complex multiplies. The real part os the         */
/*      complex multiply is implemented using _dotp2. The imaginary         */
/*      part of the complex multiply is implemented using _dotpn2           */
/*      after the twiddle factors are swizzled within the half word.        */
/*                                                                          */
/*      (X + jY) ( C + j S) = (XC + YS) + j (YC - XS).                      */
/*                                                                          */
/*      The actual twiddle factors for the FFT are cosine, - sine. The      */
/*      twiddle factors stored in the table are csine and sine, hence       */
/*      the sign of the "sine" term is comprehended during multipli-        */
/*      cation as shown above.                                              */
/*                                                                          */
/*  MEMORY NOTE                                                             */
/*      The optimized implementations are written for LITTLE ENDIAN.        */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

/*--------------------------------------------------------------------------*/
/* The following macro is used to obtain a digit reversed index, of a given */
/* number i, into j where the number of bits in "i" is "m". For the natural */
/* form of C code, this is done by first interchanging every set of "2 bit" */
/* pairs, followed by exchanging nibbles, followed by exchanging bytes, and */
/* finally halfwords. To give an example, condider the following number:    */
/*                                                                          */
/* N = FEDCBA9876543210, where each digit represents a bit, the following   */
/* steps illustrate the changes as the exchanges are performed:             */
/* M = DCFE98BA54761032 is the number after every "2 bits" are exchanged.   */
/* O = 98BADCFE10325476 is the number after every nibble is exchanged.      */
/* P = 1032547698BADCFE is the number after every byte is exchanged.        */
/* Since only 16 digits were considered this represents the digit reversed  */
/* index. Since the numbers are represented as 32 bits, there is one more   */
/* step typically of exchanging the half words as well.                     */
/*--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#if 0
# define DIG_REV(i, m, j) ((j) = (_shfl(_rotl(_bitr(_deal(i)), 16)) >> (m)))
#else
# define DIG_REV(i, m, j)                                                   \
    do {                                                                    \
        unsigned _ = (i);                                                   \
        _ = ((_ & 0x33333333) <<  2) | ((_ & ~0x33333333) >>  2);           \
        _ = ((_ & 0x0F0F0F0F) <<  4) | ((_ & ~0x0F0F0F0F) >>  4);           \
        _ = ((_ & 0x00FF00FF) <<  8) | ((_ & ~0x00FF00FF) >>  8);           \
        _ = ((_ & 0x0000FFFF) << 16) | ((_ & ~0x0000FFFF) >> 16);           \
        (j) = _ >> (m);                                                     \
    } while (0)
#endif

void DSP_fft
(
    const short *restrict w,
    int n,
    short       *restrict x,
    short       *restrict y
)
{
    int stride, i, j, k, t, s, m;

    short  xh0, xh1,  xh20,  xh21;
    short  xl0, xl1,  xl20,  xl21;
    short  xt0, yt0,  xt1,   yt1;
    short  xt2, yt2,  xt3,   yt3;

    /*----------------------------------------------------------------------*/
    /* Inform the compiler that the  input array "x", twiddle factor array  */
    /* "w" and output array "y" are double word aligned.  In addition the   */
    /* number of points to be transformed is assumed to be greater than or  */
    /* equal to 16, and less than 32768.                                    */
    /*----------------------------------------------------------------------*/

    #ifndef NOASSUME
    _nassert((int)x % 8 == 0);
    _nassert((int)y % 8 == 0);
    _nassert((int)w % 8 == 0);
    _nassert(n >= 16);
    _nassert(n <  32768);
    #endif

    /* -------------------------------------------------------------------- */
    /*  Perform initial stages of FFT in place w/out digit reversal.        */
    /* -------------------------------------------------------------------- */

    #ifndef NOASSUME
    #pragma MUST_ITERATE(1,,1);
    #endif

    for (stride = n, t = 0; stride > 4; stride >>= 2)
    {
        /* ---------------------------------------------------------------- */
        /*  Perform each of the butterflies for this particular stride.     */
        /* ---------------------------------------------------------------- */

        s = stride >> 2;

        /*------------------------------------------------------------------*/
        /* stride represents the seperation between the inputs of the radix */
        /* 4 butterfly. The C code breaks the FFT, into two cases, one when */
        /* the stride between the elements is greater than 4, other when    */
        /* the stride is less than 4. Since stride is greater than 16, it   */
        /* can be guranteed that "s" is greater than or equal to 4.         */
        /* In addition it can also be shown that the loop that shares this  */
        /* stride will iterate at least once.  The number of times this     */
        /* loop iterates depends on how many butterflies in this stage      */
        /* share a twiddle factor.                                          */
        /*------------------------------------------------------------------*/

        #ifndef NOASSUME
        _nassert(stride >= 16);
        _nassert(s      >=  4);
        #pragma MUST_ITERATE(1,,1);
        #endif

        for (i = 0; i < n; i += stride)
        {

            #ifndef NOASSUME
            _nassert(i % 4 == 0);
            _nassert(s     >= 4);
            #pragma MUST_ITERATE(2,,2);
            #endif

            for (j = 0; j < s; j += 2)
            {
                for (k = 0; k < 2; k++)
                {
                    short           w1c, w1s, w2c, w2s, w3c, w3s;
                    short x0r, x0i, x1r, x1i, x2r, x2i, x3r, x3i;
                    short y0r, y0i, y1r, y1i, y2r, y2i, y3r, y3i;

                    /* ----------------------------------------------------- */
                    /*  Read the four samples that are the input to this     */
                    /*  particular butterfly.                                */
                    /* ----------------------------------------------------- */

                    x0r = x[2*(i+j+k      ) + 0]; x0i = x[2*(i+j+k      ) + 1];
                    x1r = x[2*(i+j+k +   s) + 0]; x1i = x[2*(i+j+k +   s) + 1];
                    x2r = x[2*(i+j+k + 2*s) + 0]; x2i = x[2*(i+j+k + 2*s) + 1];
                    x3r = x[2*(i+j+k + 3*s) + 0]; x3i = x[2*(i+j+k + 3*s) + 1];

                    /* ----------------------------------------------------- */
                    /*  Read the six twiddle factors that are needed for 3   */
                    /*  of the four outputs. (The first output has no mpys.) */
                    /* ------------------------------------------------------*/

                    w1s = w[t + 2*k + 6*j + 0];    w1c = w[t + 2*k + 6*j + 1];
                    w2s = w[t + 2*k + 6*j + 4];    w2c = w[t + 2*k + 6*j + 5];
                    w3s = w[t + 2*k + 6*j + 8];    w3c = w[t + 2*k + 6*j + 9];

                    /* ----------------------------------------------------- */
                    /*  Calculate the four outputs, remembering that radix4  */
                    /*  FFT accepts 4 inputs and produces 4 outputs. If we   */
                    /*  imagine the inputs as being complex, and look at the */
                    /*  first stage as an example:                           */
                    /*                                                       */
                    /*  Four inputs are x(n) x(n+N/4) x(n+N/2) x(n+3N/4)     */
                    /*  In general the four inputs can be generalized using  */
                    /*  the stride between the elements as follows:          */
                    /*  x(n), x(n + s), x(n + 2*s), x(n + 3*s).              */
                    /*                                                       */
                    /*  These four inputs are used to calculate four outputs */
                    /*  as shown below:                                      */
                    /*                                                       */
                    /* X(4k)  = x(n) + x(n + N/4) + x(n + N/2) + x(n + 3N/4) */
                    /* X(4k+1)= x(n) -jx(n + N/4) - x(n + N/2) +jx(n + 3N/4) */
                    /* X(4k+2)= x(n) - x(n +N/4)  + x(N + N/2) - x(n + 3N/4) */
                    /* X(4k+3)= x(n) +jx(n + N/4) - x(n + N/2) -jx(n + 3N/4) */
                    /*                                                       */
                    /* These four partial results can be re-written to show  */
                    /* the underlying DIF structure similar to radix2 as     */
                    /* follows:                                              */
                    /*                                                       */
                    /* X(4k)  = (x(n)+x(n + N/2)) + (x(n+N/4)+ x(n + 3N/4))  */
                    /* X(4k+1)= (x(n)-x(n + N/2)) -j(x(n+N/4) - x(n + 3N/4)) */
                    /* x(4k+2)= (x(n)+x(n + N/2)) - (x(n+N/4)+ x(n + 3N/4))  */
                    /* X(4k+3)= (x(n)-x(n + N/2)) +j(x(n+N/4) - x(n + 3N/4)) */
                    /*                                                       */
                    /* which leads to the real and imaginary values as foll: */
                    /*                                                       */
                    /* y0r = x0r + x2r +  x1r +  x3r    =  xh0 + xh20        */
                    /* y0i = x0i + x2i +  x1i +  x3i    =  xh1 + xh21        */
                    /* y1r = x0r - x2r + (x1i -  x3i)   =  xl0 + xl21        */
                    /* y1i = x0i - x2i - (x1r -  x3r)   =  xl1 - xl20        */
                    /* y2r = x0r + x2r - (x1r +  x3r)   =  xh0 - xh20        */
                    /* y2i = x0i + x2i - (x1i +  x3i    =  xh1 - xh21        */
                    /* y3r = x0r - x2r - (x1i -  x3i)   =  xl0 - xl21        */
                    /* y3i = x0i - x2i + (x1r -  x3r)   =  xl1 + xl20        */
                    /* ----------------------------------------------------- */

                    xh0  = x0r   +   x2r;
                    xh1  = x0i   +   x2i;
                    xh20 = x1r   +   x3r;
                    xh21 = x1i   +   x3i;

                    xl0  = x0r   -   x2r;
                    xl1  = x0i   -   x2i;
                    xl20 = x1r   -   x3r;
                    xl21 = x1i   -   x3i;

                    xt0  =  xh0  +   xh20;
                    yt0  =  xh1  +   xh21;

                    xt1  =  xl0  +   xl21;
                    yt1  =  xl1  -   xl20;

                    xt2  =  xh0  -   xh20;
                    yt2  =  xh1  -   xh21;

                    xt3  =  xl0  -   xl21;
                    yt3  =  xl1  +   xl20;

                    /*-------------------------------------------------------*/
                    /* Perform twiddle factor multiplies of three terms,top  */
                    /* term does not have any multiplies. Note the twiddle   */
                    /* factors for a normal FFT are C + j (-S). Since the    */
                    /* factors that are stored are C + j S, this is          */
                    /* corrected for in the multiplies.                      */
                    /*                                                       */
                    /* Y1 = (xt1 + jyt1) (c + js) = (xc + ys) + (yc -xs)     */
                    /*-------------------------------------------------------*/

                    y0r = xt0;
                    y0i = yt0;
                    y1r = (xt1 * w1c +  yt1 * w1s) >> 15;
                    y1i = (yt1 * w1c -  xt1 * w1s) >> 15;
                    y2r = (xt2 * w2c +  yt2 * w2s) >> 15;
                    y2i = (yt2 * w2c -  xt2 * w2s) >> 15;
                    y3r = (xt3 * w3c +  yt3 * w3s) >> 15;
                    y3i = (yt3 * w3c -  xt3 * w3s) >> 15;

                    /* ---------------------------------------------------- */
                    /*  Store the final results back to the input array.    */
                    /* ---------------------------------------------------- */

                    x[2*(i+j+k      ) + 0] = y0r; x[2*(i+j+k      ) + 1] = y0i;
                    x[2*(i+j+k +   s) + 0] = y1r; x[2*(i+j+k +   s) + 1] = y1i;
                    x[2*(i+j+k + 2*s) + 0] = y2r; x[2*(i+j+k + 2*s) + 1] = y2i;
                    x[2*(i+j+k + 3*s) + 0] = y3r; x[2*(i+j+k + 3*s) + 1] = y3i;
               }
          }
        }

        /* ---------------------------------------------------------------- */
        /*  Offset to next subtable of twiddle factors. With each iteration */
        /*  of the above block, six twiddle factors get read, s times,      */
        /*  hence the offset into the twiddle factor array is advanved by   */
        /*  this amount.                                                    */
        /* ---------------------------------------------------------------- */

        t += 6 * s;
    }

    /* -------------------------------------------------------------------- */
    /*  Get the magnitude of "n", so we know how many digits to reverse.    */
    /* -------------------------------------------------------------------- */

    for (i = 31, m = 1; (n & (1 << i)) == 0; i--, m++) ;

    /* -------------------------------------------------------------------- */
    /*  Perform final stage with digit reversal.                            */
    /* -------------------------------------------------------------------- */

    s = n >> 2;

    /*----------------------------------------------------------------------*/
    /* One of the nice features, of this last stage are that, no multiplies */
    /* are required. In addition the data always strides by a fixed amount  */
    /* namely 8 elements. Since the data is stored as interleaved pairs, of */
    /* real and imaginary data, the first eight elements contain the data   */
    /* for the first four complex inputs. These are the inputs to the first */
    /* radix4 butterfly.                                                    */
    /*----------------------------------------------------------------------*/

    #ifndef NOASSUME
    #pragma MUST_ITERATE(4,,4);
    #endif
    for (i = 0; i < n; i += 4)
    {
        short x0r, x0i, x1r, x1i, x2r, x2i, x3r, x3i;
        short y0r, y0i, y1r, y1i, y2r, y2i, y3r, y3i;

        /* ---------------------------------------------------------------- */
        /*  Read the four samples that are the input to this butterfly.     */
        /* ---------------------------------------------------------------- */
        x0r = x[2*(i + 0) + 0];     x0i = x[2*(i + 0) + 1];
        x1r = x[2*(i + 1) + 0];     x1i = x[2*(i + 1) + 1];
        x2r = x[2*(i + 2) + 0];     x2i = x[2*(i + 2) + 1];
        x3r = x[2*(i + 3) + 0];     x3i = x[2*(i + 3) + 1];

        /* ---------------------------------------------------------------- */
        /*  Calculate the final FFT result from this butterfly.             */
        /* ---------------------------------------------------------------- */
        y0r  = (x0r + x2r) + (x1r + x3r);
        y0i  = (x0i + x2i) + (x1i + x3i);
        y1r  = (x0r - x2r) + (x1i - x3i);
        y1i  = (x0i - x2i) - (x1r - x3r);
        y2r  = (x0r + x2r) - (x1r + x3r);
        y2i  = (x0i + x2i) - (x1i + x3i);
        y3r  = (x0r - x2r) - (x1i - x3i);
        y3i  = (x0i - x2i) + (x1r - x3r);

        /* ---------------------------------------------------------------- */
        /*  Digit reverse our address to convert the digit-reversed input   */
        /*  into a linearized output order.  This actually results in a     */
        /*  digit-reversed store pattern since we're loading linearly, but  */
        /*  the end result is that the FFT bins are in linear order.        */
        /* ---------------------------------------------------------------- */
        DIG_REV(i, m, j); /* Note:  Result is assigned to 'j' by the macro. */

        /* ---------------------------------------------------------------- */
        /*  Store out the final FFT results.                                */
        /* ---------------------------------------------------------------- */
        y[2*(j +   0) + 0] = y0r;   y[2*(j +   0) + 1] = y0i;
        y[2*(j +   s) + 0] = y1r;   y[2*(j +   s) + 1] = y1i;
        y[2*(j + 2*s) + 0] = y2r;   y[2*(j + 2*s) + 1] = y2i;
        y[2*(j + 3*s) + 0] = y3r;   y[2*(j + 3*s) + 1] = y3i;
    }
}

/* ======================================================================== */
/*  End of file:  dsp_fft.c                                                 */
