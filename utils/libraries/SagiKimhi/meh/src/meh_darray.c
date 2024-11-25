#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "meh_io.h"
#include "meh_mem.h"
#include "meh_math.h"
#include "meh_misc.h"
#include "meh_types.h"
#include "meh_darray.h"

/* -----------------------------------------------------------------------------
 * Macros and Defines
 * ----------------------------------------------------------------------------- */

#ifndef DARRAY_INIT_CAP
# define DARRAY_INIT_CAP __WORDSIZE
#endif

#ifndef DARRAY_RESIZE_FACTOR
# define DARRAY_RESIZE_FACTOR 2
#endif

#ifndef darray_item_at
# define darray_item_at(da, index) ((da).items + ((index) * (da).stride))
#endif

#ifndef darray_byte_size
# define darray_byte_size(da) ((da).size * (da).stride)
#endif

#ifndef darray_byte_capacity
# define darray_byte_capacity(da) ((da).capacity * (da).stride)
#endif

#ifndef darray_ensure_index_valid
# define darray_ensure_index_valid(da, index, ret) \
     meh_ensure(darray_is_index_valid(da, index) == 1, ret)
#endif

#ifndef darray_ensure_stride_valid
# define darray_ensure_stride_valid(sz, ret) \
     meh_ensure(darray_is_item_size_valid(sz) == 1, ret)
#endif

#ifndef darray_ensure_valid
# define darray_ensure_valid(da, ret) meh_ensure(darray_is_valid(da) == 1, ret)
#endif

#ifndef darray_ensure_empty
# define darray_ensure_empty(da, ret) meh_ensure(darray_is_empty(da) == 1, ret)
#endif

#ifndef darray_ensure_not_null
# define darray_ensure_not_null(ptr, ret) meh_ensure((ptr) != NULL, ret);
#endif

#ifndef darray_ensure_not_empty
# define darray_ensure_not_empty(da, ret) \
     meh_ensure(meh_darray_non_empty(da) == 1, ret)
#endif

#ifndef darray_ensure_allocated
# define darray_ensure_allocated(da, ret) \
     meh_ensure(darray_is_allocated(da) == 1, ret)
#endif

#ifndef darray_ensure_reallocated
# define darray_ensure_reallocated(buf, sz, ret) \
     darray_ensure_not_null((buf) = meh_realloc((buf), (sz)), ret)
#endif

/* -----------------------------------------------------------------------------
 * Static Method Declarations
 * ----------------------------------------------------------------------------- */

static void
meh_darray_init(meh_darray_t *da, size_t item_sz);

static int
darray_is_valid(meh_darray_t da);

static int
darray_is_allocated(meh_darray_t da);

static int
darray_is_index_valid(meh_darray_t da, size_t index);

static int
darray_is_item_size_valid(size_t sz);

/* -----------------------------------------------------------------------------
 * Public Method Definitions
 * ----------------------------------------------------------------------------- */

meh_darray_t
meh_darray_create_(size_t item_sz)
{
    meh_darray_t da = {0};
    meh_darray_init(&da, item_sz);
    return da;
}

void
meh_darray_destroy(meh_darray_t *da)
{
    if (da == NULL)
        return;

    if (da->items)
        meh_free(da->items);

    da->size = 0;
    da->stride = 0;
    da->capacity = 0;
    da->items = NULL;
}

void *
meh_darray_get(meh_darray_t da, size_t index)
{
    darray_ensure_valid(da, NULL);
    darray_ensure_allocated(da, NULL);
    darray_ensure_not_empty(da, NULL);
    darray_ensure_index_valid(da, index, NULL);
    return darray_item_at(da, index);
}

int
meh_darray_set(meh_darray_t da, size_t index, const void *item)
{
    darray_ensure_valid(da, 0);
    darray_ensure_allocated(da, 0);
    darray_ensure_not_null(item, 0);
    darray_ensure_index_valid(da, index, 0);
    memcpy(darray_item_at(da, index), item, da.stride);
    return 1;
}

void *
meh_darray_pop(meh_darray_t *da)
{
    darray_ensure_not_null(da, NULL);
    darray_ensure_valid(*da, NULL);
    darray_ensure_allocated(*da, NULL);
    darray_ensure_not_empty(*da, NULL);
    return darray_item_at(*da, --(da->size));
}

void *
meh_darray_last(meh_darray_t da)
{
    darray_ensure_valid(da, NULL);
    darray_ensure_allocated(da, NULL);
    darray_ensure_not_empty(da, NULL);
    return darray_item_at(da, da.size - 1);
}

void *
meh_darray_first(meh_darray_t da)
{
    darray_ensure_valid(da, NULL);
    darray_ensure_allocated(da, NULL);
    darray_ensure_not_empty(da, NULL);
    return darray_item_at(da, 0);
}

int
meh_darray_append(meh_darray_t *da, const void *item)
{
    darray_ensure_not_null(da, 0);

    if (meh_darray_resize(da, da->size + 1)) {
        if (meh_darray_set(*da, da->size - 1, item))
            return 1;

        (da->size)--;
    }

    return 0;
}

