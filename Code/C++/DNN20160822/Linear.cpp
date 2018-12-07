#include "Linear.h"
#include <math.h>


Linear::Linear(){
}


Linear* Linear::getLinear(){
	static Linear lin;
	return &lin;
} 


double Linear::F(double input) {
	return input*1;
}

double Linear::dF(double output) {
	return 1;
}
