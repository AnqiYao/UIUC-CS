#include "declarations.h"

void
t2(float *restrict A, float *restrict B) {
    #pragma clang loop vectorize(enable)

    for (int nl = 0; nl < 10000000; nl ++) {
        for (int i = 0; i < LEN2; i ++) {
            A[i] = B[i] * A[i];
        }
        A[0] ++;
    }
}
