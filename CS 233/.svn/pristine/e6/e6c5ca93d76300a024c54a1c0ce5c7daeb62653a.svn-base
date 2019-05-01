#include "mandelbrot.h"
#include <xmmintrin.h>


// cubic_mandelbrot() takes an array of SIZE (x,y) coordinates --- these are
// actually complex numbers x + yi, but we can view them as points on a plane.
// It then executes 200 iterations of f, using the <x,y> point, and checks
// the magnitude of the result; if the magnitude is over 2.0, it assumes
// that the function will diverge to infinity.

// vectorize the code below using SIMD intrinsics
int *
cubic_mandelbrot_vector(float x[SIZE], float y[SIZE]) {
    
/*  
  float x1, y1, x2, y2;

    for (int i = 0; i < SIZE; i ++) {
        x1 = y1 = 0.0;

        // Run M_ITER iterations
        for (int j = 0; j < M_ITER; j ++) {
            // Calculate x1^2 and y1^2
            float x1_squared = x1 * x1;
            float y1_squared = y1 * y1;

            // Calculate the real piece of (x1 + (y1*i))^3 + (x + (y*i))
            x2 = x1 * (x1_squared - 3 * y1_squared) + x[i];

            // Calculate the imaginary portion of (x1 + (y1*i))^3 + (x + (y*i))
            y2 = y1 * (3 * x1_squared - y1_squared) + y[i];

            // Use the resulting complex number as the input for the next
            // iteration
            x1 = x2;
            y1 = y2;
        }

        // caculate the magnitude of the result;
        // we could take the square root, but we instead just
        // compare squares
        ret[i] = ((x2 * x2) + (y2 * y2)) < (M_MAG * M_MAG);
    }
*/
	static int ret[SIZE];
	float temp[4], acc[4], dcc[4], rcc[4];
	__m128 bcc, ccc, ecc, fcc, gcc, hcc, icc, jcc, kcc, mcc, ncc, occ, pcc, qcc, scc, tcc, ucc, X, Y;
	
	for(int k=0; k<4; k++){
		acc[k] =0.0;
		dcc[k] =3.0;  
		rcc[k] = M_MAG * M_MAG;      
	   }
	
		ucc = _mm_loadu_ps(rcc);	//M MAG
		tcc = _mm_loadu_ps(dcc);	//3
		jcc = _mm_loadu_ps(acc);	//0
	
	 
	for (int i = 0 ; i < SIZE; i += 4) {	
			
			bcc = jcc;      //x
			ccc = jcc;	//y

		for(int j = 0; j < M_ITER; j++){

			X = _mm_loadu_ps(&x[i]);
			Y = _mm_loadu_ps(&y[i]);

			ecc = _mm_mul_ps(bcc, bcc);	//x^2
			fcc = _mm_mul_ps(ccc, ccc);	//y^2
			
			gcc = _mm_mul_ps(ecc, tcc);	//3x^2
			hcc = _mm_mul_ps(fcc, tcc);	//3y^2
			
			icc = _mm_sub_ps(ecc, hcc);	//x^2 - 3y^2
			kcc = _mm_sub_ps(gcc, fcc);	//3x^2 - y^2
			
			mcc = _mm_mul_ps(bcc, icc);
			ncc = _mm_mul_ps(ccc, kcc);
				
			occ = _mm_add_ps(mcc, X);
			pcc = _mm_add_ps(ncc, Y);
	
			bcc = occ;
			ccc = pcc;
		}
	
	
		qcc = _mm_add_ps(_mm_mul_ps(occ, occ),_mm_mul_ps(pcc, pcc));
		
		scc = _mm_cmplt_ps(qcc,ucc);
		
		_mm_storeu_ps(temp, scc);
		ret[i] = temp[0];
		ret[i+1] = temp[1];
		ret[i+2] = temp[2];
		ret[i+3] = temp[3]; 
		
	}			
    return ret;
}
