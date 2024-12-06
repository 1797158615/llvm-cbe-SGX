/* Provide Declarations */
#include <stdint.h>
#ifndef __cplusplus
typedef unsigned char bool;
#endif

#ifndef _MSC_VER
#define __forceinline __attribute__((always_inline)) inline
#endif

#if defined(__GNUC__)
#define  __ATTRIBUTELIST__(x) __attribute__(x)
#else
#define  __ATTRIBUTELIST__(x)  
#endif

#ifdef _MSC_VER  /* Can only support "linkonce" vars with GCC */
#define __attribute__(X)
#endif

#ifdef _MSC_VER
#define __PREFIXALIGN__(X) __declspec(align(X))
#define __POSTFIXALIGN__(X)
#else
#define __PREFIXALIGN__(X)
#define __POSTFIXALIGN__(X) __attribute__((aligned(X)))
#endif



/* Global Declarations */

/* Types Declarations */
struct l_array_26_uint8_t;
struct l_array_3_uint8_t;
struct l_array_19_uint8_t;
struct l_array_33_uint8_t;
struct l_array_4_uint8_t;
struct l_array_100_uint32_t;

/* Function definitions */

/* Types Definitions */
struct l_array_26_uint8_t {
  uint8_t array[26];
};
struct l_array_3_uint8_t {
  uint8_t array[3];
};
struct l_array_19_uint8_t {
  uint8_t array[19];
};
struct l_array_33_uint8_t {
  uint8_t array[33];
};
struct l_array_4_uint8_t {
  uint8_t array[4];
};
struct l_array_100_uint32_t {
  uint32_t array[100];
};

/* Global Variable Declarations */
const static struct l_array_26_uint8_t _OC_str;
const static struct l_array_3_uint8_t _OC_str_OC_1;
const static struct l_array_19_uint8_t _OC_str_OC_2;
const static struct l_array_33_uint8_t _OC_str_OC_3;
const static struct l_array_4_uint8_t _OC_str_OC_4;

/* Function Declarations */
int main(void) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t printf(void* _66, ...);
uint32_t __isoc99_scanf(void* _67, ...);


/* Global Variable Definitions and Initialization */
static const struct l_array_26_uint8_t _OC_str = { "Enter number of elements\n" };
static const struct l_array_3_uint8_t _OC_str_OC_1 = { "%d" };
static const struct l_array_19_uint8_t _OC_str_OC_2 = { "Enter %d integers\n" };
static const struct l_array_33_uint8_t _OC_str_OC_3 = { "Sorted list in ascending order:\n" };
static const struct l_array_4_uint8_t _OC_str_OC_4 = { "%d\n" };


/* LLVM Intrinsic Builtin Function Bodies */
static __forceinline uint32_t llvm_add_u32(uint32_t a, uint32_t b) {
  uint32_t r = a + b;
  return r;
}
static __forceinline uint32_t llvm_sub_u32(uint32_t a, uint32_t b) {
  uint32_t r = a - b;
  return r;
}


/* Function Bodies */

