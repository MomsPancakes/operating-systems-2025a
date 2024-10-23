#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_GPROCS 100

/* -----------------------------------------------------------------------------
 * API
 * ----------------------------------------------------------------------------- */

typedef struct process_group ProcessGroup;

struct process_group {
    ProcessGroup (*new)(void);
    ProcessGroup (*fork)(size_t n);
    ProcessGroup (*join)(ProcessGroup pg);

    pid_t self;
    pid_t children[MAX_GPROCS];
    size_t num_children;
};

ProcessGroup
new_proc_group(void);

/* -----------------------------------------------------------------------------
 * Main
 * ----------------------------------------------------------------------------- */

int
main(void)
{
    ProcessGroup pg;

    pg = new_proc_group();
    pg = pg.fork(10);
    pg = pg.join(pg);

    return 0;
}

/* -----------------------------------------------------------------------------
 * Implementation
 * ----------------------------------------------------------------------------- */

ProcessGroup
fork_n(size_t n)
{
    pid_t pid = 0;
    ProcessGroup proc = new_proc_group();

    while (proc.num_children < n && (pid = fork()) > 0) {
        proc.children[proc.num_children++] = pid;
        fprintf(
            stdout, "PID %0d: created child process PID %0d\n", proc.self, pid);
    };

    if (pid < 0) {
        fprintf(stderr, "PID %0d:", proc.self);
        perror(" ");
    }

    return proc;
}

ProcessGroup
join(ProcessGroup proc)
{
    pid_t pid = 0;
    int status = 0;

    if (getpid() != proc.self)
        return proc;

    while (proc.num_children && pid >= 0) {
        pid = waitpid(proc.children[proc.num_children], &status, WNOHANG);

        if (pid > 0) {
            proc.num_children--;
            fprintf(stdout, "PID %0d: child pid %0d finished with status %0d\n",
                proc.self, pid, status);
        }
    }

    if (pid < 0) {
        fprintf(stderr, "PID %0d:", proc.self);
        perror(" ");
    }

    return proc;
}

ProcessGroup
new_proc_group(void)
{
    return (ProcessGroup){
        .new = new_proc_group,
        .fork = fork_n,
        .join = join,

        .self = getpid(),
        .num_children = 0,
        .children = {0},
    };
}

