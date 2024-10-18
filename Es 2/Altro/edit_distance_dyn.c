#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "edit_distance_dyn.h"
#define INITIAL_CAPACITY 2

//It create a correct_list with correct_list structure type
CorrectList * correct_list_create(){	
	CorrectList * correct_list = (CorrectList*)malloc(sizeof(CorrectList));
	if (correct_list == NULL) {
		fprintf(stderr, "dictionary_create: unable to allocate memory for the dictionary array");
	  exit(EXIT_FAILURE);
	}
	
	correct_list->array = (char**)malloc(INITIAL_CAPACITY * sizeof(char*));
	if (correct_list->array == NULL) {
		fprintf(stderr, "correct_list_create: unable to allocate memory for the internal array");
	  exit(EXIT_FAILURE);
	}
	
	correct_list->min = -1;
	correct_list->size = 0;
	correct_list->array_capacity = INITIAL_CAPACITY;
	
	return correct_list;
}

//It add an element in the correct_list with dynamic programming
void correct_list_add(CorrectList * correct_list, char * element) {
	if (correct_list == NULL) {
		fprintf(stderr, "correct_list_add: dictionary parameter cannot be NULL");
		exit(EXIT_FAILURE);
	} 
	if (element == NULL) {
		fprintf(stderr, "dictionary_add: element parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}

	if ((unsigned long)(correct_list->size) >= correct_list->array_capacity) {
		//printf("%ld\n",correct_list->array_capacity);
		correct_list->array_capacity = 2 * correct_list->array_capacity;
		//printf("%ld\n",correct_list->array_capacity);
	  correct_list->array = (char**)realloc(correct_list->array, (correct_list->array_capacity) * sizeof(char*));
	  if (correct_list->array == NULL) {
	  	fprintf(stderr,"correct_list_add: unable to reallocate memory to host the new element");
	    exit(EXIT_FAILURE);
	  }
	}
	correct_list->array[correct_list->size] = element;
	correct_list->size++;
}

//It remove an element from the correcr_list with dynamic programming
void correct_list_rem(CorrectList * correct_list) {
	if (correct_list == NULL) {
		fprintf(stderr, "correct_list_rem: dictionary parameter cannot be NULL");
		exit(EXIT_FAILURE);
	} 

	if(correct_list->array_capacity%2==0)
		correct_list->array_capacity = (unsigned long)((correct_list->array_capacity)/2);
	else
		correct_list->array_capacity = (unsigned long)(((correct_list->array_capacity)/2)+1);
	free(correct_list->array);
	correct_list->array = (char**)malloc((correct_list->array_capacity) * sizeof(char*));
	if (correct_list->array == NULL) {
	  fprintf(stderr,"correct_list_rem: unable to reallocate memory to host the new element");
	  exit(EXIT_FAILURE);
	}
	
	correct_list->size=0;
}

void correct_me_read(Dictionary * dictionary, const char * file_path){
	char * word;
  unsigned long buf_size = 1024;
  FILE *fp;
 
  fp = fopen(file_path,"r");
  if(fp == NULL){
  	fprintf(stderr,"edit_distance_dyn: unable to open the file %s\n",file_path);
    exit(EXIT_FAILURE);
  }  
  
  word = malloc((buf_size+1)*sizeof(char));
  	if(word == NULL){
  		fprintf(stderr,"main: unable to allocate memory for the read line");
   		exit(EXIT_FAILURE);
  }   

  while( fscanf(fp,"%s",word) != EOF){  
  	char last = word[strlen(word)-1];
  	
  	if( last == ',' || last == ':' || last == '.')
  		word[strlen(word)-1] = '\0'; 
  
  	edit_distance_dyn(word, dictionary);
	}
}

void edit_distance_dyn(char * word, Dictionary * dictionary){
	long min;
	
	CorrectList * correct_list = correct_list_create();
	
	for(unsigned long i = 0; i < dictionary->size && correct_list->min != 0; i++){
		char *  dictionary_word = dictionary->array[i];
		
		long lenght_word = (long)strlen(word);

		long lenght_dictionary_word = (long)strlen(dictionary_word);
		
		if(lenght_dictionary_word<=lenght_word && (char)tolower(word[0])==dictionary_word[0]){
			min = edit_distance(word, dictionary_word);
			//printf("%ld\n",min);
			if(correct_list->min == -1){
				correct_list->min = min;
				correct_list_add(correct_list, dictionary_word);
			}else if(min == correct_list->min){
					correct_list_add(correct_list, dictionary_word);
				} else if(min < correct_list->min){
					correct_list_rem(correct_list);
					correct_list->min = min;
					correct_list_add(correct_list, dictionary_word);
				}
		}
	}
	printf("%s:\n",word);
	for(unsigned long i=0; i<correct_list->size;i++){
		printf("\t%s\n",correct_list->array[i]);
	}
}

long edit_distance(char* word, char* dictionary_word){
	
	long ris, d_no_op, d_canc, d_ins;
	
	long lenght_word = (long)strlen(word);

	long lenght_dictionary_word = (long)strlen(dictionary_word);

	if(lenght_word==0)
		return lenght_dictionary_word;
		
	else if(lenght_dictionary_word==0)
		return lenght_word;
		
	else{
		char first_word = (char)tolower(word[0]);
		char first_dictionary_word = dictionary_word[0];
		
		if(first_word == first_dictionary_word)
			d_no_op = edit_distance(&word[1], &dictionary_word[1]);
		else
			d_no_op = UINT_MAX;
		
		d_canc = 1 + edit_distance(word, &dictionary_word[1]);
		
		d_ins = 1 + edit_distance(&word[1], dictionary_word);
		
		ris = d_no_op;
		
		if(d_canc < ris)
			ris = d_canc;
			
		if(d_ins < ris)
			ris = d_ins;
			
		return ris; 
	}
}
