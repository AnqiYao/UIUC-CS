/**
* Shell Lab
* CS 241 - Spring 2018
*/

#include <string.h>
#include <stdlib.h>
#include "format.h"
#include "shell.h"
#include "vector.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <ctype.h>

typedef struct process {
    char *command;
    char *status;
    pid_t pid;
} process;

void deal_with_charactors(char*  buffer, vector* history_string, int signal_1, int signal_2);
int exec_command(char* buffer, vector* history_string, int if_print_prompt, int if_print_cmd);

static pid_t child_id[50];
static process processes[50];
static int flagk;
static int flagh;
static int flagf;
static int fd;
static int op_used;
static int child_idx;
static char* command_argv;

void write_h_to_f(vector* history_string){
    size_t size = vector_size(history_string);
    for(size_t i = 0; i < size; i ++){
        dprintf(fd,"%s\n",(char*)vector_get(history_string,i));
    }
}

int buffer_operator(char buffers[2][100], char* file_buffer, vector* history_string) {
    char* temp;
    char* temp_1 = NULL;
    if((temp = strstr(file_buffer,"&&"))){
        vector_push_back(history_string, file_buffer); //push the command line into history_string
        *temp = '\0';
        temp_1 = temp - 1;
        while (*temp_1 == ' ') temp_1--;
        char t =  temp_1[1];
        temp_1[1] = '\0';
        strcpy(buffers[0],file_buffer);
        temp_1[1] = t;
        *temp = '&';
        temp = temp + 2;
        while(*temp == ' ') temp++;
        strcpy(buffers[1],temp);
        return 1;
    } else if ((temp = strstr(file_buffer,"||"))) {
        vector_push_back(history_string,file_buffer);
        *temp = '\0';
        temp_1 = temp - 1;
        while (*temp_1 == ' ') temp_1--;
        char t = temp_1[1];
        temp_1[1] = '\0';
        strcpy(buffers[0],file_buffer);
        *temp = '|';
        temp_1[1] = t;
        temp = temp + 2;
        while(*temp == ' ') temp++;
        strcpy(buffers[1],temp);
        return 2;
    } else if ((temp = strstr(file_buffer,";")) && temp[-1] != '\\') {
        vector_push_back(history_string,file_buffer);
        *temp = '\0';
        temp_1 = temp - 1;
        while (*temp_1 == ' ') temp_1--;
        char t = temp_1[1];
        temp_1[1] = '\0';
        strcpy(buffers[0],file_buffer);
        *temp = ';';
        temp_1[1] = t;
        temp = temp + 2;
        while(*temp == ' ') temp++;
        strcpy(buffers[1],temp);
        return 3;
    }
    return 0;
}

void deal_with_charactors(char*  buffer, vector* history_string, int signal_1, int signal_2){
       char buffers_two_line[2][100];
       int check = buffer_operator(buffers_two_line, buffer, history_string);
       if (check) op_used = 1;
       if (check == 0) {
           exec_command(buffer,history_string,signal_1,signal_2);
       } else if (check == 3) {
           exec_command(buffers_two_line[0],history_string,signal_1,signal_2);
           exec_command(buffers_two_line[1],history_string,signal_1,signal_2);
       } else if (check == 1) {
           if (exec_command(buffers_two_line[0],history_string,signal_1,signal_2) == 0)
               exec_command(buffers_two_line[1],history_string,signal_1,signal_2);
       } else if (check == 2) {
           if (exec_command(buffers_two_line[0],history_string,signal_1,signal_2) == 0) {
           } else {
               exec_command(buffers_two_line[1],history_string,signal_1,signal_2);
           }
       }
       op_used = 0;
}


