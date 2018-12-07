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
	/*需要做輸入陣列的行寬比較，以免影響與之相關的weight的無法與之相連接*/
	if( in->row==input->row && in->col==input->col){
		delete input;
		input = in->copyMatrix( 0, in->row-1, 0, in->col-1);
	}
	else{
		printf("\nErr: SetInput 的輸入陣列與所需要設定的陣列大不一樣大\n");
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
