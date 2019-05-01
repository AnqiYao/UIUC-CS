/**
* Critical Concurrency Lab
* CS 241 - Spring 2018
*/

#include "queue.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * This queue is implemented with a linked list of queue_nodes.
 */
typedef struct queue_node {
    void *data;
    struct queue_node *next;
} queue_node;

struct queue {
    /* queue_node pointers to the head and tail of the queue */
    queue_node *head, *tail;

    /* The number of elements in the queue */
    ssize_t size;

    /**
     * The maximum number of elements the queue can hold.
     * max_size is non-positive if the queue does not have a max size.
     */
    ssize_t max_size;

    /* Mutex and Condition Variable for thread-safety */
    pthread_cond_t cv;
    pthread_mutex_t m;
};

queue *queue_create(ssize_t max_size) {
    /* Your code here */
	
    queue* new = malloc(sizeof(queue));
    if(new == NULL){
      return NULL;
    }
    new->head = NULL;
    new->tail = NULL;
    new->size = 0;
    new->max_size = max_size;
    pthread_mutex_init(&(new->m),NULL);
    pthread_cond_init(&(new->cv),NULL);
    return new;

}

void queue_destroy(queue *this) {
    /* Your code here */
	
    pthread_mutex_lock(&(this->m));
    queue_node* temp = this->head;
    while(this->head){
    temp = this->head;
    if(this->head->next == NULL){
      this->head = NULL;
    }
    else{
      this->head = this->head->next;
    }
    temp->data = NULL;
    temp->next = NULL;
    free(temp);
    }
    pthread_mutex_unlock(&(this->m));
    pthread_mutex_destroy(&(this->m));
    pthread_cond_destroy(&(this->cv));
    this->size = 0;
    this->max_size = 0;
    this->head = NULL;
    this->tail = NULL;
    free(this);

}

void queue_push(queue *this, void *data) {
    /* Your code here */
	
    queue_node* new = malloc(sizeof(queue_node));
    new->data = data;
    new->next = NULL;
    pthread_mutex_lock(&(this->m));
    if(this->max_size>0){
      while(this->size == this->max_size){
        pthread_cond_wait(&(this->cv),&(this->m));
      }
    }
    if(this->tail!=NULL){
      this->tail->next = new;
      this->tail = new;
    }
    if(this->head == NULL){
      this->head = new;
      this->tail = new;
    }
    this->size+=1;
    pthread_cond_signal(&(this->cv));
    pthread_mutex_unlock(&(this->m));
}

void *queue_pull(queue *this) {
    /* Your code here */
	
    queue_node* new;
    void* dat;
    pthread_mutex_lock(&(this->m));
    while(this->head == NULL){
      pthread_cond_wait(&(this->cv),&(this->m));
    }
    new = this->head;
    if(this->head->next == NULL){
      this->head = NULL;
      this->tail = NULL;
    }
    else{
      this->head = this->head->next;
    }
    new->next = NULL;
    if(this->head == NULL){
      this->tail = NULL;
    }
    this->size-=1;
    pthread_cond_signal(&(this->cv));
    pthread_mutex_unlock(&(this->m));
    dat = new->data;
    free(new);
    return dat;

    return NULL;
}
