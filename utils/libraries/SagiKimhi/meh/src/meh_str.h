#ifndef MEH_STR_H_
#define MEH_STR_H_

#include "meh_types.h"

struct str_t {
    str_t (*str)(const str_t s);

    size_t (*len)(const str_t s);
    size_t (*count)(const str_t s, const str_t sub);
    size_t (*index)(const str_t str, const str_t substr);

    void (*copy)(str_t dst, const str_t src);
    void (*insert)(str_t s, const str_t suffix);
    void (*append)(str_t s, const str_t suffix);
    void (*prepend)(str_t s, const str_t prefix);
    void (*replace)(str_t s, const str_t suffix);
    void (*toupper)(str_t s);
    void (*tolower)(str_t s);

    int (*isupper)(const str_t str);
    int (*islower)(const str_t str);
    int (*isspace)(const str_t str);
    int (*isalpha)(const str_t str);
    int (*isalnum)(const str_t str);
    int (*isdigit)(const str_t str);
    int (*isprint)(const str_t str);
    int (*compare)(const str_t lhs, const str_t rhs);
    int (*icompare)(const str_t lhs, const str_t rhs);
    int (*endswith)(const str_t str, const str_t suffix);
    int (*startswith)(const str_t str, const str_t prefix);

    str_t (*strip)(str_t str);
    str_t (*ltrim)(str_t str, size_t nbytes);
    str_t (*rtrim)(str_t str, size_t nbytes);
    str_t (*substr)(const str_t s, size_t start, ...);
    str_t (*format)(const str_t fmt, ...);
    str_t (*reverse)(str_t str);
    str_t (*truncate)(str_t str, size_t start, size_t maxlen);

};

#endif
