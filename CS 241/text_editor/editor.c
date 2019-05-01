/**
* Text Editor Lab
* CS 241 - Spring 2018
*/

#include "document.h"
#include "editor.h"
#include "format.h"
#include "sstream.h"

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CSTRING(x) ((bytestring){(char *)x, -1})
#define DECLARE_BUFFER(name) bytestring name = {NULL, 0};
#define EMPTY_BYTES ((bytestring){NULL, 0})

char *get_filename(int argc, char *argv[]) {
	if(argc < 2){
		print_usage_error();
		return NULL;
	}
	return argv[1];
}

sstream *handle_create_stream() {
	sstream* temp = sstream_create(EMPTY_BYTES);
   	return temp;
}
document *handle_create_document(const char *path_to_file) {
	document* doc = document_create_from_file(path_to_file);
	return doc;
}

void handle_cleanup(editor *editor) {
	document_destroy(editor->document);
	sstream_destroy(editor->stream);
}

void handle_display_command(editor *editor, size_t start_line,
                            ssize_t max_lines, size_t start_col_index,
                            ssize_t max_cols) {
	if((ssize_t)document_size(editor->document)<=0 || editor->document == NULL){
		print_document_empty_error();
		return;
	}
	if(max_lines == -1){
		for(size_t i = start_line; i <= document_size(editor->document); i++){
			print_line(editor->document, i, start_col_index, max_cols);
		}
	}
	else{
		size_t temp;
		if((size_t)max_lines + start_line > document_size(editor->document))	temp = document_size(editor->document);
		else temp = max_lines + start_line - 1;
		for(size_t j = start_line; j <= temp; j++){
			print_line(editor->document, j, start_col_index, max_cols);
		}
	}
}

void handle_insert_command(editor *editor, location loc, const char *line) {
	if(line == NULL){
		return;
	}
	if(loc.line_no <= document_size(editor->document) && loc.line_no >= 1){

		int capacity = strlen(line) + strlen(document_get_line(editor->document, loc.line_no)) + 1;
      		char *old = (char*)document_get_line(editor->document, loc.line_no);
    		char *new = (char*)malloc(capacity);
		size_t length = strlen(line);
    		int i = 0;
		int temp = 0;
    		if(i < capacity - 1){
      			while(i < (int)loc.idx){
        			new[i] = *old;
                		i++;
                		old++;
            		}
      			while(i < (int)(loc.idx + length)){
                		new[i] = line[temp];
                		i++;
                		temp++;
            		}
			while(*old){
    				new[i] = *old;
            			i++;
            			old++;
			}
    		}
    		new[i] = '\0';
    		document_set_line(editor->document, loc.line_no, new);
    		free(new);
    		new = NULL;
  	}
  	else if(loc.line_no > document_size(editor->document) && loc.line_no >= 1){
    		for(int i = document_size(editor->document) + 1; i <= (int)loc.line_no -1; i++){
    			  document_insert_line(editor->document, i, "");
        }
    		document_insert_line(editor->document, loc.line_no, line);
  	}

}

char** help_for_append_write_command(const char* line, int count){

	if(line == NULL) return NULL;
	int temp = 0;	
	char** result = malloc(1024);
	if(count!=1){
		for(int i = 0; i < count; i++)
			result[i] = calloc(256,1);
	}
	int number = 0;
	int current = 0;
	temp = 0;
	while(line[temp]){
		if((line[temp] == '\\')&&(line[temp+1] == '\\')){	
		result[number][current] = '\\';
		current++;
		temp+=2;
		}
		else if((line[temp] == '\\')&&(line[temp+1] == 'n')){		
			result[number][current] = '\0';			
			number ++;
			current = 0;
			temp +=2;
		}
		else if((line[temp] == '\\') && (line[temp+1] != 'n') && (line[temp+1] != '\\')){
			temp ++;
			}
		else{
			result[number][current] = line[temp];
			current++;
			temp++;
		}
	}
		
	result[number][current] = '\0';
	
	return result;		
}

void handle_append_command(editor *editor, size_t line_no, const char *line) {
	assert(line);
	int temp = 0;	
	int count = 1;
	while(line[temp]){
		if((line[temp] == '\\')&&(line[temp+1] == '\\')){
			temp+=2;
		}
		else if((line[temp] == '\\')&&(line[temp+1] == 'n')){	
			temp +=2;
			count++;		
		}
		else{
		temp++;
		}
	}
	if(count == 1){
		if(line_no > document_size(editor->document)){
			temp = 0;
			char* new = malloc(strlen(line)+1);
			int temp1 = 0;
			while(line[temp]){
				if((line[temp] == '\\')&&(line[temp+1] == '\\')){
					new[temp1] = '\\';
					temp1++;
					temp+=2;	
				}
				else if((line[temp] == '\\'))	temp++;
				else{
					new[temp1] = line[temp];
					temp1++;
					temp++;
				}	
			}
			new[temp1] = '\0';
			document_insert_line(editor->document, line_no, new);
		}
		else {
			char* old = (char*) document_get_line(editor->document, line_no);
			old += strlen(old);
			temp = 0;
			while(line[temp]){
				if((line[temp] == '\\')&&(line[temp+1] == '\\')){
					*old = '\\';
					temp+=2;
					old ++;
				}
				else if((line[temp] == '\\'))	temp++;
				else {
					*old = line[temp];
					old++;
					temp++;
				}	
			}
			*old = '\0';
		}
	}
	else{
	char** help = help_for_append_write_command(line,count);	
	int number = 0;
	int current = 0;

	if(line_no > document_size(editor->document)){
		while(help[number]!=NULL){
			document_insert_line(editor->document, line_no, help[number]);
			number++;
			line_no++;
		}
	}
	else {
		char* old = (char*) document_get_line(editor->document, line_no);	
		old += strlen(old);
		if(help[number]!=NULL){
			while(help[number][current]!='\0'){
				*old = help[number][current];
				old++;
				current++;
			}
			number++;
			current = 0;
			*old = '\0';
		}
		line_no++;
		while(help[number]!=NULL){
			document_insert_line(editor->document, line_no, help[number]);
			number++;
			line_no++;
		}
	}
	}
}

