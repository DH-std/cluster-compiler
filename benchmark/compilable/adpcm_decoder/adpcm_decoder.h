#ifndef IMG_ADPCM_CODER_H_
#define IMG_ADPCM_CODER_H_ 1

struct adpcm_state {
    short   valprev;    /* Previous output value */
    char    index;      /* Index into stepsize table */
};

void adpcm_decoder(char indata[], short outdata[], int len, struct adpcm_state *state);

#endif