int
meh_darray_extend(meh_darray_t *da, void **items, size_t nitems)
{
    size_t idx;
    size_t offset;

    darray_ensure_not_null(da, 0);
    darray_ensure_not_null(items, 0);
    darray_ensure_not_null(*items, 0);

    if (meh_darray_resize(da, da->size + nitems)) {
        for (idx = da->size - nitems; idx < da->size; idx++) {
            offset = da->stride * (da->size - idx);

            if (!meh_darray_set(*da, idx, items[0] + offset))
                break;
        }

        nitems = da->size - idx;

        if (nitems)
            da->size -= nitems;
    }

    return nitems;
}

size_t
meh_darray_len(meh_darray_t da)
{
    return da.size;
}

size_t
meh_darray_blen(meh_darray_t da)
{
    return da.size * da.stride;
}

int
meh_darray_empty(meh_darray_t da)
{
    return !darray_is_allocated(da) || !da.size;
}

int
meh_darray_non_empty(meh_darray_t da)
{
    return darray_is_allocated(da) && da.size;
}

int
meh_darray_copy(meh_darray_t *dst, meh_darray_t src)
{
    meh_ensure(meh_darray_resize_item(dst, src.stride), 0);
    meh_ensure(meh_darray_resize(dst, src.size), 0);
    memcpy(dst->items, (const void *)src.items, darray_byte_size(src));
    return 1;
}

int
meh_darray_take(meh_darray_t *dst, meh_darray_t *src)
{
    meh_darray_destroy(dst);
    return meh_darray_swap(dst, src);
}

int
meh_darray_swap(meh_darray_t *dst, meh_darray_t *src)
{
    darray_ensure_not_null(src, 0);
    darray_ensure_not_null(dst, 0);
    meh_swap(dst->size, src->size);
    meh_swap(dst->stride, src->stride);
    meh_swap(dst->capacity, src->capacity);
    meh_ptr_swap(dst->items, src->items);
    return 1;
}

void
meh_darray_print(meh_darray_t da, const char *name)
{
    void *p;

    darray_ensure_valid(da, meh_none);

    if (!name)
        name = "darray";

    p = da.items;

    fprintf(stdout, "%s.size=%zu\n", name, da.size);
    fprintf(stdout, "%s.stride=%zu\n", name, da.stride);
    fprintf(stdout, "%s.capacity=%zu\n", name, da.capacity);
    fprintf(stdout, "%s.items=%s\n", name, p ? "[" : "NULL");

    if (!p)
        return;

    while (da.size > 1) {
        fprintf(stdout, "%p, ", p);
        p += da.stride;
        da.size--;
    }

    if (da.size)
        fprintf(stdout, "%p", p);

    fprintf(stdout, "]\n");
}

meh_darray_t
meh_darray_clone(meh_darray_t da)
{
    meh_darray_t _da = meh_darray_create_(da.stride);
    meh_ensure(meh_darray_copy(&_da, da), (meh_darray_t){0});
    return _da;
}

int
meh_darray_resize(meh_darray_t *da, size_t newsz)
{
    size_t newcap = 0;
    size_t newcap_bytes = 0;

    darray_ensure_not_null(da, 0);
    darray_ensure_valid(*da, 0);

    if (da->size != newsz) {
        if (da->capacity < newsz) {
            newcap = meh_max(da->capacity, DARRAY_INIT_CAP);

            while (newcap < newsz)
                newcap *= DARRAY_RESIZE_FACTOR;

            newcap_bytes = newcap * da->stride;
            darray_ensure_reallocated(da->items, newcap_bytes, 0);
            memset(darray_item_at(*da, da->capacity), 0, newcap_bytes);
            da->capacity = newcap;
        }
        da->size = newsz;
    }
    return 1;
}

int
meh_darray_resize_item(meh_darray_t *da, size_t newsz)
{
    darray_ensure_stride_valid(newsz, 0);
    darray_ensure_not_null(da, 0);
    darray_ensure_valid(*da, 0);
    if (da->stride != newsz) {
        darray_ensure_reallocated(da->items, da->capacity * newsz, 0);
        da->size = darray_byte_size(*da) / newsz;
        da->stride = newsz;
    }
    return 1;
}

/* -----------------------------------------------------------------------------
 * Static Method Definitions
 * ----------------------------------------------------------------------------- */

static void
meh_darray_init(meh_darray_t *da, size_t item_sz)
{
    if (item_sz == 0)
        item_sz++;

    memset(da, 0, sizeof(*da));
    da->size = 0;
    da->items = NULL;
    da->stride = item_sz;
    da->capacity = 0;
}

static int
darray_is_valid(meh_darray_t da)
{
    return da.stride > 0 && da.capacity >= da.size
           && ((da.capacity == 0 && da.items == NULL)
               || (da.capacity > 0 && da.items != NULL));
}

static int
darray_is_allocated(meh_darray_t da)
{
    return da.capacity > 0 && da.items != NULL;
}

static int
darray_is_index_valid(meh_darray_t da, size_t index)
{
    return index < da.size;
}

static int
darray_is_item_size_valid(size_t sz)
{
    return sz > 0;
}
