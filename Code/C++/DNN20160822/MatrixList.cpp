#include "MatrixList.h"
#include "Matrix.h"
#include <vector>
#include <iostream>


void MatrixList::DeleteMatrixList(){
	for( MatrixList::iterator ptr=this->begin(); ptr!= this->end(); ptr++){
		delete *ptr;
	}
	this->clear();
}

void MatrixList::SetMatrixList( MatrixList* target) {
	if( this->empty() == false){
		this->DeleteMatrixList();
	}
	for( int i=0; i<target->size(); i++){
		this->push_back( target->at(i)->mul(1));
	}
	if( target->empty() == false){
		target->DeleteMatrixList();
		delete target;
	}
}



MatrixList* MatrixList::CopyThisMatrixList(){
	MatrixList* mL = new MatrixList();
	for( int i=0; i<this->size(); i++){
		mL->push_back( this->at(i)->mul(1));
	}
	return mL;
}

void MatrixList::SetAllTo( double num){
	for( int i=0; i<this->size(); i++){
		this->at(i)->setAllTo( num);
	}
}

void MatrixList::SetMul( double num){
	for( int i=0; i<this->size(); i++){
		this->at(i)->SetMul( num);
	}
}

void MatrixList::SetMul( MatrixList* mL){
	if( this->size() == mL->size()){
		for( int i=0; i<this->size(); i++){
			this->at(i)->SetMul( mL->at(i));
		}	
	}
	else{
		printf( "\nError:　MatrixList的SetMul的輸入MatrixList與thisMatrixList之大小不同\n");
	}
	
}


