#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include "FFNN.h"
#include "Weight.h"
#include "Matrix.h"


FFNN::FFNN(DataSet* ds, int numHid){
	
	
	
	if(ds->inputSet->row == 2){
		NumOfNeuron = numHid;
		NormalizParameter = 1;
		
		Input = ds->inputSet;	
		ClassoneOut = new Matrix(NumOfNeuron, Input->col);
		ClassoneOut->setAllTo(1);
		En = new Matrix(Input->row, Input->col);			
		En->setAllTo(1);
		ClasstwoOut = new Matrix(NumOfNeuron, Input->col);
		ClasstwoOut->setAllTo(1);		
		Output = new Matrix(Input->row, Input->col);
		Output->setAllTo(1);
		target = ds->targetSet;	
		weight = new Weight( Input->row, numHid);
		maxDoubleElement = 0;	

		
		IntMatrix* intm = Input->ConversionIntType();
		InputNormal = intm;		
		InputNormal->setAllTo(1);
		InputToClassoneNormal = new IntMatrix(numHid, intm->row);
		InputToClassoneNormal->setAllTo(1);
		ClassoneToEnNormal = new IntMatrix(intm->row, numHid);
		ClassoneToEnNormal->setAllTo(1);		
		EnNormal = new IntMatrix(intm->row, intm->col);			
		EnNormal->setAllTo(1);
		EnToClasstwoNormal = new IntMatrix(numHid, intm->row);
		EnToClasstwoNormal->setAllTo(1);
		ClasstwoToOutputNormal = new IntMatrix(intm->row, numHid); 		
		ClasstwoToOutputNormal->setAllTo(1);
		OutputNormal = new IntMatrix(intm->row, intm->col);
		OutputNormal->setAllTo(1);
		maxIntElement = 0;


		delete intm;
	}
	else{
		printf("\nError : 輸入類神經程式的內容非正常的陣列，應該為2*N的陣列(N為任一整數)\n");
	}
	
}


void FFNN::InitialWeight(){
	weight->Initial();
}

void FFNN::EncryptedPass(){
	Matrix* middle = new Matrix(NumOfNeuron, Input->col);
	
	if(Input->MaxAbsElement() > maxDoubleElement){
		maxDoubleElement = Input->MaxAbsElement();
	}
	if(weight->InputToClassone->MaxAbsElement() > maxDoubleElement){
		maxDoubleElement = weight->InputToClassone->MaxAbsElement();
	}
	middle = weight->InputToClassone->MmultiMatrix(Input);	
	if(middle->MaxAbsElement() > maxDoubleElement){
		maxDoubleElement = middle->MaxAbsElement();
	}
	ClassoneOut = middle->MyTanh();	
	//ClassoneOut = middle->Hd16bitsTanh();
	//ClassoneOut = middle->Hd8bitsTanh();	
	if(ClassoneOut->MaxAbsElement() > maxDoubleElement){
		maxDoubleElement = ClassoneOut->MaxAbsElement();
	}
	if(weight->ClassoneToEn->MaxAbsElement() > maxDoubleElement){
		maxDoubleElement = weight->ClassoneToEn->MaxAbsElement();
	}
	En = weight->ClassoneToEn->MmultiMatrix(ClassoneOut);
	if(En->MaxAbsElement() > maxDoubleElement){
		maxDoubleElement = En->MaxAbsElement();	
	}

	delete middle;	
}

void FFNN::DecryptedPass(){
	Matrix* middle = new Matrix(NumOfNeuron, Input->col);	
	
	if(weight->EnToClasstwo->MaxAbsElement() > maxDoubleElement){
		maxDoubleElement = weight->EnToClasstwo->MaxAbsElement();
	}
	middle = weight->EnToClasstwo->MmultiMatrix(En);
	if(middle->MaxAbsElement() > maxDoubleElement){
		maxDoubleElement = middle->MaxAbsElement();
	}	
	ClasstwoOut = middle->MyTanh();
	//ClasstwoOut = middle->Hd16bitsTanh();
	//ClasstwoOut = middle->Hd8bitsTanh();
	if(ClasstwoOut->MaxAbsElement() > maxDoubleElement){
		maxDoubleElement = ClasstwoOut->MaxAbsElement();
	}
	if(weight->ClasstwoToOutput->MaxAbsElement() > maxDoubleElement){
		maxDoubleElement = weight->ClasstwoToOutput->MaxAbsElement();
	}
	Output = weight->ClasstwoToOutput->MmultiMatrix(ClasstwoOut);	
	if(Output->MaxAbsElement() > maxDoubleElement){
		maxDoubleElement = Output->MaxAbsElement();	
	}
		
	delete middle;
}

void FFNN::ForwardPass(DataSet* ds){
	Input = ds->inputSet;
	target = ds->targetSet;
	EncryptedPass();
	DecryptedPass();
}                                                                                                                                                               



