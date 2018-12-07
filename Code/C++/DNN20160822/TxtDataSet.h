#include "Matrix.h"
#include "DataSet.h"
#include <string>
using namespace std;

#ifndef 	TxtDataSet_h
#define		TxtDataSet_h

class Matrix;

class TxtDataSet : public DataSet{
	private:
	public:
		TxtDataSet( string, string);
		void SetInputSet( string);
		void SetTargetSet( string);
};




#endif
