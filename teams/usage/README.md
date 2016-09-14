# Test Details

Tests in this directory are example programs, and there is no
verification performed on the end of each tests. These example
programs are just used to show the users on the actual usage of
the new team creation, destroy, team-based reduction routines.

The following teams routines are used the examples:

Team Creation routines:  
1. shmemx\_team\_split\_color  
2. shmemx\_team\_split\_strided  
3. shmemx\_team\_split\_2d  
4. shmemx\_team\_split\_3d  

Team Maintenance routines:  
1. shmemx\_team\_my\_pe  
2. shmemx\_team\_n\_pes  
3. shmemx\_team\_destroy  

Team-based reduction routines:  
1. shmemx\_team\_int\_sum\_to\_all  
2. shmemx\_team\_int\_max\_to\_all  
3. shmemx\_team\_int\_min\_to\_all  
4. shmemx\_team\_int\_prod\_to\_all  
5. shmemx\_team\_int\_and\_to\_all  
6. shmemx\_team\_int\_or\_to\_all  
7. shmemx\_team\_int\_xor\_to\_all  

# Build Instructions

Each program can be compiled separately without adding any extra
flags. We should make sure that the new SHMEM team routines are
supported by the implementation. Team routines used in this 
directory are available in Cray SHMEM from version 7.4.4
```
cc shmemx-team-sum-to-all.c -o sma
```

# Running Tests

There is no need for any special flags to run these routines. On 
ALPS-based Cray system. We can run the tests as shown below:
```
aprun -n 4 -N 2 ./sma
```

