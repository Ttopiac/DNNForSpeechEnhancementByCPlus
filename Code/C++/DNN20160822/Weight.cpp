#include "Matrix.h"
#include "Weight.h"

Weight::Weight(int inRow, int numHid){
	inputRow = inRow;
	numOfHidNeuron = numHid;
	InputToClassone = new Matrix(numHid, inRow);
	InputToClassone->setAllTo(1);
	ClassoneToEn = new Matrix(inRow, numHid);
	ClassoneToEn->setAllTo(1);
	
	EnToClasstwo = new Matrix(numHid, inRow);
	EnToClasstwo->setAllTo(1);
	ClasstwoToOutput = new Matrix(inRow, numHid); 		
	ClasstwoToOutput->setAllTo(1);
}

void Weight::Initial(){
	InputToClassone->setAllRand( -1, +1, 4, true);
	InputToClassone = InputToClassone->div(1);
	ClassoneToEn->setAllRand( -1, +1, 2, false);
	ClassoneToEn = ClassoneToEn->div(1);
	EnToClasstwo->setAllRand( -1, +1, 2, false);
	EnToClasstwo = EnToClasstwo->div(1);
	ClasstwoToOutput->setAllRand( -1, +1, 2, false);
	ClasstwoToOutput = ClasstwoToOutput->div(1);
}

Weight* Weight::add( Weight* w){
	Weight* we = new Weight(inputRow, numOfHidNeuron);
	we->InputToClassone = InputToClassone->add(w->InputToClassone);
	we->ClassoneToEn = ClassoneToEn->add(w->ClassoneToEn);
	we->EnToClasstwo = EnToClasstwo->add(w->EnToClasstwo);
	we->ClasstwoToOutput = ClasstwoToOutput->add(w->ClasstwoToOutput);
	return we;
}
Weight* Weight::sub( Weight* w){
	Weight* we = new Weight(inputRow, numOfHidNeuron);
	we->InputToClassone = InputToClassone->sub(w->InputToClassone);
	we->ClassoneToEn = ClassoneToEn->sub(w->ClassoneToEn);
	we->EnToClasstwo = EnToClasstwo->sub(w->EnToClasstwo);
	we->ClasstwoToOutput = ClasstwoToOutput->sub(w->ClasstwoToOutput);
	return we;
}
Weight* Weight::mul( Weight* w){
	Weight* we = new Weight(inputRow, numOfHidNeuron);
	we->InputToClassone = InputToClassone->mul(w->InputToClassone);
	we->ClassoneToEn = ClassoneToEn->mul(w->ClassoneToEn);
	we->EnToClasstwo = EnToClasstwo->mul(w->EnToClasstwo);
	we->ClasstwoToOutput = ClasstwoToOutput->mul(w->ClasstwoToOutput);
	return we;
}
Weight* Weight::div( Weight* w){
	Weight* we = new Weight(inputRow, numOfHidNeuron);
	we->InputToClassone = InputToClassone->div(w->InputToClassone);
	we->ClassoneToEn = ClassoneToEn->div(w->ClassoneToEn);
	we->EnToClasstwo = EnToClasstwo->div(w->EnToClasstwo);
	we->ClasstwoToOutput = ClasstwoToOutput->div(w->ClasstwoToOutput);
	return we;
}

Weight* Weight::add( double num){
	Weight* we = new Weight(inputRow, numOfHidNeuron);
	we->InputToClassone = InputToClassone->add(num);
	we->ClassoneToEn = ClassoneToEn->add(num);
	we->EnToClasstwo = EnToClasstwo->add(num);
	we->ClasstwoToOutput = ClasstwoToOutput->add(num);
	return we;
}
Weight* Weight::sub( double num){
	Weight* we = new Weight(inputRow, numOfHidNeuron);
	we->InputToClassone = InputToClassone->sub(num);
	we->ClassoneToEn = ClassoneToEn->sub(num);
	we->EnToClasstwo = EnToClasstwo->sub(num);
	we->ClasstwoToOutput = ClasstwoToOutput->sub(num);
	return we;
}
Weight* Weight::mul( double num){
	Weight* we = new Weight(inputRow, numOfHidNeuron);;
	we->InputToClassone = InputToClassone->mul(num);
	we->ClassoneToEn = ClassoneToEn->mul(num);
	we->EnToClasstwo = EnToClasstwo->mul(num);
	we->ClasstwoToOutput = ClasstwoToOutput->mul(num);
	return we;
}
Weight* Weight::div( double num){
	Weight* we = new Weight(inputRow, numOfHidNeuron);
	we->InputToClassone = InputToClassone->div(num);
	we->ClassoneToEn = ClassoneToEn->div(num);
	we->EnToClasstwo = EnToClasstwo->div(num);
	we->ClasstwoToOutput = ClasstwoToOutput->div(num);
	return we;
}


