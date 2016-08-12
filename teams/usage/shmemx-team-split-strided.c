/*
 * Example Program to show the usage of shmemx_team_split_strided routine
 * 
 * SYNOPSIS:
 * void shmemx_team_split_strided(  shmem_team_t parent_team,
 *                                  int PE_start,
 *                                  int PE_stride,
 *                                  int PE_size,
 *                                  shmem_team_t *new_team  )
 *
 * DESCRIPTION:
 * The shmemx_team_split_strided function is a collective routine. It
 * Tpartitions the existing parent team into a new SHMEM team based on the
 * PE triplet (PE_start, PE_stride, and PE_size) supplied to the
 * function. It is important to note the use of the less restrictive
 * PE_stride argument instead of logPE_stride. This method of creating a
 * team with an arbitrary set of PEs is inherently restricted by its
 * parameters, but allows for many additional use‐cases over using a
 * logPE_stride parameter, and may provide an easier transition for
 * existing SHMEM programs to create and use SHMEM teams. This function
 * must be called by all processes contained in the SHMEM triplet
 * specification. It may be called by additional PEs not included in the
 * triplet specification, but for those processes a newteam value of
 * SHMEM_TEAM_NULL is returned. All calling processes must provide the
 * same values for the PE triplet. This function will return a newteam
 * containing the PE subset specified by the triplet, and ordered by the
 * existing global PE rank value. None of the parameters need to reside
 * in symmetric memory.
 *
 * Error checking will be done to ensure a valid PE triplet is provided,
 * and also to determine whether a valid team handle is provided for the
 * parent_team.
 *
 * All errors are considered fatal and will result in the job aborting
 * with an informative error message.
 *
 * The shmemx_team_split_strided function supports the following
 * arguments:
 *
 * parent_team
 *        A valid SHMEM team. The predefined teams SHMEM_TEAM_WORLD or
 *        SHMEM_TEAM_NODE may be used, or any team created by the
 *        users.
 *
 * PE_start  
 *        The lowest virtual PE number of the parent_team of PEs.
 *
 * PE_stride 
 *        The stride between consecutive virtual PE numbers in the
 *        parent_team.
 *     
 * PE_size   
 *        The number of PEs in the defined set.
 *
 * newteam   
 *        A new SHMEM team handle, representing a PE subset of all the
 *        PEs, that is created from the PE triplet provided.
 *
 * EXAMPLE DETAILS:
 * The example program creates a team based on the strided triplet
 * value with all the even ranked PEs.
 */
#include <stdio.h>
#include <shmem.h>
#include <shmemx.h>

int main(int argc, char *argv[]) {
    int rank, npes;
    int t_pe, t_size;
    shmem_team_t new_team;

    shmem_init();
    rank = shmem_my_pe();
    npes = shmem_n_pes();

    /* create a team of all even ranked PEs from SHMEM_TEAM_WORLD */
    shmemx_team_split_strided(SHMEM_TEAM_WORLD, 0, 2, npes/2, &new_team);
    
    if (new_team != SHMEM_TEAM_NULL) {
        t_size = shmem_team_n_pes(new_team);
        t_pe   = shmem_team_my_pe(new_team);

        printf("Global PE %d has team_pe of %d out of %d\n", 
                rank, t_pe, t_size);
    }

    shmem_barrier_all();
    shmem_finalize();
    return 0;
}
