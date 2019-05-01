#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "transpose.h"

// will be useful
// remember that you shouldn't go over SIZE
using std::min;

// modify this function to add tiling
void
transpose_tiled(int **src, int **dest) {
    for (int i = 0; i < SIZE; i = i +32) {	
        for (int j = 0; j < SIZE; j = j + 32) {
	       
		int litx = SIZE;
		int lity = SIZE;
		if( i + 32 < SIZE)
			litx = i + 32;
		if( j + 32 < SIZE)
			lity = j + 32;

	
		for (int k = i; k < litx; k++){
			for (int m = j; m < lity; m++){
                              dest[k][m] = src[m][k];
				}
			}
        }
    }
}
