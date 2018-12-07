#include "Matrix.h"
#include "DataSet.h"
#include <string>
using namespace std;

#ifndef 	HalfTxtDataSet_h
#define		HalfTxtDataSet_h

class Matrix;

class HalfTxtDataSet : public DataSet{
	private:
	public:
		HalfTxtDataSet( string, string);
		void SetInputSet( string);
		void SetTargetSet( string);
};




#endif