void FFNN::EncryptedNormalPass(){
	IntMatrix* middleInt = new IntMatrix(NumOfNeuron, InputNormal->col);
	Matrix* middle = new Matrix(NumOfNeuron, Input->col);
	
	InputNormal = Input->NormalizatIntType(NormalizParameter);
	InputToClassoneNormal = weight->InputToClassone->NormalizatIntType(NormalizParameter);
	ClassoneToEnNormal = weight->ClassoneToEn->NormalizatIntType(NormalizParameter);
	
	if(InputNormal->MaxAbsElement() > maxIntElement){
		maxIntElement = InputNormal->MaxAbsElement();
	}
	if(InputToClassoneNormal->MaxAbsElement() > maxIntElement){
		maxIntElement = InputToClassoneNormal->MaxAbsElement();
	}
	middleInt = InputToClassoneNormal->MmultiMatrix(InputNormal);
	if(middleInt->MaxAbsElement() > maxIntElement){
		maxIntElement = middleInt->MaxAbsElement();	
	}
	middle = middleInt->NormalizatDoubleType(NormalizParameter*NormalizParameter);
	middle = middle->MyTanh();
	middleInt = middle->NormalizatIntType(NormalizParameter);
	if(middleInt->MaxAbsElement() > maxIntElement){
		maxIntElement = middleInt->MaxAbsElement();	
	}
	if(ClassoneToEnNormal->MaxAbsElement() > maxIntElement){
		maxIntElement = ClassoneToEnNormal->MaxAbsElement();			
	}
	middleInt = ClassoneToEnNormal->MmultiMatrix(middleInt);
	if(middleInt->MaxAbsElement() > maxIntElement){
		maxIntElement = middleInt->MaxAbsElement();	
	}
	En = middleInt->NormalizatDoubleType(NormalizParameter*NormalizParameter);
	
	delete middle;	
	delete middleInt;
	
}

void FFNN::DecryptedNormalPass(){
	IntMatrix* middleInt = new IntMatrix(NumOfNeuron, InputNormal->col);
	Matrix* middle = new Matrix(NumOfNeuron, Input->col);
	
	EnNormal = En->NormalizatIntType(NormalizParameter); 
	EnToClasstwoNormal = weight->EnToClasstwo->NormalizatIntType(NormalizParameter);
	ClasstwoToOutputNormal = weight->ClasstwoToOutput->NormalizatIntType(NormalizParameter);
	
	if(EnNormal->MaxAbsElement() > maxIntElement){
		maxIntElement = EnNormal->MaxAbsElement();		
	}
	if(EnToClasstwoNormal->MaxAbsElement() > maxIntElement){
		maxIntElement = EnToClasstwoNormal->MaxAbsElement();
	}
	middleInt = EnToClasstwoNormal->MmultiMatrix(EnNormal);
	if(middleInt->MaxAbsElement() > maxIntElement){
		maxIntElement = middleInt->MaxAbsElement();	
	}
	middle = middleInt->NormalizatDoubleType(NormalizParameter*NormalizParameter);
	middle = middle->MyTanh();
	middleInt = middle->NormalizatIntType(NormalizParameter);
	if(middleInt->MaxAbsElement() > maxIntElement){
		maxIntElement = middleInt->MaxAbsElement();
	}	
	if(ClasstwoToOutputNormal->MaxAbsElement() > maxIntElement){
		maxIntElement = ClasstwoToOutputNormal->MaxAbsElement();					
	}
	middleInt = ClasstwoToOutputNormal->MmultiMatrix(middleInt);	
	if(middleInt->MaxAbsElement() > maxIntElement){
		maxIntElement = middleInt->MaxAbsElement();	
	}
	Output = middleInt->NormalizatDoubleType(NormalizParameter*NormalizParameter);
	
	delete middle;	
	delete middleInt;
	
}

void FFNN::ForwardNormalPass(){
	EncryptedNormalPass();
	DecryptedNormalPass();
}

double FFNN::Loss(){
	Matrix* mm = new Matrix(Input->row, Input->col);
	double num;
	mm = target->sub(Output);
	mm = mm->mul(mm);
	mm = mm->div(2);
	num = mm->Sum();
	num = num/Input->col;
	return num;
}

