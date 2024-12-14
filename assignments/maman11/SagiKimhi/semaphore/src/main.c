#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "binarysem.h"

#define N 100

int
main(int argc, char *argv[])
{
    size_t i = 0;
    pthread_t th[N] = {0};

    srand(time(NULL));

    sem_init(1);

    for (i = 0; i < N; i++)
        pthread_create(&th[i], NULL, &bash_abc, NULL);

    for (i = 0; i < N; i++)
        pthread_join(th[i], NULL);

    (void)(argc);
    (void)(argv);
    exit(EXIT_SUCCESS);
}

void *
bash_abc(void *_)
{
    int cnt = 0;
    struct abc _abc = {0};

    (void)(_);
    while (cnt++ < 5) {
        sem_down();
        abc.a = rand();
        abc.b = rand();
        abc.c = rand();
        _abc = abc;
        randsleep();
        assert(abc.a == _abc.a && abc.b == _abc.b && abc.c == _abc.c);
        sem_up();
    }
    pthread_exit(0);
}
float
randfloat(float min, float max)
{
    return (((float)rand()) / RAND_MAX) * (max - min) + min;
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
