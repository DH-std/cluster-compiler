/*============================================================================*/
/*                                                                            */
/*                                                                            */
/*     TEXAS INSTRUMENTS, INC.                                                */
/*                                                                            */
/*     NAME                                                                   */
/*           wave_horz : 1D Wavelet Transform                                 */
/*                                                                            */
/*     USAGE                                                                  */
/*           This routine is C-callable and can be called as:                 */
/*                                                                            */
/*           void wave_horz_co(short *iptr, short *qmf, short *filter,        */
/*                                             short * optr, int  ish_x_dim ) */
/*                  iptr =  input row of data                                 */
/*                  qmf =  qmf filter-bank for Low-Pass                       */
/*                  filter =  Mirror qmf filter bank for High_pass            */
/*                  optr = output row of detailed/reference decimated outputs */
/*                  ish_x_dim = width of the input row                        */
/*                                                                            */
/*           (See the C compiler reference guide.)                            */
/*                                                                            */
/*     DESCRIPTION                                                            */
/*                                                                            */
/*            This kernel performs a 1D Periodic Orthogonal Wavelet decomp-   */
/*     osition. This also performs athe row decomposition in a 2D wavelet     */
/*     transform. An in put signal x[n] is first low pass and high pass       */
/*     filterd and decimated by two. This results in a reference signal       */
/*     r1[n] which is the decimated output obtained by dropping the odd       */
/*     samples of the low pass filtered output and a detail signal d[n]       */
/*     obtained by dropping the odd samples of the high-pass output. A        */
/*     circular convolution algorithm is implemented and hence the wave-      */
/*     let transform is periodic. The reference signal and the detail         */
/*     signal are half the size of the original signal. The reference         */
/*     signal may then be iterated again to perform another scale of          */
/*     multi-resolution analysis.                                             */
/*                                                                            */
/*                                                                            */
/*     ASSUMPTIONS                                                            */
/*        This kernel uses the Daubechies D4 filter bank for analysis with 4  */
/*     vansishing moments. Hence the length of the analyzing low-pass and     */
/*     high pass filters is 8.                                                */
/*                                                                            */
/*     MEMORY NOTE                                                            */
/*        Hand Assembly kernel should not have any bank conflicts             */
/*                                                                            */
/*     TECHNIQUES                                                             */
/*        The main idea behind the optimized C code is to issue one set of    */
/*     reads to the x array and to perform low-pass and high pass filtering   */
/*     together and to perfrom the filtering operations together to maximize  */
/*     the number of multiplies.  The last 6 elements of the low-pass filter  */
/*     and the first 6 elements of the high pass filter use the same input    */
/*     This is used to appropraitely change the output pointer to the low     */
/*     pass filter after 6 iterations. However for the first six iterations   */
/*     pointer wrap-around can occurr and hence this creates a dependency.    */
/*     Pre-reading those 6 values outside the array prevents the checks that  */
/*     introduce this dependency. In addtion the input data is read as word   */
/*     wide quantities and the low-pass and high-pass filter coefficients     */
/*     are stored in registers allowing for the input loop to be completely   */
/*     unrolled. Thus the intrinsic C code has only one loop. A predication   */
/*     register is used to reset the low-pass output pointer after three      */
/*     iterations. The merging of the loops in this fashion allows for the    */
/*     maximum number of multiplies with the minimum number of reads.         */
/*     The dotp2 instruction performs the computation of the partial products */
/*     and is used to compute the low pass and high pass summation results.   */
/*============================================================================*/
/*      Copyright (C) 1997-1999 Texas Instruments Incorporated.               */
/*                      All Rights Reserved                                   */
/*============================================================================*/

#define Qpt 15
#define Qr 16384
#define Qs 32767
#include <stdio.h>
#include <stdlib.h>
#pragma CODE_SECTION(wave_horz_c,   ".text:intrinsic");
static const char Copyright[] = "Copyright (C) 1999 Texas Instruments "
                                 "Incorporated.  All Rights Reserved.";

