#include "Matrix.h"
#include "ActFunc.h"
#include <stdio.h>

#ifndef Logistic_h
#define Logistic_h
/**/


class Logistic: public ActFunc{	
	private:
		Logistic();
	public:
	static Logistic* getLogist();
	double F(double);	
	double dF(double);
};

#endif
