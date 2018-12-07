#include "Matrix.h"
#include "ActFunc.h"
#include <stdio.h>

#ifndef CmpRand_h
#define CmpRand_h
/**/


class CmpRand: public ActFunc{	
	private:
		CmpRand();
	public:
	static CmpRand* getCmpRand();
	double F(double);	
	double dF(double);
};

#endif
