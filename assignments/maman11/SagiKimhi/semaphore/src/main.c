#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/types.h>

/* --------------------------------------------------------------------------
 * Defines
 * -------------------------------------------------------------------------- */

#define N 20

/* --------------------------------------------------------------------------
 * Structs
 * -------------------------------------------------------------------------- */

struct abc {
    int a;
    int b;
    size_t c;
};

/* --------------------------------------------------------------------------
 * Method Declarations
 * -------------------------------------------------------------------------- */

void
sem_handler(int sig);

void
sem_init(int status);

void
sem_down(void);

void
sem_up(void);

void *
bash_abc(void *_);

/* --------------------------------------------------------------------------
 * Constants
 * -------------------------------------------------------------------------- */

enum sem_sigcmd {
    SEM_UP_SIGCMD = SIGUSR1,
    SEM_DOWN_SIGCMD = SIGUSR2,
};

/* --------------------------------------------------------------------------
 * Globals
 * -------------------------------------------------------------------------- */

struct abc abc = {0};
sigset_t set_up = {0};
sigset_t set_down = {0};
struct sigaction sa = {0};

volatile pthread_t _grant = 0;
volatile sig_atomic_t _semaphore = 1;

/* --------------------------------------------------------------------------
 * Main
 * -------------------------------------------------------------------------- */

int
main(int argc, char *argv[])
{
    size_t i = 0;
    pthread_t th[N] = {0};

    (void)(argc);
    (void)(argv);

    srand(time(NULL));
    sem_init(1);
    memset(&abc, 0, sizeof(abc));

    for (i = 0; i < N; i++) {
        pthread_create(&th[i], NULL, &bash_abc, NULL);
    }

    for (i = 0; i < N; i++) {
        pthread_join(th[i], NULL);
    }

    exit(EXIT_SUCCESS);
}

/* --------------------------------------------------------------------------
 * Method Definitions
 * -------------------------------------------------------------------------- */

float
randfloat(float min, float max)
{
    return (((float)rand()) / RAND_MAX) * (max - min) + min;
}

int
randint(int min, int max)
{
    return ((int)randfloat(min, max));
}

void
randsleep(void)
{
    float t = 0;

    t = randfloat(0.0f, 1.2f);

    fprintf(
        stdout,
        "[INFO] THREAD-%lu: going to sleep for %0.3f seconds...\n",
        pthread_self(),
        t);
    sleep(t);
    fprintf(stdout, "[INFO] THREAD-%lu: sleep period ended.\n", pthread_self());
}

void *
bash_abc(void *_)
{
    int cnt = 0;
    bool done = false;
    struct abc _abc = {0};

    (void)(_);

    while (!done) {
        sem_down();
        abc.a = rand();
        abc.b = rand();
        abc.c = rand();
        _abc = abc;
        randsleep();

        if (abc.a != _abc.a || abc.b != _abc.b || abc.c != _abc.c) {
            fprintf(
                stdout, "[ERROR] THREAD-%0lu: abc != _abc.\n", pthread_self());
        }
        sem_up();

        if (++cnt >= 5)
            done = true;
    }
    pthread_exit(0);
}

/* --------------------------------------------------------------------------
 * Semaphore Definition
 * -------------------------------------------------------------------------- */

void
sem_init(int status)
{
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = sem_handler;

    sigemptyset(&set_up);
    sigemptyset(&set_down);
    sigemptyset(&sa.sa_mask);
    sigaddset(&set_up, SEM_UP_SIGCMD);
    sigaddset(&set_down, SEM_DOWN_SIGCMD);
    sigaddset(&sa.sa_mask, SEM_UP_SIGCMD);
    sigaddset(&sa.sa_mask, SEM_DOWN_SIGCMD);

    _semaphore = 1;

    if (sigprocmask(SIG_BLOCK, &sa.sa_mask, NULL) != 0) {
        perror("pthread_sigmask");
        exit(EXIT_FAILURE);
    }

    if (sigaction(SEM_UP_SIGCMD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    if (sigaction(SEM_DOWN_SIGCMD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    if (!status)
        sem_down();
}

void
sem_handler(int sig)
{
    if (sig == SEM_UP_SIGCMD) {
        _grant = 0;
        _semaphore = 1;
    } else {
        if (_grant == 0) {
            _grant = pthread_self();
        }
        if (_semaphore > 0) {
            _semaphore = 0;
        }
    }
}

void
sem_down(void)
{
    sigset_t set;
    pthread_t tid = pthread_self();

    sigemptyset(&set);
    sigaddset(&set, SEM_DOWN_SIGCMD);

    while (_grant != tid || _semaphore == 1) {
        pthread_sigmask(SIG_UNBLOCK, &set, NULL);
        pthread_kill(pthread_self(), SEM_DOWN_SIGCMD);
        pthread_sigmask(SIG_BLOCK, &set, NULL);
    }

    fprintf(stdout, "\n[INFO] THREAD-%lu: SEM_DOWN!\n", pthread_self());
}

void
sem_up(void)
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SEM_UP_SIGCMD);
    fprintf(stdout, "[INFO] THREAD-%lu: SEM_UP!\n", pthread_self());
    pthread_sigmask(SIG_UNBLOCK, &set, NULL);
    pthread_kill(pthread_self(), SEM_UP_SIGCMD);
    pthread_sigmask(SIG_BLOCK, &set, NULL);
}
