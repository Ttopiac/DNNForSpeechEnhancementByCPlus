/*******************************************************************/
/*                                                                 */
/*     filename : FloatingField.c                                  */
/*     author   : edison.shih/edisonx                              */
/*     compiler : Visual C++ 2008                                  */
/*     date     : 2011.03.07                                       */
/*                                                                 */
/*         A.L.L.      R.I.G.H.T.S.     R.E.S.E.R.V.E.             */
/*                                                                 */
/*******************************************************************/
#include <stdio.h>

typedef unsigned uint;
typedef unsigned long long ull;
//--------------------------------------------------
#define FLT_SIGN_BITS 1           // float signed     field using bit
#define FLT_EXP_BITS  8           // float exponment  field using bits
#define FLT_MAT_BITS  23          // float mantissa   field using bits

#define FLT_SIGN_MASK 0x80000000U // float signed bit
#define FLT_EXP_MASK  0x7f800000U // float exponment bits
#define FLT_MAT_MASK  0x007fffffU // float mantissa bits
#define FLT_MAT_MASK2GET8BIT  0x000000ffU // float mantissa mask to get 8bits

#define DBL_SIGN_BITS 1           // double signed    field using bit
#define DBL_EXP_BITS  11          // double exponment field using bits
#define DBL_MAT_BITS  52          // double mantissa  field using bits

#define DBL_SIGN_MASK 0x8000000000000000ULL
#define DBL_EXP_MASK  0x7ff0000000000000ULL
#define DBL_MAT_MASK  0x000fffffffffffffULL

//--------------------------------------------------
void   Get754Field32(float v, uint* sign, uint* exp, uint* mat, uint* bit);
void   Get754Field64(double v, uint* sign, uint* exp, ull* mat);
float  Set754Field32(uint sign, uint exp, uint mat);
double Set754Field64(uint sign, uint exp, ull  mat);
float  GetValue(uint sign, uint* bit);
double MyTanh(double x);


///////////////////////////////////////////////////////////////////

int main()
{
     float  x = 0.5, x2;
	 
     double d = 0.75, tanhx;
     
     tanhx = MyTanh(d);
     
     printf("\nx=%f , tanhx=%f\n", d, tanhx);
     
     return 0;
}

///////////////////////////////////////////////////////////////////
//--------------------------------------------------
//Hyperbolic tangent function
double MyTanh(double x)
{
	 float  f = (float)x, f2;
     uint f_sign, f_exp, f_mat, f_bit, f_out;

     double d = x, d2;
     uint d_sign, d_exp;
     ull  d_mat;
     
	 Get754Field32(f, &f_sign, &f_exp, &f_mat, &f_bit); // 取得f 欄位
     printf("\nsign=%x , exp=%x , mat=%x , bit=%x\n", f_sign, f_exp, f_mat, f_bit);//各欄位數值 
     
     if(f_bit>=0x80)
     {
     	printf("r1");
     	//f2 = Set754Field32(0, 0x7e, 0x780000);  // 設定f2 欄位
     	f_out = f_bit;
	 }
	 else if(f_bit>=0x40)
     {
     	printf("r2");
     	//f2 = Set754Field32(0, 0x7e, 0x780000);  // 設定f2 欄位
     	f_out = f_bit;
	 }
	 else if(f_bit>=0x20)
     {
     	printf("r3");
     	if(f_bit>=0x3c)
     		//f2 = 0.96875;
     		f_out = 0x1f;
     	else if(f_bit>=0x38)
     		//f2 = 0.96875;
     		f_out = 0x1f;
     	else if(f_bit>=0x34)
     		//f2 = 0.9375;
     		f_out = 0x1e;
     	else if(f_bit>=0x30)
     		//f2 = 0.90625;
     		f_out = 0x1d;
     	else if(f_bit>=0x2c)
     		//f2 = 0.90625;
     		f_out = 0x1d;
     	else if(f_bit>=0x28)
     		//f2 = 0.875;
     		f_out = 0x1c;
     	else if(f_bit>=0x24)
     		//f2 = 0.4375;
     		f_out = 0x1b;
     	else 
     		//f2 = 0.78125;
     		f_out = 0x1a;
     		     	
	 }
	 else if(f_bit>=0x10)
     {
     	printf("r4");
     	if(f_bit>=0x1e)
     		//f2 = 0.75;
     		f_out = 0x18;
     	else if(f_bit>=0x1c)
     		//f2 = 0.71875;
     		f_out = 0x17;
     	else if(f_bit>=0x1a)
     		//f2 = 0.6875;
     		f_out = 0x16;
     	else if(f_bit>=0x18)
     		//f2 = 0.65625;
     		f_out = 0x15;
     	else if(f_bit>=0x16)
     		//f2 = 0.625;
     		f_out = 0x14;
     	else if(f_bit>=0x14)
     		//f2 = 0.5625;
     		f_out = 0x12;
     	else if(f_bit>=0x12)
     		//f2 = 0.53125;
     		f_out = 0x11;
     	else 
     		//f2 = 0.5;
     		f_out = 0x10;
	 }
	 else
     {
     	printf("r5");
     	//f2 = Set754Field32(f_sign, f_exp, f_mat);  // 設定f2 欄位
     	f_out = f_bit;
     	         // 觀查是否一樣
	 }
	 f2 = GetValue(f_sign,&f_out);

	 d2 = (double)f2;
//	 printf("\nf=%f , f2=%f\n", f, f2);
//     f2 = Set754Field32(f_sign, f_exp, f_mat);  // 設定f2 欄位
//     printf("\nf=%e , f2=%e\n", f, f2);         // 觀查是否一樣
//
//     Get754Field64(d, &d_sign, &d_exp, &d_mat); // 取得d 欄位
//     printf("\nsign=%x , exp=%x , mat=%x \n", d_sign, d_exp, d_mat);//各欄位數值
//     d2 = Set754Field64(d_sign, d_exp, d_mat);  // 設定d2 欄位
//     printf("\nd=%e , d2=%e\n", d, d2);         // 觀查是否一樣
	return d2;
}

