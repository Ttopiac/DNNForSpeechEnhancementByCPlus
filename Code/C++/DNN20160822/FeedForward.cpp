#include "FeedForward.h"
#include <stdio.h>
#include <stdlib.h>
#include "LayerList.h"
#include "MatrixList.h"
#include <iostream>

FeedForward::FeedForward( LayerList* llist){
	//layerList->assign(llist->begin(), llist->end());
	layerList = llist;
	numOfLayers = layerList->size();
} 

/*有關vector的記憶體是否需要處理?*/
FeedForward::~FeedForward(){
	
}

double FeedForward::Forward( DataSet* dataSet){
	Matrix* I = dataSet->inputSet->mul(1.0);
	Matrix* T = dataSet->targetSet->mul(1.0);
	if(I->row != layerList->at(0)->input->row){
		printf("\nErr: In Forward function, the row size of the input matrix isn't as same as the row size of DataSet's input\n");
	}
	else if( T->row != layerList->at(numOfLayers-1)->output->row){
		printf("\nErr: In Forward function, the row size of the output matrix isn't as same as the row size of DataSet's output\n");
	}
	delete layerList->at(0)->input;
	layerList->at(0)->input = I->mul(1);
	Matrix* outputF;
	
	for( int i=0; i<numOfLayers; i++){
		delete layerList->at(i)->output;
		layerList->at(i)->output = layerList->at(i)->weight->MmultiMatrix( layerList->at(i)->input);
		/*最後一層的輸出不必輸出至下一層的輸入*/
		outputF = layerList->at(i)->output->F(layerList->at(i)->actF);
		delete layerList->at(i)->output;
		layerList->at(i)->output = outputF->mul(1);
		if(i<numOfLayers-1){
			delete layerList->at(i+1)->input;
			layerList->at(i+1)->input = layerList->at(i)->output->mul(1);
		}
		delete outputF;
	}
	double err = Err( layerList->at(numOfLayers-1)->output, T);
	delete I;
	delete T;
	return err;
}

double FeedForward::Forward( Matrix* I, Matrix* T){
	if(I->row != layerList->at(0)->input->row){
		printf("\nErr: In Forward function, the row size of the input matrix isn't as same as the row size of DataSet's input\n");
	}
	if( T->row != layerList->at(numOfLayers-1)->output->row){
		printf("\nErr: In Forward function, the row size of the output matrix isn't as same as the row size of DataSet's output\n");
	}
	delete layerList->at(0)->input;
	layerList->at(0)->input = I->mul(1);
	Matrix* outputF;
	for( int i=0; i<numOfLayers; i++){
		delete layerList->at(i)->output;
		layerList->at(i)->output = layerList->at(i)->weight->MmultiMatrix( layerList->at(i)->input);
		/*最後一層的輸出不必輸出至下一層的輸入*/
		outputF = layerList->at(i)->output->F(layerList->at(i)->actF);
		delete layerList->at(i)->output;
		layerList->at(i)->output = outputF->mul(1);
		if(i<numOfLayers-1){
			delete layerList->at(i+1)->input;
			layerList->at(i+1)->input = layerList->at(i)->output->mul(1);
		}
		delete outputF;
	}
	
	return Err( layerList->at(numOfLayers-1)->output, T);
}

MatrixList* FeedForward::GetPartialElementList( Matrix* T){
	Matrix* L= Loss(layerList->at(numOfLayers-1)->output, T);
	Matrix* gradient;
	Matrix* newL;
	Matrix* dL;
	Matrix* dOut; 
	Matrix* tran;
	Matrix* gradientFinal;
	MatrixList* gradientPostOrderList = new MatrixList();
	for(int i=numOfLayers-1; i>=0; i--){
		dOut = layerList->at(i)->output->dF(layerList->at(i)->actF);
		dL = L->mul(dOut);	
		delete dOut;
		delete L;
		L = dL->mul(1);
		delete dL;
		tran = layerList->at(i)->input->transpose();
		gradient = L->MmultiMatrix(tran); 
		gradient->SetSign();
		gradientPostOrderList->push_back( gradient);
		delete tran;
		tran = layerList->at(i)->weight->transpose();
		newL = tran->MmultiMatrix(L); 
		delete tran;
		delete L;
		L = newL->mul(1);
		delete newL;
	}
	delete L;
	MatrixList* gradientList = new MatrixList();
	for( int i=gradientPostOrderList->size()-1; i>=0; i--){
		gradientList->push_back( gradientPostOrderList->at(i)->mul(1.0));
	}
	gradientPostOrderList->DeleteMatrixList();
	delete gradientPostOrderList;
	return gradientList;
}

