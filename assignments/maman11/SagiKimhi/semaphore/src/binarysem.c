#include "binarysem.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/types.h>

static void
sem_handler(int sig);

sigset_t _ss_up = {0};
sigset_t _ss_down = {0};

volatile pthread_t _grant = 0;
volatile sig_atomic_t _semaphore = 1;

void
sem_init(int status)
{
    struct sigaction sa = {0};

    memset(&sa, 0, sizeof(sa));
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = sem_handler;
    SEM_INIT_SIGSET(sa.sa_mask, SEM_UP_SIGCMD, SEM_DOWN_SIGCMD);
    SEM_INIT_SIGSET(_ss_up, SEM_UP_SIGCMD);
    SEM_INIT_SIGSET(_ss_down, SEM_DOWN_SIGCMD);
    assert(sigprocmask(SIG_BLOCK, &sa.sa_mask, NULL) == 0);
    assert(sigaction(SEM_UP_SIGCMD, &sa, NULL) != -1);
    assert(sigaction(SEM_DOWN_SIGCMD, &sa, NULL) != -1);

    _semaphore = 1;

    if (status == 0)
        sem_down();
}

static void
sem_handler(int sig)
{
    if (sig == SEM_UP_SIGCMD) {
        _grant = 0;
        _semaphore = 1;
        return;
    }

    if (!_grant)
        _grant = pthread_self();
        
    if (_semaphore)
        _semaphore = 0;
}

void
sem_down(void)
{
    pthread_t tid = pthread_self();
    while (_grant != tid || _semaphore == 1) {
        pthread_sigmask(SIG_UNBLOCK, &_ss_down, NULL);
        pthread_kill(tid, SEM_DOWN_SIGCMD);
        pthread_sigmask(SIG_BLOCK, &_ss_down, NULL);
    }
    fprintf(stdout, "\n[INFO] THREAD-%lu: SEM_DOWN!\n", tid);
}

void
sem_up(void)
{
    pthread_t tid = pthread_self();
    fprintf(stdout, "[INFO] THREAD-%lu: SEM_UP!\n", tid);
    pthread_sigmask(SIG_UNBLOCK, &_ss_up, NULL);
    pthread_kill(tid, SEM_UP_SIGCMD);
    pthread_sigmask(SIG_BLOCK, &_ss_up, NULL);
}
