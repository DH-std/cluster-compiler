// Need add -std=c99 to compile
unsigned DSP_popCnt(unsigned input) {
  unsigned sum = 0;
  for (unsigned i = 0; i < 32; i++) {
    sum += (input) & 1;
    input = input / 2;
  }
  return sum;
}