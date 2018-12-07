#include "Matrix.h"
#include "DataSet.h"

#ifndef 	LearningDataSet_h
#define		LearningDataSet_h

class DataSet;

class LearningDataSet{
	private:
		
	public:
		DataSet* trainingSet;	
		DataSet* validationSet;
		DataSet* testSet;
		
		LearningDataSet( int, int, int, int, int, char*);
		
};




#endif
