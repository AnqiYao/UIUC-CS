/**
* Pointers Gone Wild Lab
* CS 241 - Spring 2018
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "callbacks.h"
#include "part3-functions.h"
#include "vector.h"

vector *vector_map(vector *input, mapper map) {
    // TODO implement this
    vector * output = string_vector_create();
    VECTOR_FOR_EACH(input, elem, {
      char * in = map(elem);
      vector_push_back(output, in);
      free(in);});
    return output;
}

void *vector_reduce(vector *input, reducer reduce, void *acc) {
    // TODO implement this
    VECTOR_FOR_EACH(input, elem, {
      acc = reduce(elem, acc);});
    return acc;
}

void *length_reducer(char *input, void *output) {
    // TODO implement this
    if(output == NULL){
      output = malloc(sizeof(int));
      *((int*)output) = strlen(input);
    }else{
      int temp = *((int*)output) + strlen(input);
      *((int*)output) = temp;
    }
    //printf("%d\n", count);
    //printf("%d\n", *((int*)output));
    return output;
}

void *concat_reducer(char *input, void *output) {
    // TODO implement this
    if(output == NULL){
      output = strdup(input);
      return output;
    }else{
      output = realloc(output, sizeof(char)*(strlen(input)+strlen(output)+1));
      output = strcat(output, input);
    }
    return output;
}
