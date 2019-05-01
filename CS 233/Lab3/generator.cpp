// a code generator for the ALU chain in the 32-bit ALU
// see example_generator.cpp for inspiration

// make generator
// ./generator

#include <cstdio>
#include <iostream>
using namespace std;

int
main() {
    int width = 32;
    printf("  alu0 a0(out[0], carryout[0], A[0],B[0], control[0], control);\n");
    for (int i = 1; i < width; i ++) {
        printf("  alu1 a%d(out[%d],carryout[%d], A[%d], B[%d], carryout[%d], control);\n", i, i, i, i, i, i-1);
    }
}
