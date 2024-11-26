#include "meh_bits.h"

/* -----------------------------------------------------------------------------
 * Macros
 * ----------------------------------------------------------------------------- */

#define itobv(w) ((meh_bitvec_t){.word = (w)})

#define meh_bit_cast(V) ((meh_word_t)(V))

#define meh_bit_size(T) (sizeof(T) * MEH_BYTE_BITS)

#define bit_mask(H, L) ((~(meh_bit_cast(~0) << ((H) - (L)))) << ((H) - (L)))

#define get_bits(V, H, L) (bit_mask(H, L) & meh_bit_cast(V))

#define set_bits(DEST, H, L, V)               \
    (((~bit_mask(H, L)) & meh_bit_cast(DEST)) \
     | (bit_mask(H, L) & meh_bit_cast(V)))

#define toggle_bits(V, H, L) set_bits(V, H, L, (~get_bits(V, H, L)))

#define compare_bits(A, AH, AL, B, BH, BL) \
    (get_bits(A, AH, AL) == get_bits(B, BH, BL))

/* -----------------------------------------------------------------------------
 * Method Definitions
 * ----------------------------------------------------------------------------- */

meh_bitvec_t
meh_bits_get(size_t val, size_t high, size_t low)
{
    return itobv(get_bits(val, high, low));
}

meh_bitvec_t
meh_bits_set(size_t dst, size_t high, size_t low, size_t src)
{
    return itobv(set_bits(dst, high, low, src));
}

meh_bitvec_t
meh_bits_toggle(size_t val, size_t high, size_t low)
{
    return itobv(toggle_bits(val, high, low));
}

int
meh_bits_compare(
    meh_word_t a,
    meh_word_t ahigh,
    meh_word_t alow,
    meh_word_t b,
    meh_word_t bhigh,
    meh_word_t blow)
{
    return compare_bits(a, ahigh, alow, b, bhigh, blow);
}

size_t
meh_bits_countones(size_t value)
{
    return (meh_bit_size(value) - meh_bits_countzeros(value));
}

size_t
meh_bits_countzeros(size_t value)
{
    int count;

    for (count = 0; value; count++)
        value &= value - 1;

    return count;
}
