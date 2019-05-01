/**
* Malloc Lab
* CS 241 - Spring 2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BLOCK_SIZE sizeof(struct block)

struct block{
        size_t size;
        struct block *next;
        struct block *prev;
};

static char* list[60000000];

static struct block* head = (void*)NULL;

static struct block* last = (void*)NULL;
/*
void split(struct block* curr, size_t size){
	void* temp = (curr + 1);
	struct block* this_meta = (temp + size);
	this_meta->size = (curr->size - size - BLOCK_SIZE);
	this_meta->prev = curr->prev;
	this_meta->next = curr->next;
	curr->next = NULL;
	curr->prev = NULL;
	if(curr == head && curr == last){
		head = this_meta;
		last = this_meta;
		return;
	}else if(curr == head){
		head = this_meta;
		this_meta->next->prev = this_meta;	
		return;
	}else if(curr == last){
		this_meta->prev->next = this_meta;
		last = this_meta;
		return;
	}else{
		this_meta->next->prev = this_meta;
		this_meta->prev->next = this_meta;
	}
}
*/	
void merge(struct block* first, struct block* second, struct block* third){
	if(first == NULL){
		head = second;
		void* temp = second + 1;
		temp += second->size;
		if(temp == third){
			second->size += third->size + BLOCK_SIZE;
			second->next = third->next;
			if(second -> next == NULL){
				last = second;
				return;
			}
			second->next->prev = second;
			third->prev = NULL;
			third->next = NULL;
		}	
	}else if(third == NULL){
		void* temp = first + 1;
                temp += first->size;
                if(temp == second){
                        first->size += second->size + BLOCK_SIZE;
                        first->next = NULL;
			last = first;
                        second->prev = NULL;
                        second->next = NULL;
                }
	}else{
		void* temp = first + 1;
                temp += first->size;
                if(temp == second){
                        first->size += second->size + BLOCK_SIZE;
                        first->next = second->next;
			first->next->prev = first;
                        second->prev = NULL;
                        second->next = NULL;
			void* new_temp = first + 1;
			new_temp += first->size;
			if(new_temp == third){
				first->size += third->size + BLOCK_SIZE;
				first->next = third->next;
				third->next = NULL;
				third->prev = NULL;
				if(first->next == NULL){
					last = first;
					return;
				}
				first->next->prev = first;
			}
                }else{
			void* temp_1 = second + 1;
			temp_1 += second->size;
			if(temp_1 == third){
				second->size += third->size + BLOCK_SIZE;
				second->next = third->next;
				third->next = NULL;
				third->prev = NULL;
				if(second->next == NULL){
					last = second;
					return;
				}
				second->next->prev = second;
			}	
		}
		
	}	
}	

void insert(struct block* curr){
	if(head == NULL){
		head = curr;
		last = curr;
		curr->next = NULL;
		curr->prev = NULL;	
	}
	else{
		struct block* temp = head;
		while(temp != NULL){
			if(temp > curr)	
				break;
			temp = temp->next;
		}
		if(temp == head){
			head->prev = curr;
			curr->next = head;
			head = curr;
		}else if(temp == NULL){
			last -> next = curr;
			curr -> prev = last;
			curr -> next = NULL;
			last = curr;	 
		}
		else{
			curr->prev = temp->prev;
			curr->next = temp;
			if(curr->prev != NULL)		
				curr->prev->next = curr;
			temp->prev = curr;
		}
		merge(curr->prev,curr,curr->next);
	}	
}
/*
struct block* find_free_space(size_t size){
	struct block* curr = head;
	while(curr != NULL){
		if(curr->size >= size){
			if((curr->size >  size +  BLOCK_SIZE)){
				void* temp = (curr + 1);
				struct block* this_meta = (temp + size);
				this_meta->size = (curr->size - size - BLOCK_SIZE);
				this_meta->prev = curr->prev;
				this_meta->next = curr->next;
				curr->next = NULL;
				curr->prev = NULL;
				if(curr == head && curr == last){
					head = this_meta;
					last = this_meta;
					return curr;
				}else if(curr == head){
					head = this_meta;
					this_meta->next->prev = this_meta;	
					return curr;
				}else if(curr == last){
					this_meta->prev->next = this_meta;
					last = this_meta;
					return curr;
				}else{
					this_meta->next->prev = this_meta;
					this_meta->prev->next = this_meta;
					}
				}
			return curr;	
		}	
		curr = curr->next;
	}	
	return NULL;
}
*/

