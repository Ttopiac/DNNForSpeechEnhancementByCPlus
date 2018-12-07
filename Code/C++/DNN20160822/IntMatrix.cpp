#include "IntMatrix.h"
#include "Matrix.h"
#include <stdio.h> 
#include <string.h>
#include "math.h"


IntMatrix::IntMatrix(int inRow,int inCol){
	row = inRow;
	col = inCol;
	maxElement = 0;
	oriMatrix = new int[col*row];
	matrix = new int*[row];
	

	for(int i=0;i<row;i++){
		matrix[i] = &oriMatrix[i*col];
	}
	for(int i=0;i<row*col;i++){
		if(oriMatrix[i] > maxElement)
			maxElement = oriMatrix[i];
	}
	
}

IntMatrix::~IntMatrix(){
	delete matrix;
	delete oriMatrix;
}





void IntMatrix::setAllTo(int num){	


	for(int i=0;i<row*col;i++){
		oriMatrix[i] = num;
	}
	
	
}

IntMatrix* IntMatrix::MmultiMatrix(IntMatrix* m){
	IntMatrix* mm = NULL;
	
	if(col == m->row){
		mm = new IntMatrix(row,m->col);
		mm->setAllTo(0);
		
		for(int i=0;i<mm->row;i++){
			for(int j=0;j<mm->col;j++){
				for(int k=0;k<col;k++){
					
					mm->matrix[i][j] += matrix[i][k] * m->matrix[k][j];
					
				}
			}
		}
	}
	else{
		printf("\nError : 痻皚猭┮ぇ痻皚计籔痻皚︽计ぃ单\n");
	}
	
	return mm;
}


IntMatrix*  IntMatrix::add(IntMatrix* m){
	
	IntMatrix* mm = NULL;
		
	if(row==m->row && col==m->col){
		mm = new IntMatrix(row,col);
		for(int i=0;i<row*col;i++){
			mm->oriMatrix[i] = oriMatrix[i]+m->oriMatrix[i]; 
		}
		
	}
	else{
		printf("\nError : じ猭┮ぇ痻皚籔痻皚ぃ单\n");
	}
	
	return mm;
	
}

IntMatrix*  IntMatrix::sub(IntMatrix* m){
	
	IntMatrix* mm = NULL;
		
	if(row==m->row && col==m->col){
		mm = new IntMatrix(row,col);
		for(int i=0;i<row*col;i++){
			mm->oriMatrix[i] = oriMatrix[i]-m->oriMatrix[i]; 
		}
		
	}
	else{
		printf("\nError : じ猭┮ぇ痻皚籔痻皚ぃ单\n");
	}
	
	return mm;
	
}


IntMatrix*  IntMatrix::mul(IntMatrix* m){
	
	IntMatrix* mm = NULL;
		
	if(row==m->row && col==m->col){
		mm = new IntMatrix(row,col);
		for(int i=0;i<row*col;i++){
			mm->oriMatrix[i] = oriMatrix[i]*m->oriMatrix[i]; 
		}
		
	}
	else{
		printf("\nError : じ猭┮ぇ痻皚籔痻皚ぃ单\n");
	}
	
	return mm;
	
}

IntMatrix*  IntMatrix::div(IntMatrix* m){
	
	IntMatrix* mm = NULL;
		
	if(row==m->row && col==m->col){
		mm = new IntMatrix(row,col);
		for(int i=0;i<row*col;i++){
			mm->oriMatrix[i] = oriMatrix[i]/m->oriMatrix[i]; 
		}
		
	}
	else{
		printf("\nError : じ猭┮ぇ痻皚籔痻皚ぃ单\n");
	}
	
	return mm;
	
}

IntMatrix*  IntMatrix::add(int num){	
	IntMatrix* mm = new IntMatrix(row,col);;
		for(int i=0;i<row*col;i++){
			mm->oriMatrix[i] = oriMatrix[i]+num; 
		}			
	return mm;	
}

IntMatrix*  IntMatrix::sub(int num){	
	IntMatrix* mm = new IntMatrix(row,col);;
		for(int i=0;i<row*col;i++){
			mm->oriMatrix[i] = oriMatrix[i]-num; 
		}			
	return mm;
}

IntMatrix*  IntMatrix::mul(int num){	
	IntMatrix* mm = new IntMatrix(row,col);;
		for(int i=0;i<row*col;i++){
			mm->oriMatrix[i] = oriMatrix[i]*num; 
		}			
	return mm;	
}

IntMatrix*  IntMatrix::div(int num){	
	IntMatrix* mm = new IntMatrix(row,col);;
		for(int i=0;i<row*col;i++){
			mm->oriMatrix[i] = oriMatrix[i]/num; 
		}			
	return mm;	
}



void IntMatrix::priMatrix(){
	
	printf("\n");
	printf("%d\t%d\t\n", row, col);
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			printf("%d\t",matrix[i][j]);
		}
		printf("\n");
	}
	
	
}

IntMatrix* IntMatrix::copyMatrix(){
	
	IntMatrix* mm = new IntMatrix(row,col);
	
	for(int i=0;i<row*col;i++){
		mm->oriMatrix[i] = oriMatrix[i];
	}
	
	
	return mm;
	
}

int IntMatrix::MaxAbsElement(){
	int max = 0;
	for(int i=0;i<row*col;i++){
		if(fabs(oriMatrix[i]) > max){
			max = abs(oriMatrix[i]);
		}
	}
	return max;
} 

IntMatrix* IntMatrix::mergeHorizontal(IntMatrix* m){
	
	IntMatrix* mm = NULL;



	if(row == m->row){
		mm = new IntMatrix(row,col+m->col);
			
		for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				mm->matrix[i][j] = matrix[i][j];
			}
		}
		for(int i=0;i<m->row;i++){
			for(int j=col;j<col+m->col;j++){
				mm->matrix[i][j] = m->matrix[i][j-col];
			}
		}
	}
	else{
		printf("\nError : キよ┮舱ぇ痻皚计籔痻皚计ぃ单\n");
	}


	
	return mm;
}


IntMatrix* IntMatrix::mergeVertical(IntMatrix* m){
	
	IntMatrix* mm = NULL;
	if(col == m->col){
		mm = new IntMatrix(row+m->row,col);
		for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				mm->matrix[i][j] = matrix[i][j];
			}
		}
		for(int i=row;i<row+m->row;i++){
			for(int j=0;j<m->col;j++){
				mm->matrix[i][j] = m->matrix[i-row][j];
			}
		}
	}
	else{
		printf("\nError : よ┮舱ぇ痻皚︽计籔痻皚︽计ぃ单\n");
	}


	return mm;
}


Matrix* IntMatrix::ConversionDoubleType(){
	Matrix* mm = new Matrix( row, col);
	for(int i=0;i<row*col;i++){
			mm->oriMatrix[i] = (double)oriMatrix[i];
	}
	return mm;	
}

Matrix* IntMatrix::NormalizatDoubleType(double num){
	Matrix* middle = new Matrix( row, col);
	middle = ConversionDoubleType();
	middle = middle->div(num);
	return middle;	
}
