#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]) {

    int NCHILD;

    if(argc<2)
        NCHILD = 2;
    else 
        NCHILD = atoi(argv[1]);

    printf(1, "*Case1: Parent has no children*\n");
    int wtime1, rtime1;
    int status = wait2(&wtime1, &rtime1);

    if(status == -1) {
        printf(1, "wait2 status: %d\n", status);
    } else {
        printf(1, "wait2 should return -1 if calling process has no children\n");
    }


    printf(1, "*Case2: Parent has children*\n");
    for ( int child = 0; child < NCHILD; child++ ) {
        int pid = fork ();
        if ( pid < 0 ) {
            printf(1, "%d failed in fork!\n", getpid());
            exit();
        } else if (pid == 0) {
            sleep(100);
            printf(1, "Child %d created\n",getpid());
            volatile double a, b;
            a = 3.14;
            b = 36.29;
            volatile double x = 0, z;
            for (z = 0; z < 90000.0; z += 0.1)
            {
                x = x + a * b; 
            }
            printf(1, "Child %d finished\n",getpid());
            exit();
        }
    }
    int wtime, rtime;
    for(int i=0; i<NCHILD; i++){
        status = wait2(&wtime, &rtime);
        printf(1, "Child no. %d, Child pid: %d exited with Status: %d, Waiting Time: %d, Run Time: %d\n", i, status, status, wtime, rtime);
    }
    exit();
}
