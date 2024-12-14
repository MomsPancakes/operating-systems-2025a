#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <pthread.h>

struct abc {
    int a;
    int b;
    size_t c;
} abc;

void
randsleep(void);
void *
bash_abc(void *_);

#endif