int main(void) {
  uint32_t _1;    /* Address-exposed local */
  __PREFIXALIGN__(16) struct l_array_100_uint32_t _2 __POSTFIXALIGN__(16);    /* Address-exposed local */
  uint32_t _3;    /* Address-exposed local */
  uint32_t _4;    /* Address-exposed local */
  uint32_t _5;    /* Address-exposed local */
  uint32_t _6;    /* Address-exposed local */
  uint32_t _7;    /* Address-exposed local */
  uint32_t _8;
  uint32_t _9;
  uint32_t _10;
  uint32_t _11;
  uint32_t _12;
  uint32_t _13;
  uint32_t _14;
  uint32_t _15;
  uint32_t _16;
  uint32_t _17;
  uint32_t _18;
  uint32_t _19;
  uint32_t _20;
  uint32_t _21;
  uint32_t _22;
  uint32_t _23;
  uint32_t _24;
  uint32_t _25;
  uint32_t _26;
  uint32_t _27;
  uint32_t _28;
  uint32_t _29;
  uint32_t _30;
  uint32_t _31;
  uint32_t _32;
  uint32_t _33;
  uint32_t _34;
  uint32_t _35;
  uint32_t _36;
  uint32_t _37;
  uint32_t _38;
  uint32_t _39;
  uint32_t _40;
  uint32_t _41;
  uint32_t _42;
  uint32_t _43;
  uint32_t _44;
  uint32_t _45;

  _1 = 0;
#line 4 "/home/yxk/llvm-cbe/test/selectionsort/main.c"
  ;
  ;
  ;
  ;
  ;
  ;
#line 6 "/home/yxk/llvm-cbe/test/selectionsort/main.c"
  _8 = printf((&_OC_str));
#line 7 "/home/yxk/llvm-cbe/test/selectionsort/main.c"
  _9 = __isoc99_scanf((&_OC_str_OC_1), (&_3));
#line 9 "/home/yxk/llvm-cbe/test/selectionsort/main.c"
  _10 = _3;
  _11 = printf((&_OC_str_OC_2), _10);
#line 11 "/home/yxk/llvm-cbe/test/selectionsort/main.c"
  _4 = 0;
  goto _46;

  do {     /* Syntactic loop '' to make GCC happy */
_46:
  _12 = _4;
  _13 = _3;
  if ((((int32_t)_12) < ((int32_t)_13))) {
    goto _47;
  } else {
    goto _48;
  }

_47:
#line 12 "/home/yxk/llvm-cbe/test/selectionsort/main.c"
  _14 = _4;
  _15 = __isoc99_scanf((&_OC_str_OC_1), (((&(&_2)->array[((int64_t)(((int64_t)(int32_t)_14)))]))));
  goto _49;

_49:
#line 11 "/home/yxk/llvm-cbe/test/selectionsort/main.c"
  _16 = _4;
  _4 = (llvm_add_u32(_16, 1));
  goto _46;

  } while (1); /* end of syntactic loop '' */
_48:
#line 14 "/home/yxk/llvm-cbe/test/selectionsort/main.c"
  _4 = 0;
  goto _50;

  do {     /* Syntactic loop '' to make GCC happy */
_50:
  _17 = _4;
  _18 = _3;
  if ((((int32_t)_17) < ((int32_t)(llvm_sub_u32(_18, 1))))) {
    goto _51;
  } else {
    goto _52;
  }

_51:
#line 15 "/home/yxk/llvm-cbe/test/selectionsort/main.c"
  _19 = _4;
  _6 = _19;
#line 17 "/home/yxk/llvm-cbe/test/selectionsort/main.c"
  _20 = _4;
  _5 = (llvm_add_u32(_20, 1));
  goto _53;

  do {     /* Syntactic loop '' to make GCC happy */
_53:
  _21 = _5;
  _22 = _3;
  if ((((int32_t)_21) < ((int32_t)_22))) {
    goto _54;
  } else {
    goto _55;
  }

_54:
#line 18 "/home/yxk/llvm-cbe/test/selectionsort/main.c"
  _23 = _6;
  _24 = *(uint32_t*)(((&(&_2)->array[((int64_t)(((int64_t)(int32_t)_23)))])));
  _25 = _5;
  _26 = *(uint32_t*)(((&(&_2)->array[((int64_t)(((int64_t)(int32_t)_25)))])));
  if ((((int32_t)_24) > ((int32_t)_26))) {
    goto _56;
  } else {
    goto _57;
  }

_56:
#line 19 "/home/yxk/llvm-cbe/test/selectionsort/main.c"
  _27 = _5;
  _6 = _27;
  goto _57;

_57:
  goto _58;

_58:
#line 17 "/home/yxk/llvm-cbe/test/selectionsort/main.c"
  _28 = _5;
  _5 = (llvm_add_u32(_28, 1));
  goto _53;

  } while (1); /* end of syntactic loop '' */
_55:
#line 21 "/home/yxk/llvm-cbe/test/selectionsort/main.c"
  _29 = _6;
  _30 = _4;
  if ((_29 != _30)) {
    goto _59;
  } else {
    goto _60;
  }

_59:
#line 22 "/home/yxk/llvm-cbe/test/selectionsort/main.c"
  _31 = _4;
  _32 = *(uint32_t*)(((&(&_2)->array[((int64_t)(((int64_t)(int32_t)_31)))])));
  _7 = _32;
#line 23 "/home/yxk/llvm-cbe/test/selectionsort/main.c"
  _33 = _6;
  _34 = *(uint32_t*)(((&(&_2)->array[((int64_t)(((int64_t)(int32_t)_33)))])));
  _35 = _4;
  *(uint32_t*)(((&(&_2)->array[((int64_t)(((int64_t)(int32_t)_35)))]))) = _34;
#line 24 "/home/yxk/llvm-cbe/test/selectionsort/main.c"
  _36 = _7;
  _37 = _6;
  *(uint32_t*)(((&(&_2)->array[((int64_t)(((int64_t)(int32_t)_37)))]))) = _36;
  goto _60;

_60:
  goto _61;

_61:
#line 14 "/home/yxk/llvm-cbe/test/selectionsort/main.c"
  _38 = _4;
  _4 = (llvm_add_u32(_38, 1));
  goto _50;

  } while (1); /* end of syntactic loop '' */
_52:
#line 28 "/home/yxk/llvm-cbe/test/selectionsort/main.c"
  _39 = printf((&_OC_str_OC_3));
#line 30 "/home/yxk/llvm-cbe/test/selectionsort/main.c"
  _4 = 0;
  goto _62;

  do {     /* Syntactic loop '' to make GCC happy */
_62:
  _40 = _4;
  _41 = _3;
  if ((((int32_t)_40) < ((int32_t)_41))) {
    goto _63;
  } else {
    goto _64;
  }

_63:
#line 31 "/home/yxk/llvm-cbe/test/selectionsort/main.c"
  _42 = _4;
  _43 = *(uint32_t*)(((&(&_2)->array[((int64_t)(((int64_t)(int32_t)_42)))])));
  _44 = printf((&_OC_str_OC_4), _43);
  goto _65;

_65:
#line 30 "/home/yxk/llvm-cbe/test/selectionsort/main.c"
  _45 = _4;
  _4 = (llvm_add_u32(_45, 1));
  goto _62;

  } while (1); /* end of syntactic loop '' */
_64:
  return 0;
}

