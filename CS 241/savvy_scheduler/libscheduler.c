/**
* Savvy_scheduler Lab
* CS 241 - Spring 2018
*/

#include "libpriqueue/libpriqueue.h"
#include "libscheduler.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _job_info {
    	int id;
    	int priority;
	unsigned arrival_time;
	double remaining_time;
	double running_time;
	double last_time;
	double start_time;
    /* Add whatever other bookkeeping you need into this struct. */
} job_info;

priqueue_t pqueue;
scheme_t pqueue_scheme;
comparer_t comparision_func;
double total_job;
double total_waiting_time;
double total_turnaround_time;
double total_response_time;

void scheduler_start_up(scheme_t s) {
    switch (s) {
    case FCFS:
        comparision_func = comparer_fcfs;
        break;
    case PRI:
        comparision_func = comparer_pri;
        break;
    case PPRI:
        comparision_func = comparer_ppri;
        break;
    case PSRTF:
        comparision_func = comparer_psrtf;
        break;
    case RR:
        comparision_func = comparer_rr;
        break;
    case SJF:
        comparision_func = comparer_sjf;
        break;
    default:
        printf("Did not recognize scheme\n");
        exit(1);
    }
    priqueue_init(&pqueue, comparision_func);
    pqueue_scheme = s;
    // Put any set up code you may need here
}

static int break_tie(const void *a, const void *b) {
    return comparer_fcfs(a, b);
}

int comparer_fcfs(const void *a, const void *b) {
      job_info* new_a = (job_info*)(((job*)a)->metadata);
      job_info* new_b = (job_info*)(((job*)b)->metadata);
    	if (new_a->arrival_time < new_b->arrival_time)	return -1;
	    else if(new_a->arrival_time > new_b->arrival_time) return 1;
      return 0;
}

int comparer_ppri(const void *a, const void *b) {
    // Complete as is
    return comparer_pri(a, b);
}

int comparer_pri(const void *a, const void *b) {
      job_info* new_a = (job_info*)(((job*)a)->metadata);
      job_info* new_b = (job_info*)(((job*)b)->metadata);
    	if (new_a->priority <new_b->priority)	return -1;
	    else if (new_a->priority == new_b->priority)	return break_tie(a,b);
	    else return 1;
}

int comparer_psrtf(const void *a, const void *b) {
      job_info* new_a = (job_info*)(((job*)a)->metadata);
      job_info* new_b = (job_info*)(((job*)b)->metadata);
    	if (new_a->remaining_time < new_b->remaining_time ) return -1;
    	else if (new_a->remaining_time > new_b->remaining_time ) return 1;
	    return break_tie(a,b);
}

int comparer_rr(const void *a, const void *b) {
      job_info* new_a = (job_info*)(((job*)a)->metadata);
      job_info* new_b = (job_info*)(((job*)b)->metadata);
      if(new_a->last_time == new_b->last_time) return break_tie(a, b);
      if(new_a->last_time == -1) return -1;
      if(new_b->last_time == -1) return 1;
      if(new_a->last_time < new_b->last_time) return -1;
      return 1;
}

int comparer_sjf(const void *a, const void *b) {
      job_info* new_a = (job_info*)(((job*)a)->metadata);
      job_info* new_b = (job_info*)(((job*)b)->metadata);
    	if (new_a->running_time > new_b->running_time) return 1;
    	if (new_a->running_time < new_b->running_time) return -1;
	return break_tie(a,b);
}

// Do not allocate stack space or initialize ctx. These will be overwritten by
// gtgo
void scheduler_new_job(job *newjob, int job_number, double time,
                       scheduler_info *sched_data) {
    // TODO complete me!
  newjob->metadata = malloc(sizeof(job_info));
	job_info* new_job = (job_info*)newjob->metadata;
	new_job -> id = job_number;
  new_job -> priority = sched_data-> priority;
	new_job -> running_time = sched_data-> running_time;
	new_job -> arrival_time = time;
	new_job -> remaining_time = (int)(sched_data-> running_time);
	new_job -> start_time = -1;
	new_job -> last_time = -1;

	priqueue_offer(&pqueue, newjob);
}

job *scheduler_quantum_expired(job *job_evicted, double time) {
    // TODO complete me!
    if(job_evicted == NULL){
      job* cur = priqueue_poll(&pqueue);
      if(cur == NULL) return NULL;
      job_info* cur_info = cur->metadata;
      cur_info->start_time = time;
      cur_info->last_time = time;
      return cur;
    }
    if((comparision_func == comparer_fcfs) || (comparision_func == comparer_pri) || (comparision_func == comparer_sjf)){
      return job_evicted;
    }
    job_info* ev_info = job_evicted->metadata;
    ev_info->remaining_time -= time - ev_info->last_time;
    priqueue_offer(&pqueue, job_evicted);
    job* cur = priqueue_poll(&pqueue);
    job_info* cur_info = cur->metadata;
    if(cur_info->start_time == -1) cur_info->start_time = time;
    cur_info->last_time = time;
    return cur;
}

void scheduler_job_finished(job *job_done, double time) {
    // TODO complete me!
    total_job++;
    job_info* job_done_info = job_done->metadata;
    total_waiting_time += time - job_done_info->arrival_time - job_done_info->running_time;
    total_turnaround_time += time - job_done_info->arrival_time;
    total_response_time += job_done_info->start_time - job_done_info->arrival_time;
    free(job_done_info);
}

static void print_stats() {
    fprintf(stderr, "turnaround     %f\n", scheduler_average_turnaround_time());
    fprintf(stderr, "total_waiting  %f\n", scheduler_average_waiting_time());
    fprintf(stderr, "total_response %f\n", scheduler_average_response_time());
}

double scheduler_average_waiting_time() {
    // TODO complete me!
    return total_waiting_time / total_job;
}

double scheduler_average_turnaround_time() {
    // TODO complete me!
    return total_turnaround_time / total_job;
}

double scheduler_average_response_time() {
    // TODO complete me!
    return total_response_time / total_job;
}

void scheduler_show_queue() {
    // Implement this if you need it!
}

void scheduler_clean_up() {
    priqueue_destroy(&pqueue);
    print_stats();
}
