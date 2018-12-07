#include "Matrix.h"
#ifndef 	DataSet_h
#define		DataSet_h

class Matrix;

class DataSet{
	private:	
	public:
		Matrix* inputSet;	
		Matrix* targetSet;
		
		void SetInputSet( Matrix*);
		void SetTargetSet( Matrix*);
};




#endif
