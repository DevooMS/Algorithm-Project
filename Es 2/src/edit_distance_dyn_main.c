#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "edit_distance_dyn.h"
#define INITIAL_CAPACITY 2

//It create a Dictionary with Dictionary structure type
static Dictionary * dictionary_create(){	
	Dictionary * dictionary = (Dictionary*)malloc(sizeof(Dictionary));
	if (dictionary == NULL) {
		fprintf(stderr, "dictionary_create: unable to allocate memory for the dictionary array");
	  exit(EXIT_FAILURE);
	}
	
	dictionary->array = (char**)malloc(INITIAL_CAPACITY * sizeof(char*));
	if (dictionary->array == NULL) {
		fprintf(stderr, "dictionary_array_create: unable to allocate memory for the internal array");
	  exit(EXIT_FAILURE);
	}
	
	dictionary->size = 0;
	dictionary->array_capacity = INITIAL_CAPACITY;
	
	return dictionary;
}

//It add an element in the dictionary
void dictionary_add(Dictionary * dictionary, char * element) {
	if (dictionary == NULL) {
		fprintf(stderr, "dictionary_add: dictionary parameter cannot be NULL");
		exit(EXIT_FAILURE);
	} 
	if (element == NULL) {
		fprintf(stderr, "dictionary_add: element parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}

	if ((unsigned long)(dictionary->size) >= dictionary->array_capacity) {
		dictionary->array_capacity = 2 * dictionary->array_capacity;
	  dictionary->array = (char**)realloc(dictionary->array, dictionary->array_capacity * sizeof(char*));
	  if (dictionary->array == NULL) {
	  	fprintf(stderr,"dictionary_add: unable to reallocate memory to host the new element");
	    exit(EXIT_FAILURE);
	  }
	}
	dictionary->array[dictionary->size] = element;
	dictionary->size++;
}

//It read the file Dictionary.txt and save it in the struct Dictionary
static void load_dictionary(Dictionary * dictionary, const char* file_path){
    char *read_line_p;
    char buffer[1024];
    
    FILE *fp;
    printf("\nLoading data from file...\n");
    fp = fopen(file_path,"r");
    if(fp == NULL){
        fprintf(stderr,"main: unable to open the file %s\n",file_path);
        exit(EXIT_FAILURE);
    }
    
    while(fscanf(fp,"%s",buffer) != EOF){  
        read_line_p = malloc((strlen(buffer)+1)*sizeof(char));
        if(read_line_p == NULL){
            fprintf(stderr,"main: unable to allocate memory for the read line");
            exit(EXIT_FAILURE);
        }   
        
        strcpy(read_line_p,buffer);   
        
        char *line = malloc((strlen(read_line_p)+1)*sizeof(char));
        if(line == NULL){
            fprintf(stderr,"main: unable to allocate memory for the string field of the read record");
            exit(EXIT_FAILURE);
        }  
        strcpy(line,read_line_p);
        
        dictionary_add(dictionary, line);
        free(read_line_p);
    }   
    fclose(fp);
    printf("\nDONE\n");
}

// It should be invoked with two parameter specifying the path of the data file
int main(int argc, char const *argv[]){
    if(argc < 3){
        printf("Usage: edit_distamce_dyn_main <path_to_data_file>\n");
        exit(EXIT_FAILURE);
    }
    
    Dictionary * dictionary = dictionary_create();
    
    load_dictionary(dictionary,argv[1]);
    
    correct_me_read(dictionary, argv[2]);
}
