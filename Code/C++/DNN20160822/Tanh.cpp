#include "Tanh.h"
#include <math.h>


Tanh::Tanh(){
}


Tanh* Tanh::getTanh(){
	static Tanh t;
	return &t;
} 


double Tanh::F(double input) {
	return tanh(input);
}

double Tanh::dF(double output) {
	return 1-output*output;
}
