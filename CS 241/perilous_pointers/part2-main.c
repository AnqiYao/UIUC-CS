/**
* Pointers Gone Wild Lab
* CS 241 - Spring 2018
*/

#include "part2-functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * (Edit this function to print out the "Illinois" lines in
 * part2-functions.c in order.)
 */
int main() {
//case 1-2
	int *temp;
	int temp1 = 132;
	int count = 8942;
	temp = &temp1;
	first_step(81);
	second_step(temp);
//case 3
	int *temp3_1 = &count;
	int **temp3 = &temp3_1;		
	double_step(temp3);
//case 4	
	char temp4_1[12];
	for(int i = 0; i < 12; i++){
		temp4_1[i] = 0;
	}
		temp4_1[5] = 15;
	char *temp4 = &temp4_1[0];
//	printf("%p\n",temp4);
//	printf("%d\n",(*(int *)(temp4+5)));
//	printf("%p\n",&temp4_1[0]);
//	printf("%p\n",&temp4_1[5]);
//	printf("%d\n",temp4_1[5]);
	strange_step(temp4);
//case 5
	char temp5_1[4];
	temp5_1 [3] = 0;
	void *temp5 = &temp5_1;
	empty_step(temp5);
//case 6
	char temp6_1[4];
	temp6_1 [3] = 'u';
	void *temp6 = &temp6_1[0];
	char *temp6_2 = &temp6_1[0];
	two_step(temp6,temp6_2);
//case 7
	char temp7_1[5];
	char* temp7 = &temp7_1[0];
	char* temp7_2 = &temp7_1[2];
	char* temp7_3 = &temp7_1[4];
	three_step(temp7,temp7_2,temp7_3);
//case 8
	char temp8_1[4];
	temp8_1[1] = 0;
	temp8_1[2] = 8;
	temp8_1[3] = 16;
	char* temp8 = &temp8_1[0];
	step_step_step(temp8,temp8,temp8);		
//case 9
	char temp9_1 = 1;
	int a = 1;
	char* temp9 = &temp9_1;
	it_may_be_odd(temp9,a);
//case 10
	char temp10[80]= "ok,CS241,CS241,";
	tok_step(temp10);
//case 11
	char temp11_1[4];	
	temp11_1[0] = 1;
	void* temp11 = &temp11_1[0];
	temp11_1[1] = 2;
	temp11_1[2] = 0;
	temp11_1[3] = 0;
	the_end(temp11,temp11);	
    return 0;
}
