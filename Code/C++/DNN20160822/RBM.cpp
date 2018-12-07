#include "RBM.h" 
#include <stdio.h>
#include <stdlib.h>
#include "CmpRand.h"

RBM::RBM( Layer* l, double lr, int nI, int k, int bs){
	layer = l;
	learningRate = lr;
	numIters = nI;
	kTimes = k;
	miniBatchSize = bs;
	actF = Logistic::getLogist();
	nh_means = propup( layer->input);
	nv_means = propdown( layer->output);
}

Matrix* RBM::propup( Matrix* v){
	if(v->row != layer->input->row){
		printf("\nErr: In RBM's propup function, the row size of the input matrix isn't as same as the row size of DataSet's input\n");
	}
	Matrix* newIn = v->mul(1.0);
	delete layer->input;
	layer->input = newIn->mul(1.0);
	delete newIn;
	delete layer->output;
	layer->output = layer->weight->MmultiMatrix( layer->input);
	
	return layer->output->F(actF);
}

Matrix* RBM::propdown( Matrix* h){
	if(h->row != layer->output->row){
		printf("\nErr: In RBM's propdown function, the row size of the input matrix isn't as same as the row size of DataSet's input\n");
	}
	Matrix* newOut = h->mul(1.0);
	delete layer->output;
	layer->output = newOut->mul(1.0);
	delete newOut;
	Matrix* wT = layer->weight->transpose();
	delete layer->input;
	layer->input = wT->MmultiMatrix( layer->output);	
	delete wT;
	return layer->input->F(actF);
}

/*
Sample the data of hidden neurons from the data of visible neurons 
	*v0_sample:	the data of visible neurons
	*mean:		the matrix in which the conditional proability will be placed after execute propup function
	*sample:	the matrix in which the sample will be placed after execute binomial function (compare the conditional proability with random number and )
*/
Matrix* RBM::Sample_h_given_v( Matrix* v0_sample) {
	delete nh_means;
	nh_means = propup(v0_sample);
	ActFunc* cr = CmpRand::getCmpRand();
	Matrix* sample = nh_means->F(cr);
	return sample;
}

/*
Sample the value of visible neuron from the value of hidden neuron 
	*v0_sample:	the data of hidden neurons
	*mean:		the matrix in which the conditional proability will be placed after execute propdown function
	*sample:	the matrix in which the sample will be placed after execute binomial function (compare the conditional proability with random number and )
*/
Matrix* RBM::Sample_v_given_h(Matrix* h0_sample) {
	delete nv_means;
  	nv_means = propdown(h0_sample);
  	ActFunc* cr = CmpRand::getCmpRand();
	Matrix* sample = nv_means->F(cr);
	return sample;
}



/*
the overall process of contrastive divergence
	*input:	training dataset
	lr:		learning rate
	k:		the number of Gibbs sampling steps(the k in CD-k)
*/
double RBM::contrastive_divergence( Matrix* data) {	
	/* START POSITIVE PHASE */
	Matrix* posHidProbs = propup(data);
	Matrix* dataT = data->transpose();
	Matrix* posProds = posHidProbs->MmultiMatrix( dataT);
	delete dataT;
	/* END OF POSITIVE PHASE */
	ActFunc* cr = CmpRand::getCmpRand();
	Matrix* posHidStates = posHidProbs->F(cr);
	delete posHidProbs;
	
	/* START NEGATIVE PHASE */
	Matrix* negData = propdown( posHidStates);
	delete posHidStates;
	Matrix* negHidProbs = propup( negData);
	Matrix* negDataT = negData->transpose();
	delete negData;
	Matrix* negProds = negHidProbs->MmultiMatrix(negDataT);
	delete negHidProbs;
	delete negDataT;

	/*  UPDATE WEIGHTS */
	Matrix* pSn = posProds->sub( negProds);
	double err = pSn->Sum();
	delete posProds;
	delete negProds;
	
	Matrix* pSnDivBatch = pSn->div( data->col);
	delete pSn;
	
	Matrix* gradient = pSnDivBatch->mul(learningRate);
	delete pSnDivBatch;
	
	Matrix* newW = layer->weight->add(gradient);
	delete gradient;
	
	delete layer->weight;
	layer->weight = newW->mul(1.0);
	delete newW;
	
	return err;
}

double RBM::Energy( Matrix* hv) {
	Matrix* energy = hv->mul(layer->weight);
	double e = energy->Sum();
	e = e/( miniBatchSize*miniBatchSize )*(-1.0);
	delete energy;
	return e;
}
 
 
void RBM::LearnByCD( Matrix* dataSet){
	Matrix* I;
	I = dataSet->mul(1.0);
	for( int Iters=0; Iters<numIters; Iters++){
		if((Iters+1)%10 == 0){
			printf("PreLearningFor %d iterations: %le\n", Iters+1, contrastive_divergence( I));
		}
		else{
			contrastive_divergence( I);	
		}
		
		//delete I;
	}
	//printf("PreLearning Complete\n\n");
	delete I;
}

Matrix* RBM::Reconstruct( Matrix* v) {
	Matrix* h;
	Matrix* pre_sigmoid_activation;
	
	Matrix* reconstruct;
	h = propup( v);
  	reconstruct = propdown( h);
  	
  	delete h;
  	//delete pre_sigmoid_activation;
	return reconstruct;	
}
