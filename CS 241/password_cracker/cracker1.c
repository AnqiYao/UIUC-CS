/**
* Password Cracker Lab
* CS 241 - Spring 2018
*/

#include "cracker1.h"
#include "format.h"
#include "utils.h"
#include "queue.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <crypt.h>

typedef struct mypthread{
	pthread_t id;
	int num;
	int success;
	int fail;
}mypthread;

static queue* list;

static size_t total_recover = 0;

static size_t total_fail = 0;

void* readFromFile(void* ptr){	
	char* file_buffer = NULL;
	FILE* file_t = (FILE*)ptr;
	size_t num;
	ssize_t read = 0;
	while((read = getline(&file_buffer, &num,file_t))!= -1){
		char* temp = strdup(file_buffer);
	       	queue_push(list, temp);
        }
	free(file_buffer);
	for(size_t k = 0; k < 10; k++)	queue_push(list,"xinruiy2");
	return NULL;
}

char** getinfo(char* line){
	char** temp = malloc(128);
	char * tokens;
	int i = 0;
	tokens = strtok(line, " ");
	while(tokens != NULL){
		temp[i] = tokens;
		i++;
		tokens = strtok(NULL, " ");
	}
	return temp;	
}

void* mycrypt(void* ptr){
	size_t* id = (size_t*) ptr;
	char* line = "start";
	line = queue_pull(list);
	while(strcmp(line,"xinruiy2") != 0){
		char** info = getinfo(line);
		v1_print_thread_start(*id, info[0]);
		double time1 = getThreadCPUTime();
		int num = 0;
		int count = 0;
		int flag = 0;
		int num_hashed = 0;
		const char* hash = 0;
//		printf("info[2]: %s\n", info[2]);
		while(info[2][count]){
//			printf("info:%c\n", info[2][count]);
			if(info[2][num]!='.')	num++;
			count++;
		}
		count--;
		info[2][count] = '\0';
		for(int i = num; i < count; i++){
			info[2][i] = 'a';
		}
		char copy[count];
		strcpy(copy, info[2]);			
		for(int i = num; i < count; i++){
                        copy[i] = 'z';
                }
		incrementString(copy);
		struct crypt_data cdata;
		cdata.initialized = 0;	
		hash = crypt_r(info[2], "xx", &cdata);
		num_hashed++;
//		printf("%s\n",hash);
		while(strcmp(hash,info[1])!=0 && strcmp(info[2],copy)!=0){
			incrementString(info[2]);
			hash = crypt_r(info[2], "xx", &cdata);
//			printf("%s\n",info[2]);
			num_hashed ++;
		}
		if(strcmp(info[2],copy)==0){
			flag = 1;
			total_fail ++;
		}
		else	total_recover ++;
		double time2 = getThreadCPUTime();
		v1_print_thread_result(*id, info[0], info[2], num_hashed, (time2-time1), flag);
		free(line);
		line = queue_pull(list);
		free(info);
	}
	return NULL;
}

int start(size_t thread_count) {
    // TODO your code here, make sure to use thread_count!
    // Remember to ONLY crack passwords in other threads
//To push into the queue
	list = queue_create(-1);
//	pthread_t first;
//	pthread_create(&first,NULL,readFromFile, stdin);
//let threads to do their job
	readFromFile(stdin);
	mypthread group[thread_count-1];
	for(size_t i = 0; i < thread_count; i++){
		group[i].num = i+1;
		pthread_create(&group[i].id,NULL,mycrypt, &group[i].num);
	}
//join all threads
//	void* ret;
//	pthread_join(first,&ret);
	for(size_t i = 0; i < thread_count; i++){
		void *result;
		pthread_join(group[i].id,&result);	
	}
	v1_print_summary(total_recover, total_fail);
	queue_destroy(list);	
    return 0; // DO NOT change the return code since AG uses it to check if your
              // program exited normally
}
