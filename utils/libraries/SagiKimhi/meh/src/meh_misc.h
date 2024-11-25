#ifndef MEH_MISC_H_
#define MEH_MISC_H_

#ifndef meh_cast
# define meh_cast(t, x) ((t)(x))
#endif

#ifndef meh_array_len
# define meh_array_len(array) (sizeof(array) / sizeof((array)[0]))
#endif

#ifndef meh_dref_cast
# define meh_dref_cast(t, x) meh_cast(t *, x)[0]
#endif

#ifndef meh_none
# define meh_none meh_cast(void, 0)
#endif

#ifndef meh_as_none
# define meh_as_none(x) meh_cast(void, (x))
#endif

#ifndef meh_swap
# define meh_swap(a, b)   \
     do {                 \
         (a) = (a) ^ (b); \
         (b) = (b) ^ (a); \
         (a) = (a) ^ (b); \
     } while (0)
#endif

#ifndef meh_ptr_swap
# define meh_ptr_swap(pa, pb) \
     do {                     \
         void *tmp = (pa);    \
         (pa) = (pb);         \
         (pb) = (tmp);        \
     } while (0)
#endif

#endif