void FeedForward::UpdateWeight( MatrixList* gradientList){
	if( layerList->size() == gradientList->size()){
		Matrix* gradient; 
		for( int i=0; i<layerList->size(); i++){
			gradient = layerList->at(i)->weight->add(gradientList->at(i));
			delete layerList->at(i)->weight;
			layerList->at(i)->weight = gradient->mul(1.0);
			delete gradient;
		}
	}
	else{
		printf("\nError: FeedForward的UpdateWeight輸入的gradientList與FeedForward的layerList大小不同\n");
	}
}

void FeedForward::BackProp(  Matrix* T, double learningRate){
	Matrix* L= Loss(layerList->at(numOfLayers-1)->output, T);
	Matrix* gradient;
	Matrix* newL;
	Matrix* dL;
	Matrix* dOut; 
	Matrix* tran;
	Matrix* gradientFinal;
	Matrix* newW; 
	for(int i=numOfLayers-1; i>=0; i--){
		dOut = layerList->at(i)->output->dF(layerList->at(i)->actF);
		dL = L->mul(dOut);	
		delete dOut;
		delete L;
		L = dL->mul(1);
		delete dL;
		tran = layerList->at(i)->input->transpose();
		gradient = L->MmultiMatrix(tran); 
		delete tran;
		tran = layerList->at(i)->weight->transpose();
		newL = tran->MmultiMatrix(L); 
		delete tran;
		delete L;
		L = newL->mul(1);
		delete newL;
		gradientFinal = gradient->mul(learningRate);
		delete gradient; 
		newW = layerList->at(i)->weight->sub(gradientFinal);
		delete layerList->at(i)->weight;
		layerList->at(i)->weight = newW->mul(1);
		delete gradientFinal;
		delete newW;
	}
	delete L;
	
}

Matrix* FeedForward::LearnByRPROP( double initial, double nPlus, double nMinus, double gradientMax, double gradientMin, double errTarget, DataSet* dataSet){
	Matrix* I;
	Matrix* T;
	int Iters = 0;
	I = dataSet->inputSet->mul(1);
	T = dataSet->targetSet->mul(1);
	MatrixList* partialOldElement = new MatrixList();
	MatrixList* partialNowElement = NULL;
	MatrixList* updataOldValue = new MatrixList();
	MatrixList* updataNowValue = NULL;
	MatrixList* updataOldWeightValue = new MatrixList();
	MatrixList* updataNowWeightValue = NULL;
	double	err = errTarget+1;
	Matrix* errRecord = new Matrix( 0, 0);
	err = Forward( I, T);
	Matrix* nowErr = new Matrix( 1, 1);
	nowErr->matrix[0][0] = err;
	errRecord->MergeHorizontal( nowErr);
	
	while( err > errTarget){
		if( Iters > 0){		
			partialOldElement->SetMatrixList( partialNowElement);
			partialNowElement = GetPartialElementList( T); 
			updataOldValue->DeleteMatrixList();
			delete updataOldValue;
			updataOldValue = updataNowValue->CopyThisMatrixList();
			updataOldWeightValue->DeleteMatrixList();
			delete updataOldWeightValue;
			updataOldWeightValue = updataNowWeightValue->CopyThisMatrixList();
			for( int i=0; i<partialNowElement->size(); i++){
				for( int j=0, r=partialNowElement->at(i)->row, c=partialNowElement->at(i)->col; j<r*c; j++){
					double cat = partialOldElement->at(i)->oriMatrix[j] * partialNowElement->at(i)->oriMatrix[j];
					if( cat > 0){
						if( nPlus*updataOldValue->at(i)->oriMatrix[j] < gradientMax){
							updataNowValue->at(i)->oriMatrix[j] = nPlus*updataOldValue->at(i)->oriMatrix[j];
						}else{
							updataNowValue->at(i)->oriMatrix[j] = gradientMax;
						}
						updataNowWeightValue->at(i)->oriMatrix[j] = partialNowElement->at(i)->oriMatrix[j]*(-1)*updataNowValue->at(i)->oriMatrix[j];
					}
					else if( cat < 0){
						if( nMinus*updataOldValue->at(i)->oriMatrix[j] > gradientMin){
							updataNowValue->at(i)->oriMatrix[j] = nMinus*updataOldValue->at(i)->oriMatrix[j];
						}else{
							updataNowValue->at(i)->oriMatrix[j] = gradientMin;
						}
						updataNowWeightValue->at(i)->oriMatrix[j] = updataOldWeightValue->at(i)->oriMatrix[j]*(-1);
						partialNowElement->at(i)->oriMatrix[j] = 0;
					}
					else{
						updataNowWeightValue->at(i)->oriMatrix[j] = partialNowElement->at(i)->oriMatrix[j]*(-1)*updataNowValue->at(i)->oriMatrix[j];	
					}
				}
			}
		}
		else{
			partialNowElement = GetPartialElementList( T); 
			updataNowValue = partialNowElement->CopyThisMatrixList();
			updataNowValue->SetAllTo( initial);
			updataNowWeightValue = partialNowElement->CopyThisMatrixList();
			updataNowWeightValue->SetMul(-1);
			updataNowWeightValue->SetMul( updataNowValue);
		}
		UpdateWeight( updataNowWeightValue);
		Iters++;
		err = Forward( I, T);
		nowErr = new Matrix( 1, 1);
		nowErr->matrix[0][0] = err;
		errRecord->MergeHorizontal( nowErr);
		if( Iters%1==0){
			printf("LearningLossFor %d iterations: %le\n", Iters+1, err);	
		}
		else{
		}

		
	}
	if( Iters>=1){
		partialOldElement->DeleteMatrixList();
		delete partialOldElement;
		partialNowElement->DeleteMatrixList();
		delete partialNowElement;
		updataOldValue->DeleteMatrixList();
		delete updataOldValue;
		updataNowValue->DeleteMatrixList();
		delete updataNowValue;
		updataOldWeightValue->DeleteMatrixList();
		delete updataOldWeightValue;
		updataNowWeightValue->DeleteMatrixList();
		delete updataNowWeightValue;	
	}
	else{
		partialOldElement->DeleteMatrixList();
		delete partialOldElement;
		updataOldValue->DeleteMatrixList();
		delete updataOldValue;
		updataOldWeightValue->DeleteMatrixList();
		delete updataOldWeightValue;
	}
	
	
	printf("Learning Complete\n");
	delete I;
	delete T;
	return errRecord;
}

