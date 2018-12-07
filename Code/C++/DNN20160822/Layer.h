#include "Matrix.h"


#ifndef Layer_h
#define Layer_h

class Layer{
	private:
	public:
		Matrix* input;
		Matrix* weight;
		Matrix* output;
		ActFunc* actF;
		/*
			Matrix* 輸入的陣列 (需學習input陣列) 
			int     輸出的neuron數量 
		*/
		Layer(Matrix*, int, ActFunc*);
		~Layer();
		void SetInput( Matrix*);
		void SetOutput( void);
		void PriLayer( void);
};

#endif