//run command
int exec_command(char* buffer, vector* history_string, int if_print_prompt, int if_print_cmd){
    if (flagk == 1) return 0;
    int temp = 0;
    if (if_print_prompt) {
      char command_list[5000];
      memset(command_list,0,5000);
      pid_t pid_now = getpid();
      getcwd(command_list,sizeof(command_list));
      print_prompt(command_list,pid_now);
    }
    if (if_print_cmd) print_command(buffer);
    size_t size = vector_size(history_string);
    char* ptr;
    if ((ptr = strstr(buffer,"cd "))) { //cd section
      char path[100];
      memset(path,0,100);
      strcpy(path,ptr+3);

      if((temp = chdir(path)) <0) print_no_directory(path);
      if(!op_used)  vector_push_back(history_string, buffer);
      if(temp < 0)  return -1;
    }else if(strcmp(buffer,"ps") == 0){ //ps section
      print_process_info("Running",getpid(),command_argv);
      for(int i = 0; i < child_idx; i++){
          char new_cmd[100];
          memset(new_cmd, 0, 100);
          strcpy(new_cmd,processes[i].command);
			    int status, status_2;
    		  int child_status = waitpid(processes[i].pid,&status,WNOHANG);
    		  char* status_print;
    		  waitpid(processes[i].pid,&status_2,WUNTRACED | WNOHANG);
    		  if ((strcmp(processes[i].status,"Stopped") == 0) ) {
    				  status_print = "Stopped";
    				  print_process_info(status_print,processes[i].pid,new_cmd);
    		  } else if (child_status == 0) {
    			    status_print = "Running";
        			print_process_info(status_print,processes[i].pid,new_cmd);
    		  } else if (child_status == processes[i].pid || child_status == -1) {
              continue;
          }
      }
      return 0;
    }else if((ptr = strstr(buffer,"kill")) || (ptr = strstr(buffer,"cont")) || (ptr = strstr(buffer,"stop"))){
      if (!op_used) vector_push_back(history_string,buffer);
      int pid_to_k;
      char* temp_ptr = ptr;
      temp_ptr += 3;
      while (*temp_ptr) {
        if (*temp_ptr >= '0' && *temp_ptr <= '9') break;
        temp_ptr++;
      }
      if (!*temp_ptr) {
        print_invalid_command(buffer);
        return -1;
      }
      sscanf(temp_ptr,"%d",&pid_to_k);
      int status;
      int ret = waitpid((pid_t)pid_to_k,&status,WNOHANG);
      if (ret == -1 || ret == pid_to_k) {
          print_no_process_found(pid_to_k);
          return -1;
      }
          if (strstr(buffer,"kill")) {
              kill(pid_to_k,SIGTERM);
              for (int k = 0; k < child_idx; k++) {
                  if (processes[k].pid == pid_to_k) {
                      print_killed_process(pid_to_k,processes[k].command);
                      return 0;
                  }
              }
          } else if (strstr(buffer,"cont")) {
              kill(pid_to_k,SIGCONT);
              for (int k = 0; k < child_idx; k++) {
                  if (processes[k].pid == pid_to_k) {
                      if (strcmp(processes[k].status,"Stopped") == 0)
                          processes[k].status = "Running";
                      return 0;
                  }
              }
          }else if (strstr(buffer,"stop")) {
              kill(pid_to_k,SIGTSTP);
              for (int k = 0; k < child_idx; k++) {
                  if (processes[k].pid == pid_to_k) {
                      processes[k].status = "Stopped";
                      print_stopped_process(pid_to_k,processes[k].command);
                      return 0;
                  }
              }
          }
    }else if (strcmp(buffer,"!history") == 0){
      size_t temp_history_i = 0;
      while (temp_history_i < size) {
        print_history_line(temp_history_i,(const char *)vector_get(history_string, temp_history_i));
        temp_history_i++;
      }
    }else if(*buffer == '!'){
      char temp_for_p[100];
      memset(temp_for_p,0,100);
    	strcpy(temp_for_p,buffer+1);
    	unsigned long temp_for_p_len = strlen(temp_for_p);
    	if (*temp_for_p == 0) {
        deal_with_charactors((char *)vector_get(history_string,size-1), history_string , 0, 1);
    	} else {
    		int i;
    		for (i = size - 1; i >= 0; i--) {
    			char* commands = (char *)vector_get(history_string,i);
    			if (strlen(commands) < temp_for_p_len) continue;
    			char temp_char_1 = commands[temp_for_p_len];
    			commands[temp_for_p_len] = '\0';
    			if (strcmp(commands,temp_for_p) == 0) {
    				commands[temp_for_p_len] = temp_char_1;
            deal_with_charactors(commands, history_string , 0, 1);
    				break;
    			} else {
    				commands[temp_for_p_len] = temp_char_1;
    			}
    		}
    		if (i < 0) print_no_history_match();
    	}
    }else if ((ptr = strstr(buffer,"#"))) {
    	int temp_num;
    	sscanf(ptr+1,"%d",&temp_num);
    	char commands[100];
      memset(commands,0,100);
    	if (temp_num >= (int)size) {
    		print_invalid_index();
    	} else {
    		strcpy(commands,(const char *)vector_get(history_string,temp_num));
        deal_with_charactors(commands, history_string , 0, 1);
    	}
    }else if (strcmp(buffer,"exit") == 0) {
    	if (flagh) write_h_to_f(history_string);
    	vector_destroy(history_string);
    	for (int i = 0; i < child_idx; i++) {
    		int temp_pid = processes[i].pid;
    		char* status = processes[i].status;
    		if (*status == 'R' || *status == 'S') {
    			kill(temp_pid,SIGTERM);
    		}
    		free(processes[i].command);
    	}
    	exit(0);
    }else{    //other
      if (!op_used) vector_push_back(history_string,buffer);
      char* background = NULL;
      int length_buf = strlen(buffer);
      for (int i = length_buf - 1 ; i >= 0; i--) {
        if (buffer[i] == '&') {
          background = buffer + i;
          if (buffer[i-1] == '\\') background = NULL;
          else *background = '\0';
          break;
        }
      }

      pid_t pid_prior = fork();
     	int status;
     	if (pid_prior < 0) print_fork_failed();
     	if (pid_prior > 0) {
  			  if (setpgid(pid_prior, pid_prior) == -1) {
      			print_setpgid_failed();
      			exit(1);
    			}

     			if (! background) {
     				waitpid(pid_prior,&status,0);
          	temp = WEXITSTATUS(status);

          	    if (temp != 0) return -1;
          	    else return 0;
              } else {
              	process newp;
              	newp.command = strdup(buffer);
              	newp.status = "Running";
              	newp.pid = pid_prior;
              	processes[child_idx] = newp;
              	child_idx++;
              	waitpid(pid_prior,&status,WNOHANG);
              	return 0;
              }
     		} else {

  			char* loc_escap;
  			char temp_escap[1000]; memset(temp_escap,0,1000);

  			while ((loc_escap = strchr(buffer,'\\'))) {
  				*loc_escap = '\0';
  				strcat(temp_escap,buffer);

  				buffer = loc_escap + 1;
  			}
  			if (*temp_escap) {
  				strcat(temp_escap,buffer);
  				buffer = temp_escap;

  			}
        char* new_args[1000];
        char* temp_buf = strtok(buffer," ");
        int i = 0;
        while (temp_buf != NULL) {
            new_args[i++] = temp_buf;
            temp_buf = strtok(NULL," ");
        }
              new_args[i] = NULL;

     			print_command_executed(getpid());
     			int check_zt = execvp(*new_args,new_args);
     			if (check_zt < 0) print_exec_failed(buffer);

     			flagk = 1;
          exit(9);
     		}
    }
    return 0;
}

