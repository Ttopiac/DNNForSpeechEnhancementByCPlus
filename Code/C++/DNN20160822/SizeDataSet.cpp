#include "SizeDataSet.h"
#include "Matrix.h"


SizeDataSet::SizeDataSet( int inRow, int inCol){
	inputSet = new Matrix( inRow, inCol);
	targetSet = new Matrix( inRow, inCol);	
}
