/**
* Utilities Unleashed Lab
* CS 241 - Spring 2018
*/
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include "format.h"

extern char** environ;

char** get_each(char* input){
	char** temp = malloc(1024);
	while(*input != '='){
		input++;
	}
	input++;
	char * tokens;
	int i = 0;
	tokens = strtok(input, ",");
	while(tokens != NULL){
		temp[i] = tokens;
		i++;
		tokens = strtok(NULL, ",");
	}
	return temp;
}

char* get_env_variable(char* key){
	char* result = malloc(strlen(key));
	int i = 0;
	while(key[i]!='='){
		result[i] = key[i];
		i++;
	}
	result[i] = '\0';
	return result;
}

int main(int argc, char *argv[]) {
	if(argc<3)	print_env_usage();
	int number = 1;
	int position = 1;
	int end = 1;
	int i = 1;
	int status;
	char* command = malloc(1024);
	char*** values = malloc(1024);
	char** key = malloc(1024);
	char** keyword = malloc(1024);
	if(strcmp(argv[1],"-n") == 0){
		number = atoi(argv[2]);
		position = 3;
	}
	while(argv[i]){
		if(strcmp(argv[i],"--") == 0){
			end = i;
			if(argv[i+1])	command = argv[i+1];
			else print_env_usage();
		}
		i++;
		
	}
	if(end == 1)	print_env_usage();
	
//	printf("command is: %s\n", command);
	
	if(end-position == 0){
	int child = fork();
	if(child == -1) print_fork_failed();
	else if(child > 0){
		pid_t pid = waitpid(child, &status, 0);
                if(pid != -1 && WIFEXITED(status)){
                	int exit_status = WEXITSTATUS(status);
                        	if(exit_status != 0){
                                	exit(1);
                        	}
		}
	}else{
		execvp(command,&command);
		print_exec_failed();
		}
	}else{
//	char** key = malloc(1024);
	for(int i = 0; i < end-position;i++){
		key[i] = argv[position+i];
		}	
//	char *** values = malloc(1024);
	int temp1 = 0;
//	char ** keyword = malloc(1024);
	while(key[temp1]){
		keyword[temp1] = get_env_variable(key[temp1]);
		values[temp1] = get_each(key[temp1]);
//		printf("%s\n",values[0][temp1]);
		temp1++;
		//printf("%s\n",keyword[temp1]);	
		}		
	}
	
	for(int i = 0; i < end-position; i ++){
		int count = 0;
		while(values[i][count]){
			count++;
		}
		if(count != number && count != 1) print_env_usage();	
	}	
	
	for(int i = 0; i < number; i++){
		for(int k = 0; k < end-position;k++){
			if(values[k][i] == NULL)
				values[k][i] = values[k][0];
			}
	}
			
	for(int i = 0; i < number; i++){
		int child = fork();
		if(child == -1) print_fork_failed();
		else if (child > 0){
			pid_t pid = waitpid(child, &status, 0);
			if(pid!=-1 && WIFEXITED(status)){
				int exit_status = WEXITSTATUS(status);
                                if(exit_status != 0){
                                       	exit(1);
                          	}	
			}
		}else{
			for(int k = 0; k < (int)(end - position); k++){
			//	printf("end: %d, position: %d\n", end, position);
				if(values[k][i][0] == '%'){
					values[k][i] ++;
		 			values[k][i] = getenv(values[k][i]);
					if(values[k][i] == NULL) print_environment_change_failed();
				}	
				if(setenv(keyword[k], values[k][i], 1) == -1)  print_environment_change_failed();	
                        }	
			execvp(command, &command);
                        print_exec_failed();
                }
	}
			


    return 0;
}
