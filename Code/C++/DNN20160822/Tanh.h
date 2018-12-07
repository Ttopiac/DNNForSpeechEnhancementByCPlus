#include "Matrix.h"
#include "ActFunc.h"
#include <stdio.h>

#ifndef Tanh_h
#define Tanh_h
/**/


class Tanh: public ActFunc{	
	private:
		Tanh();
	public:
	static Tanh* getTanh();
	double F(double);	
	double dF(double);
};

#endif
