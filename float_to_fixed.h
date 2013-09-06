/*
 * 16位定点数的转换 
 *
 * Copyright (C) 2013 smalltigerlee <smalltigerlee@gmail.com>
 *
 * Released under the GPL version 2 only.
 *
 */

#ifndef __FLOAT_TO_FIXED_H__
#define __FLOAT_TO_FIXED_H__

#include <math.h>

#define OVERFLOW_GT_32BIT 0 

typedef int FIXED16 ;  //这里的int为16位
typedef long FIXED32; //这里的long为32位

FIXED16 float_to_fixed(float num, int q_value);
float fixed_to_float(FIXED16 num, int q_value);

FIXED16 fixed_add(FIXED16 a, FIXED16 b, int a_qvalue, int b_qvalue, int c_qvalue);
FIXED32 fixed_add_overflow32(FIXED16 a, FIXED16 b, int a_qvalue, int b_qvalue, int c_qvalue);

FIXED16 fixed_sub(FIXED16 a, FIXED16 b, int a_qvalue, int b_qvalue, int c_qvalue);

FIXED32 fixed_mul(FIXED16 a, FIXED16 b, int a_qvalue, int b_qvalue, int c_qvalue);

FIXED32 fixed_div(FIXED32 a, FIXED32 b, int a_qvalue, int b_qvalue, int c_qvalue);

FIXED32 fixed_exp(FIXED16 a, int q_qvalue, int index, int c_qvalue);

#endif

