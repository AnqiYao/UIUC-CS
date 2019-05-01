/**
* Parallel Make Lab
* CS 241 - Spring 2018
*/


#include "format.h"
#include "graph.h"
#include "parmake.h"
#include "parser.h"
#include <pthread.h>
#include <sys/stat.h>
#include <stdio.h>
#include "compare.h"
#include "dictionary.h"
#include <time.h>
#include <unistd.h>
#include "set.h"
#include "queue.h"

set* cycle_group;
graph* graph_file;
vector* command_group;
set* newttt;
pthread_mutex_t m_1;
pthread_mutex_t m;
pthread_cond_t cv;
pthread_cond_t cv_1;
int new_change;

void create_command_set(char* target){
	set_remove(cycle_group, target);
        if (!set_contains(newttt, target)) {
                rule_t *rule = (rule_t *)graph_get_vertex_value(graph_file, target);
        	rule->data = (void *)graph_vertex_degree(graph_file, target);
        	set_add(newttt, target);
        }
}

//return 1 if there is circle detected
int detect_cycle(char* target){
	if(set_contains(cycle_group, target)){
		return 1;
	}
	set_add(cycle_group,target);
	vector* neighbors = graph_neighbors(graph_file, target);
	for(size_t i = 0; i < vector_size(neighbors); i++){
		char* new_target = (char*)vector_get(neighbors, i);
		int result = detect_cycle(new_target);
		if(result == 1){
			vector_destroy(neighbors);
			return 1;
		}
	}
	vector_destroy(neighbors);
	create_command_set(target);
	return 0;
}


//return 0 if its name is not a file on disk
int check_name(char* name){
	return access(name,F_OK);
}

//return 1 if the command is the last one
int check_command(){
	return (vector_size(command_group) == 0);
}

void help_badneighbors(vector* badneighbors){
	pthread_mutex_lock(&m);
        for (size_t i = 0; i < vector_size(badneighbors); i++) {
      		char *bad_neighbor = (char *)vector_get(badneighbors, i);
          	rule_t * bad_neighbor_rule = (rule_t *)graph_get_vertex_value(graph_file, bad_neighbor);
	        bad_neighbor_rule->data = (void *)(((size_t)(bad_neighbor_rule->data)) - 1);
		}
	new_change = 1;
  	pthread_cond_broadcast(&cv);
        pthread_mutex_unlock(&m);
}