struct block* find_free_space(size_t size){
	struct block* curr = head;
  if(head == NULL){
    return NULL;
  }
	while((curr != NULL) && (curr->size < size)){
      if(curr->next == NULL){
        return NULL;
    }
		curr = curr->next;
	}
  if((curr->prev == NULL)&&(curr->next == NULL)){
		curr->next = NULL;
		curr->prev = NULL;
		head = NULL;
		last = NULL;
    return curr;
	}else if(curr->prev == NULL){
		head = curr->next;
		curr->next = NULL;
		curr->next = NULL;
    head->prev = NULL;
    return curr;
	}else if(curr->next == NULL){
		last = curr->prev;
    last->next = NULL;
		curr->prev = NULL;
		curr->prev = NULL;
    return curr;
	}else{
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		curr->next = NULL;
		curr->prev = NULL;
    return curr;
	}
}

struct block* request_space(struct block* curr,size_t size){
	struct block* result;
	result = sbrk(0);
	void *request_next = sbrk(size + BLOCK_SIZE);	 
	if(request_next == (void*)-1)	return NULL;
	result->prev = NULL;
	result->size = size;
	result->next = NULL;
	return result;	
}






/**
 * Allocate memory block
 *
 * Allocates a block of size bytes of memory, returning a pointer to the
 * beginning of the block.  The content of the newly allocated block of
 * memory is not initialized, remaining with indeterminate values.
 *
 * @param size
 *    Size of the memory block, in bytes.
 *
 * @return
 *    On success, a pointer to the memory block allocated by the function.
 *
 *    The type of this pointer is always void*, which can be cast to the
 *    desired type of data pointer in order to be dereferenceable.
 *
 *    If the function failed to allocate the requested block of memory,
 *    a null pointer is returned.
 *
 * @see h ttp://www.cplusplus.com/reference/clibrary/cstdlib/malloc/
 */

void *malloc(size_t size) {/*
    // implement malloc!
    // say we have never malloc anything on the heap before     
	if(size == 0)	return NULL;  
 	if(head == NULL){
		struct block* temp;
	        temp = request_space(NULL, size);
        	if(temp == NULL) return NULL;
		return (temp+1);
	}else{ 
		struct block* curr = head;
	        while(curr != NULL){
                	if(curr->size >= size){
        	                if((curr->size >  size +  BLOCK_SIZE)){
                        	        void* temp = (curr + 1);
                                	struct block* this_meta = (struct block*)(temp + size);
                                	this_meta->size = (curr->size - size - BLOCK_SIZE);
                                	this_meta->prev = curr->prev;
                             	   	this_meta->next = curr->next;
                             	   	curr->next = NULL;
                             	   	curr->prev = NULL;
                               		if(curr == head && curr == last){
                                        	head = this_meta;
                                        	last = this_meta;
                                        	
                              		}else if(curr == head){
                                        	head = this_meta;
                                        	this_meta->next->prev = this_meta;
                                        	
                               		}else if(curr == last){
                                        	this_meta->prev->next = this_meta;
                                        	last = this_meta;
                                        }else{
                                        	this_meta->next->prev = this_meta;
                                        	this_meta->prev->next = this_meta;
                                        }
                                }
                        return (curr+1);
                }
                curr = curr->next;
        }
        	if(curr == NULL){
			curr = request_space(NULL, size);
	             	if(curr == NULL) return NULL;
		}
		return (curr+1);
	}
}
*/

      if(size==0) return NULL;
        struct block* temp;
        if(head == NULL){
                temp = request_space(NULL,size);
                if(temp == NULL) return NULL;
                return (temp+1);
        }
        temp = find_free_space(size);
  	    if(temp == NULL){
  			       temp = request_space(NULL,size);
  	           if(temp == NULL)        return NULL;
               return (temp+1);
  	    }
        else{
          if(temp->size -size > BLOCK_SIZE){
            void* address = (temp+1);
            struct block *curr = (address + size);
            curr->size = (temp->size-BLOCK_SIZE-size);
            curr->prev = NULL;
            curr->next = NULL;
            insert(curr);
            temp->size = size;
            return (temp+1);
          }else{
            return (temp+1);
          }
        }
	return (temp+1);
}