Matrix* FeedForward::LearnByBP( double learningRate, double errTarget, DataSet* dataSet){
	Matrix* I;
	Matrix* T;
	int Iters = 0;
	I = dataSet->inputSet->mul(1);
	T = dataSet->targetSet->mul(1);
	double	err = errTarget+1;
	Matrix* errRecord = new Matrix( 0, 0);
	err = Forward( I, T);
	Matrix* nowErr = new Matrix( 1, 1);
	nowErr->matrix[0][0] = err;
	errRecord->MergeHorizontal( nowErr);
	while( err > errTarget){
		BackProp( T, learningRate);
		Iters++;
		err = Forward( I, T);
		nowErr = new Matrix( 1, 1);
		nowErr->matrix[0][0] = err;
		errRecord->MergeHorizontal( nowErr);
		if( Iters%10==0){
			printf("LearningLossFor %d iterations: %le\n", Iters+1, err);	
		}
		else{
		}
	}
	printf("Learning Complete\n");
	delete I;
	delete T;
	return errRecord;
}

Matrix* FeedForward::LearnByBP( double learningRate, int numIters, DataSet* dataSet){
	Matrix* I;
	Matrix* T;
	I = dataSet->inputSet->mul(1);
	T = dataSet->targetSet->mul(1);
	double		err;
	Matrix* errRecord = new Matrix(1,numIters);
	for( int Iters=0; Iters<numIters; Iters++){
		err = Forward( I, T);
		if( Iters%10==0){
			printf("LearningLossFor %d iterations: %le\n", Iters+1, err);	
		}
		else{
		}
		errRecord->matrix[0][Iters] = err;
		BackProp( T, learningRate);
	}
	printf("Learning Complete\n");
	delete I;
	delete T;
	return errRecord;
}

Matrix* FeedForward::LearnByBP( double learningRate, int numIters, DataSet* dataSet, int miniBatchSize){
	Matrix* I;
	Matrix* T;
	double		err;
	Matrix* errRecord = new Matrix(1,numIters);
	for( int Iters=0; Iters<numIters; Iters++){
		I = dataSet->inputSet->copyMatrix( 0, dataSet->inputSet->row-1, Iters*miniBatchSize%(dataSet->inputSet->col), Iters*miniBatchSize%(dataSet->inputSet->col)+miniBatchSize-1);
		T = dataSet->targetSet->copyMatrix( 0, dataSet->targetSet->row-1, Iters*miniBatchSize%(dataSet->targetSet->col), Iters*miniBatchSize%(dataSet->targetSet->col)+miniBatchSize-1);
		err = Forward( I, T);
		if( Iters%10==0){
			printf("LearningLossFor %d iterations: %le\n", Iters+1, err);	
		}
		else{
		}
		errRecord->matrix[0][Iters] = err;
		BackProp( T, learningRate);
		delete I;
		delete T;
	}
	printf("Learning Complete\n");
	return errRecord;
} 

Matrix* FeedForward::Loss( Matrix* O, Matrix* T){
	Matrix* oSt = O->sub(T);
	Matrix* loss = oSt->div(O->col);
	delete oSt; 
	return loss;
}

double FeedForward::Err( Matrix* O, Matrix* T){
	double num;
	Matrix* tSo = T->sub(O);
	Matrix* tSo2 = tSo->mul(tSo);
	num = tSo2->Sum();
	num = num/2;
	num = num/(O->col);
	delete tSo;
	delete tSo2;
	return num;
}