///////////////////////////////////////////////////////////////////
//--------------------------------------------------
//將bit數轉回float
float   GetValue(uint sign, uint* bit)
{
	float f = 0;
	if((*bit & 0x01) == 0x01)
 	f = f + 0.03125;
 	if((*bit & 0x02) == 0x02)
 	f = f + 0.0625;
 	if((*bit & 0x04) == 0x04)
 	f = f + 0.125;
 	if((*bit & 0x08) == 0x08)
 	f = f + 0.25;
 	if((*bit & 0x10) == 0x10)
 	f = f + 0.5;
 	
 	if(sign==1) f = 0 - f;
 	
 	return f;
}
//--------------------------------------------------
// 將32 位浮點數v , 拆成signed, exp, mat
void Get754Field32(float v, uint* sign, uint* exp, uint* mat, uint* bit)
{
     uint value = *(uint*)&v; // dump 到unsigned
     *sign = (value & FLT_SIGN_MASK) >> (FLT_MAT_BITS + FLT_EXP_BITS);
     *exp  = (value & FLT_EXP_MASK) >> (FLT_MAT_BITS);
     *mat  = (value & FLT_MAT_MASK);
     
     *bit  = *mat + 0x800000;
     *bit  = *bit >> (23-5+(0x7F-*exp));
     *bit  = *bit & 0x000000FF;
     
}
//--------------------------------------------------
// 將64 位浮點數v , 拆成signed, exp, mat
void Get754Field64(double v, uint* sign, uint* exp, ull* mat)
{
     ull value = *(ull*)&v;
     *sign = (uint)((value & DBL_SIGN_MASK) >> (DBL_MAT_BITS + DBL_EXP_BITS));
     *exp  = (uint)((value & DBL_EXP_MASK ) >> (DBL_MAT_BITS));
     *mat  =       ( value & DBL_MAT_MASK );
}
//--------------------------------------------------
// 依sign, exp , mat 設32 位元浮點數
float  Set754Field32(uint sign, uint exp, uint mat)
{
     unsigned x;
     x = (sign << (FLT_MAT_BITS + FLT_EXP_BITS) ) |
           (exp  << FLT_MAT_BITS) |
           (mat);
     return *(float*)&x;
}
//--------------------------------------------------
// 依sign, exp , mat 設64 位元浮點數
double Set754Field64(uint sign, uint exp, ull mat)
{
     ull x;
     x = ((ull)sign << (DBL_MAT_BITS + DBL_EXP_BITS) ) |
           ((ull)exp  << DBL_MAT_BITS) |
           (mat);
     return *(double*)&x;
}
