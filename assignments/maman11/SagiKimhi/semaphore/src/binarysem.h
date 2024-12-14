#ifndef _BINARYSEM_H
#define _BINARYSEM_H

#define _GNU_SOURCE
#include <signal.h>

#define __SEM_INIT_SIGSET(SET, ...)   \
    do {                              \
        int i = 0;                    \
        int sig[] = {__VA_ARGS__};    \
        sigset_t *set = &(SET);       \
        sigemptyset(set);             \
        while (sig[i]) {              \
            sigaddset(set, sig[i++]); \
        }                             \
    } while (0)

#define _SEM_INIT_SIGSET(SET, ...) __SEM_INIT_SIGSET(SET, __VA_ARGS__, 0)

#define SEM_INIT_SIGSET(SET, SIG, ...) _SEM_INIT_SIGSET(SET, SIG, ##__VA_ARGS__)

enum sem_sigcmd {
    SEM_UP_SIGCMD = SIGUSR1,
    SEM_DOWN_SIGCMD = SIGUSR2,
};

void
sem_init(int status);

void
sem_down(void);

void
sem_up(void);

#endif
