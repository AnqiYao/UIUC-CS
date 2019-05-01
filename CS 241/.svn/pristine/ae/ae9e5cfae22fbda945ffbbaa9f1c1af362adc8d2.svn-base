/*
* Extreme Edge Cases Lab
* CS 241 - Spring 2018
*/

#include "camelCaser.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

char **camel_caser(const char *input_str) {
        if (input_str == NULL){
            return NULL;
        }
	
	int nopunct = 0;
	int temp = 0;
        while(input_str[temp]){
                if(ispunct(input_str[temp])){
                        nopunct ++;		
                }	
                temp++;
        }
	

        char **result = malloc((nopunct+1)*sizeof(char*));


	if(nopunct == 0) {
		*result = NULL;
		return result;
	}

        for (int k = 0; k < nopunct+1; k++){
              result[k] = malloc(strlen(input_str)+1);
        }

        int row = 0;
        int col = 0;
        int id = 0;
        int i = 0;
	int choice = 0;         
		
	while(input_str[i] && row <nopunct){
		if(isalpha(input_str[i]) && id && choice){
                        id = 0;
                        result[row][col] = toupper(input_str[i]);
                        col++;
                        i++;
                }
                else if(!isspace(input_str[i])  && !ispunct(input_str[i])){
			choice = 1;
                        result[row][col] = tolower(input_str[i]);
                        col++;
                        i++;
                }
                else if(isspace(input_str[i])){
			if(choice == 1){
                             id = 1;
			}
                        i++;
                }
                else if(ispunct(input_str[i])){
                        result[row][col] = '\0';
                        i ++;
                        row++;
                        col = 0;
			choice = 0;
			id = 0;
                }          
         }
	free(result[row]);	
	result [row] = NULL;	
        return result;
}


void destroy(char **result) {
	if(result == NULL)
		return;
	if(*result == NULL){
		free(result);	
		result = NULL;
	}
	char** r = result;
	while(*r){
	    free(*r);
	    (*r) = NULL;
            r ++;
	}
	free(result);
	result = NULL;
    	return;
}

