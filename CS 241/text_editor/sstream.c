/**
* Text Editor Lab
* CS 241 - Spring 2018
*/

#include "sstream.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define MIN(a,b) (((a)<(b))?(a):(b))
#include <limits.h>
struct sstream{
	char *str;
	size_t position;
	size_t size;
};

sstream *sstream_create(bytestring bytes) {
	sstream* result = malloc(sizeof(sstream));
	int i  = 0;
	if(bytes.str == NULL) {
		result->str = NULL;
		result->position = 0;
		result->size = 0;
		return result;
	}
	else if(bytes.size < 0) {
		result-> str = malloc(strlen(bytes.str)+1);
		while(bytes.str[i]!='\0'){
			result->str[i] = bytes.str[i];
			i++;
		}
		result->str[i] = '\0';
		result->position = 0;
		result->size = strlen(result->str);
		return result;
	}
	else{
	  	result-> str = malloc(bytes.size);
		i = 0;
		for(; i < bytes.size; i++){
			result->str[i] = bytes.str[i];
		}
		result->position = 0;
		result->size = bytes.size;
		return result;
	}
}

void sstream_destroy(sstream *this) {
	assert(this);
	if(this->str!=NULL){
		free(this->str);
		this->str = NULL;
	}
	free(this);
	this = NULL;
}

void sstream_str(sstream *this, bytestring bytes) {
		assert(this);
		int i = 0;
		if(bytes.str == NULL) {
			this->str[0] = '\0';
			this->str = realloc(this->str,0);
			this->position = 0;
			this->size = 0;
			return;
		}
		else if(bytes.size < 0) {
			if(this->size < strlen(bytes.str)+1){
		  		this->str = realloc(this -> str,strlen(bytes.str)+1);
				while(bytes.str[i]!='\0'){
					this->str[i] = bytes.str[i];
					i++;
				}
				this->str[i] = '\0';
			}
			else {  
				i = 0;
				while(bytes.str[i]!='\0'){
					this->str[i] = bytes.str[i];
					i++;
				}
				this->str[i] = '\0';
			}
			this->position = 0;
			this->size = strlen(bytes.str);
			return;
		}
		else{
			if(this->size < (size_t)bytes.size+1){
				this->str = realloc(this -> str,bytes.size+1);
				i = 0;
				for(; i < bytes.size; i++){
					this->str[i] = bytes.str[i];
				}
				this->str[bytes.size] = '\0';
			}
			else{
				i = 0;
				for(; i < bytes.size; i++){
					this->str[i] = bytes.str[i];
				}
				this->str[bytes.size] = '\0';
			}
			this->position = 0;
			this->size = bytes.size;
			return;
		}

}

bool sstream_eos(sstream *this) {
	if(this == NULL)	return true;	
	if(this->position == (this->size))	return true;
	return false;
}

char sstream_peek(sstream *this, ssize_t offset) {
	assert((this->position + offset)>=0);
	size_t place = this->position + offset;
	assert(place < this->size);
	return (this->str[place]);
}

char sstream_getch(sstream *this) {
	assert((this->position)>=0);
	assert(!sstream_eos(this));
	char temp =  (this->str[this->position]);
	this->position ++;
	return temp;

}

size_t sstream_size(sstream *this) {
	assert(this);
    return this->size;
}

size_t sstream_tell(sstream *this) {
	assert(this);
    return this->position;
}

int sstream_seek(sstream *this, ssize_t offset, int whence) {
		ssize_t newp = this->position;
		if(whence == SEEK_SET){
			newp = offset;
		}
		else if (whence == SEEK_CUR){
			newp = this->position + offset;
		}
		else {
			newp = this->size + offset;
		}
		if(newp >= (ssize_t)this->size || newp < 0)
			return -1;
		else {
			this->position = newp;
			return 0;
		}
}

size_t sstream_remain(sstream *this) {
	return this->size - this->position;
}

size_t sstream_read(sstream *this, bytestring *out, ssize_t count) {
    	assert(this);
	 ssize_t temp;
    if(count >= 0) temp = MIN(labs(count), (ssize_t)sstream_remain(this));
    else temp = MIN(labs(count), (ssize_t)sstream_tell(this));
    
    if(out->str == NULL){
	out->str = malloc(temp + 1);
	out->size = temp;
    }else{
	if(out->size < temp){
	    free(out->str);
	    out->str = malloc(temp + 1);
	    out->size = temp;
	}
    }

    if(count >= 0){
	count = temp;
	ssize_t temp3 = this->position;
	this->position += count;
	int i = 0;
	while(i < count){
		out->str[i++] = this->str[temp3 ++];
	
	}
    }else{
	count = -temp;
	char * temp1 = &this->str[this->position + count];
	char * temp2 = out->str;
        while(temp1 != &this->str[this->position]){
	    *temp2++ = *temp1++;
	}
    }    
    out->str[temp] = '\0';
    return temp;
}

