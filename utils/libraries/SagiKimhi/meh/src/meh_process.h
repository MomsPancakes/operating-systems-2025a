#ifndef MEH_PROCESS_H_
#define MEH_PROCESS_H_

#include <sys/types.h>
#include "meh_darray.h"

#define meh_process_print(p) meh_process_print_(p, #p)

/* -----------------------------------------------------------------------------
 * Struct Definitions
 * ----------------------------------------------------------------------------- */

struct meh_process {
    pid_t pid;
    pid_t ppid;
    meh_darray_t children;
};

/* -----------------------------------------------------------------------------
 * Method Declarations
 * ----------------------------------------------------------------------------- */

extern meh_process_t
meh_process_self(void);

extern meh_process_t 
meh_process_init(pid_t pid, pid_t ppid);

extern void
meh_process_destroy(meh_process_t *p);

extern int
meh_process_fork(meh_process_t *p, size_t nchildren);

extern int
meh_process_join(meh_process_t *p);

extern int
meh_process_join_any(meh_process_t *p);

extern void
meh_process_join_none(meh_process_t *p);

extern void
meh_process_print_(meh_process_t p, char *name);

#endif
