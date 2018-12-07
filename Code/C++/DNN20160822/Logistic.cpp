#include "Logistic.h"
#include <math.h>


Logistic::Logistic(){
}


Logistic* Logistic::getLogist(){
	static Logistic l;
	return &l;
} 


double Logistic::F(double input) {
	return 1.0 / (1.0 + exp(-input));
}

double Logistic::dF(double output) {
	return output*(1-output);
}
