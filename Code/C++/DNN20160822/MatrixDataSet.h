#include "Matrix.h"
#include "DataSet.h"
#include <string>
using namespace std;

#ifndef 	MatrixDataSet_h
#define		MatrixDataSet_h

class Matrix;

class MatrixDataSet : public DataSet{
	private:
	public:
		MatrixDataSet( Matrix*, Matrix*, bool whetherCopy);
		void SetInputSet( Matrix*, bool whetherCopy);
		void SetTargetSet( Matrix*, bool whetherCopy);
};




#endif
