/* 
 * Example program to show the usage of shmemx_team_split_color routine
 *
 * SYNOPSIS:
 * void shmemx_team_split_color(    shmem_team_t parent_team,
 *                                  int color,
 *                                  int key,
 *                                  shmem_team_t *new_team  )
 *
 * The shmem_team_split_color routine is a collective routine. It
 * partitions an existing parent team into disjoint subgroups, one
 * for each value of color. Each subgroup contains all PEs of the same
 * color. Within each subgroup, the PEs are ranked in the order defined
 * by the value of the argument key, with ties broken according to their
 * rank in the parent team. A new team is created for each subgroup and
 * returned in the handle new_team. Each resulting new_team consists of
 * a set of disjoint PEs.
 *
 * A PE may supply the color value SHMEM_COLOR_UNDEFINED, in which
 * case a value of SHMEM_TEAM_NULL is returned for new_team, as this PE
 * will not be a member of any new team. This is a collective call over
 * all members of the parent team, but each PE is permitted to provide
 * different values for color and key. This routine involves gathering
 * the color and key data from all PEs in the parent team to determine
 * the participants in the new team.
 *
 * Any valid PE team can be used as the parent team. This routine must
 * be called by all PEs in the parent team. The value of color must be
 * nonnegative or SHMEM_COLOR_UNDEFINED. None of the parameters need to
 * reside in symmetric memory.
 *
 * Error checking will be done to ensure a valid team handle is provided.
 * All errors are considered fatal and will result in the job aborting
 * with an informative error message.
 *
 * The shmem_team_split_color routine supports the following options:
 *
 * parent_team
 *        A valid PE team. A predefined team constant or any
 *        team created by a split team routine may be used
 *
 * color     
 *        A nonnegative integer representing the subgroup. PEs
 *        with the same color are in the same new team. A value of
 *        SHMEM_COLOR_UNDEFINED may be used to avoid team membership.
 *
 * key       
 *        An integer controlling the PE number within the subgroup.
 *
 * new_team  
 *        A new PE team handle representing a PE subset of all the
 *        PEs that supplied the same color as the calling PE.
 *
 * EXAMPLE DETAILS:
 * This example shows the shmem_team_split_color routine being used to
 * create two disjoint PE subsets, one with all the even numbered PEs and
 * one with the odd numbered PEs.
 */
#include <stdio.h>
#include <shmem.h>
#include <shmemx.h>

int main(int argc, char *argv[]) {
    int rank, npes;
    int color, key;
    int t_pe, t_size;
    shmem_team_t new_team;

    shmem_init();
    rank = shmem_my_pe();
    npes = shmem_n_pes();

    /* split two teams from SHMEM_TEAM_WORLD into odd and even subsets */ 
    color = rank % 2;
    key   = rank;
    shmemx_team_split_color(SHMEM_TEAM_WORLD, color, key, &new_team);
    
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
