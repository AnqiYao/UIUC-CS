/**
* Utilities Unleashed Lab
* CS 241 - Spring 2018
*/

#include "format.h"
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	if(argc<2) {
                print_time_usage();
        }

        struct timespec tp,tp1;

        clock_gettime(CLOCK_MONOTONIC,&tp);
        //printf("%ld\n",tp.tv_sec);
        pid_t child_id = fork();

        if (child_id == -1) {
                print_fork_failed();
        }
        else if (child_id > 0) {
                int status;
                pid_t pid = waitpid( child_id, &status, 0 );
                if(pid != -1 && WIFEXITED(status)){
                        if(WEXITSTATUS(status) != 0){
                                exit(1);
                        }
                }
                clock_gettime(CLOCK_MONOTONIC,&tp1);
                double result = (tp1.tv_sec - tp.tv_sec) + (tp1.tv_nsec - tp.tv_nsec)/1000000000;
                display_results(argv, result);
                return 1;

        }
        else{
                execvp(argv[1],&argv[1]);
                print_exec_failed();
        }

}
