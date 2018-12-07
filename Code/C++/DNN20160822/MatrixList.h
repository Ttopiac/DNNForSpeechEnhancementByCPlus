#include <stdio.h>
#include <vector>
#include "Matrix.h" 

#ifndef MatrixList_h
#define MatrixList_h
class MatrixList : public vector<Matrix*>{
	private:
	public: 
		void DeleteMatrixList();
		void SetMatrixList( MatrixList*);
		MatrixList* CopyThisMatrixList();
		void SetAllTo( double);
		void SetMul( double);
		void SetMul( MatrixList*);
};
#endif
