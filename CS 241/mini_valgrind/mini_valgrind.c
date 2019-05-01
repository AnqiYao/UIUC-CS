/*
* Mini Valgrind Lab
* CS 241 - Spring 2018
*/

#include "mini_valgrind.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

meta_data *head = NULL;
size_t total_memory_requested = 0;
size_t total_memory_freed = 0;
size_t invalid_addresses = 0;

void *mini_malloc(size_t request_size, const char *filename,
                  void *instruction) {
    // your code here
	if(request_size == 0)	return NULL;
	total_memory_requested += request_size;
	meta_data *temp = malloc(request_size + sizeof(meta_data));
	if(!temp)	return NULL;
	temp->filename = filename;
	temp->request_size = request_size;
	temp->instruction = instruction;
	if(head!=NULL)
		temp->next = head;
	head = temp;
	return head+1;
}

void *mini_calloc(size_t num_elements, size_t element_size,
                  const char *filename, void *instruction) {
    // your code here
	assert(num_elements != 0 && element_size != 0);
	total_memory_requested += (num_elements * element_size);
	meta_data *temp = malloc(sizeof(meta_data)+num_elements*element_size);

	if(!temp)	return NULL;
	memset(temp+1, 0, num_elements*element_size);
	temp->filename = filename;
	temp->request_size = (num_elements * element_size);
	temp->instruction = instruction;
	if(head!=NULL)
	temp->next = head;
	head = temp;
	return head+1;
}

void *mini_realloc(void *payload, size_t request_size, const char *filename,
                   void *instruction) {
    // your code here
	assert(payload != NULL && request_size != 0);
	if(payload == NULL)	return mini_malloc(request_size, filename, instruction);
	if(request_size == 0){
		mini_free(payload);
		return NULL;
	}
	meta_data *temp;
	temp = head;
	while(temp+1 != payload && temp != NULL)	temp = temp->next;
	if(temp == NULL){
		invalid_addresses ++;
		return NULL;
	}
	temp = realloc(temp, sizeof(meta_data)+request_size);
	if(!temp)	return NULL;
	
	if(temp->request_size >= request_size)	total_memory_freed += ( temp->request_size - request_size);
	else	total_memory_requested += (request_size - temp->request_size);
	temp->request_size = request_size;
	temp->filename = filename;
	temp->instruction = instruction;
	return temp+1;
}

void mini_free(void *payload) {
    // your code here
	if(payload == NULL)	return;
			
	else{
		meta_data *temp = NULL;
		meta_data *temp1 = NULL;
		temp = head;
		while(temp+1 != payload && temp!=NULL){
			temp1 = temp;			
			temp = temp->next;
		}
		if(temp == NULL){
			invalid_addresses ++;
			return;
		}
		total_memory_freed += temp->request_size;
		if(temp1 == NULL){
			head = temp->next;
			free(temp);
			temp = NULL;
			return;
		}
		temp1->next = temp->next;
		free(temp);
		temp = NULL;
		return;	
	}
}
