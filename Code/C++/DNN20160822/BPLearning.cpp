#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Matrix.h"
#include "FFNN.h"
#include "DataSet.h"
#include "LearningDataSet.h" 
#include "BPLearning.h"

#include "Weight.h"

BPLearning::BPLearning(LearningDataSet* lDS, int nN, int nI, double lR, double momM, bool dES, int miniBS){
	dataSet = lDS;
	numOfNeuron = nN;
	numIters = nI;
	learningRate = lR;
	momentumMultiplier = momM;
	doEarlyStoping = dES;
	miniBatchSize = miniBS;
}

void BPLearning::runBPLearning(){
	DataSet* batchData = new DataSet(dataSet->trainingSet->inputSet->row, miniBatchSize);
	Weight* gradient;
	FFNN* trainFN = new FFNN( batchData, numOfNeuron);
	Weight* momentumSpeed = trainFN->weight->mul(0.0);
	trainFN->InitialWeight();
	for( int Iters=0; Iters<numIters; Iters++){
		batchData->inputSet = dataSet->trainingSet->inputSet->copyMatrix( 0, dataSet->trainingSet->inputSet->row-1, Iters*miniBatchSize%(dataSet->trainingSet->inputSet->col), Iters*miniBatchSize%(dataSet->trainingSet->inputSet->col)+miniBatchSize-1);
		batchData->targetSet = batchData->inputSet;
		trainFN->ForwardPass(batchData);
		printf("LearningLossFor%diterations: %le\n", Iters+1,trainFN->Loss());
		gradient = trainFN->dLossBydModel();
		momentumSpeed = momentumSpeed->mul(momentumMultiplier)->sub(gradient);
		trainFN->weight = momentumSpeed->mul(learningRate)->add(trainFN->weight); 
	}	
	printf("Learning Complete\n");
	FFNN* testFN = new FFNN( dataSet->testSet, numOfNeuron);
	testFN->weight = trainFN->weight;
	testFN->ForwardPass(dataSet->testSet);	
	testFN->Input->priMatrix( 0, testFN->Output->row-1, testFN->Output->col-5, testFN->Output->col-1);
	testFN->Output->priMatrix( 0, testFN->Output->row-1, testFN->Output->col-5, testFN->Output->col-1);
	//testFN->Output->priMatrix();
	printf("TestingLoss: %le\n", testFN->Loss());

}
 