void wave_horz_c
(
    const short *restrict iptr,      /* Row of input pixels  */
    const short *restrict qmf,       /* Low-pass QMF filter  */
    const short *restrict filter,    /* High-pass QMF filter */
    short       *restrict optr,      /* Row of output data   */
    int                   ish_x_dim  /* Length of input.     */
)
{
    const int M = 8;

    int    i, iters;
    short  res_h, res_l;
    int    prod_h10, prod_h32, prod_h54, prod_h76;
    int    prod_l10, prod_l32, prod_l54, prod_l76;
    int    sum_h, sum_l;
    int    h10, h32, h54, h76;
    int    l10, l32, l54, l76;
    int    x10, x32, x54, x76;
    int    h01, h23, h45, h67;
    double hf_val0, hf_val1;
    double lf_val0, lf_val1;
    int    p;
    int    offset;


    const short  *restrict xstart;
    short        *restrict yptr_h, *restrict yptr_l0, *restrict yptr_l1;
    const double *restrict lf_ptr, *restrict hf_ptr;
    const int    *restrict xiptr;

    /*---------------------------------------------------------------------*/
    /* Cast filters into double pointers and perform double word loads.    */
    /* Obtain low and high halves of the double words for the different    */
    /* filter coefficients. However in order to achieve the multiply and   */
    /* accumulate capability using dotp2 's the filter coefficients need   */
    /* to be reversed in order, since the high pass filter computes:       */
    /* x0h7 + x1h6 + x2h5 + x3h4 + x4h3 + x5h2 + x6h1 + x7h0               */
    /* This is done using the _packlh2 that accomplishes the swap2         */
    /* ility, that is being sought after. The low pass filters are fine    */
    /* in the sense that their order need not be reversed.                 */
    /*---------------------------------------------------------------------*/

    hf_ptr = (const double *) filter;
    lf_ptr = (const double *) qmf;

    hf_val0 = hf_ptr[0];
    hf_val1 = hf_ptr[1];
    lf_val0 = lf_ptr[0];
    lf_val1 = lf_ptr[1];

    h10 = (int) _lo(hf_val0);
    h32 = (int) _hi(hf_val0);
    h54 = (int) _lo(hf_val1);
    h76 = (int) _hi(hf_val1);

    h01 = _packlh2(h10, h10);
    h23 = _packlh2(h32, h32);
    h45 = _packlh2(h54, h54);
    h67 = _packlh2(h76, h76);

    l10 = (int) _lo(lf_val0);
    l32 = (int) _hi(lf_val0);
    l54 = (int) _lo(lf_val1);
    l76 = (int) _hi(lf_val1);

    /*-----------------------------------------------------------------------*/
    /* The number of loop iterations is x_dim >> 1 and for each iteration 2  */
    /* outputs one for the low-pass and one for the high pass will be produ  */
    /* ced. Pre-read the last 6 values of the input line into registers so   */
    /* that the sependency that arises from checking pointer updates and     */
    /* wrapping around need not be done. Data reuse is achieved by issuing   */
    /* moves within the kernel. Because of this the input data reads now     */
    /* start from the beginning of the input line in the loop.  Predication  */
    /* register is used to switch the location where the output low-pass     */
    /* samples are stored. The high pass output pointer need not be switched */
    /* though.                                                               */
    /*-----------------------------------------------------------------------*/
   
    iters    = ish_x_dim  >> 1 ;
    offset   = (ish_x_dim - M)  + 2;
    xstart   = iptr + offset; 

    yptr_h   = optr + (ish_x_dim >> 1);
    yptr_l0  = optr + ( offset >> 1); 
    yptr_l1  = optr;

    xiptr    =  (const int *) xstart;

    x10 = *xiptr++;   
    x32 = *xiptr++;   
    x54 = *xiptr++; 

    /*-----------------------------------------------------------------------*/
    /* Re-allign input pointer to point to the beginning of the input line   */
    /* and cast as an int pointer to perform word wide loads. The _dotp2     */
    /* instruction computes the various partial products and sums these      */
    /* up together to form the high pass output and low pass output sam-     */
    /* ples. These are shifted by 15 because of Q15 math and stored as       */
    /* low pass and high pass outputs.                                       */
    /*                                                                       */
    /* The foll: are the intermediate results being computed                 */
    /*                                                                       */
    /* High Pass:                                                            */
    /*            prod_h0 = x0 * h7  prod_h1 = x1 * h6                       */
    /*            prod_h2 = x2 * h5  prod_h3 = x3 * h4                       */
    /*            prod_h4 = x4 * h3  prod_h5 = x5 * h2                       */
    /*            prod_h6 = x6 * h1  prod_h7 = x7 * h0                       */
    /*                                                                       */
    /* Low Pass:                                                             */
    /*            prod_l0 = x0 * g0  prod_l1 = x1 * g1                       */
    /*            prod_l2 = x2 * g2  prod_l3 = x3 * g3                       */
    /*            prod_l4 = x4 * g4  prod_l5 = x5 * g5                       */
    /*            prod_l6 = x6 * g6  prod_l7 = x7 * g7                       */
    /*                                                                       */
    /* In addition note the use of p which serves as a pedication register   */
    /* to switch pointers to the low pass filter. The first three low-pass   */
    /* samples that are computed actually need to be stored at the end of    */
    /* the low-pass array, after which samples need to be stored at the      */
    /* beginning of the array. The predication register p accomplishes this. */
    /*                                                                       */
    /*-----------------------------------------------------------------------*/  

    xiptr    = (int *) iptr;
    p        = 3;


    for(i = iters; i > 0; i--)
    {
        sum_l  = Qr;
        sum_h  = Qr;

        x76 = *xiptr++;
         
        prod_h10 = _dotp2(x10, h67);
        prod_h32 = _dotp2(x32, h45);
        prod_h54 = _dotp2(x54, h23);
        prod_h76 = _dotp2(x76, h01);
 
        prod_l10 = _dotp2(x10, l10);
        prod_l32 = _dotp2(x32, l32);
        prod_l54 = _dotp2(x54, l54);
        prod_l76 = _dotp2(x76, l76);

        sum_h  += prod_h10 + prod_h32 + prod_h54 + prod_h76;
        sum_l  += prod_l10 + prod_l32 + prod_l54 + prod_l76;

        x10 = x32;
        x32 = x54;
        x54 = x76;

        res_h = (sum_h >> Qpt);
        res_l = (sum_l >> Qpt);

        *yptr_h++ =  res_h;

        if (p)  *yptr_l0++ =  res_l;
        if (!p) *yptr_l1++ = res_l;
        if (p)  p--;

    }

}


/*============================================================================*/
/*      Copyright (C) 1997-1999 Texas Instruments Incorporated.               */
/*                      All Rights Reserved                                   */
/*============================================================================*/
