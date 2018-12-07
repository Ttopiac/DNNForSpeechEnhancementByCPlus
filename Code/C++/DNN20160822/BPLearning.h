#include "Matrix.h"
#include "IntMatrix.h"
#include "LearningDataSet.h"

#ifndef BPLearning_h
#define BPLearning_h

class BPLearning {
	private:
		int numOfNeuron;
		int numIters;
		double learningRate;
		double momentumMultiplier;
		bool doEarlyStoping;
		int miniBatchSize;
	public:
		LearningDataSet* dataSet;
			
		BPLearning( LearningDataSet*, int, int, double, double, bool, int);
		
		void runBPLearning();
		
};

#endif
