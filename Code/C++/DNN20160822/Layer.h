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
			Matrix* ��J���}�C (�ݾǲ�input�}�C) 
			int     ��X��neuron�ƶq 
		*/
		Layer(Matrix*, int, ActFunc*);
		~Layer();
		void SetInput( Matrix*);
		void SetOutput( void);
		void PriLayer( void);
};

#endif
