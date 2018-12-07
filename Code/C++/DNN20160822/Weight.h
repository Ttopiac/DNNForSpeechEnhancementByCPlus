#ifndef Weight_h
#define Weight_h

class Matrix;

class Weight{
	
	private:
		
	public:
		int inputRow;
		int numOfHidNeuron;
		Matrix* InputToClassone;
		Matrix* ClassoneToEn;	
		Matrix* EnToClasstwo;
		Matrix* ClasstwoToOutput;
		
		Weight( int, int); 
		
		void Initial();
		Weight* add(Weight*);
		Weight* sub(Weight*);
		Weight* mul(Weight*);
		Weight* div(Weight*);
		
		Weight* add(double);
		Weight* sub(double);
		Weight* mul(double);
		Weight* div(double);
};

#endif
 
