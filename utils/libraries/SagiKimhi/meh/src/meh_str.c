#include <stdio.h>
#include "meh_str.h"
#include "meh_types.h"

#define __MEH_STR_SIZE sizeof(struct _str_t)
#define __MEH_STR_INIT_CAPACITY __WORDSIZE
#define __MEH_STR_RESIZE_FACTOR 2

/* -----------------------------------------------------------------------------
 * API
 * ----------------------------------------------------------------------------- */

/* str_t _str(const str_t s); */
/* str_t _format(const str_t fmt, ...); */
/* str_t _substr(const str_t s, size_t start, ...); */

/* size_t _len(const str_t s); */
/* size_t _count(const str_t s, const str_t sub); */
/* size_t _index(const str_t str, const str_t substr); */

/* void _copy(str_t dst, const str_t src); */
/* void _insert(str_t s, const str_t suffix); */
/* void _append(str_t s, const str_t suffix); */
/* void _prepend(str_t s, const str_t prefix); */
/* void _replace(str_t s, const str_t suffix); */

/* str_t _upper(str_t s); */
/* str_t _lower(str_t s); */
/* str_t _strip(str_t str); */
/* str_t _ltrim(str_t str, size_t nbytes); */
/* str_t _rtrim(str_t str, size_t nbytes); */
/* str_t _reverse(str_t str); */
/* str_t _truncate(str_t str, size_t start, size_t maxlen); */

/* int _isupper(const str_t str); */
/* int _islower(const str_t str); */
/* int _isspace(const str_t str); */
/* int _isalpha(const str_t str); */
/* int _isalnum(const str_t str); */
/* int _isdigit(const str_t str); */
/* int _isprint(const str_t str); */
/* int _compare(const str_t lhs, const str_t rhs); */
/* int _icompare(const str_t lhs, const str_t rhs); */
/* int _endswith(const str_t str, const str_t suffix); */
/* int _startswith(const str_t str, const str_t prefix); */

/* /1* ----------------------------------------------------------------------------- */
/*  * Static Method Declarations */
/*  * ----------------------------------------------------------------------------- *1/ */

/* static void _resize(struct _str_t s, size_t newsize); */

/* /1* ----------------------------------------------------------------------------- */
/*  * Structs */
/*  * ----------------------------------------------------------------------------- *1/ */

/* struct _str_t { */
/*     str_t buff; */
/*     size_t size; */
/*     size_t capacity; */
/* }; */

/* union _str_u { */
/*     meh_i8_t size[__MEH_STR_SIZE]; */
/*     int align; */
/* }; */

/* /1* ----------------------------------------------------------------------------- */
/*  * API Implementation */
/*  * ----------------------------------------------------------------------------- *1/ */

/* str_t _str(const str_t s) */
/* { */

/* } */

/* str_t _format(const str_t fmt, ...) */
/* { */

/* } */

/* str_t _substr(const str_t s, size_t start, ...) */
/* { */

/* } */


/* size_t _len(const str_t s) */
/* { */

/* } */

/* size_t _count(const str_t s, const str_t sub) */
/* { */

/* } */

/* size_t _index(const str_t str, const str_t substr) */
/* { */

/* } */


/* void _copy(str_t dst, const str_t src) */
/* { */

/* } */

/* void _insert(str_t s, const str_t suffix) */
/* { */

/* } */

/* void _append(str_t s, const str_t suffix) */
/* { */

/* } */

/* void _prepend(str_t s, const str_t prefix) */
/* { */

/* } */

/* void _replace(str_t s, const str_t suffix) */
/* { */

/* } */


/* str_t _upper(str_t s) */
/* { */

/* } */

/* str_t _lower(str_t s) */
/* { */

/* } */

/* str_t _strip(str_t str) */
/* { */

/* } */

/* str_t _ltrim(str_t str, size_t nbytes) */
/* { */

/* } */

/* str_t _rtrim(str_t str, size_t nbytes) */
/* { */

/* } */

/* str_t _reverse(str_t str) */
/* { */

/* } */

/* str_t _truncate(str_t str, size_t start, size_t maxlen) */
/* { */

/* } */


/* int _isupper(const str_t str) */
/* { */

/* } */

/* int _islower(const str_t str) */
/* { */

/* } */

/* int _isspace(const str_t str) */
/* { */

/* } */

/* int _isalpha(const str_t str) */
/* { */

/* } */

/* int _isalnum(const str_t str) */
/* { */

/* } */

/* int _isdigit(const str_t str) */
/* { */

/* } */

/* int _isprint(const str_t str) */
/* { */

/* } */

/* int _compare(const str_t lhs, const str_t rhs) */
/* { */

/* } */

/* int _icompare(const str_t lhs, const str_t rhs) */
/* { */

/* } */

/* int _endswith(const str_t str, const str_t suffix) */
/* { */

/* } */

/* int _startswith(const str_t str, const str_t prefix) */
/* { */

/* } */


/* -----------------------------------------------------------------------------
 * Static Method Implementation
 * ----------------------------------------------------------------------------- */

