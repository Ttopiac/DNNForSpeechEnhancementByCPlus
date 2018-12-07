#include "Layer.h"
#include "stdio.h" 



Layer::Layer(Matrix* in, int outSize, ActFunc* af){
	input = in->mul(1);
	weight = new Matrix(outSize, in->row);
	weight->setAllRand( -1, 1, 2, false);
	output = weight->MmultiMatrix(input);
	actF = af;
}

Layer::~Layer(){
	delete input;
	delete weight;
	delete output;
}

void Layer::SetInput( Matrix* in){
	/*�ݭn����J�}�C����e����A�H�K�v�T�P��������weight���L�k�P���۳s��*/
	if( in->row==input->row && in->col==input->col){
		delete input;
		input = in->copyMatrix( 0, in->row-1, 0, in->col-1);
	}
	else{
		printf("\nErr: SetInput ����J�}�C�P�һݭn�]�w���}�C�j���@�ˤj\n");
	}
}

void Layer::PriLayer( void){
	printf("input: ");
	input->priMatrix();
	printf("weight: ");
	weight->priMatrix();
	printf("output: ");
	output->priMatrix();
}
