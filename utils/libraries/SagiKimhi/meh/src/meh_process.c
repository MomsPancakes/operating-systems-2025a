#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "meh_process.h"
#include "meh_darray.h"
#include "meh_types.h"
#include "meh_io.h"
#include "meh_misc.h"

/* -----------------------------------------------------------------------------
 * Defines
 * ----------------------------------------------------------------------------- */

#ifndef process_get_child
# define process_get_child(p, i) \
     meh_cast(meh_process_t *, meh_darray_get((p).children, i))
#endif

#ifndef process_pop_child
# define process_pop_child(p) \
     meh_cast(meh_process_t *, meh_darray_pop(&((p).children)))
#endif

#ifndef process_last_child
# define process_last_child(p) \
     meh_cast(meh_process_t *, meh_darray_last((p).children))
#endif

#ifndef process_first_child
# define process_first_child(p) \
     meh_cast(meh_process_t *, meh_darray_first((p).children))
#endif

/* -----------------------------------------------------------------------------
 * Implementation
 * ----------------------------------------------------------------------------- */

meh_process_t
meh_process_self(void)
{
    return meh_process_init(getpid(), getppid());
}

meh_process_t
meh_process_init(pid_t pid, pid_t ppid)
{
    return (meh_process_t){
        .pid = pid,
        .ppid = ppid,
        .children = meh_darray_create(meh_process_t),
    };
}

void
meh_process_destroy(meh_process_t *p)
{
    if (p != NULL && p->pid == getpid()) {
        meh_process_join(p);
        meh_darray_destroy(&p->children);
    }
}

int
meh_process_fork(meh_process_t *p, size_t nchildren)
{
    pid_t pid;

    meh_ensure(p != NULL, 0);
    meh_ensure(getpid() == p->pid, 0);

    while (nchildren-- && (pid = fork()) > 0) {
        meh_process_t cp = meh_process_init(pid, p->pid);
        meh_darray_append(&p->children, &cp);
        meh_debug("pid-%0d: successfuly forked child pid-%0d.", p->pid, pid);
    };

    return pid != -1;
}

int
meh_process_join(meh_process_t *p)
{
    size_t n = 0;
    size_t sz = 0;

    meh_ensure(p != NULL, 0);

    if (getpid() != p->pid)
        _exit(0);

    sz = p->children.size;

    while (meh_process_join_any(p))
        n++;

    return sz - n;
}

int
meh_process_join_any(meh_process_t *p)
{
    size_t i = 0;
    size_t j = 0;
    pid_t pid = 0;
    int status = 0;

    if (getpid() != p->pid)
        _exit(0);

    meh_ensure(p != NULL, 0);

    if (p->children.size == 0)
        return 0;

    while ((pid = waitpid(0, &status, WNOHANG)) == 0)
        sleep(0);

    if (pid < 0) {
        meh_error("waitpid returned -1");
        perror("");
        return 0;
    }

    meh_debug("pid-%0d: joining child process %0d (exit_status: %0d)...", p->pid, pid, status);
    
    for (i = 0; i < p->children.size; i++)
        if (process_get_child(*p, i)->pid == pid)
            break;

    meh_debug("pid-%0d: removing pid %0d from children_list[%0zu]...", p->pid, pid, i);

    for (j = i + 1; j < p->children.size; j++, i++)
        meh_darray_set(p->children, i, process_get_child(*p, j));

    meh_ensure((i == p->children.size - 1), 0);
    meh_ensure((process_pop_child(*p) != NULL), 0);
    meh_debug("pid-%0d: done.", p->pid);
    return 1;
}

void
meh_process_join_none(meh_process_t *p)
{
    meh_ensure(p != NULL, meh_none);
    if (getpid() != p->pid)
        _exit(0);
}

void
meh_process_print_(meh_process_t p, char *name)
{
    if (!name)
        name = "process";

    fprintf(stdout, "%s: process.pid = %0d\n", name, p.pid);
    fprintf(stdout, "%s: process.ppid = %0d\n", name, p.ppid);
    meh_da_print(p.children);
}
