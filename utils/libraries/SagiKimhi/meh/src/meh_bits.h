#ifndef MEH_BITS_H_
#define MEH_BITS_H_

#include "meh_types.h"

/* -----------------------------------------------------------------------------
 * Defines
 * ----------------------------------------------------------------------------- */

#define MEH_BYTE_BITS __CHAR_BIT__
#define MEH_WORD_BITS (sizeof(meh_word_t) * MEH_BYTE_BITS)
#define MEH_WORD_BYTES (sizeof(meh_word_t) / sizeof(char))
#define MEH_WORD_SHORTS (sizeof(meh_word_t) / sizeof(short))
#define MEH_WORD_LONGS (sizeof(meh_word_t) / sizeof(long))
#define MEH_WORD_LONGINTS (sizeof(meh_word_t) / sizeof(long int))

/* -----------------------------------------------------------------------------
 * Unions
 * ----------------------------------------------------------------------------- */

union meh_bitvec {
    meh_i8_t ia8[MEH_WORD_BYTES];
    meh_u8_t ua8[MEH_WORD_BYTES];
    meh_i16_t ia16[MEH_WORD_SHORTS];
    meh_u16_t ua16[MEH_WORD_SHORTS];
    meh_i32_t ia32[MEH_WORD_LONGS];
    meh_u32_t ua32[MEH_WORD_LONGS];
#if __WORDSIZE >= 64
    meh_i64_t ia64[MEH_WORD_LONGINTS];
    meh_u64_t ua64[MEH_WORD_LONGINTS];
#endif
    meh_word_t word;
    meh_bitfld_t bits;
};

/* -----------------------------------------------------------------------------
 * Method Declarations
 * ----------------------------------------------------------------------------- */

extern meh_bitvec_t
meh_bits_get(meh_word_t val, size_t high, size_t low);

extern meh_bitvec_t
meh_bits_set(meh_word_t dst, size_t high, size_t low, meh_word_t src);

extern meh_bitvec_t
meh_bits_toggle(meh_word_t val, size_t high, size_t low);

extern int
meh_bits_compare(
    meh_word_t a,
    meh_word_t ahigh,
    meh_word_t alow,
    meh_word_t b,
    meh_word_t bhigh,
    meh_word_t blow);

extern size_t
meh_bits_countones(meh_word_t value);

extern size_t
meh_bits_countzeros(meh_word_t value);

#endif
