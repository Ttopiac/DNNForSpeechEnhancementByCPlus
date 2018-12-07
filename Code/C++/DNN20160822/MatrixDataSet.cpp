#include "MatrixDataSet.h"
#include "Matrix.h"
#include <string>
using namespace std;

MatrixDataSet::MatrixDataSet( Matrix* in, Matrix* tar, bool whetherCopy){
	if( whetherCopy){
		inputSet = in->mul(1.0);
		targetSet = tar->mul(1.0);
	}
	else{
		inputSet = in;
		targetSet = tar;		
	}
}

void MatrixDataSet::SetInputSet( Matrix* in, bool whetherCopy){
	delete inputSet;
	if( whetherCopy){
		inputSet = in->mul(1.0);
	}
	else{
		inputSet = in;
	}
}

void MatrixDataSet::SetTargetSet( Matrix* tar, bool whetherCopy){
	delete targetSet;
	if( whetherCopy){
		targetSet = tar->mul(1.0);
	}
	else{
		targetSet = tar;		
	}
}
