void bubble_sort_c(int size, int *xp) {
  int i = 0, j = 0;
  for (j = 0; j < size; j += 1) {
    for (i = 0; i < size - 1; i += 1) {
      if (xp[i] > xp[i + 1]) {
        int t = xp[i];
        xp[i] = xp[i + 1];
        xp[i + 1] = t;
      }
    }
  }
  // for (i = 0; i < size; i += 1) {
  //   printf("Sorted i = %d %d", i, xp[i]);
  // }
}