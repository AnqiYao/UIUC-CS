/**
* Text Editor Lab
* CS 241 - Spring 2018
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "document.h"
#include "vector.h"

struct document {
    vector *vector;
};

document *document_create() {
    document *this = (document *)malloc(sizeof(document));
    assert(this);
    this->vector = vector_create(string_copy_constructor, string_destructor,
                                 string_default_constructor);
    return this;
}

void document_write_to_file(document *this, const char *path_to_file) {
    assert(this);
    assert(path_to_file);
    // see the comment in the header file for a description of how to do this!
    // TODO: your code here!
	int fildes = open(path_to_file, O_CREAT|O_TRUNC|O_RDWR, S_IRUSR|S_IWUSR);
	for(size_t i = 0; i < vector_size(this->vector); i++){
		dprintf(fildes,"%s\n", (char*) vector_get(this->vector,i));
	}
	close(fildes);
}

document *document_create_from_file(const char *path_to_file) {
    assert(path_to_file);
    // this function will read a file which is created by document_write_to_file
    // TODO: your code here!
	document* result = document_create();
	FILE* file = fopen(path_to_file,"r+");
	if(file==NULL)	return result;
	size_t initial = 1;
	char *buffer = NULL;
	size_t bufsize = 0;;
	while(1){
		if(getline(&buffer,&bufsize,file) == -1) break;
		buffer[strlen(buffer)-1] = '\0';
		vector_push_back(result->vector,buffer);
		initial++;
	}
	fclose(file);
	free(buffer);	
	return result;
}

void document_destroy(document *this) {
    assert(this);
    vector_destroy(this->vector);
    free(this);
}

size_t document_size(document *this) {
    assert(this);
    return vector_size(this->vector);
}

void document_set_line(document *this, size_t line_number, const char *str) {
    assert(this);
    assert(str);
    size_t index = line_number - 1;
    vector_set(this->vector, index, (void *)str);
}

const char *document_get_line(document *this, size_t line_number) {
    assert(this);
    assert(line_number > 0);
    size_t index = line_number - 1;
    return (const char *)vector_get(this->vector, index);
}

void document_insert_line(document *this, size_t line_number, const char *str) {
    assert(this);
    assert(str);
    // TODO: your code here!
    // How are you going to handle the case when the user wants to
    // insert a line past the end of the document?
	// if (str == NULL)	return;
	// if (line_number > document_size(this)){
	// 	size_t num_btwn;
	// 	for(num_btwn = 1; num_btwn < (line_number - document_size(this)); num_btwn++){
	// 		const char * in = "";
	// 		document_set_line(this, document_size(this)+num_btwn, in);
	// 	}
	// 	document_set_line(this, line_number, str);
	// 	return;
	// }
	// const char* line = document_get_line(this, line_number);
	// document_set_line(this, line_number, str);
	// line_number++;
	// document_insert_line(this,line_number,line);
	//if(line_number>vector_capacity(this->vector))
	//vector_reserve(this->vector,line_number);
  	//vector_insert(this->vector, line_number-1, (void*)str);
	size_t index = line_number - 1;
	if(index >= vector_size(this->vector)){
		vector_resize(this->vector,index+1);
		vector_set(this->vector,index,(void*)str);
	}
	else
		vector_insert(this->vector,index,(void*)str);
}

void document_delete_line(document *this, size_t line_number) {
    assert(this);
    assert(line_number > 0);
    size_t index = line_number - 1;
    vector_erase(this->vector, index);
}