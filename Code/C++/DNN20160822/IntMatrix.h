

#ifndef IntMatrix_h
#define IntMatrix_h

class Matrix;

class IntMatrix{	
	private:
		
	public:
		int row;
		int	col;
		int maxElement;
		int* oriMatrix;
		int** matrix;
		IntMatrix(int,int);
		~IntMatrix();

		void priMatrix();
		void setAllTo(int);
		
		IntMatrix* MmultiMatrix(IntMatrix*);
		IntMatrix* add(IntMatrix*);
		IntMatrix* sub(IntMatrix*);
		IntMatrix* mul(IntMatrix*);
		IntMatrix* div(IntMatrix*);
		
		IntMatrix* add(int);
		IntMatrix* sub(int);
		IntMatrix* mul(int);
		IntMatrix* div(int);
		
		IntMatrix* MyTanh();
		IntMatrix* MyNorTanh(double);
		int 	MaxAbsElement();
		
		IntMatrix* copyMatrix();
		IntMatrix* mergeHorizontal(IntMatrix*);
		IntMatrix* mergeVertical(IntMatrix*);
		
		Matrix* ConversionDoubleType();
		Matrix* NormalizatDoubleType(double);
};

#endif
