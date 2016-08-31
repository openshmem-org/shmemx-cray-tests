/*
 * Example program to show the usage of shmemx_team_<datatype>_or_to_all
 * routine
 *
 * SYNOPSIS:
 * void shmemx_team_<datatype>_or_to_all(    shmem_team_t team,
 *                                              <datatype>  *dest,
 *                                              <datatype>  *source,
 *                                              int          nreduce,
 *                                              <datatype>  *pWrk,
 *                                              long        *pSync  )
 * 
 * where <datatype> is one from short, int, long, and longlong
 *
 * DESCRIPTION:
 * The shmemx_team_<datatype>_or_to_all is a collective routine which 
 * compute one or more reductions across symmetric arrays on multiple 
 * virtual PEs. A reduction performs an associative binary operation across
 * a set of values. Each of these routines asandes that only PEs which are
 * members of the team call the routine. If a PE not a member of the team
 * calls a collective reduction routine, undefined behaviour results.
 *
 * The nreduce argument determines the number of separate reductions to
 * perform. The source array on all PEs in the team provides one 
 * element for each reduction. The results of the reductions are placed
 * in the target array on all PEs in the team. The team is determined using 
 * the team handle provided as input.
 *
 * The source and target arrays may be the same array, but they may not be 
 * overlapping arrays.
 *
 * The shmemx_team_<datatype>_or_to_all supports the following options:
 * team     
 *              A valid PE team. A predefined team constant or any team 
 *              created by a split team routine may be used
 *
 * dest
 *              A symmetric array of length nreduce elements to receive 
 *              the results of the reduction operations.
 * source
 *              A symmetric array, of length nreduce elements, that 
 *              contains one element for each separate reduction operation. 
 *              The source argument must have the same data type as target.
 *
 * nreduce
 *              The number of elements in the target and source arrays. 
 *              nreduce must be of type integer. If you are using Fortran, 
 *              it must be a default integer value.
 *
 * pWrk
 *              A symmetric work array. The pWrk argument must have the same
 *              data type as target.
 *              In C/C++ or Fortran, this contains 
 *              max(nreduce/2+1, SHMEM_REDUCE_MIN_WRKDATA_SIZE) elements.
 *
 * pSync
 *              A symmetric work array. In C/C++, pSync is of type long and 
 *              size SHMEM_REDUCE_SYNC_SIZE. In Fortran, pSync is of type 
 *              integer and size SHMEM_REDUCE_SYNC_SIZE. If you are using
 *              Fortran, it must be a default integer value. Every element 
 *              of this array must be initialized with the value 
 *              SHMEM_SYNC_VALUE before any of the PEs in the team enter 
 *              the reduction routine.
 *
 * The values for arguments nreduce and team must be same in all PE team 
 * members. The same target and source arrays, and the same pWrk and pSync 
 * work arrays, must be passed to all PEs in the team. 
 *
 * Before any PE calls a reduction routine, you must ensure that the
 * following conditions exist (synchronization via a barrier or some 
 * other method is often needed to ensure this):
 *
 *    . The pWrk and pSync arrays on all PEs in the team are not
 *      still in use from a prior call to a collective routine.
 *
 *    . The target array on all PEs in the team is ready to accept
 *      the results of the reduction.
 *
 * Upon return from a reduction routine, the following is true for the
 * local PE:
 *
 *    ·  The target array is updated.
 *
 * EXAMPLE DETAILS:
 * The example program shows shmemx_team_int_or_to_all routine used to 
 * perform collective reduction operation across all the PEs in the
 * SHMEM_TEAM_WORLD team. SHMEM_TEAM_WORLD is a predefined team which
 * includes all PEs
 */
#include <stdio.h>
#include <shmem.h>
#include <shmemx.h>

long pSync[SHMEM_REDUCE_SYNC_SIZE];

#define N 3
int dest[N];
int source[N];

#define MAX(a, b) ((a > b) ? a : b)
#define PWRK_MAX_SIZE MAX(N/2+1, SHMEM_REDUCE_MIN_WRKDATA_SIZE)
int pWrk[PWRK_MAX_SIZE];

int main(int argc, char *argv[]) {
    int i;
    int me, npes;

    shmem_init();
    me = shmem_my_pe();
    npes = shmem_n_pes();

    for (i = 0; i < SHMEM_REDUCE_SYNC_SIZE; i++) {
        pSync[i] = SHMEM_SYNC_VALUE;
    }

    for (i = 0; i < N; i++) {
        source[i] = (me+1)%4;
    }

    shmem_barrier_all();
    shmemx_team_int_or_to_all(SHMEM_TEAM_WORLD, dest, source, N, 
                               pWrk, pSync);

    for (i = 0; i < N; i++) {
        printf("[PE:%d] dest[%d]=%d\n", me, i, dest[i]);
    }

    shmem_barrier_all();
    shmem_finalize();
    return 0;
}
