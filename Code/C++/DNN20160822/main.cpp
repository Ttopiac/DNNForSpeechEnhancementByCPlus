#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Matrix.h"
#include "DataSet.h"
#include "LearningDataSet.h" 
#include "BPLearning.h"
#include "Tanh.h"
#include "Logistic.h"
#include "Layer.h"
#include "FeedForward.h"
#include <vector>
#include <time.h>
#include "RBM.h"
#include "Linear.h"
#include "DataSet.h"
#include "TxtDataSet.h"
#include "HalfTxtDataSet.h"
#include "SizeDataSet.h"
#include "MatrixDataSet.h"
#include <string>
#include <iostream>
#include "LayerList.h"
#include "MatrixList.h"
using namespace std;


int main(int argc, char** argv) {	

/*新版 類神經網路 寫法*/
	srand(time(NULL));
	string file = "11Add1LogNorF";
	string sp[] = {"sp01", "sp02", "sp03", "sp04", "sp05", "sp06", "sp07", "sp08", "sp09", "sp10", "sp11", "sp12", "sp13", "sp14", "sp15", 
					"sp16", "sp17", "sp18", "sp19", "sp20", "sp21", "sp22", "sp23", "sp24", "sp25", "sp26", "sp27", "sp28", "sp29", "sp30"}; 
	int setSize = sizeof(sp)/(sizeof(sp[0]));
	int trainStart = 0;
	int trainSize = 1;					
	int testSize = 10;
	string noiseType[] = { "airport_", "babble_", "car_", "exhibition_", "restaurant_", "station_", "street_", "train_"};
	int typeSize = sizeof(noiseType)/sizeof(noiseType[0]);
	int typeStart = 0;
	int trainType = 4;					
	int testType = 2;
	string noisedB[] = { "0dB", "5dB", "10dB", "15dB"};
	string sn[] = { "sn0", "sn5", "sn10", "sn15"};  
	int snSize = sizeof(sn)/sizeof(sn[0]);
	int snStart = 0;
	int trainSn = snSize;					
	int testSn = snSize;					
	string input( "11Add1LogNorF\\airport_0dB\\0dB\\sp01_airport_sn0.txt");
	string target( "11Add1LogNorF\\clean\\sp01.txt");
	MatrixDataSet* dataSet = new MatrixDataSet( new Matrix(input), new Matrix( target), false);
	ActFunc* t = Tanh::getTanh(); 
	ActFunc* l = Logistic::getLogist(); 
	ActFunc* lin = Linear::getLinear(); 
	LayerList* v = new LayerList();
	vector<RBM*> r;
	double RBMlr = 0.0005;
	int RBMiters = 200;
	double FNlimit = 1000;
	double initialRate = 0.01;
	double nPlus = 1.2;
	double nMinus = 0.5;
	double gradientMax = 0.1; 
	double gradientMin = 0.000001;
	int rbmLayerNum;
	int whetherLin; 
	string errFileName;
	
	int testNum;


	cout<< rbmLayerNum <<endl;
	errFileName.assign( argv[1]);
	trainStart = atoi( argv[2]);
	trainSize = atoi( argv[3]);
	typeStart = atoi( argv[4]);
	trainType = atoi( argv[5]);
	snStart = atoi( argv[6]);
	trainSn = atoi( argv[7]);
	RBMlr = atof( argv[8]);
	RBMiters = atoi(argv[9]);
	FNlimit = atof( argv[10]);
	rbmLayerNum = atoi( argv[11]);
	whetherLin = atoi( argv[12+rbmLayerNum]);
	
	
	cout << "Err File Name:";
	cout<< errFileName <<endl;
	cout << "Clean Sample Start:" ;
	cout<< trainStart <<endl;
	cout << "Clean Sample Size:" ;
	cout<< trainSize <<endl;
	cout << "Noise Type Start:" ;
	cout<< typeStart <<endl;
	cout << "Noise Type Size:" ;
	cout<< trainType <<endl;
	cout << "SNR(dB) Start:" ;
	cout<< snStart <<endl;
	cout << "SNR(dB) Size:" ;
	cout<< trainSn <<endl;
	cout << "RBM Learning Rate:" ;
	cout<< RBMlr <<endl;
	cout << "RBM Epochs:" ;
	cout<< RBMiters <<endl;
	cout<< "FFNN Err Limit: ";
	cout<< FNlimit <<endl;
	cout << "RBM Layers: ";
	cout<< rbmLayerNum <<endl;
	
	if(rbmLayerNum > 0){
		int neuronNum;
		cout << 1;
		cout << " Hidden Neurons: "; 
		neuronNum = atoi(argv[12]);
		v->push_back(new Layer( dataSet->inputSet, neuronNum, l) );
		Layer* layer = v->at(0);
		cout << layer->weight->row <<endl;
		cout << layer->weight->col <<endl;
		r.push_back(new RBM( layer, RBMlr, RBMiters, 1, dataSet->inputSet->col));
		
		for( int i=1; i<rbmLayerNum; i++){
			cout << i + 1;
			cout << " Hidden Neurons: ";
			neuronNum = atoi(argv[12+i]);
			cout << neuronNum << endl;
			v->push_back(new Layer( v->at(i-1)->output, neuronNum, l) );
			r.push_back(new RBM( v->at(i), RBMlr, RBMiters, 1, dataSet->inputSet->col));
		}
		for( int i=rbmLayerNum, j=1; i<rbmLayerNum*2-1; i++, j++){
			neuronNum = atoi(argv[12+rbmLayerNum-j]);
			v->push_back(new Layer( v->at(i-1)->output, neuronNum, l) );
		}
		v->push_back( new Layer( v->at(rbmLayerNum*2-2)->output, dataSet->targetSet->row, l) );			
		
		cout << " Do you want to add a linear layer?";
		if( whetherLin>0){
			v->push_back( new Layer( v->at(rbmLayerNum*2-1)->output, dataSet->targetSet->row, lin) );		
			delete v->at( v->size()-1)->weight;
			v->at( v->size()-1)->weight = new Matrix( dataSet->targetSet->row);
			cout << "Yes" << endl;
		}
		else{
			cout << "No" << endl;
		}
	}
	else{
		cout << " Do you want to add a linear layer?";
		if( whetherLin>0){
			v->push_back( new Layer( dataSet->inputSet, dataSet->targetSet->row, lin) );		
			delete v->at( v->size()-1)->weight;
			v->at( v->size()-1)->weight = new Matrix( dataSet->targetSet->row);
			cout << "Yes" << endl;
		}
		else{
			cout << "No" << endl;
		}
	}
	
	

	Matrix* rDS;
	Matrix* ds;
	cout<<  "Start PreLearning: ";	
	cout<< trainSize*trainType*trainSn << endl;
	Matrix* allInFile = new Matrix( 0, 0);
	Matrix* allTarFile = new Matrix( 0, 0);
	for(int dBi=snStart, cntdB=0; cntdB<trainSn; dBi=(dBi+1)%snSize, cntdB++){
		for(int type=typeStart, cntType=0; cntType<trainType ; type=(type+1)%typeSize, cntType++){
			for( int spi=trainStart, cntSpi=0; cntSpi<trainSize; spi=(spi+1)%setSize, cntSpi++){
				target = file + "\\" + "clean" + "\\" + sp[spi] + ".txt";
				Matrix* partTar = new Matrix( target);
				allTarFile->MergeHorizontal( partTar);
				input = file + "\\" + noiseType[type] + noisedB[dBi] + "\\" + noisedB[dBi] + "\\"+ sp[spi] + "_" + noiseType[type] + sn[dBi] + ".txt";
				Matrix* partIn = new Matrix( input);
				allInFile->MergeHorizontal( partIn);
				cout<<  spi*testType*testSn+type*testSn+dBi+1;	
				cout<<  ": " + target << endl;
				cout<<  ": " + input << endl;
				cout<<  allInFile->row << endl;
				cout<<  allInFile->col << endl;
			}
		}
	}
	dataSet->SetInputSet(allInFile, true);
	dataSet->SetTargetSet(allTarFile, true);
	cout<<  allInFile->row << endl;
	cout<<  allInFile->col << endl;
	delete allInFile;
	delete allTarFile;
	
	
	rDS = dataSet->inputSet->mul(1.0);
	for( int i=0; i<rbmLayerNum; i++){
		r[i]->LearnByCD( rDS);	
		ds = rDS->mul(1);
		delete rDS; 
		rDS = r[i]->propup( ds);
		delete ds;
	}
	delete rDS;	

	cout<<  "PreLearning is finished\n" << endl;
	for( int i=0; i<rbmLayerNum; i++){
		delete v->at(i+rbmLayerNum)->weight;
		v->at(i+rbmLayerNum)->weight = v->at(rbmLayerNum-i-1)->weight->transpose();
	}
	
	
	cout<<  "Start Fine-tuning: ";	
	cout<< trainSize*trainType*trainSn << endl;
	FeedForward* FN = new FeedForward( v);
	clock_t t1, t2;
    t1 = clock();
	//Matrix* errRecord = FN->LearnByBP( initialRate, FNlimit, dataSet);
	Matrix* errRecord = FN->LearnByRPROP( initialRate, nPlus, nMinus, gradientMax, gradientMin, FNlimit, dataSet);
	t2 = clock();
    printf("%lf\n", (t2-t1)/(double)(CLOCKS_PER_SEC));
	errRecord->writeMatrixToTxt( errFileName, false);
	v->writeLayerListToTxt("weight" + errFileName);
	cout<<  "Fine-tuning is finished" << endl;	
	cout<<  "DNN Learning is completed\n" << endl;
	
	
	cout<<  "Start Testing: ";	
	Matrix* testErrRecord = new Matrix( 0, 0);
	Matrix* nowTestErr;
	testNum = atoi( argv[13+rbmLayerNum]);
	cout<< testNum << endl;
	for( int testI=0; testI<testNum; testI++){
		cout<< trainSize*trainType*trainSn << endl;
		allInFile = new Matrix( 0, 0);
		allTarFile = new Matrix( 0, 0);
		int testSnStart = atoi( argv[18+rbmLayerNum+6*testI]);
		int testTrainSn = atoi( argv[19+rbmLayerNum+6*testI]);
		int testTypeStart = atoi( argv[16+rbmLayerNum+6*testI]);
		int testTrainType = atoi( argv[17+rbmLayerNum+6*testI]);
		int testTrainStart = atoi( argv[14+rbmLayerNum+6*testI]);
		int testTrainSize = atoi( argv[15+rbmLayerNum+6*testI]);
		for(int dBi=testSnStart, cntdB=0; cntdB<testTrainSn; dBi=(dBi+1)%snSize, cntdB++){
			for(int type=testTypeStart, cntType=0; cntType<testTrainType ; type=(type+1)%typeSize, cntType++){
				for( int spi=testTrainStart, cntSpi=0; cntSpi<testTrainSize; spi=(spi+1)%setSize, cntSpi++){
					target = file + "\\" + "clean" + "\\" + sp[spi] + ".txt";
					Matrix* partTar = new Matrix( target);
					allTarFile->MergeHorizontal( partTar);
					input = file + "\\" + noiseType[type] + noisedB[dBi] + "\\" + noisedB[dBi] + "\\"+ sp[spi] + "_" + noiseType[type] + sn[dBi] + ".txt";
					Matrix* partIn = new Matrix( input);
					allInFile->MergeHorizontal( partIn);
					cout<<  spi*testType*testSn+type*testSn+dBi+1;	
					cout<<  ": " + target << endl;
					cout<<  ": " + input << endl;
					cout<<  allInFile->row << endl;
					cout<<  allInFile->col << endl;
				}
			}
		}
		dataSet->SetInputSet(allInFile, true);
		dataSet->SetTargetSet(allTarFile, true);
		cout<<  allInFile->row << endl;
		cout<<  allInFile->col << endl;	
		delete allInFile;
		delete allTarFile;	
		cout<< "Testing Err:";
		nowTestErr = new Matrix( 1, 1);
		nowTestErr->matrix[0][0] = FN->Forward(dataSet);
		cout<< nowTestErr->matrix[0][0]  << endl;
		testErrRecord->MergeHorizontal( nowTestErr);
	}
	testErrRecord->writeMatrixToTxt( "test" + errFileName, false);


	
	

	
	return 0;
}


