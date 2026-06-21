/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2022 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
    // 原来都为1，那么取反后都为0，使用|运算挑出
    return ~(~x | ~y);
}
/* 
 * bitConditional - x ? y : z for each bit respectively
 *   Example: bitConditional(0b00110011, 0b01010101, 0b00001111) = 0b00011101
 *   Legal ops: & | ^ ~
 *   Max ops: 8
 *   Rating: 1
 */
int bitConditional(int x, int y, int z) {
    // 如果x和y都为1，那么res为1
    // 如果~x和z都为1，那么res为1
    return (x & y) | (~x & z);
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
    int mask1, mask2, n0, m0;
    // 要移动的位数
    n = n << 3;
    m = m << 3;
    // 获得要交换的字节
    mask1 = 0xFF << n;
    mask2 = 0xFF << m;
    // 把字节移动到最右端，方便一会交换
    n0 = ((x & mask1) >> n) & 0xff;
    x = x & ~mask1;
    m0 = ((x & mask2) >> m) & 0xff;
    x = x & ~mask2;
    return x | (n0 << m) | (m0 << n);
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
    // 先保存符号位，然后将其最高位变成0后就进行逻辑移位
    // 最后再补上符号位
    int sign = (x >> 31) & 1;
    x = x & ~(1 << 31);
    return (x >> n) | (sign << (31 + ~n + 1));
}
/* 
 * cleanConsecutive1 - change any consecutive 1 to zeros in the binary form of x.
 *   Consecutive 1 means a set of 1 that contains more than one 1.
 *   Examples cleanConsecutive1(0x10) = 0x10
 *            cleanConsecutive1(0xF0) = 0x0
 *            cleanConsecutive1(0xFFFF0001) = 0x1
 *            cleanConsecutive1(0x4F4F4F4F) = 0x40404040
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 4
 */
int cleanConsecutive1(int x){
    // 分别向左和向右移动1位，再进行取或运算
    // 如果是不连续的1，那么必然左右都为0
    // 对于取或后的0，表示其左右都是0，这是要保存在位，无论其是0或1
    // 至于其它所有的1，要么原来是0(1 | 0)，要么是连续的1(1 | 1)，不需要保留
    int left_mask = x << 1;
    int right_mask = (x >> 1) & ~(1 << 31);
    x &= ~(left_mask | right_mask);
    return x;
}
/* 
 * countTrailingZero - return the number of consecutive 0 from the lowest bit of 
 *   the binary form of x.
 *   YOU MAY USE BIG CONST IN THIS PROBLEM, LIKE 0xFFFF0000
 *   YOU MAY USE BIG CONST IN THIS PROBLEM, LIKE 0xFFFF0000
 *   YOU MAY USE BIG CONST IN THIS PROBLEM, LIKE 0xFFFF0000
 *   Examples countTrailingZero(0x0) = 32, countTrailingZero(0x1) = 0,
 *            countTrailingZero(0xFFFF0000) = 16,
 *            countTrailingZero(0xFFFFFFF0) = 8,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int countTrailingZero(int x){
    int n = 0;
    x = x & (~x + 1); // the lowwest 1

    n += !(x & 0x0000FFFF) << 4;
    n += !(x & 0x00FF00FF) << 3;
    n += !(x & 0x0F0F0F0F) << 2;
    n += !(x & 0x33333333) << 1;
    n += !(x & 0x55555555);
    n += !x;
    
    return n;
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
    int sign = x & (1 << 31);
    int bias = (sign >> 31) & ((1 << n) + (~1 + 1));
    x += bias;
    return x >> n;
}
/* 
 * oneMoreThan - return 1 if y is one more than x, and 0 otherwise
 *   Examples oneMoreThan(0, 1) = 1, oneMoreThan(-1, 1) = 0
 *   Legal ops: ~ & ! ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int oneMoreThan(int x, int y) {
    // y - x = 1 -> y + ~x + 1 = 1 -> y + ~x = 0;
    // y can't equals TMin;
    return !((~x + y) | !(y ^ (1 << 31)));
}
/*
 * satMul3 - multiplies by 3, saturating to Tmin or Tmax if overflow
 *  Examples: satMul3(0x10000000) = 0x30000000
 *            satMul3(0x30000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0x70000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0xD0000000) = 0x80000000 (Saturate to TMin)
 *            satMul3(0xA0000000) = 0x80000000 (Saturate to TMin)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 3
 */
