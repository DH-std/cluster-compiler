long DSP_fibonacci
(
  int pos
)
{
  long first, second;
  if (pos == 0) return 0;
  first = 0;
  if (pos == 1) return 1;
  second = 1;
  long tmp;
  int i;
  for (i = 2; i < pos; ++i) {
    tmp = first + second;
    first = second;
    second = tmp;
  }
  return second;
}
