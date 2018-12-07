#include "TxtDataSet.h"
#include "Matrix.h"
#include <string>
using namespace std;

TxtDataSet::TxtDataSet( string inTxt, string tarTxt){
	inputSet = new Matrix( inTxt);
	targetSet = new Matrix( tarTxt);	
}

void TxtDataSet::SetInputSet( string inTxt){
	delete inputSet;
	inputSet = new Matrix( inTxt);
}

void TxtDataSet::SetTargetSet( string tarTxt){
	delete targetSet;
	targetSet = new Matrix( tarTxt);
}
