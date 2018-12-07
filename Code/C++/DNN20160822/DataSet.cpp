#include "DataSet.h"
#include "Matrix.h"

void DataSet::SetInputSet( Matrix* in){
	delete inputSet;
	inputSet = in;
}

void DataSet::SetTargetSet( Matrix* tar){
	delete targetSet;
	targetSet = tar;
}