Weight* FFNN::dLossBydModel(){
	Weight* gradient = new Weight( Input->row, NumOfNeuron);
	Matrix* dLossBydOut = new Matrix( target->row, target->col);
	Matrix* dLossBydClasstwoOut = new Matrix( weight->ClasstwoToOutput->col, target->col);
	Matrix* dLossBydClasstwoIn = new Matrix( dLossBydClasstwoOut->row, dLossBydClasstwoOut->col);
	Matrix* dLossBydEnOut = new Matrix( weight->EnToClasstwo->col, dLossBydClasstwoIn->col);
	Matrix* dLossBydEnIn = new Matrix(dLossBydEnOut->row, dLossBydEnOut->col);
	Matrix* dLossBydClassoneOut = new Matrix( weight->ClassoneToEn->col, dLossBydEnIn->col);
	Matrix* dLossBydClassoneIn = new Matrix( dLossBydClassoneOut->row, dLossBydClassoneOut->col);
	
	dLossBydOut = Output->sub(target)->div(target->col);
	dLossBydClasstwoOut = weight->ClasstwoToOutput->transpose()->MmultiMatrix(dLossBydOut);
	dLossBydClasstwoIn = dLossBydClasstwoOut->mul(ClasstwoOut->mul(ClasstwoOut)->mul(-1)->add(1));
	dLossBydEnOut = weight->EnToClasstwo->transpose()->MmultiMatrix(dLossBydClasstwoIn);
	dLossBydEnIn = dLossBydEnOut;
	dLossBydClassoneOut = weight->ClassoneToEn->transpose()->MmultiMatrix(dLossBydEnIn);
	dLossBydClassoneIn = dLossBydClassoneOut->mul(ClassoneOut->mul(ClassoneOut)->mul(-1)->add(1));
	
	gradient->ClasstwoToOutput = dLossBydOut->MmultiMatrix(ClasstwoOut->transpose());
	gradient->EnToClasstwo = dLossBydClasstwoIn->MmultiMatrix(En->transpose());
	gradient->ClassoneToEn = dLossBydEnIn->MmultiMatrix(ClassoneOut->transpose());
	gradient->InputToClassone = dLossBydClassoneIn->MmultiMatrix(Input->transpose());
	
//	delete dLossBydOut, dLossBydClasstwoOut, dLossBydClasstwoIn, dLossBydEnOut, dLossBydEnIn, dLossBydClassoneOut, dLossBydClassoneIn;
	return gradient;
} 

double FFNN::Entropy(){
	Matrix* mm = new Matrix(Input->row, Input->col);
	double num;
	mm = Input->sub(En);
	mm = mm->mul(mm);
	mm = mm->div(2);
	num = mm->Sum();
	num = num/Input->col;
	return num;
}

 
void FFNN::ReadFFNNdata(){	
	FILE* fp;
	int inRow,inCol;
	char c;
	double var;
	Matrix* allWeight = NULL;
	fp = fopen("FFNNdata.txt", "r");
	fscanf(fp, "\nInputs\t%d\t%d", &inRow, &inCol);	
	for(int i=0;i<inRow;i++){
		for(int j=0;j<inCol;j++){
			fscanf(fp, "%le%c", &var, &c);
			Input->matrix[i][j] = var;	
		}
	}
	fscanf(fp, "\nOutputs\t%d\t%d", &inRow, &inCol);	
	for(int i=0;i<inRow;i++){
		for(int j=0;j<inCol;j++){
			fscanf(fp, "%le%c", &var, &c);
			Output->matrix[i][j] = var;	
		}
	}
	fscanf(fp, "\nWeights\t%d\t%d", &inRow, &inCol);	
	allWeight = new Matrix(inRow, inCol);
	for(int i=0;i<inRow;i++){
		for(int j=0;j<inCol;j++){
			fscanf(fp, "%le%c", &var, &c);
			allWeight->matrix[i][j] = var;	
		}
	}

	for(int i=0; i<weight->InputToClassone->col; i++){
		for(int j=0; j<weight->InputToClassone->row; j++){
			weight->InputToClassone->matrix[j][i] = allWeight->oriMatrix[0*inRow*inCol/4+i*weight->InputToClassone->row+j];
		}
	}
	for(int i=0; i<weight->ClassoneToEn->col; i++){
		for(int j=0; j<weight->ClassoneToEn->row; j++){
			weight->ClassoneToEn->matrix[j][i] = allWeight->oriMatrix[1*inRow*inCol/4+i*weight->ClassoneToEn->row+j];
		}
	}
	for(int i=0;i<weight->EnToClasstwo->col;i++){
		for(int j=0;j<weight->EnToClasstwo->row;j++){
			weight->EnToClasstwo->matrix[j][i] = allWeight->oriMatrix[2*inRow*inCol/4+i*weight->EnToClasstwo->row+j];
		}
	}
	for(int i=0;i<weight->ClasstwoToOutput->col;i++){
		for(int j=0;j<weight->ClasstwoToOutput->row;j++){
			weight->ClasstwoToOutput->matrix[j][i] = allWeight->oriMatrix[3*inRow*inCol/4+i*weight->ClasstwoToOutput->row+j];
		}
	}	
	delete allWeight;	
	fclose(fp);
}


void FFNN::WriteDedata(){
	FILE* fp;
	
	fp = fopen("FFNNdataDe.txt", "w+");
	fprintf( fp, "\n%s\t%4d\t%4d\n", "De", Output->row, Output->col);
	for(int i=0; i<Output->row; i++){
		for(int j=0; j<Output->col; j++){
			fprintf( fp, "%le\t", Output->matrix[i][j]);
		}
		fprintf( fp, "\n");
	}
	fclose(fp);
	
}

void FFNN::Normalization(){
	int int_32 = (int) pow(2,12)-1 ;
    if(weight->ClassoneToEn->MaxAbsElement() > weight->ClasstwoToOutput->MaxAbsElement()){
    	NormalizParameter = weight->ClassoneToEn->MaxAbsElement();
	}
	else{
		NormalizParameter = weight->ClasstwoToOutput->MaxAbsElement();
	} 
	NormalizParameter = NormalizParameter*NumOfNeuron*Input->row;
	NormalizParameter = int_32/NormalizParameter;
	


   
}
