/**
* Extreme Edge Cases Lab
* CS 241 - Spring 2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "camelCaser.h"
#include "camelCaser_tests.h"

/*
 * Testing function for various implementations of camelCaser.
 *
 * @param  camelCaser   A pointer to the target camelCaser function.
 * @param  destroy      A pointer to the function that destroys camelCaser
 * output.
 * @return              Correctness of the program (0 for wrong, 1 for correct).
 */
int test_camelCaser(char **(*camelCaser)(const char *),
                    void (*destroy)(char **)) {
    // TODO: Return 1 if the passed in function works properly; 0 if it doesn't.
/*
        	char * test = "The Heisenbug is an incredible creature. Facenovel servers get their power from its indeterminism. Code smell can be ignored with INCREDIBLE use of air freshener. God objects are the new religion.";
	char ** myR = camel_caser(test);
	printf("%s\n",myR[0]);
	printf("%s\n",myR[1]);
	printf("%s\n",myR[2]);
	printf("%s\n",myR[3]);
	destroy(myR);
*/
	
// case 1:  NULL to NULL
	const char* test1 = NULL;
	char** ob1 = camelCaser(test1);
	if(ob1 != NULL){
		destroy(ob1);
		return 0;
	}
	printf("1\n");

// case 2: sadfgh. to sadfgh
	const char* test2 = "sadfgh.";
	char** ob2 = camelCaser(test2);
	int temp = 0; 
	temp = strcmp(ob2[0],"sadfgh");
	if(ob2[1]!=NULL){
		destroy(ob2);
		return 0;
	}
	destroy(ob2);
	
	if(temp!=0) return 0;
	printf("2\n");

// case 3: sadfgh to NULL
	const char* test3 = "sadfgh";
	char** ob3 = camelCaser(test3);
//	printf("%s\n",ob3[0]);
	if(ob3[0] != NULL){
		destroy(ob3);
		return 0;
	}
	destroy(ob3);
	printf("3\n");

//case 4: ABcDe fG. to abcfeFg
	const char* test4 = "ABcDe fG.";
	char** ob4 = camelCaser(test4);
	temp = 0;
	temp = strcmp(*ob4,"abcdeFg");
	if(ob4[1]!=NULL){
		destroy(ob4);
		return 0;
	}
	destroy(ob4);
	if(temp!=0) return 0;
	printf("4\n");


// case 5:   abcdefg. to abcdefg
	const char* test5 = "  abcdefg.";
	char** ob5 = camelCaser(test5);
	temp = 0; 
	temp = strcmp(*ob5,"abcdefg");
	if(ob5[1]!=NULL){
		destroy(ob5);
		return 0;
	}
	destroy(ob5);
	if(temp!=0) return 0;
	printf("5\n");


// case 6: I Love cS.    i LoVe mP to iLoveCs
	const char* test6 = "I Love cS.    i LoVe mP";
	char** ob6 = camelCaser(test6);
	temp = 0; 
	temp = strcmp(*ob6,"iLoveCs");
	if(ob6[1]!=NULL){
		destroy(ob6);
		return 0;
	}
	destroy(ob6);
	if(temp!=0) return 0;
	printf("6\n");

// case 7: example test
	const char* test7 = "The Heisenbug is an incredible creature. Facenovel servers get their power from its indeterminism. Code smell can be ignored with INCREDIBLE use of air freshener. God objects are the new religion.";
	char** ob7 = camelCaser(test7);
	int t0 = strcmp(ob7[0],"theHeisenbugIsAnIncredibleCreature"); 
	int t1 = strcmp(ob7[1],"facenovelServersGetTheirPowerFromItsIndeterminism");
	int t2 = strcmp(ob7[2],"codeSmellCanBeIgnoredWithIncredibleUseOfAirFreshener");
	int t3 = strcmp(ob7[3],"godObjectsAreTheNewReligion");
	if(ob7[4]!=NULL){
		destroy(ob7);
		return 0;
	}
	destroy(ob7);
	if((t1|t2|t3|t0)!=0) return 0;

	printf("7\n");

// case 8: . sadfgh. to sadfgh
	const char* test8 = ". sadfgh.";
	char** ob8 = camelCaser(test8);
	t0 = 0;
	t1 = 0; 
	t0 = strcmp(*ob8,"");
	t1 = strcmp(ob8[1],"sadfgh");
	if(ob8[2]!=NULL){
		destroy(ob8);
		return 0;
	}
	destroy(ob8);
	if((t0|t1)!=0) return 0;
	printf("8\n");

// case 9: 9sa 9dfgh. to 9sa9Dfgh
	const char* test9 = " 9sa 9dfgh.";
	char** ob9 = camelCaser(test9);
	temp = 0; 
	temp = strcmp(*ob9,"9sa9Dfgh");
	if(ob9[1]!=NULL){
		destroy(ob9);
		return 0;
	}
	destroy(ob9);
	if(temp!=0) return 0;
	printf("9\n");

// case 10: asd.fghjkl. to asd  fghjkl
	const char* test10 = "asd.fghjkl.";
	char** ob10 = camelCaser(test10);
	temp = 0; 
	t0 = strcmp(ob10[0],"asd");
	temp = strcmp(ob10[1],"fghjkl");
	if(ob10[2] != NULL){
		destroy(ob10);
		return 0;
	}
	destroy(ob10);
	if((temp|t0)!=0) return 0;
	printf("10\n");

// case 11: . to ""
	const char* test11 = ".";
	char** ob11 = camelCaser(test11);
	temp = 0; 
	temp = strcmp(*ob11,"");
	if(ob11[1] != NULL){
		destroy(ob11);
		return 0;
	}
	destroy(ob11);
	if(temp!=0) return 0;
	printf("11\n");

// case 12: s....a to s    a
	const char* test12 = "s....a.";
	char** ob12 = camelCaser(test12);
	temp = 0; 
	temp = strcmp(*ob12,"s");
	t1 = strcmp(ob12[1],"");
	t2 = strcmp(ob12[2],"");
	t3 = strcmp(ob12[3],"");
	t0 = strcmp(ob12[4],"a");
	if(ob12[5]!=NULL){
		destroy(ob12);
		return 0;
	}
	destroy(ob12);
	if((temp|t1|t3|t2|t0)!=0) return 0;
	printf("12\n");

// case 13: ....a to     a
	const char* test13 = "....a.";
	char** ob13 = camelCaser(test13);
	temp = 0; 
	temp = strcmp(*ob13,"");
	t1 = strcmp(ob13[1],"");
	t2 = strcmp(ob13[2],"");
	t3 = strcmp(ob13[3],"");
	t0 = strcmp(ob13[4],"a");
	if(ob13[5]!=NULL){
		destroy(ob13);
		return 0;
	}	
	destroy(ob13);
	if((temp|t1|t3|t2|t0)!=0) return 0;
	printf("13\n");
// case 14: hello ... world.
	const char* test14 = "hello ... world.";
	char** ob14 = camelCaser(test14);
	temp = strcmp(ob14[0],"hello");
	t0 = strcmp(ob14[1],"");
	t1 = strcmp(ob14[2],"");
	t2 = strcmp(ob14[3],"world");
	if(ob14[4]!=NULL){
		destroy(ob14);
		return 0;
	}
	destroy(ob14);
	if((temp|t0|t1|t2)!=0) return 0;
	printf("14\n");
// case 15: abc\12 123\23. def\123;
	const char* test15 = "abc\12 123\23. def\123;";

	char** ob15 = camelCaser(test15);
	temp = strcmp(ob15[0],"abc123\x13");
	printf("%s\n",ob15[0]);
	printf("%d\n",temp);
	t0 = strcmp(ob15[1],"defs");
	printf("%s\n",ob15[1]);
	printf("%d\n",temp);
	destroy(ob15);
	if((t0|temp)!=0) return 0;
	printf("15\n");
	
	
	
   return 1;
}

