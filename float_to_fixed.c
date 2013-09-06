/*
 * 16位定点数的转换 
 *
 * Copyright (C) 2013 smalltigerlee <smalltigerlee@gmail.com>
 *
 * Released under the GPL version 2 only.
 *
 */
 
#include "float_to_fixed.h"


/**
 * num为需要转换的浮点数，qvalue为要转换的数对应的Q值 
 * 返回值为定点数 
 */
FIXED16 float_to_fixed(float num, int qvalue)
{
      return (FIXED16)(num << qvalue);
}


float fixed_to_float(FIXED16 num, int qvalue)
{
      return (float)(num >> qvalue);
}

/**
 * a, b分别为参加运算的定点数，a_qvalue为a的Q值，b_qvalue为b的Q值，c_qvalue为计算结果的Q值 
 * 返回值为Q为c_qvalue的定点数 
 */
FIXED16 fixed_add(FIXED16 a, FIXED16 b, int a_qvalue, int b_qvalue, int c_qvalue)
{
      FIXED16 c16
      
      if (a_qvalue >= b_qvalue) {
             c16 = (a + b << (a_qvalue - b_qvalue)) << (c_qvalue - a_qvalue);
      } else {
             c16 = (b + a << (b_qvalue - a_qvalue)) << (c_qvalue - b_qvalue); 
      }
      
      if ((-2<<15) <= c16 && c16 <= ((2<<15) - 1) {
             return c16;
      } else if ((-2<<31) <= c && c <=((2<<31) - 1) {
             return fixed_add_overflow32(a, b, a_qvalue, b_qvalue, c_qvalue);       
      } else {
             return OVERFLOW_GT_32BIT;
}

/* 考虑到16位整型的加法造成溢出的情况，如果有溢出结果用32位整型表示*/
FIXED32 fixed_add_overflow32(FIXED16 a, FIXED16 b, int a_qvalue, int b_qvalue, int c_qvalue)
{
        FIXED32 c32;
        FIXED32 temp_num;
        
        if (a_qvalue >= b_qvalue) {
             temp_num =  b << (a_qvalue - b_qvalue);
             temp_num = temp_num + a;
             if (a_qvalue > c_qvalue) {
                c32 = temp_num >> (a_qvalue - c_qvalue);
             }
             if (a_qvalue < c_qvalue) {
                c32 = temp_num << (c_qvalue - a_qvalue); 
             }
        } else {
               temp_num = a << (b_qvalue - a_qvalue);
               temp_num = temp_num + b;
               if (b_qvalue > c_qvalue) {
                  c32 = temp_num >> (b_qvalue - c_qvalue);
               }
               if (b_qvalue < c_qvalue) {
                  c32 = temp_num << (c_qvalue - b_qvalue);
               } 
        } 
        
        return c32;
}

FIXED16 fixed_sub(FIXED16 a, FIXED16 b, int a_qvalue, int b_qvalue, int c_qvalue)
{
      return fixed_add(a, -b, a_qvalue, b_qvalue, c_qvalue);
}

FIXED32 fixed_mul(FIXED16 a, FIXED16 b, int a_qvalue, int b_qvalue, int c_qvalue)
{
        FIXED32 c32;
        
        c32 = (a*b) << (c_value - (a_value + b_qvalue)); 
        
        if ((-2<<31) <= c && c <=((2<<31) - 1) {
               return c32;
        }

        return OVERFLOW_GT_32BIT;
}

FIXED32 fixed_div(FIXED32 a, FIXED32 b, int a_qvalue, int b_qvalue, int c_qvalue)
{
       return (a << (c_qvalue - a_qvalue + b_qvalue)) / b; 
      
}

FIXED32 fixed_exp(FIXED16 a, int q_qvalue, int index, int c_qvalue)
{
        FIXED32 c32;
        
        c32 = pow((a >> a_qvalue), index) >> c_qvalue);
        if ((-2<<31) <= c && c <=((2<<31) - 1) {
               return c32;
        }

        return OVERFLOW_GT_32BIT;
}
