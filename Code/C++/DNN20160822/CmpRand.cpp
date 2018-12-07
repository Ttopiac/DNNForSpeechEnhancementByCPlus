#include "CmpRand.h"
#include <math.h>
#include <stdlib.h> 

CmpRand::CmpRand(){
}

CmpRand* CmpRand::getCmpRand(){
	static CmpRand l;
	return &l;
}

double CmpRand::F(double p) {
	double result = 0;
	double r;
	if(p < 0 || p > 1) return result;
	
	r = (double)rand() / (RAND_MAX + 1.0);
    if (r < p) result += 1.0;
    
	return result;
}

double CmpRand::dF(double p) {
	return 0;
}
