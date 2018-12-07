#include "LayerList.h"
#include "Layer.h"
#include "Matrix.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Logistic.h"

void LayerList::priLayerList(){
	for(int i=0; i< this->size(); i++){
		//this->at(i)->weight->priMatrix();
		printf("%d", this->at(i)->weight->row);
		printf("\t%d\n", this->at(i)->weight->col);
	}
}

void LayerList::writeLayerListToTxt( string layerListTxtFileName){
	char* fileName = (char*)malloc(sizeof(char)*100);
	strcpy( fileName, layerListTxtFileName.c_str());
	FILE* fp;
	fp = fopen( fileName, "wt");	
	fprintf(fp, "\n\t%4d\n", this->size());
	fclose( fp);
	free( fileName);
	
	for( int i=0; i<this->size(); i++){
		this->at(i)->weight->writeMatrixToTxt( layerListTxtFileName, true);
	}
}

void LayerList::readTxtToLayerList( string layerListTxtFileName){
	FILE* fp;
	int inRow,inCol,size;
	char c;
	double var;
	char* fileName = (char*)malloc(sizeof(char)*100);
	strcpy( fileName, layerListTxtFileName.c_str());
	fp = fopen( fileName, "r");	
	fscanf(fp, "\n\t%4d\n", &size);
	for(int k =0; k<size; k++){
		fscanf(fp, "\n%d\t%d", &inRow, &inCol);	
		Matrix* mm = new Matrix( inRow, inCol);
		for(int i=0;i<inRow;i++){
			for(int j=0;j<inCol;j++){
				fscanf(fp, "%le%c", &var, &c);
				mm->matrix[i][j] = var;	
			}
		}
		this->push_back(new Layer( new Matrix( mm->col, mm->row), mm->row, Logistic::getLogist())) ;
		delete 	this->at(k)->weight;
		this->at(k)->weight = mm;
	}
	fclose( fp);
	free(fileName);
}
