/**
* Teaching Threads Lab
* CS 241 - Spring 2018
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "reduce.h"
#include "reducers.h"

/* You might need a struct for each task ... */
struct T{
	pthread_t id;
//	int check;
//	int oldvalue;
	int sum;
	int* nlist;
	int size;
	reducer function;
	void* result;
};
/* You should create a start routine for your threads. */
void *start_routine(void* ptr){
//	if(((struct T *)ptr)->oldvalue!=-1)
	((struct T *)ptr)->sum += ((struct T *)ptr)->nlist[0];
//	if(((struct T *)ptr)->oldvalue!=-1){
//		if(((struct T *)ptr)->check == 1) ((struct T *)ptr)->sum += ((struct T *)ptr)->oldvalue;
//		else	((struct T *)ptr)->sum *= ((struct T *)ptr)->oldvalue;
//	}
//	printf("size is :%d\n",((struct T*) ptr)->size);
	for(int i = 1; i < ((struct T*)ptr)->size; i++){
//		printf("%d\n",((struct T *)ptr)->nlist[i]);
		((struct T*)ptr)->sum = ((struct T*)ptr)->function(((struct T *)ptr)->sum,((struct T *)ptr)->nlist[i]);
//	printf("sum is changing to:%d\n", ((struct T*)ptr)->sum);
	}
	return NULL;
}

//int check_func(reducer func){
//	if(func(2,3)==5)	return 1;
//	else	return 2;	
//}
int par_reduce(int *list, size_t list_len, reducer reduce_func, int base_case,
               size_t num_threads) {
    /* Your implementation goes here */
//	int checker = check_func(reduce_func);
//	int result = 0; 
	if(num_threads >= list_len)	num_threads = list_len;
	struct T *info = calloc(num_threads,sizeof(struct T));
	int k = (int) list_len/num_threads;
	int list_final[num_threads];
	list_final[0] = base_case;
	int flag = 0;
	if(k*num_threads < list_len)	flag = 1;
	int i = 0;
	while(i<(int)num_threads){
		if(flag && (i == (int)(num_threads-1))){
			info[i].nlist = list+i*k;
			info[i].size = k +(list_len-k*num_threads);
		}else{
		info[i].nlist = list+i*k;
		info[i].size = k;
		}
//		info[i].check = checker;
//		if(i!=0)	info[i].oldvalue = info[i-1].sum;
//		else		info[i].oldvalue = -1;
		info[i].function = reduce_func;
		pthread_create(&info[i].id,NULL,start_routine,&info[i]);
//		pthread_join(info[i].id,&info[i].result);
//		list_final[i+1] = info[i].sum;
//		printf("sum coming out is:%d\n",info[i].sum);
		i++;
	}
//	int result = base_case;
	for(int n = 0; n < (int) num_threads; n ++){	
		pthread_join(info[n].id,&info[n].result);
		list_final[n] = info[n].sum;
//		if(checker == 1)result += info[n].sum;
//		else result *= info[n].sum;
//		result = reduce_func(result,info[n].sum);		
	}
//	pthread_exit(NULL);
//	int result = base_case;
//	for(int m = 0; m < (int)(num_threads); m++){
//		printf("list_final[m] is:%d\n", list_final[m]);
//		printf("result is:%d\n",result);
//		result = reduce_func(result,info[m].sum);
//	}
//	pthread_exit(NULL);
//	return reduce_func(base_case,result);
	return reduce(list_final,num_threads,reduce_func,base_case);
//    return result;
}
