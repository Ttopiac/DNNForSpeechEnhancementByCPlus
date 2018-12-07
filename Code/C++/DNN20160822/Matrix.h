#include <string>

using namespace std;

#ifndef Matrix_h
#define Matrix_h
/**/
class IntMatrix;
class ActFunc;

class Matrix{	
	private:
		
	public:
		int row;
		int col;
		double* oriMatrix;
		double** matrix;
		Matrix(int,int);
		Matrix( int);
		Matrix(string);
		~Matrix();
		
		void priMatrix();
		void priMatrix( unsigned int, unsigned int, unsigned int, unsigned int); 
		void setAllTo(double);
		void setAllRand(int, int ,int, bool);
		void setAllUniform( double, double);
		void SetSign(); 
		void SetMinimum( double);
		void SetMaximum( double);
		void SetAdd( double);
		void SetSub( double);
		void SetMul( double);
		void SetDiv( double);
		void SetAdd( Matrix*);
		void SetSub( Matrix*);
		void SetMul( Matrix*);
		void SetDiv( Matrix*);
		
		Matrix* MmultiMatrix(Matrix*);
		Matrix* add(Matrix*);
		Matrix* sub(Matrix*);
		Matrix* mul(Matrix*);
		Matrix* div(Matrix*);
		
		Matrix* add(double);
		Matrix* sub(double);
		Matrix* mul(double);
		Matrix* div(double);
		
		
		Matrix* F( ActFunc*);
		Matrix* dF( ActFunc*);
		Matrix* transpose(); 
		Matrix* MyTanh();
		Matrix* Hd16bitsTanh();
		Matrix* Hd8bitsTanh();
		Matrix* Sum(int);
		double 	Sum();
		double 	Max();
		double 	Min();
		double 	MaxAbsElement();
		
		Matrix* copyMatrix( unsigned int, unsigned int, unsigned int, unsigned int);
		Matrix* MirrorMatrix( bool);
		void MergeHorizontal(Matrix*);
		void MergeVertical(Matrix*);
		Matrix* GetMergeVertical(Matrix*);
		Matrix* GetMergeHorizontal(Matrix*);
		void readMatrixFromTxt( string);
		void writeMatrixToTxt( string, bool);
		
		IntMatrix* ConversionIntType();
		IntMatrix* NormalizatIntType(double);
};

#endif
