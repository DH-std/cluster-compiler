#include <stdio.h>
#include <stdlib.h>

/* Header file for the DSPLIB function */
#include "fibonacci.h"
#include "support.h"

/* Header file for the C function */
long fibonacci(int pos);

int main()
{
    settime();
    fibonacci(40);
    gettime();

    fibonacci_c(40);
}
