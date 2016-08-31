# Test Details

---

Tests in this directory are example programs, and there is no
verification performed on the end of each tests. These example
programs are just used to show the users on the actual usage of
the new team creation, destroy, team-based reduction routines.

# Build Instructions

---

Each program can be compiled separately without adding any extra
flags. We should make sure that the new SHMEM team routines are
supported by the implementation. Team routines used in this 
directory are available in Cray SHMEM from version 7.5.0
```
cc shmemx-team-sum-to-all.c -o sma
```

# Running Tests

---

There is no need for any special flags to run these routines. On 
ALPS-based Cray system. We can run the tests as shown below:
```
aprun -n 4 -N 2 ./sma
```

