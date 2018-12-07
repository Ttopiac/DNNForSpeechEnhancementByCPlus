#include "Matrix.h"
#include "ActFunc.h"
#include <stdio.h>

#ifndef Linear_h
#define Linear_h
/**/


class Linear: public ActFunc{	
	private:
		Linear();
	public:
	static Linear* getLinear();
	double F(double);	
	double dF(double);
};

#endif
