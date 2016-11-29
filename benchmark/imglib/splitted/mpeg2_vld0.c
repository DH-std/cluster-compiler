/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  IMGLIB  DSP Image/Video Processing Library                              */
/*                                                                          */
/*      Release:        Revision 1.04b                                      */
/*      CVS Revision:   1.8     Sun Mar 17 04:50:04 2002 (UTC)              */
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
/*      IMG_mpeg2_vld_inter                                                 */
/*                                                                          */
/*  PLATFORM                                                                */
/*      C6400                                                               */
/*                                                                          */
/*  REVISION DATE                                                           */
/*      12-Dec-2001                                                         */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This routine takes a bitstream of an MPEG-2 non-intra coded         */
/*      macroblock and returns the decoded IDCT coefficients. The routine   */
/*      is implemented as specified in the MPEG-2 standard text (ISO/IEC    */
/*      13818-2). The routine checks the coded block pattern (cbp),         */
/*      performs coefficient decoding inlcuding, variable length decode,    */
/*      run-length expansion, inverse zigzag, dequantization, saturation    */
/*      and mismatch control.                                               */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C callable, and has the following C prototype:      */
/*                                                                          */
/*      void IMG_mpeg2_vld_inter                                            */
/*      (                                                                   */
/*          const short    *restrict Wptr,                                  */
/*          short          *restrict outi,                                  */
/*          IMG_mpeg2_vld  *restrict Mpeg2v,                                */
/*          int            mode_12Q4,                                       */
/*          int            num_blocks,                                      */
/*          int            bsbuf_words                                      */
/*      );                                                                  */
/*                                                                          */
/*        Wptr:   Pointer to array that contains quantization matrix. The   */
/*                elements of the quantization matrix in *Wptr must be      */
/*                ordered according to the scan pattern used (zigzag or     */
/*                alternate scan). Video format 4:2:0 requires one          */
/*                quantization matrix (64 array elements).  For formats     */
/*                4:2:2 and 4:4:4 two quantization matrices (one for luma   */
/*                and one for chroma) must specified in the array (128      */
/*                array elements).                                          */
/*                                                                          */
/*        outi:   Pointer to the IDCT coefficients output array             */
/*                (6*64 elements), elements must be set to zero prior to    */
/*                function call.                                            */
/*                                                                          */
/*        Mpeg2v: Pointer to the context object containing the coding       */
/*                parameters of the MB to be decoded and the current state  */
/*                of the bitstream buffer. The structure is described       */
/*                below.                                                    */
/*                                                                          */
/*     mode_12Q4: 0: Coefficients are returned in normal 16-bit integer     */
/*                format.                                                   */
/*                Otherwise: Coefficients are returned in 12Q4 format       */
/*                (normal 16-bit integer format left shifted by 4). This    */
/*                mode is useful for directly passing the coefficients      */
/*                into the IMG_idct_8x8 routine.                            */
/*                                                                          */
/*    num_blocks: Number of blocks that the MB contains. Valid values are   */
/*                6 for 4:2:0, 8 for 4:2:2 and 12 for 4:4:4 format.         */
/*                                                                          */
/*   bsbuf_words: Size of bitstream buffer in words. Must be a power of 2.  */
/*                Bitstream buffer must be aligned at an address boundary   */
/*                equal to its size in bytes (bitstream buffer is           */
/*                addressed circularly by this routine.)                    */
/*                                                                          */
/*      The structure Mpeg2v is defined as follows:                         */
/*                                                                          */
/*C         #ifndef IMG_MPEG2_VLD_STRUCT_                                  C*/
/*C         #define IMG_MPEG2_VLD_STRUCT_ 1                                C*/
/*C                                                                        C*/
/*C         typedef struct {                                               C*/
/*C           unsigned int  *bsbuf;      // pointer to bitstream buffer    C*/
/*C           unsigned int  next_wptr;   // next word to read from buffer  C*/
/*C           unsigned int  bptr;        // bit position within word       C*/
/*C           unsigned int  word1;       // word aligned buffer            C*/
/*C           unsigned int  word2;       // word aligned buffer            C*/
/*C           unsigned int  top0;        // top 32 bits of bitstream       C*/
/*C           unsigned int  top1;        // next 32 bits of bitstream      C*/
/*C           const unsigned char *scan; // inverse zigzag scan matrix     C*/
/*C           unsigned int  intravlc;    // intra_vlc_format               C*/
/*C           unsigned int  quant_scale; // quant_scale                    C*/
/*C           unsigned int  dc_prec;     // intra_dc_precision             C*/
/*C           unsigned int  cbp;         // coded_block_pattern            C*/
/*C           unsigned int  fault;       // fault condition (returned)     C*/
/*C           unsigned int  reserved;    // reserved                       C*/
/*C         } IMG_mpeg2_vld;                                               C*/
/*C                                                                        C*/
/*C         #endif                                                         C*/
/*                                                                          */
/*      The Mpeg2v variables should  have a fixed layout since they are     */
/*      accessed by this routine. If the layout is changed, the             */
/*      corresponding changes have to be made in the assembly code too.     */
/*                                                                          */
/*      The routine sets the fault flag Mpeg2v.fault to 1 if an invalid     */
/*      VLC code was encountered or the total run went beyond 63. In        */
/*      theses cases the decoder has to resynchronize.                      */
/*                                                                          */
/*      The required lookup tables for this routine are provided in         */
/*      IMGLIB and are linked in automatically when linking against         */
/*      IMGLIB.                                                             */
/*                                                                          */
/*      Before calling the routine the bitstream varaibles in Mpeg2v        */
/*      have to be initialized. If bsbuf is a circular buffer and bsptr     */
/*      contains the number of bits in the buffer that already have         */
/*      been consumed, then next_wptr, bptr, word1, word2, top0 and         */
/*      top1 are initialized as follows:                                    */
/*                                                                          */
/*      1. nextwptr: bsptr may not be a multiple of 32, therefore obtain    */
/*      the next lower multiple of 32.                                      */
/*                                                                          */
/*          next_wptr = (bsptr >> 5);                                       */
/*                                                                          */
/*      2. bptr: bptr is the bit pointer which points to the current        */
/*      bit WITHIN the word pointed to by next_wptr.                        */
/*                                                                          */
/*          bptr = bsptr & 31;                                              */
/*          bptr_cmpl = 32 - bptr;                                          */
/*                                                                          */
/*      3. word1 and word2: read next 3 words from the bitstream buffer     */
/*      (word0 is a temporary variable). bsbuf_words is the size of the     */
/*      bitstream buffer in words.                                          */
/*                                                                          */
/*          word0 = bsbuf[next_wptr];                                       */
/*          next_wptr = (next_wptr + 1) & (bsbuf_words-1);                  */
/*                                                                          */
/*          word1 = bsbuf[next_wptr];                                       */
/*          next_wptr = (next_wptr + 1) & (bsbuf_words-1);                  */
/*                                                                          */
/*          word2 = bsbuf[next_wptr];                                       */
/*          next_wptr = (next_wptr + 1) & (bsbuf_words-1);                  */
/*                                                                          */
/*      4. top0 and top1: Shift words word0, word1, word2 by bptr to the    */
/*      left so that the current bit becomes the MSB in word0. word0 can    */
/*      simply be shifted by bptr; the then empty LSBs of word0 have to be  */
/*      filled with the MSBs of word1. To do that the required MSBs are     */
/*      brought into the position of empty LSBs of word0 by shifting word1  */
/*      to the right by (32-bptr). The result is then copied into word0 by  */
/*      an addition. Rather than overwriting word0, top0 is used to hold    */
/*      the new bit aligned word. The same procedure is used to obtain      */
/*      top1. top0 and top1 contain the next 64 bits of the bitstream.      */
/*                                                                          */
/*          s1 = word0 << bptr;                                             */
/*          s2 = word1 >> bptr_cmpl;  // unsigned right-shift //            */
/*          top0 = s1 + s2;                                                 */
/*                                                                          */
/*          s3 = word1 << bptr;                                             */
/*          s4 = word2 >> bptr_cmpl;  // unsigned right-shift //            */
/*          top1 = s3 + s4;                                                 */
/*                                                                          */
/*      Note that the routine returns the updated state of the bitstream    */
/*      buffer variables, top0, top1, word1, word2, bptr and next_wptr. If  */
/*      all other functions which access the bitstream in a decoder system  */
/*      maintain the buffer variables in the same way, then the above       */
/*      initialization procedure has to be performed only once at the       */
/*      beginning.                                                          */
/*                                                                          */
/*                                                                          */
/*  TECHNIQUES                                                              */
/*      The instruction NORM is used to detect the number of leading zeros  */
/*      or ones in a code word. This value together with additional bits    */
/*      extracted from the codeword is then used as an index into look-up   */
/*      tables to determine the length, run, level and sign. Escape code    */
/*      sequences are directly extracted from the code word.                */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      The bitstream must be stored in memory in 32-bit words which are    */
/*      in little endian byte order.                                        */
/*                                                                          */
/*      Wptr is allowed to overrun once (to detect total run overrun), so   */
/*      maximum overrun that can occur is 66 (Error mark). Therefore,       */
/*      in memory 66+1 halfwords behind the weighting matrix should be      */
/*      valid (e.g. peripherals). No memory is overwritten,                 */
/*      only loads occurr.                                                  */
/*                                                                          */
/*      Note that the AMR register is set to zero on exit.                  */
/*                                                                          */
/*  MEMORY REQUIREMENTS                                                     */
/*      1792 bytes for the lookup tables                                    */
/*      (can be shared with mpeg2_vld_intra)                                */
/*                                                                          */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

