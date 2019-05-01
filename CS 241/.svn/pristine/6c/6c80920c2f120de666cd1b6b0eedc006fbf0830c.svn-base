/**
* Pied Piper Lab
* CS 241 - Spring 2018
*/

#include "pied_piper.h"
#include "utils.h"
#include <fcntl.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define TRIES 3

static char messages[50][1000];
static int err_status[50];

int pied_piper(int input_fd, int output_fd, char **executables) {
	// Your code goes here...
	if(input_fd < 0) input_fd = 0;
	if(output_fd < 0) output_fd = 1;
	
	int count = 0;
	char** temp = executables;
	while(*temp != NULL){
		count++;
		temp++;
	}
	//printf("count:%d\n",count);
	pid_t p[50];
	int times = 0;
	int flag = 0;

RESTART:
	for(int i = 0; i < count; i++){
		memset(messages[i], 0, 1000);
	}
	reset_file(input_fd);
	reset_file(output_fd);
	for(int i = 0; i < count; i++){
		char* command = executables[i];
		int fd[2];
		int fd_err[2];
		pipe(fd);
		pipe(fd_err);
		p[i] = fork();
		if(p[i] == 0){	//child
			if(i == 0){
				dup2(input_fd, 0);
			}	
			close(fd[0]);
			if(i == count-1){
				dup2(output_fd, 1);
			}else{
				dup2(fd[1], 1);
			}
			close(fd_err[0]);
			dup2(fd_err[1], 2);
			exec_command(command);
			fprintf(stderr, "EXEC FAIL!!\n");
 			exit(-1);
		}else{	//parent
			int status;
			waitpid(p[i], &status, 0);
			err_status[i] = status;
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd_err[1]);
			read(fd_err[0], messages[i], 1000);
		}
	}
	//int times = 0;
	//int flag = 0;
	for(int i = 0; i < count; i++){
		if(WEXITSTATUS(err_status[i]) != 0){
			times++;
			if(times == 3){
				flag = 1;
				break;
			}else{
				goto RESTART;
			}	
		}
	}
	if(flag){
		failure_information info[50];
		for(int i = 0; i < count; i++){
			info[i].command = executables[i];
			info[i].status = err_status[i];
			info[i].error_message = messages[i];
		}
		print_failure_report(info, count);
		exit(3);
	}
	return EXIT_SUCCESS;
}	
