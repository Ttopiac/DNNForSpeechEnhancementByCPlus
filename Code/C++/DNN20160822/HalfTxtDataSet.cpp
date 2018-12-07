#include "HalfTxtDataSet.h"
#include "Matrix.h"
#include <string>
using namespace std;

HalfTxtDataSet::HalfTxtDataSet( string inTxt, string tarTxt){
	Matrix* in = new Matrix( inTxt);
	inputSet = in->copyMatrix( 0, in->row/2-1, 0, in->col-1);
	delete in;
	Matrix* tar = new Matrix( tarTxt);	
	targetSet = tar->copyMatrix( 0, tar->row/2-1, 0, tar->col-1);
	delete tar;
}

void HalfTxtDataSet::SetInputSet( string inTxt){
	delete inputSet;
	Matrix* in = new Matrix( inTxt);
	inputSet = in->copyMatrix( 0, in->row/2-1, 0, in->col-1);
	delete in;
}

void HalfTxtDataSet::SetTargetSet( string tarTxt){
	delete targetSet;
	Matrix* tar = new Matrix( tarTxt);	
	targetSet = tar->copyMatrix( 0, tar->row/2-1, 0, tar->col-1);
	delete tar;
}