/**
 * Allocate space for array in memory
 *
 * Allocates a block of memory for an array of num elements, each of them size
 * bytes long, and initializes all its bits to zero. The effective result is
 * the allocation of an zero-initialized memory block of (num * size) bytes.
 *
 * @param num
 *    Number of elements to be allocated.
 * @param size
 *    Size of elements.
 *
 * @return
 *    A pointer to the memory block allocated by the function.
 *
 *    The type of this pointer is always void*, which can be cast to the
 *    desired type of data pointer in order to be dereferenceable.
 *
 *    If the function failed to allocate the requested block of memory, a
 *    NULL pointer is returned.
 *
 * @see http://www.cplusplus.com/reference/clibrary/cstdlib/calloc/
 */


void *calloc(size_t num, size_t size) {
    // implement calloc!
    void* result = malloc(num*size);
    memset(result, 0, num*size);
    return result; 
}

/**
 * Deallocate space in memory
 *
 * A block of memory previously allocated using a call to malloc(),
 * calloc() or realloc() is deallocated, making it available again for
 * further allocations.
 *
 * Notice that this function leaves the value of ptr unchanged, hence
 * it still points to the same (now invalid) location, and not to the
 * null pointer.
 *
 * @param ptr
 *    Pointer to a memory block previously allocated with malloc(),
 *    calloc() or realloc() to be deallocated.  If a null pointer is
 *    passed as argument, no action occurs.
 */
void free(void *ptr) {
	// implement free!
	if(ptr == NULL)	return;
	struct block* temp = (struct block*)(ptr - BLOCK_SIZE);
	insert(temp);
}

/**
 * Reallocate memory block
 *
 * The size of the memory block pointed to by the ptr parameter is changed
 * to the size bytes, expanding or reducing the amount of memory available
 * in the block.
 *
 * The function may move the memory block to a new location, in which case
 * the new location is returned. The content of the memory block is preserved
 * up to the lesser of the new and old sizes, even if the block is moved. If
 * the new size is larger, the value of the newly allocated portion is
 * indeterminate.
 *
 * In case that ptr is NULL, the function behaves exactly as malloc, assigning
 * a new block of size bytes and returning a pointer to the beginning of it.
 *
 * In case that the size is 0, the memory previously allocated in ptr is
 * deallocated as if a call to free was made, and a NULL pointer is returned.
 *
 * @param ptr
 *    Pointer to a memory block previously allocated with malloc(), calloc()
 *    or realloc() to be reallocated.
 *
 *    If this is NULL, a new block is allocated and a pointer to it is
 *    returned by the function.
 *
 * @param size
 *    New size for the memory block, in bytes.
 *
 *    If it is 0 and ptr points to an existing block of memory, the memory
 *    block pointed by ptr is deallocated and a NULL pointer is returned.
 *
 * @return
 *    A pointer to the reallocated memory block, which may be either the
 *    same as the ptr argument or a new location.
 *
 *    The type of this pointer is void*, which can be cast to the desired
 *    type of data pointer in order to be dereferenceable.
 *
 *    If the function failed to allocate the requested block of memory,
 *    a NULL pointer is returned, and the memory block pointed to by
 *    argument ptr is left unchanged.
 *
 * @see http://www.cplusplus.com/reference/clibrary/cstdlib/realloc/
 */
void *realloc(void *ptr, size_t size) {
    // implement realloc!
    	if(size == 0 && ptr == NULL)	return NULL;
    	if(size == 0){
		free(ptr);
		return NULL;
	}
	if(ptr == NULL)		return malloc(size);
	struct block* thismeta = (struct block*)(ptr-BLOCK_SIZE);
	if(thismeta->size >= size){
		return ptr;
	}
	else{
		size_t news = thismeta->size;
		memcpy(list,ptr,thismeta->size);
		free(ptr);	
		void* result = malloc(size);
		if(result == NULL)	return NULL;
		memcpy(result, list, news); 
		return result;
	}
}

