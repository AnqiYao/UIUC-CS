/*
*  Lab
* CS 241 - Spring 2018
*/

#include "utils.h"
#include <alloca.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

void setup_fds(int new_stdin, int new_stdout);
void close_and_exec(char *exe, char *const *params);
pid_t start_reducer(char *reducer_exec, int in_fd, char *output_filename);
pid_t *read_input_chunked(char *filename, int *fds_to_write_to,
                          int num_mappers);
pid_t *start_mappers(char *mapper_exec, int num_mappers, int *read_mapper,
                     int write_reducer);
size_t count_lines(const char *filename);

void usage() {
    print_usage();
}

int main(int argc, char **argv) {
	if(argc != 6){
		usage();
        	exit(1);	
	}
	int num = atoi(argv[5]);
    // Create an input pipe for each mapper.
 	int mapper_pipe[2];
	pipe(mapper_pipe);
    // Create one input pipe for the reducer.
//	int reducer_pipe[2];
//	pipe(reducer_pipe);
    // Open the output file.
	int input_start = open(argv[1], O_RDONLY);
        int output_end = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
    // Start a splitter process for each mapper.
	pid_t splitter_id[num];
	pid_t mapper_id[num];
	for(int i = 0; i < num; i++){
		int splitter_pipe[2];
		pipe(splitter_pipe);

		splitter_id[i] = fork();
		if(splitter_id[i] == 0){	// child
			
			close(mapper_pipe[1]);
			close(mapper_pipe[0]);
			close(splitter_pipe[0]);
			
			
			dup2(input_start,0);	//redirect 
			dup2(splitter_pipe[1], 1);
			
			char splitter_idx[2];
            		sprintf(splitter_idx, "%d", i);
		
			execlp("./splitter","./splitter",argv[1],argv[5],splitter_idx, (char*)NULL);	
			exit(1);
		}else if (splitter_id[i] != 0) {
			//parents
		}
		//Start the mapper processe.
			mapper_id[i] = fork();
        		if (mapper_id[i] == 0) {//child
            			close(mapper_pipe[0]);
           	 		close(splitter_pipe[1]);

            			dup2(splitter_pipe[0], 0);
            			dup2(mapper_pipe[1], 1);
	
		            	execlp(argv[3], argv[3], (char *)NULL);
            			exit(1);
        		}
			//parent
        		close(splitter_pipe[0]);
        		close(splitter_pipe[1]);
				
	}
 
    // Start the reducer process.
	pid_t reducer_id = fork();		// take one reducer to complete the task
    // Wait for the reducer to finish.
	if (reducer_id == 0) {	//child 
        	close(mapper_pipe[1]);
		
        	dup2(mapper_pipe[0], 0);
        	dup2(output_end, 1);

        	execlp(argv[4], argv[4], (char *)NULL);
        	exit(1);
    	}else{
        	close(mapper_pipe[0]);
        	close(mapper_pipe[1]);

        	for (int i = 0; i < num; i++) {
            		int status;
            		waitpid(splitter_id[i], &status, 0);
            		if (WIFEXITED(status) && WEXITSTATUS(status)) {
                		print_nonzero_exit_status("./splitter", WEXITSTATUS(status));
            		}
        	}
		
		for (int i = 0; i < num; i++) {
            		int mapper_s;
            		waitpid(mapper_id[i], &mapper_s, 0);
            		if (WIFEXITED(mapper_s) && WEXITSTATUS(mapper_s)) {
                	print_nonzero_exit_status(argv[3], WEXITSTATUS(mapper_s));
            		}
        	}

		int reducer_s;
        	waitpid(reducer_id, &reducer_s, 0);
        	if (WIFEXITED(reducer_s) && WEXITSTATUS(reducer_s)) {
            		print_nonzero_exit_status(argv[4], WEXITSTATUS(reducer_s));
        		}
   	}
	

    // Print nonzero subprocess exit codes.
	print_num_lines(argv[2]);

	close(input_start);
	close(output_end);
    // Count the number of lines in the output file.
    return 0;
}