int satMul3(int x) {
    int mul_2, mul_3, is_overflow, tmin, sign_mask;
    mul_2 = x << 1;
    mul_3 = mul_2 + x;
    // every mul may cause overflow
    is_overflow = (x ^ mul_2) >> 31;
    is_overflow |= (x ^ mul_3) >> 31;
    tmin = 1 << 31;
    sign_mask = x >> 31;
    return (~is_overflow & mul_3) | (is_overflow & ~(tmin ^ sign_mask));
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
    return !(((x ^ y) & (x ^ (x + ~y + 1))) >> 31);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    // case1: diffrient signs, x <= y if x < 0, y > 0;
    // case2: same signs, x <= y if x - y <= 0;
    // overflow happans only when case1
    return ((x & ~y) | ~((x ^ y) | (y + ~x + 1))) >> 31 & 1;
}
/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *   avoiding errors due to overflow
 *   Examples: trueThreeFourths(11) = 8
 *             trueThreeFourths(-9) = -6
 *             trueThreeFourths(1073741824) = 805306368 (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int trueThreeFourths(int x) {
    int num = x >> 2, fraction = x & 3;
    return (num + (num << 1) + ((fraction + (fraction << 1) + (x >> 31 & 3)) >> 2));
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
    int sign_mask = 0x80000000, exp_mask = 0x7f800000, frac_mask = 0x007fffff;
    int sign = uf & sign_mask, exp = uf & exp_mask, frac = uf & frac_mask;
    int res = exp + sign;

    if (exp == exp_mask) {
        return uf;
    } else if (exp == 0) {
        frac <<= 1;
        res += frac;
    } else {
        if (exp == 0x7f000000) {
            return sign | 0x7f800000;
        } else {
            res += 0x00800000;
        }
    }
    exp = res & exp_mask;
    sign = res & sign_mask;
    return sign | exp | frac;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
    int sign, exp, frac, ux;
    int frac_mask, round;
    sign = (x >> 31) & 1;
    if (x == 0x80000000) 
        return 0xcf000000;
    if (!x) 
        return 0;
    if (sign)
        x = -x;

    // cal exp
    ux = x;
    exp = -1;
    while (ux) {
        ux >>= 1;
        exp++;
    }
    x <<= (31 - exp);
    exp += 0x7f;

    // cal frac
    frac_mask = 0x7fffff;
    frac = (x >> 8) & frac_mask;
    round = x & 0xff;
    frac += ((round > 0x80) || ((round == 0x80) && (frac & 1))); // add 1
    if (frac >> 23) {
        frac &= frac_mask;
        exp += 1;
    }
    return sign << 31 | exp << 23 | frac;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
    int sign = uf >> 31;
    int exp = uf >> 23 & 0xff;
    int frac = uf & 0x7fffff;
    int E, M;


    if (exp == 0xff)
        return 0x80000000;
    else if (!exp)
        return 0;
    
    E = exp - 127;
    M = frac | 0x800000;

    if (E < 0)
        return 0;
    else if (E > 31)
        return 0x80000000;

    if (E > 23) {
        M = M << (E - 23);
    } else {
        M = M >> (23 - E);
    }

    if (sign) 
        return -M;
    return M;
}
/* 
 * float_pwr2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned float_pwr2(int x) {
    if (x < -149)
        return 0;
    if (x >= 128)
        return 0x7f800000;
    if (x > -127)
        return (x + 127) << 23;
    return 1 << (149 + x);
}