void handle_write_command(editor *editor, size_t line_no, const char *line) {
	assert(line);
	int temp = 0;	
	int count = 1;
	while(line[temp]){
		if((line[temp] == '\\')&&(line[temp+1] == '\\')){
			temp+=2;
		}
		else if((line[temp] == '\\')&&(line[temp+1] == 'n')){	
			temp +=2;
			count++;		
		}
		else{
			temp++;
		}
	}
	if(count == 1){
			temp = 0;
			char* new = malloc(strlen(line)+1);
			int temp1 = 0;
			while(line[temp]){
				if((line[temp] == '\\')&&(line[temp+1] == '\\')){
					new[temp1] = '\\';
					temp1++;
					temp+=2;
				}	
				else if((line[temp] == '\\'))	temp++;
				else{
					new[temp1] = line[temp];
					temp1++;
					temp++;
				}	
			}
			new[temp1] = '\0';
		
		if(line_no > document_size(editor->document)){
			
			document_insert_line(editor->document, line_no, new);
		}
		else {
			document_delete_line(editor->document, line_no);
			document_insert_line(editor->document, line_no, new);
		}
	}
	else{
	char** help = help_for_append_write_command(line,count);	
	int number = 0;

	if(line_no > document_size(editor->document)){
		while(help[number]!=NULL){
			document_insert_line(editor->document, line_no, help[number]);
			number++;
			line_no++;
		}
	}
	else {
		document_delete_line(editor->document, line_no);	
		while(help[number]!=NULL){
			document_insert_line(editor->document, line_no, help[number]);
			number++;
			line_no++;
		}
	}
	}
}

void handle_delete_command(editor *editor, location loc, size_t num_chars) {
	char* line = (char*)document_get_line(editor->document, loc.line_no);
	if(strlen(line) - loc.idx <= num_chars){
		line[loc.idx] = '\0';
	}else{
		line += loc.idx;
		while(line[num_chars]){
			*line = line[num_chars];
			line++;
		}
		*line = '\0';
	}
}

void handle_delete_line(editor *editor, size_t line_no) {
	if((line_no <= document_size(editor->document)) && (line_no >= 1))
		document_delete_line(editor->document, line_no);
}

location handle_search_command(editor *editor, location loc,
                               const char *search_str) {
    	if(*search_str == '\0') return (location){0, 0};
	if(loc.line_no > document_size(editor->document)) return (location){0, 0};
	char * line = (char*) document_get_line(editor->document, loc.line_no);
	if(strlen(search_str) > (strlen(line)-loc.idx)) return (location){0, 0};
	line += loc.idx;
	int new_idx1 = loc.idx;
	int new_idx = 0;
	int found = 1;
	while(line[new_idx]){
		if(line[new_idx] == search_str[0]){
			for(size_t i = 1; i < strlen(search_str);i++){
				if(found!=1)
					break;
				else {
					if(line[new_idx+i] != search_str[i])
						found = 0;
				}
			}
			if (found == 1) return (location) {loc.line_no,loc.idx+new_idx};
		}
		found = 1;
		new_idx += 1;
	}
	return  handle_search_command(editor,(location){loc.line_no+1,new_idx1},search_str) ;
}

void handle_merge_line(editor *editor, size_t line_no) {
	char* old= (char*) document_get_line(editor->document, line_no);
	char* line = (char*) document_get_line(editor->document, line_no+1);
	char* temp = (char*) malloc(sizeof(char)* strlen(old) + strlen(line) + 1);
	strcpy(temp,old);
	strcat(temp,line);
	document_set_line(editor->document, line_no, temp);
	document_delete_line(editor->document, line_no+1);
	free(temp);
}

void handle_split_line(editor *editor, location loc) {
	char* old_ori = (char*)document_get_line(editor->document, loc.line_no);
	int capacity = strlen(old_ori) - loc.idx + 1;
	char* new = (char*)malloc(sizeof(char)* capacity);
	int i = 0;
	char* a = old_ori;
	a += loc.idx;
	while(i<capacity-1){
		new[i++] = *a;
		*a = '\0';
		a++;
	}
	new[i] = '\0';
	document_insert_line(editor->document,loc.line_no+1,new);
	free(new);
	new = NULL;
}

void handle_save_command(editor *editor) {
	if(editor->filename != NULL && editor->document == NULL)	editor->document = document_create_from_file(editor->filename);
	document_write_to_file(editor->document, editor->filename);
}