/**
* Password Cracker Lab
* CS 241 - Spring 2018
*/

#include "cracker2.h"
#include "format.h"
#include "utils.h"
#include "stdio.h"
#include "queue.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <crypt.h>
	
typedef struct mypthread{
	pthread_t id;
	int num;
	size_t num_hashed;
}mypthread;

char* file_buffer;

static char* final_pass;

static char** info;

size_t num_h[50];

static int flag;

static int unknow;

static size_t num_thread;

pthread_mutex_t lock;

pthread_barrier_t mybarrier;
	
pthread_barrier_t mybarrier1;

char** getinfo(char* piece){
	char** temp = malloc(128);
	char * tokens;
	int i = 0;
	tokens = strtok(piece, " ");
	while(tokens != NULL){
		temp[i] = tokens;
		i++;
		tokens = strtok(NULL, " ");
	}
	return temp;	
}

void* mycrypt(void* ptr){
	pthread_barrier_wait(&mybarrier);
	mypthread group = *((mypthread*)(ptr));
	while(strcmp(file_buffer,"xinruiy2")!=0){
		long start_index = 0;
		long count = 0;
		size_t temp = 0;
		getSubrange(unknow, num_thread, group.num, &start_index, &count);
		char* start_char = strdup(info[2]); //need to free
		setStringPosition(start_char+getPrefixLength(start_char), start_index);
		v2_print_thread_start(group.num, info[0],start_index, start_char);
		struct crypt_data cdata;
		cdata.initialized = 0;	
		const char *hash  = crypt_r(start_char, "xx", &cdata);
		temp ++;
		while(strcmp(hash,info[1])!=0 && (temp < (size_t)count) && flag==0){
			incrementString(start_char);
			hash = crypt_r(start_char, "xx", &cdata);
			temp ++;
		}
		if(temp >= (size_t)count){
			v2_print_thread_result(group.num,temp,2);
			num_h[group.num-1] = temp;
			pthread_barrier_wait(&mybarrier1);
		}else if(strcmp(hash,info[1])==0){
			v2_print_thread_result(group.num,temp,0);
			final_pass = strdup(start_char);
			pthread_mutex_lock(&lock);
			flag = 1;
			pthread_mutex_unlock(&lock);
			num_h[group.num-1] = temp;
			pthread_barrier_wait(&mybarrier1);
		}else{
			v2_print_thread_result(group.num,temp,1);
			num_h[group.num-1] = temp;
			pthread_barrier_wait(&mybarrier1);
		}
		free(start_char);
		pthread_barrier_wait(&mybarrier);
	}
	return NULL;
}



int start(size_t thread_count) {
    // TODO your code here, make sure to use thread_count!
    // Remember to ONLY crack passwords in other threads
	mypthread group[thread_count];
	num_thread = thread_count;
	pthread_mutex_init(&lock, NULL);
	file_buffer = NULL;
	for(int i = 0; i < 50; i++){
		num_h[i] = 0;
	}
	size_t num;
	ssize_t read = 0;
	pthread_barrier_init(&mybarrier, NULL, thread_count + 1);
	pthread_barrier_init(&mybarrier1, NULL, thread_count + 1);
	for(size_t i = 0; i < thread_count; i++){
               		group[i].num = i+1;
			group[i].num_hashed = 0;
                        pthread_create(&group[i].id,NULL,mycrypt, &group[i]);
        }
	while((read = getline(&file_buffer, &num,stdin))!= -1){
		info = getinfo(file_buffer);
		v2_print_start_user(info[0]);
		pthread_mutex_lock(&lock);
		flag = 0;
		pthread_mutex_unlock(&lock);
		final_pass = NULL;
		int count = 0;
		int num_start = 0;
		for(size_t i = 0; i < thread_count; i++){
                        num_h[i] = 0;
                }
		while(info[2][count]){
			if(info[2][num_start]!='.')	num_start++;
			count++;
		}
		count--;
		info[2][count] = '\0';
		unknow = count - num_start;
		double time1 = getTime();
                double cputime1 = getCPUTime();
		pthread_barrier_wait(&mybarrier);	
		pthread_barrier_wait(&mybarrier1);
		double time2 = getTime();
                double cputime2 = getCPUTime();
		size_t total_hashcount = 0;
		for(size_t i = 0; i < thread_count; i++){
			total_hashcount+= num_h[i];
		}
		pthread_mutex_lock(&lock);
		v2_print_summary(info[0], final_pass, total_hashcount, (time2 - time1), (cputime2-cputime1),!flag);     
		free(info);
		if(flag){
			free(final_pass);
		}
		pthread_mutex_unlock(&lock);
	}
	free(file_buffer);
	file_buffer = "xinruiy2";
	pthread_barrier_wait(&mybarrier);
	for(size_t i = 0; i < thread_count; i ++){
		void* result;
		pthread_join(group[i].id, &result);	
	}
	pthread_barrier_destroy(&mybarrier);
	pthread_barrier_destroy(&mybarrier1);
	pthread_mutex_destroy(&lock);
    	return 0; 
}
