#include "Matrix.h"
#include "Layer.h"
#include "LearningDataSet.h"
#include <vector>
#include "Logistic.h"


using namespace std;

#ifndef RBM_h
#define RBM_h


class RBM{
	private:
		ActFunc* actF;
	public:
		Layer* layer;
		double learningRate;
		int numIters;
		int miniBatchSize;
		int kTimes;
		Matrix*	nh_means;
		Matrix* nv_means;
		
		
		RBM( Layer*, double, int, int, int);
		~RBM();
		
		
		Matrix* Sample_h_given_v( Matrix*);
  		Matrix* Sample_v_given_h( Matrix*);
  		Matrix* propup(  Matrix*);
  		Matrix* propdown(  Matrix*);
  		double contrastive_divergence( Matrix*);
		void LearnByCD( Matrix*);
		Matrix* Reconstruct( Matrix*);
		double Energy( Matrix*);
		
};

#endif