typedef struct {
    unsigned int  *bsbuf;      // pointer to bitstream buffer
    unsigned int  next_wptr;   // next word to read from buffer
    unsigned int  bptr;        // bit position within word
    unsigned int  word1;       // word aligned buffer
    unsigned int  word2;       // word aligned buffer
    unsigned int  top0;        // top 32 bits of bitstream
    unsigned int  top1;        // next 32 bits of bitstream
    const unsigned char *scan; // inverse zigzag scan matrix
    unsigned int  intravlc;    // intra_vlc_format
    unsigned int  quant_scale; // quant_scale
    unsigned int  dc_prec;     // intra_dc_precision
    unsigned int  cbp;         // coded_block_pattern
    unsigned int  fault;       // fault condition (returned)
    unsigned int  reserved;    // reserved
} IMG_mpeg2_vld;

/*********************************************************************/
/* C6000 functions                                                   */
/*********************************************************************/
#ifdef _TMS320C6X
# define SHL(x,y) ( (x) << (y) )
# define SHR(x,y) ( (x) >> (y) )

#else

# define SHL(x,y) ( ((y) & 32) ? 0 : ((x) << (y)) )
# define SHR(x,y) ( ((y) & 32) ? 0 : ((x) >> (y)) )

unsigned int _lmbd(int bit, unsigned num);
unsigned int _norm(unsigned int x);
unsigned int _ext(int x, unsigned int a, unsigned int b);
unsigned int _extu(unsigned int x, unsigned int a, unsigned int b);
int _sshl(int x, unsigned int s);

