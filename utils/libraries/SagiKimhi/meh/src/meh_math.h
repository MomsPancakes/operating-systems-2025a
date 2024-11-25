#ifndef MEH_MATH_H_
#define MEH_MATH_H_

#ifndef meh_min
# define meh_min(a, b) ((a) < (b) ? (a) : (b));
#endif

#ifndef meh_max
# define meh_max(a, b) ((a) > (b) ? (a) : (b));
#endif

#ifndef meh_divceil
# define meh_divceil(a, b) \
     (((a) != 0 && (b) != 0) ? (1 + (((a) - 1) / (b))) : 1)
#endif

#endif
