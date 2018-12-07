

#ifndef ActFunc_h
#define ActFunc_h
/**/

class Matrix;

class ActFunc{	
	private:
		
	public:
		virtual double F( double input) = 0;
		virtual double dF( double input) = 0;
};

#endif
