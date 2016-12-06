#include <stdio.h>

int fibonacci(int pos) {
  int first, second;
  if (pos == 0) return 0;
  first = 0;
  if (pos == 1) return 1;
  second = 1;
  int tmp;
  for (int i = 2; i < pos; ++i) {
    tmp = first + second;
    first = second;
    second = tmp;
  }
  return second;
}

int main() {
  int res = fibonacci(6);
  printf("%d", res);
  return 0;
}