//deal with -f command
void file_command(int flagh, char* filename, vector* history_string){
    FILE* input_file = fopen(filename,"r");
    if (!input_file) {
		    print_script_file_error();
		    return;
	  }
//read the input_file
    char* file_buffer = NULL;
    size_t num = 0;
    ssize_t read = 0;
    while((read = getline(&file_buffer, &num, input_file))!= -1){
        if (file_buffer[read - 1] == '\n') {
            file_buffer[read - 1] = '\0';
        }
        char buffered_used[2][100];
        int check = buffer_operator(buffered_used, file_buffer, history_string);
        if (check) op_used = 1;
        if (check == 0) {
            exec_command(file_buffer,history_string,1,1);
        }else if (check == 3) {
            exec_command(buffered_used[0],history_string,1,1);
            exec_command(buffered_used[1],history_string,1,1);
        } else if (check == 1) {
            if (exec_command(buffered_used[0],history_string,1,1) == 0)
                exec_command(buffered_used[1],history_string,1,1);
        } else if (check == 2) {
            if (exec_command(buffered_used[0],history_string,1,1) == 0) {
                continue;
            } else {
                exec_command(buffered_used[1],history_string,1,1);
            }
        }
        op_used = 0;

    	  free(file_buffer);
    	  file_buffer = NULL;
    }
    if (file_buffer) free(file_buffer);
    if (flagh) {
    	write_h_to_f(history_string);
    }
    vector_destroy(history_string);
    for (int i = 0; i < child_idx; i++) {
    	int pid = processes[i].pid;
    	char* status = processes[i].status;
    	if (*status == 'R' || *status == 'S') {
    		kill(pid,SIGTERM);
    	}
    	free(processes[i].command);
    }
    fclose(input_file);
	  exit(0);
}