//return 0 if the command success
void* runCommand(void* pointer){
	int condition = 1;
	while(condition){
		char *target = NULL;
		int wait = 1;
		int empty;
		while(wait){
			pthread_mutex_lock(&m);
			empty = check_command();
			if(empty){
				wait = 0;
				new_change = 1;
			}
			else{
				size_t index = 0;
				for(size_t i = 0; i < vector_size(command_group); i++){
					char* ret= (char *)vector_get(command_group, i);
				//if there is no vertex around it
					if((size_t)(((rule_t *)graph_get_vertex_value(graph_file, ret))->data) == 0){
						target = strdup(ret);  //need to free!
                       				wait = 0;
						index = i;
                        			break;
					}
				}
				if(!wait){
					vector_erase(command_group, index);
					if(new_change!=1)	new_change = 1;
				}
				else new_change = 0;
			}
			while(!new_change)	pthread_cond_wait(&cv, &m);
			pthread_mutex_unlock(&m);
		}
		if(empty)	break;
	//dealing with bad neighbor
		rule_t * rule_1 = (rule_t *)graph_get_vertex_value(graph_file, target);
        	if (rule_1 ->state != 0) {
		//get bad neighbors
        		vector *badneighbors = graph_antineighbors(graph_file, target);
    			help_badneighbors(badneighbors);
    			vector_destroy(badneighbors);
    			free(target);
          		continue;
        	}
		vector* neighbors_depend = graph_neighbors(graph_file, target);
		struct stat myst;
		int in_file = check_name(target);
		if (in_file == 0)	stat(target, &myst);

		int depend_fail = 0;
		int non_file_depend = 0;
		int new_file_depend = 0;
//check three dependency failing parts
		for(size_t i = 0; i < vector_size(neighbors_depend); i++){
			char* temp_target = (char*) vector_get(neighbors_depend,i);
			if(check_name(temp_target)!=0){
				non_file_depend = 1;


				rule_t * rule_2 = (rule_t *)graph_get_vertex_value(graph_file, temp_target);
                		pthread_mutex_lock(&m_1);
				if(condition == 1){
                			while(rule_2->state == 0) pthread_cond_wait(&cv_1, &m_1);

				if(rule_2->state == -1)	depend_fail = 1;
				}
	                	pthread_mutex_unlock(&m_1);
			}
			else if(in_file == 0){
				struct stat myst_1;
                		stat(temp_target, &myst_1);
                		if (difftime(myst.st_mtime, myst_1.st_mtime) < 0)
                    		new_file_depend = 1;
			}
		}//end of for
		vector_destroy(neighbors_depend);
		if(depend_fail){
			pthread_mutex_lock(&m_1);
        	    	rule_1->state = -1;
            		pthread_cond_broadcast(&cv_1);
            		pthread_mutex_unlock(&m_1);
              //change the bad neighbor
                	vector *badneighbors = graph_antineighbors(graph_file, target);
          		help_badneighbors(badneighbors);	
          		vector_destroy(badneighbors);
          		free(target);
            		continue;
		}
	if(in_file == 0){
    		if (!non_file_depend && !new_file_depend) {
        		pthread_mutex_lock(&m_1);
       			rule_1->state = 1;
        		pthread_cond_broadcast(&cv_1);
        		pthread_mutex_unlock(&m_1);
        		//change the bad neighbor
          		vector *badneighbors = graph_antineighbors(graph_file, target);
          		help_badneighbors(badneighbors);
          		vector_destroy(badneighbors);
          		free(target);
        		continue;
    			}
		}

	int fff = 0;
for (size_t i = 0; i < vector_size(rule_1->commands); i++) {
    if (system(vector_get(rule_1->commands, i)) != 0) {
        fff = 1;
        break;
    }
}

if (fff) {
    pthread_mutex_lock(&m_1);
    rule_1->state = -1;
    pthread_cond_broadcast(&cv_1);
    pthread_mutex_unlock(&m_1);
}
else {
    pthread_mutex_lock(&m_1);
    rule_1->state = 1;
    pthread_cond_broadcast(&cv_1);
    pthread_mutex_unlock(&m_1);
}
//change the bad neighbor
  vector *badneighbors = graph_antineighbors(graph_file, target);
  help_badneighbors(badneighbors);
  vector_destroy(badneighbors);
  free(target);
	}// end of while(condition)
//	printf("it is at the end of while\n");
	return NULL; //ending of the function
}

int parmake(char *makefile, size_t num_threads, char **targets) {
	graph_file = parser_parse_makefile(makefile,targets);	// need destory
	vector* graph_targets = graph_vertices(graph_file);	// need destory
	vector* graph_goal = graph_neighbors(graph_file,"");	// need destory
//start from goal to see if there is circle condition
	for(size_t i = 0; i < vector_size(graph_goal); i++){
		cycle_group = string_set_create();
		newttt = string_set_create();
		char* goal_rule = (char *)vector_get(graph_goal,i);
		int find_cycle = detect_cycle(goal_rule);
		if(find_cycle == 1){
			print_cycle_failure(goal_rule);
		}else{
			pthread_mutex_init(&m, NULL);
    			pthread_mutex_init(&m_1, NULL);
    			pthread_cond_init(&cv, NULL);
			pthread_cond_init(&cv_1, NULL);
			pthread_t pthread_id[num_threads];

			command_group = set_elements(newttt);
			for(size_t i = 0; i < num_threads; i++){
				pthread_id[i] =i+1;
				pthread_create(&pthread_id[i], NULL, runCommand, NULL);
			}
//			printf("!111\n");
			for (size_t i = 0; i < num_threads; i++) {
			        pthread_join(pthread_id[i], NULL);
			}
//			printf("111111111\n");	
		    	pthread_mutex_destroy(&m);
    			pthread_mutex_destroy(&m_1);
    			pthread_cond_destroy(&cv);
    			pthread_cond_destroy(&cv_1);
			vector_destroy(command_group);
		}
		set_destroy(cycle_group);
		set_destroy(newttt);
	}
	//end of running commands and free\destroy
	vector_destroy(graph_targets);
	vector_destroy(graph_goal);
	graph_destroy(graph_file);
//	printf("I am at the end\n");
    	return 0;
}