void sstream_append(sstream *this, bytestring bytes) {
	if(bytes.size >= 0){
	this->str = realloc(this->str, this->size + bytes.size + 1);
	int temp = strlen(this->str);
	int num = 0;
	while(num < bytes.size){
	    this->str[temp] = bytes.str[num];
	    num++;
	    temp++;
	}
	this->size += bytes.size;
	this->str[this->size] = '\0';
	
    }
    else{
	this->str = realloc(this->str, strlen(bytes.str) + 1);
	strcat(this->str, bytes.str);
	this->size += strlen(bytes.str);
	this->str[this->size] = '\0';
    }
}

ssize_t sstream_subseq(sstream *this, bytestring bytes) {
	assert(this);
	sstream * mystr = sstream_create(bytes);
	char * sub = strstr(this->str, mystr->str);
	ssize_t result = -1;
	size_t temp = this->position;
	for(; (sstream_size(this) - temp) > 0  ; temp++){
		sub = strstr(&this->str[temp], mystr->str);
		if(sub == &this->str[temp]){
			result = temp - this->position;
			sstream_destroy(mystr);
			return result;
		}
	}
	sstream_destroy(mystr);
	return -1;
}

size_t sstream_erase(sstream *this, ssize_t number) {
	if(number == 0) return 0;
    	else if(number > 0){
	if(sstream_remain(this) > (size_t)number){
		size_t k = 0;
		while(k < (sstream_remain(this)-number)){
			this->str[this->position+k] = this->str[k+this->position+(size_t)number];
	    	k++;
	    }
	    this->size -= (size_t)number;
	    this->str[this->size] = '\0';
	    return (size_t)number;
	    
	}
        else{
	    this->str[this->position] = '\0';
	    size_t era = sstream_remain(this);
	    this->size -= era;
	    return era;
	}
    }else{
	if((ssize_t)this->position + number <= 0){
	    size_t i= 0; 
	    while(i < sstream_remain(this)){
		this->str[i] = this->str[i+this->position];
		i++;
	    }
	    size_t ret = this->position;
	    this->position = 0;
	    this->size -= ret;
	    this->str[this->size] = '\0';
	    return ret;
	}else{
	    size_t j = 0;
	    while(j<sstream_remain(this)){
		this->str[this->position + number+j] = this->str[this->position+j];
		j++;
	    } 
	    this->size += number;
	    this->position += number;
	    this->str[this->size] = '\0';
	    return (size_t)labs(number);
	}
    }
	return 0;
}

void sstream_write(sstream *this, bytestring bytes) {
	sstream* a = sstream_create(bytes);
	ssize_t capacity = (ssize_t) sstream_size(this) - this->position - sstream_size(a);
	 if(capacity<0){
		this->size = (this->position+sstream_size(a));
		this->str = realloc(this->str,this->size+1);
	}
	size_t temp = 0;
	while(temp<sstream_size(a)){
		this->str[temp+this->position] = a->str[temp];
		temp++;
	}
	this->str[this->size] = '\0';
	sstream_destroy(a);
}

void sstream_insert(sstream *this, bytestring bytes) {
	sstream * myss = sstream_create(bytes);
	char * result = malloc(sstream_size(this) + sstream_size(myss) + 1);
	memcpy(result, this->str, this->position);
	memcpy(&result[this->position], myss->str, sstream_size(myss));
	memcpy(&result[this->position + sstream_size(myss)], &this->str[this->position], sstream_size(this) - this->position + 1);
	free(this->str);
	this->size = sstream_size(this) + sstream_size(myss);
	this->str = result;
	this->str[this->size] = '\0';
	sstream_destroy(myss);
}

int sstream_parse_long(sstream *this, long *out) {
	char* temp;
	int num = 0;
	char* curr = this->str + this->position;
	long result = strtol(curr,&temp,10);
	if(result == 0) return -1;
	else if(result > LONG_MAX && result > LONG_MIN){
		num = 0;
		long a = LONG_MAX;
		while(a!=0){
			a/=10;
			num++;	
		}	
		if(result>=0){
			this->position += num;
			char* temp1 = malloc(num+1);
			strncpy(temp1,temp,num);
			temp1[num]='\0';
			result = strtol(temp1,&temp,10);
			*out = result;
			free(temp1);
			return num;
		}
		else{
			this->position += (num + 1);
			char* temp2 = malloc(num+2);
			strncpy(temp2,temp,num+1); 
			temp2[num+1] = '\0';
			result = strtol(temp2,&temp,10);
			*out = result;
			free(temp2);
			return num+1;
		}
	}
	else{
		num = 0;
		*out = result;
		while(result!=0){
			result/=10;
			num++;
		}
		if(result>=0)	return num;
		else	return num+1;
	}
	return -1;	

}