void INTSINGAL_handler(){
    int i = 0;
    while(i<10){
          if(child_id[i]>0) kill(child_id[i], SIGKILL);
          i++;
    }
}

int shell(int argc, char *argv[]) {
// TODO: This is the entry point for your shell.
//exception for both -f and -h
  if(argc>5 || argc==2 || argc==4){
	   print_usage();
		 fflush(stdout);
		 return 0;
  }
  child_idx = 0;
  for (int i = 0; i < 10; i++) child_id[i] = 0;
//create universal
	vector* history_string = string_vector_create(); // need to free!
//process process_gen;
	//pid_t mainid = getpid();
  command_argv = argv[0];
//deal with ctrl + c
	signal(SIGINT, INTSINGAL_handler);
//flags for -h and -f
  flagf = 0;
  flagh = 0;
  flagk = 0;
//create file for f and h
  char command_file[100];
  memset(command_file,0,100);
  char hisfile[100];
  memset(hisfile,0,100);
//start from -h or -f
  while(*argv){
    if((strcmp(*argv,"-h") == 0)){
        flagh = 1;
        strcpy(hisfile, argv[1]); //argv is now -f
        fd = open(hisfile,O_CREAT | O_TRUNC | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
    }else if(strcmp(*argv,"-f") == 0){
        flagf = 1;
        strcpy(command_file,argv[1]);
    }
    //next command
    argv++;
  }
  if(flagf)  file_command(flagh,command_file,history_string);
//read from stdin
  while(1){
    char commands_From_stdin[5000];
    memset(commands_From_stdin,0,5000);
    pid_t now_pid = getpid();
    getcwd(commands_From_stdin,sizeof(commands_From_stdin));
    print_prompt(commands_From_stdin,now_pid);

    char buffer[500];
    memset(buffer,0,500);
    if (feof(stdin)) {
          if (flagh) write_h_to_f(history_string);
          vector_destroy(history_string);
          for (int i = 0; i < child_idx; i++) {
    			     int pid = processes[i].pid;
    			     char* status = processes[i].status;
    			     if (*status == 'R' || *status == 'S') {
    			          kill(pid,SIGTERM);
    			}
    			free(processes[i].command);
    		}
    		//fprintf(stderr,"exit~~~\n");
            return 0;
    }
    	 fgets(buffer,100,stdin);
        buffer[strlen(buffer)-1] = 0;
        if (buffer[0] == EOF) exit(0);
        char buffers_two_line[2][100];
        int check = buffer_operator(buffers_two_line, buffer, history_string);
        if (check)	op_used = 1;

    	if (check == 0) {
            exec_command(buffer,history_string,0,0);
        } else if (check == 3) {
            exec_command(buffers_two_line[0],history_string,0,0);
            exec_command(buffers_two_line[1],history_string,0,0);
        } else if (check == 1) {
            if (exec_command(buffers_two_line[0],history_string,0,0) == 0)
                exec_command(buffers_two_line[1],history_string,0,0);
        } else if (check == 2) {
            if (exec_command(buffers_two_line[0],history_string,0,0) == 0) {
                continue;
            } else {
                exec_command(buffers_two_line[1],history_string,0,0);
            }
        }
        op_used = 0;
  }
//finishing doing all commands and free all need to free

//end of reading whole file free all need to free
	return 0;
}//end of int shell
