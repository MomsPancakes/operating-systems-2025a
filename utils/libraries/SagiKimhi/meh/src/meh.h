#ifndef MEH_H_
#define MEH_H_

#include "meh_io.h"
#include "meh_api.h"
#include "meh_mem.h"
#include "meh_bits.h"
#include "meh_math.h"
#include "meh_misc.h"
#include "meh_types.h"
#include "meh_darray.h"
#include "meh_process.h"

extern const struct meh_api meh;
extern const struct meh_bits_api meh_bits;
extern const struct meh_darray_api meh_darray;
extern const struct meh_process_api meh_process;

struct meh_api {
    struct meh_bits_api bits;
    struct meh_darray_api darray;
    struct meh_process_api process;
};

#ifdef MEH_SHORT_NAMESPACE
extern const struct meh_bits_api bits;
extern const struct meh_darray_api darray;
extern const struct meh_process_api process;
#endif

#endif
