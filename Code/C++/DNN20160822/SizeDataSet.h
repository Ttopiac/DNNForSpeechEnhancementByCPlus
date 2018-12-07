#include "Matrix.h"
#include "DataSet.h"
#ifndef 	SizeDataSet_h
#define		SizeDataSet_h

class Matrix;

class SizeDataSet : public DataSet{
	private:
		
	public:
		Matrix* inputSet;	
		Matrix* targetSet;
		SizeDataSet( int, int);
};




#endif