#endif

/* ------------------------------------------------------------------------ */
/*  Run-Level Tables                                                        */
/* ------------------------------------------------------------------------ */
extern unsigned short IMG_rld_table0[576];

/* ------------------------------------------------------------------------ */
/*  Length tables                                                           */
/* ------------------------------------------------------------------------ */
extern const unsigned char IMG_len_tbl0[640];

/* ------------------------------------------------------------------------ */
/*  Function                                                                */
/* ------------------------------------------------------------------------ */
void IMG_mpeg2_vld_inter
(
    const short *restrict Wptr,      // quantization matrix
    short *restrict outi,            // IDCT coefficients output array
    IMG_mpeg2_vld *restrict Mpeg2v,  // bitstream context structure
    int mode_12Q4,                   // if !=0 returns coeffs in 12Q4 format
    int num_blocks,                  // number of blocks in the MB
    int bsbuf_words                  // bitstream buffer size
)
{

/* ------------------------------------------------------------------------ */
/*  get bitstream info                                                      */
/* ------------------------------------------------------------------------ */
    unsigned int         *bsbuf     = Mpeg2v->bsbuf;
             int          next_wptr = Mpeg2v->next_wptr;
             int          bptr      = Mpeg2v->bptr;
    unsigned int          word1     = Mpeg2v->word1;
    unsigned int          word2     = Mpeg2v->word2;
    unsigned int          top0      = Mpeg2v->top0;
    unsigned int          top1      = Mpeg2v->top1;
    const unsigned char  *zzptr     = Mpeg2v->scan;
    unsigned int          qscl      = Mpeg2v->quant_scale;
    unsigned int          cbp       = Mpeg2v->cbp;

    unsigned int bptr_cmpl, top0_bk, word1_rw;

    unsigned long ltop0, t1, t5; /* 40-bit registers */

/* ------------------------------------------------------------------------ */
/*  block number (0-3: lum, 4, 5: chrom)                                    */
/* ------------------------------------------------------------------------ */
    int block;

/* ------------------------------------------------------------------------ */
/*  Variables for length, run and level decoding                            */
/* ------------------------------------------------------------------------ */
    unsigned int t2, t4, t7, t8, t9;
    int rld_left, rld_index;
    unsigned short run_level;
    unsigned char run, len, len_c;
    const unsigned char *t3;
    short level;
    unsigned int fault, eob_err, nrm;
    unsigned int test1, test2;

/* ------------------------------------------------------------------------ */
/*  Variables for de-quantization                                           */
/* ------------------------------------------------------------------------ */
    int neg, pos, f1, f3, f5, qW, sum, cc;
#ifdef _TMS320C6X
    int f4;
#else
    _int64 f4;
#endif
    const short *Wptr_origin=Wptr;
    const short *Wptr_end;
    short W;
    unsigned char cnum;

/* ------------------------------------------------------------------------ */
/*  Variables for 12Q4 mode                                                 */
/* ------------------------------------------------------------------------ */
    int mask, shr, lsb;

/* ------------------------------------------------------------------------ */
/*  In 12Q4 mode the returned DCT coefficients are left shifted by 4,       */
/*  i.e. in 12Q4 format.                                                    */
/* ------------------------------------------------------------------------ */
    if (mode_12Q4)
    {
        mask = 0xFFF0; /* clear 4 LSBs of 12Q4 number */
        shr  = 16;     /* shift right after saturate shift */
        lsb  = 16;     /* LSB for mismatch control */
    }
    else
    {
        mask = 0xFFFF; /* keep 4 LSBs */
        shr  = 20;     /* shift right after saturate shift */
        lsb  = 1;      /* LSB for mismatch control */
    }

/* ------------------------------------------------------------------------ */
/*  Advance bitsream by 8 bit to convert to 40-bit top0                     */
/* ------------------------------------------------------------------------ */
    ltop0 = ((long)top0 << 8) + (top1 >> 24);

    bptr += 8;
    test2 = (bptr >= 32);
    if (test2)
    {
        word1_rw = word1;
        word1 = word2;
        word2 = bsbuf[next_wptr];
        next_wptr += 1;
        next_wptr &= (bsbuf_words-1);
    }
    bptr = bptr & 31;
    bptr_cmpl = 32 - bptr;
    t8 = SHL(word1, bptr);
    t9 = SHR(word2, bptr_cmpl);                   /* unsigned shift */
    top1 = t8 + t9;

    fault = 0;

/* ------------------------------------------------------------------------ */
/*  block loop                                                              */
/* ------------------------------------------------------------------------ */
    for (block=0; block<num_blocks; block++)
    {

    /* -------------------------------------------------------------------- */
    /*  cbp: Bit 5 4 3 2 1 0 , if the corresponding bit is zero block no.   */
    /*  (5-bit pos) is not coded                                            */
    /* -------------------------------------------------------------------- */
        if (!(cbp & (1 << (num_blocks-block-1))))
            continue;

        zzptr = Mpeg2v->scan;

        cc = (block<4) ? 0 : (block&1)+1;

        if (cc!=0 && num_blocks>6)
            Wptr=Wptr_origin + 64;   /* weighting matrix for chrominance */
        else
            Wptr=Wptr_origin;        /* weighting matrix for luminance */

        Wptr_end = Wptr + 64;

        sum = 0;
        eob_err = 0;

    /* -------------------------------------------------------------------- */
    /*  Decode first coefficient                                            */
    /*                                                                      */
    /*  First code is special case: when the MSB of the first code is '1',  */
    /*  we know it can only be VLC '1s' (because EOB cannot occur and the   */
    /*  only other code is '11s' which is not valid for the first code.)    */
    /*  If MSB=0 skip to normal AC loop, i.e. use NORM+4 extra bits as      */
    /*  table index; if MSB=1 execute special case, do not use              */
    /*  NORM because it may have overrun but set LEN=2, LEN_C=30.           */
    /* -------------------------------------------------------------------- */
        if (ltop0>>39)
        {

        /* ---------------------------------------------------------------- */
        /*  Length computation, not required since we know LEN is 2.        */
        /* ---------------------------------------------------------------- */
           len  = 2;
           len_c = 30;

        /* ---------------------------------------------------------------- */
        /*  now that we know the length of the current VL code we can       */
        /*  advance bitstream to next one:                                  */
        /*                                                                  */
        /*  1. update ltop0 from ltop0 and top1                             */
        /* ---------------------------------------------------------------- */
            t5  = ltop0 << len;
            t7  = top1 >> len_c;
            top0_bk = (unsigned) (ltop0>>8);
            ltop0 = t5 + t7;

        /* ---------------------------------------------------------------- */
        /*  2. update top1 from word1 and word2 after increasing bptr by    */
        /*  len.  if neccesary (i.e. if new bptr is greater than 32)        */
        /*  update word1 and word2 from memory first. Don't forget that     */
        /*  bptr is always relative to the next lower word boundary and     */
        /*  therefore needs to be ANDed with 31 in case it become >=32.     */
        /* ---------------------------------------------------------------- */
            bptr += len;
            test2 = (bptr >= 32);
            if (test2) {
                word1_rw = word1;
                word1 = word2;
                word2 = bsbuf[next_wptr];
                next_wptr += 1;
                next_wptr &= (bsbuf_words-1);
            }
            bptr = bptr & 31;
            bptr_cmpl = 32 - bptr;
            t8 = SHL(word1, bptr);
            t9 = SHR(word2, bptr_cmpl);                   /* unsigned shift */
            top1 = t8 + t9;

        /* ---------------------------------------------------------------- */
        /*  Run-Level Decode: run = 0, level = 1                            */
        /* ---------------------------------------------------------------- */
            neg = _extu(top0_bk,1,31);

        /* ---------------------------------------------------------------- */
        /*  Run-lengh expansion and DQ                                      */
        /* ---------------------------------------------------------------- */

        /* ---------------------------------------------------------------- */
        /*  Dequantisation: *out_i = ((2*level + Sign(level)) * W * qscl)   */
        /*  / 32. Sign(x)=-1 for x<0, 0 for x=0, +1 for x>0. Division '/':  */
        /*  "Integer division with truncation of the result toward zero.    */
        /*  For example, 7/4 and -7/-4 are truncated to 1 and -7/4 and      */
        /*  7/-4 are truncated to -1." (MPEG-2 Standard Text)               */
        /* ---------------------------------------------------------------- */
            if (neg)
                f1=-3;                                          /* 2*(-1)-1 */
            else
                f1=3;                                              /* 2*1+1 */

        /* ---------------------------------------------------------------- */
        /*  find quantization matrix element at zigzag position and         */
        /*  multiply f1 with W * qscl                                       */
        /* ---------------------------------------------------------------- */
            W = *Wptr++;
            qW = qscl * W;
            f3 = f1 * qW;

        /* ---------------------------------------------------------------- */
        /*  for negative numbers we first need to add 31 before dividing    */
        /*  by 32 to achieve truncation towards zero as required by the     */
        /*  standard.                                                       */
        /* ---------------------------------------------------------------- */
            if (neg) f3 += 31;

        /* ---------------------------------------------------------------- */
        /*  saturate to signed 12 bit word (with /32 <-> >>5 incorporated)  */
        /*  SSHL: shift left and saturate to 32 bits                        */
        /* ---------------------------------------------------------------- */
            f4 = _sshl(f3, 15);
            f5 = (int)(f4 >> shr);
            f5 &= mask;

        /* ---------------------------------------------------------------- */
        /*  mismatch control: determine if sum of coefficents is odd or     */
        /*  even                                                            */
        /* ---------------------------------------------------------------- */
            sum += f5;

        /* ---------------------------------------------------------------- */
        /*  find un-zigzag position of DCT coefficient                      */
        /* ---------------------------------------------------------------- */
            zzptr++;                                            /* always 0 */
            outi[block*64] = f5;
        }

    /* -------------------------------------------------------------------- */
    /*  Decode AC coefficients                                              */
    /* -------------------------------------------------------------------- */
        while (!eob_err)
        {

        /* ---------------------------------------------------------------- */
        /*  Length computation                                              */
        /* ---------------------------------------------------------------- */

        /* ---------------------------------------------------------------- */
        /*  _lnorm returns the number of redundant sign bits in ltop0, e.g. */
        /*  0001 xxxx ... xxxx returns 2, 1111 10xx ... xxxx returns 4.     */
        /*  Example: top=0000 101s xxxx xxxx, then nrm=3                    */
        /* ---------------------------------------------------------------- */
            nrm = _lnorm(ltop0);

        /* ---------------------------------------------------------------- */
        /*  get rid of the leading all 0s/1s.                               */
        /*  Example: t1=0101 sxxx xxxx xxxx                                 */
        /* ---------------------------------------------------------------- */
            t1  = ltop0 << nrm;

        /* ---------------------------------------------------------------- */
        /*  use the number of leading bits (norm) as index,                 */
        /*  Example: t2= xxxx xxxx 0011 rrrr                                */
        /* ---------------------------------------------------------------- */
            t2  = nrm << 4;
            t3 = &IMG_len_tbl0[t2];

        /* ---------------------------------------------------------------- */
        /*  use 4 extra bits after leading bits to distinguish special      */
        /*  cases (40-4=36)                                                 */
        /* ---------------------------------------------------------------- */
            t4  = (unsigned) (t1 >> 36);
        /* ---------------------------------------------------------------- */
        /*  get len and 32-len from tables                                  */
        /* ---------------------------------------------------------------- */
            len  = t3[t4];
            len_c = 32 - len;

        /* ---------------------------------------------------------------- */
        /*  now that we know the length of the current VL code we can       */
        /*  advance bitstream to next one:                                  */
        /*                                                                  */
        /*  1. update ltop0 from ltop0 and top1                             */
        /* ---------------------------------------------------------------- */
            t5  = ltop0 << len;
            t7  = top1 >> len_c;
            top0_bk = (unsigned)(ltop0 >> 8);
            ltop0 = t5 + t7;

        /* ---------------------------------------------------------------- */
        /*  2. update top1 from word1 and word2 after increasing bptr by    */
        /*  len.  if neccesary (i.e. if new bptr is greater than 32)        */
        /*  update word1 and word2 from memory first. Don't forget that     */
        /*  bptr is always relative to the next lower word boundary and     */
        /*  therefore needs to be ANDed with 31 in case it become >=32.     */
        /* ---------------------------------------------------------------- */
            bptr += len;
            test2 = (bptr >= 32);
            if (test2) {
                word1_rw = word1;
                word1 = word2;
                word2 = bsbuf[next_wptr];
                next_wptr += 1;
                next_wptr &= (bsbuf_words-1);
            }
            bptr = bptr & 31;
            bptr_cmpl = 32 - bptr;
            t8 = SHL(word1, bptr);
            t9 = SHR(word2, bptr_cmpl);                   /* unsigned shift */
            top1 = t8 + t9;

        /* ---------------------------------------------------------------- */
        /*  Run-Level Decode                                                */
        /* ---------------------------------------------------------------- */

        /* ---------------------------------------------------------------- */
        /*  check if it is an ESCAPE code which has a unique fixed length   */
        /*  of 24 bits                                                      */
        /* ---------------------------------------------------------------- */
            test1 = len - 24;

            if (!test1)
            {
            /* ------------------------------------------------------------ */
            /* ESCAPE code: no look up required, just extract bits: 6 bits  */
            /* for ESCAPE, 6 bits for RUN, then 12 bits for LEVEL           */
            /* ------------------------------------------------------------ */
                run = _extu(top0_bk, 6, 26);
                level = _ext(top0_bk, 12, 20);
            }
            else
            {
                rld_left = len-5;
                if (len<5) rld_left=0;

                /* -------------------------------------------------------- */
                /*  last 5 bits of VLC incl. sign form 2nd part of index    */
                /* -------------------------------------------------------- */
                rld_index = ((len)<<5) + _extu(top0_bk, rld_left, 32-5);
                run_level = IMG_rld_table0[rld_index];

                run   = run_level >> 8;
                level = (char)run_level;
            }

            eob_err = (run >= 64);

        /* ---------------------------------------------------------------- */
        /*  Run-lengh expansion and DQ                                      */
        /* ---------------------------------------------------------------- */

        /* ---------------------------------------------------------------- */
        /*  Dequantisation: *out_i = ((2*level + Sign(level)) * W * qscl)   */
        /*  / 32. Sign(x)=-1 for x<0, 0 for x=0, +1 for x>0. Division '/':  */
        /*  "Integer division with truncation of the result toward zero.    */
        /*  For example, 7/4 and -7/-4 are truncated to 1 and -7/4 and      */
        /*  7/-4 are truncated to -1." (MPEG-2 Standard Text)               */
        /* ---------------------------------------------------------------- */
            neg = (level < 0);
            f1 = 2*level;

        /* ---------------------------------------------------------------- */
        /*  This needs to be added over intra                               */
        /* ---------------------------------------------------------------- */
            pos = (level > 0);
            f1 = f1 - neg;
            f1 = f1 + pos;

        /* ---------------------------------------------------------------- */
        /*  find quantization matrix element at zigzag position and         */
        /*  multiply f1 with W * qscl                                       */
        /* ---------------------------------------------------------------- */
            if (!eob_err)         /* prevent from accessing memory when EOB */
            {
                W = *(Wptr += run);
                Wptr++;
                /* detect total run overrun */
                eob_err = (Wptr > Wptr_end); //- Wptr_origin)>64;
            }

            qW = qscl * W;
            f3 = f1 * qW;

        /* ---------------------------------------------------------------- */
        /*  for negative numbers we first need to add 31 before dividing    */
        /*  by 32 to achieve truncation towards zero as required by the     */
        /*  standard.                                                       */
        /* ---------------------------------------------------------------- */
            if (neg) f3 += 31;

        /* ---------------------------------------------------------------- */
        /*  saturate to signed 12 bit word (with /32 <-> >>5 incorporated)  */
        /*  SSHL: shift left and saturate to 32 bits                        */
        /* ---------------------------------------------------------------- */
            f4 = _sshl(f3, 15);
            f5 = (int)(f4 >> shr);
            f5 &= mask;

        /* ---------------------------------------------------------------- */
        /*  mismatch control: determine if sum of coefficents is odd or     */
        /*  even                                                            */
        /* ---------------------------------------------------------------- */
            if (!eob_err)
                sum += f5;

        /* ---------------------------------------------------------------- */
        /*  find un-zigzag position of DCT coefficient                      */
        /* ---------------------------------------------------------------- */
            if (!eob_err)         /* prevent from accessing memory when EOB */
                cnum = *(zzptr += run);
            zzptr++;
            if (!eob_err)
                outi[block*64+cnum] = f5;

        } /* while */

    /* -------------------------------------------------------------------- */
    /*  mismatch control: toggle last bit of last coefficient if sum of     */
    /*  coefficents is even.                                                */
    /* -------------------------------------------------------------------- */

        if ((sum & lsb)==0)            // 12Q4
     {
            outi[block*64+63] ^= lsb;  // 12Q4
     }

    /* -------------------------------------------------------------------- */
    /*  Determine nature of fault, invalid code word or exceeding of the    */
    /*  allowed total run of 64.                                            */
    /* -------------------------------------------------------------------- */
    fault = (run>65) || (Wptr > Wptr_end); //- Wptr_origin)>64);

    if (fault) break;

    } /* for */

    /* -------------------------------------------------------------------- */
    /*  rewind bitstream by 8 bits to convert back to 32-bit top0           */
    /* -------------------------------------------------------------------- */
    top0 = (unsigned) (ltop0 >> 8);
    top1 = (top1 >> 8) + (unsigned)(ltop0 << 24);
    bptr = bptr - 8;
    if (bptr<0)
    {
        word2 = word1;
        word1 = word1_rw;
        bptr += 32;
        next_wptr -= 1;
        next_wptr &= (bsbuf_words-1);
    }

    /* -------------------------------------------------------------------- */
    /*  Update bitstream variables                                          */
    /* -------------------------------------------------------------------- */
    Mpeg2v->next_wptr = next_wptr;
    Mpeg2v->bptr      = bptr;
    Mpeg2v->word1     = word1;
    Mpeg2v->word2     = word2;
    Mpeg2v->top0      = top0;
    Mpeg2v->top1      = top1;
    Mpeg2v->fault     = fault;
}

/* ======================================================================== */
/*  End of file:  img_mpeg2_vld_inter.c                                     */
