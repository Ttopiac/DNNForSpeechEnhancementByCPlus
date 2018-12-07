#include "Matrix.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "TxtDataSet.h"
#include "DataSet.h"
#include "LearningDataSet.h"
#include <string>
using namespace std;


LearningDataSet::LearningDataSet(int inputNum, int trainSetSize, int trainSetMin, int trainSetMax, int decimalPrecision, char* testSetFileName){
	string c( "clean (3).txt");
	string n( "noisy (3).txt");
	trainingSet = new TxtDataSet( n, c);
	validationSet = new TxtDataSet( n, c);
	testSet = new TxtDataSet( n, c);
	/*trainingSet = new SizeDataSet( inputNum,trainSetSize);
	//trainingSet->inputSet = trainingSet->inputSet->readMatrixFromTxt(testSetFileName);
	trainingSet->inputSet = trainingSet->inputSet->readMatrixFromTxt(n);
	//trainingSet->inputSet->setAllRand( trainSetMin, trainSetMax, decimalPrecision, false);
	//trainingSet->inputSet->setAllTo(1);
	//trainingSet->targetSet = trainingSet->inputSet->mul(1);
	trainingSet->targetSet = trainingSet->targetSet->readMatrixFromTxt(c);
	validationSet = new SizeDataSet( inputNum,trainSetSize);
	validationSet->inputSet->setAllRand( trainSetMin, trainSetMax, decimalPrecision, false);
	validationSet->targetSet = validationSet->inputSet;
	testSet = new SizeDataSet( inputNum,trainSetSize);
//	testSet->inputSet = testSet->inputSet->readMatrixFromTxt(testSetFileName);
//	testSet->inputSet->setAllRand( trainSetMin, trainSetMax, decimalPrecision, false);
	//trainingSet->inputSet->setAllTo(1);
	testSet->inputSet = trainingSet->inputSet->mul(1);
	testSet->targetSet = trainingSet->targetSet->mul(1);*/
}
