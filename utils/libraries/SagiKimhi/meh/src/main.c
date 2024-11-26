#include "meh_darray.h"
#include "meh_misc.h"
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef MEH_SHORT_NAMESPACE
# define MEH_SHORT_NAMESPACE
# include "meh.h"
#endif

/* -----------------------------------------------------------------------------
 * Typedefs
 * ----------------------------------------------------------------------------- */

typedef int req_val_t;
typedef int unsigned id_t;

typedef enum req_kind req_kind_t;
typedef enum rsp_kind rsp_kind_t;
typedef enum rsrv_state rsrv_state_t;

typedef struct seat seat_t;
typedef struct flight flight_t;
typedef struct booking booking_t;
typedef struct request request_t;
typedef struct response response_t;
typedef struct registry registry_t;
typedef struct travel_agent travel_agent_t;
typedef struct booking_center booking_center_t;
typedef struct booking_manager booking_manager_t;
typedef struct booking_system booking_system_t;
typedef struct airline_booking_system airline_system_t;

/* -----------------------------------------------------------------------------
 * Constants
 * ----------------------------------------------------------------------------- */

enum req_kind {
    RESERVATION,
    CANCELATION,
};

enum rsp_kind {
    OK,
    ERR,
};

enum rsrv_state {
    RESERVED,
    UNRESERVED,
};

/* -----------------------------------------------------------------------------
 * Structs
 * ----------------------------------------------------------------------------- */

struct process_info {
    pid_t pid;
};

struct seat {
    id_t id;
    rsrv_state_t state;
};

struct flight {
    id_t id;
    meh_darray_t seat_da;
};

struct booking {
    id_t id;
    id_t agent_id;
    id_t flight_id;
    meh_darray_t seatno_da;
};

struct request {
    id_t id;
    id_t agent_id;
    req_kind_t kind;
    size_t nof_seats;
};

struct response {
    id_t id;
    request_t req;
    rsp_kind_t status;
};

struct registry {
    id_t flight_id;
    meh_darray_t booking_da;
    meh_darray_t request_da;
    meh_darray_t response_da;
};

struct travel_agent {
    id_t id;
    meh_darray_t booking_da;
    meh_process_t p_info;
};

struct booking_center {
    meh_darray_t rsrved_da;
    meh_darray_t unrsrved_da;
    meh_process_t p_info;
};

struct booking_manager {
    meh_darray_t flight_da;
    meh_darray_t registry_da;
    meh_process_t p_info;
};

struct airline_booking_system {
    meh_darray_t travel_agents;
    booking_center_t booking_center;
    booking_manager_t booking_manager;
    meh_process_t p_info;
};

/* -----------------------------------------------------------------------------
 * Method Declarations
 * ----------------------------------------------------------------------------- */

int
airline_booking_system(void);

airline_system_t
airline_booking_system_create(void);

booking_manager_t
booking_manager_create(void);

booking_center_t
booking_center_create(void);

travel_agent_t
travel_agent_create(void);

void
airline_booking_system_destroy(airline_system_t *as);

void
booking_manager_destroy(booking_manager_t *bm);

void
booking_center_destroy(booking_center_t *bc);

void
travel_agent_destroy(travel_agent_t *ta);

/* -----------------------------------------------------------------------------
 * Main
 * ----------------------------------------------------------------------------- */

int
main(int argc, char *argv[])
{
    meh_as_none(argc);
    meh_as_none(argv);
    return airline_booking_system() ? EXIT_SUCCESS : EXIT_FAILURE;
}

/* -----------------------------------------------------------------------------
 * Method Definitions
 * ----------------------------------------------------------------------------- */

int
airline_booking_system(void)
{
    int ok = 1;
    size_t i = 0;
    travel_agent_t tmp = {0};
    airline_system_t airline = {0};

    airline = airline_booking_system_create();

    for (i = 0, ok = 1; ok && i < 15; i++) {
        tmp = travel_agent_create();
        meh_check(darray.append(&airline.travel_agents, &tmp));
    }

    ok &= darray.extend(
              &airline.travel_agents,
              &airline.travel_agents.items,
              airline.travel_agents.size)
          == meh_cast(int, airline.travel_agents.size);

    ok &= process.fork(&airline.p_info, 3);

    if (getpid() != airline.p_info.pid)
        airline_booking_system_destroy(&airline);

    ok &= process.join(&airline.p_info);

    airline_booking_system_destroy(&airline);

    return ok;
}

airline_system_t
airline_booking_system_create(void)
{
    airline_system_t as;

    memset(&as, 0, sizeof(as));
    as.p_info = process.self();
    as.booking_center = booking_center_create();
    as.booking_manager = booking_manager_create();
    as.travel_agents = darray.create(sizeof(travel_agent_t));
    return as;
}

void
airline_booking_system_destroy(airline_system_t *as)
{
    if (as == NULL)
        return;

    while (as->travel_agents.size)
        travel_agent_destroy(darray.pop(&as->travel_agents));

    process.destroy(&as->p_info);
    darray.destroy(&as->travel_agents);
    booking_center_destroy(&as->booking_center);
    booking_manager_destroy(&as->booking_manager);
}

booking_center_t
booking_center_create(void)
{
    booking_center_t bc;

    memset(&bc, 0, sizeof(bc));
    bc.p_info = process.self();
    bc.rsrved_da = darray.create(sizeof(seat_t));
    bc.unrsrved_da = darray.create(sizeof(seat_t));
    return bc;
}

void
booking_center_destroy(booking_center_t *bc)
{
    if (bc != NULL) {
        process.destroy(&bc->p_info);
        darray.destroy(&bc->rsrved_da);
        darray.destroy(&bc->unrsrved_da);
    }
}

booking_manager_t
booking_manager_create(void)
{
    booking_manager_t bm;

    memset(&bm, 0, sizeof(bm));
    bm.p_info = process.self();
    bm.flight_da = darray.create(sizeof(flight_t));
    bm.registry_da = darray.create(sizeof(registry_t));
    return bm;
}

void
booking_manager_destroy(booking_manager_t *bm)
{
    if (bm != NULL) {
        process.destroy(&bm->p_info);
        darray.destroy(&bm->flight_da);
        darray.destroy(&bm->registry_da);
    }
}

travel_agent_t
travel_agent_create(void)
{
    travel_agent_t ta;
    
    memset(&ta, 0, sizeof(ta));
    ta.id = getpid() - getppid();
    ta.p_info = process.self();
    ta.booking_da = darray.create(sizeof(booking_t));
    return ta;
}

void
travel_agent_destroy(travel_agent_t *ta)
{
    if (ta != NULL) {
        process.destroy(&ta->p_info);
        darray.destroy(&ta->booking_da);
    }
}
