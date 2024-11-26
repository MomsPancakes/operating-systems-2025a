#ifndef MEH_TYPES_H_
#define MEH_TYPES_H_

/* -----------------------------------------------------------------------------
 * Includes
 * ----------------------------------------------------------------------------- */

#include <sys/types.h>

/* -----------------------------------------------------------------------------
 * Typedefs
 * ----------------------------------------------------------------------------- */

typedef union meh_bitvec meh_bitvec_t;
typedef struct meh_darray meh_darray_t;
typedef struct meh_process meh_process_t;

typedef char *str_t;

typedef signed char meh_i8_t;
typedef __S16_TYPE meh_i16_t;
typedef __S32_TYPE meh_i32_t;
typedef __S64_TYPE meh_i64_t;

typedef unsigned char meh_u8_t;
typedef __U16_TYPE meh_u16_t;
typedef __U32_TYPE meh_u32_t;
typedef __U64_TYPE meh_u64_t;

typedef __UWORD_TYPE meh_word_t;
typedef __UWORD_TYPE meh_uword_t;
typedef __SWORD_TYPE meh_sword_t;

#if __WORDSIZE == 32
typedef float meh_f16_t;
typedef double meh_f32_t;
#else
typedef float meh_f32_t;
typedef double meh_f64_t;
#endif

#if __WORDSIZE == 32
typedef struct bitfld32 meh_bitfld_t;
#elif __WORDSIZE >= 64
typedef struct bitfld64 meh_bitfld_t;
#endif

typedef struct bitfld8 meh_bitfld8_t;

typedef struct bitfld16 meh_bitfld16_t;

#if __WORDSIZE >= 32
typedef struct bitfld32 meh_bitfld32_t;
#endif

#if __WORDSIZE >= 64
typedef struct bitfld64 meh_bitfld64_t;
#endif

/* -----------------------------------------------------------------------------
 * Struct Definitions
 * ----------------------------------------------------------------------------- */

struct bitfld8 {
    meh_u8_t bit0 : 1;
    meh_u8_t bit1 : 1;
    meh_u8_t bit2 : 1;
    meh_u8_t bit3 : 1;
    meh_u8_t bit4 : 1;
    meh_u8_t bit5 : 1;
    meh_u8_t bit6 : 1;
    meh_u8_t bit7 : 1;
};

struct bitfld16 {
    meh_u16_t bit0 : 1;
    meh_u16_t bit1 : 1;
    meh_u16_t bit2 : 1;
    meh_u16_t bit3 : 1;
    meh_u16_t bit4 : 1;
    meh_u16_t bit5 : 1;
    meh_u16_t bit6 : 1;
    meh_u16_t bit7 : 1;
    meh_u16_t bit8 : 1;
    meh_u16_t bit9 : 1;
    meh_u16_t bit10 : 1;
    meh_u16_t bit11 : 1;
    meh_u16_t bit12 : 1;
    meh_u16_t bit13 : 1;
    meh_u16_t bit14 : 1;
    meh_u16_t bit15 : 1;
};

#if __WORDSIZE >= 32
struct bitfld32 {
    meh_u32_t b0 : 1;
    meh_u32_t b1 : 1;
    meh_u32_t b2 : 1;
    meh_u32_t b3 : 1;
    meh_u32_t b4 : 1;
    meh_u32_t b5 : 1;
    meh_u32_t b6 : 1;
    meh_u32_t b7 : 1;
    meh_u32_t b8 : 1;
    meh_u32_t b9 : 1;
    meh_u32_t b10 : 1;
    meh_u32_t b11 : 1;
    meh_u32_t b12 : 1;
    meh_u32_t b13 : 1;
    meh_u32_t b14 : 1;
    meh_u32_t b15 : 1;
    meh_u32_t b16 : 1;
    meh_u32_t b17 : 1;
    meh_u32_t b18 : 1;
    meh_u32_t b19 : 1;
    meh_u32_t b20 : 1;
    meh_u32_t b21 : 1;
    meh_u32_t b22 : 1;
    meh_u32_t b23 : 1;
    meh_u32_t b24 : 1;
    meh_u32_t b25 : 1;
    meh_u32_t b26 : 1;
    meh_u32_t b27 : 1;
    meh_u32_t b28 : 1;
    meh_u32_t b29 : 1;
    meh_u32_t b30 : 1;
    meh_u32_t b31 : 1;
};
#endif

#if __WORDSIZE >= 64
struct bitfld64 {
    meh_u64_t b0 : 1;
    meh_u64_t b1 : 1;
    meh_u64_t b2 : 1;
    meh_u64_t b3 : 1;
    meh_u64_t b4 : 1;
    meh_u64_t b5 : 1;
    meh_u64_t b6 : 1;
    meh_u64_t b7 : 1;
    meh_u64_t b8 : 1;
    meh_u64_t b9 : 1;
    meh_u64_t b10 : 1;
    meh_u64_t b11 : 1;
    meh_u64_t b12 : 1;
    meh_u64_t b13 : 1;
    meh_u64_t b14 : 1;
    meh_u64_t b15 : 1;
    meh_u64_t b16 : 1;
    meh_u64_t b17 : 1;
    meh_u64_t b18 : 1;
    meh_u64_t b19 : 1;
    meh_u64_t b20 : 1;
    meh_u64_t b21 : 1;
    meh_u64_t b22 : 1;
    meh_u64_t b23 : 1;
    meh_u64_t b24 : 1;
    meh_u64_t b25 : 1;
    meh_u64_t b26 : 1;
    meh_u64_t b27 : 1;
    meh_u64_t b28 : 1;
    meh_u64_t b29 : 1;
    meh_u64_t b30 : 1;
    meh_u64_t b31 : 1;
    meh_u64_t b32 : 1;
    meh_u64_t b33 : 1;
    meh_u64_t b34 : 1;
    meh_u64_t b35 : 1;
    meh_u64_t b36 : 1;
    meh_u64_t b37 : 1;
    meh_u64_t b38 : 1;
    meh_u64_t b39 : 1;
    meh_u64_t b40 : 1;
    meh_u64_t b41 : 1;
    meh_u64_t b42 : 1;
    meh_u64_t b43 : 1;
    meh_u64_t b44 : 1;
    meh_u64_t b45 : 1;
    meh_u64_t b46 : 1;
    meh_u64_t b47 : 1;
    meh_u64_t b48 : 1;
    meh_u64_t b49 : 1;
    meh_u64_t b50 : 1;
    meh_u64_t b51 : 1;
    meh_u64_t b52 : 1;
    meh_u64_t b53 : 1;
    meh_u64_t b54 : 1;
    meh_u64_t b55 : 1;
    meh_u64_t b56 : 1;
    meh_u64_t b57 : 1;
    meh_u64_t b58 : 1;
    meh_u64_t b59 : 1;
    meh_u64_t b60 : 1;
    meh_u64_t b61 : 1;
    meh_u64_t b62 : 1;
    meh_u64_t b63 : 1;
};
#endif

#endif
