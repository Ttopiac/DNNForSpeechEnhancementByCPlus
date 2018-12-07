#include "Matrix.h"
#include "IntMatrix.h"
#include "Weight.h"
#include "DataSet.h"

#ifndef FFNN_h
#define FFNN_h

class FFNN {
	private:
		int NumOfNeuron;
		double NormalizParameter;
	public:
		Matrix* Input;
		Matrix* ClassoneOut; 
		Matrix* En;
		Matrix* ClasstwoOut;
		Matrix* Output;
		Matrix* target;
		Weight* weight;
		double 	maxDoubleElement;
		
		IntMatrix*	InputNormal;
		IntMatrix* 	InputToClassoneNormal;
		IntMatrix*	ClassoneToEnNormal;
		IntMatrix*	EnNormal;
		IntMatrix*	EnToClasstwoNormal;
		IntMatrix*	ClasstwoToOutputNormal;
		IntMatrix* 	OutputNormal;
		int 		maxIntElement;

		
		FFNN(DataSet*, int);
		
		void InitialWeight();
		void EncryptedPass(); 
		void DecryptedPass();
		void ForwardPass(DataSet*);
		
		void EncryptedNormalPass(); 
		void DecryptedNormalPass();
		void ForwardNormalPass();
		
		void ReadFFNNdata();
		void WriteDedata();
		void Normalization();
		Weight* dLossBydModel();
		
		double Loss();
		double Entropy();
		double LossNormal();
		
		

		
};

#endif
