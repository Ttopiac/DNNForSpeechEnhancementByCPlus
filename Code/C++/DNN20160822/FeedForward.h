#include "Matrix.h"
#include "Layer.h"
#include "DataSet.h"
#include <vector>
#include "LayerList.h"
#include "MatrixList.h"

using namespace std;

#ifndef FeedForward_h
#define FeedForward_h


class FeedForward{
	private:
	public:
		LayerList* layerList;
		int numOfLayers;
		
		FeedForward( LayerList*);
		~FeedForward();
		
		double Forward( Matrix*, Matrix*);
		double Forward( DataSet*);
		double Err( Matrix*, Matrix*);
		MatrixList* GetPartialElementList( Matrix*);
		void UpdateWeight( MatrixList*);
		void BackProp( Matrix*, double);
		Matrix* LearnByBP( double, int, DataSet*, int);
		Matrix* LearnByBP( double, int, DataSet*);
		Matrix* LearnByBP( double, double, DataSet*);
		Matrix* LearnByRPROP( double, double, double, double, double, double, DataSet*);
		Matrix* Loss( Matrix*, Matrix*);
};

#endif

