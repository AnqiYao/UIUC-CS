/**
* Deadlocked Diners Lab
* CS 241 - Spring 2018
*/

#include "company.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *work_interns(void *p) {
	Company* company = (Company *) p;
	pthread_mutex_t *left_intern, *right_intern;
	while(running){
		int count = Company_get_billable_days(company);	
		if(count > 88) continue;
		left_intern = Company_get_left_intern(company);
		int k = pthread_mutex_trylock(left_intern);
		if(k != 0)	continue;
		right_intern = Company_get_right_intern(company);
		int j = pthread_mutex_trylock(right_intern);
		if(j!=0){
			pthread_mutex_unlock(left_intern);
			continue;
		}
		Company_hire_interns(company);
		pthread_mutex_unlock(right_intern);
       		pthread_mutex_unlock(left_intern);
		Company_have_board_meeting(company);
	}
    return NULL;
}
