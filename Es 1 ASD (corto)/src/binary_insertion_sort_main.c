#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "binary_insertion_sort.h"

struct record{
    int id_field;
    char* field_one;
    int field_two;
    float field_three;
};

static int order_string_field(void* r1_p,void* r2_p){
    if(r1_p == NULL){
        fprintf(stderr,"precedes_string: the first parameter cannot be NULL");
        exit(EXIT_FAILURE);
    }
    if(r2_p == NULL){
        fprintf(stderr,"precedes_string: the second parameter cannot be NULL");
        exit(EXIT_FAILURE);
    }
    char * rec1_p = ((struct record*)r1_p)->field_one;
    rec1_p[0] = (char) tolower(rec1_p[0]);
    char * rec2_p = ((struct record*)r2_p)->field_one;
    rec2_p[0] = (char) tolower(rec2_p[0]);

    return strcmp(rec1_p,rec2_p);
}

static int order_int_field(void* r1_p,void* r2_p){
    if(r1_p == NULL){
        fprintf(stderr,"precedes_string: the first parameter cannot be NULL");
        exit(EXIT_FAILURE);
    }
    if(r2_p == NULL){
        fprintf(stderr,"precedes_string: the second parameter cannot be NULL");
        exit(EXIT_FAILURE);
    }
    struct record * rec1_p = (struct record *)r1_p;
    struct record * rec2_p = (struct record *)r2_p;

    if(rec1_p->field_two < rec2_p->field_two)
        return -1;
    if(rec1_p->field_two > rec2_p->field_two)
        return 1;
    else
        return 0;
}

  static int order_float_field(void* r1_p,void* r2_p){
	if(r1_p == NULL){
		fprintf(stderr,"precedes_string: the first parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	if(r2_p == NULL){
		fprintf(stderr,"precedes_string: the second parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	struct record *rec1_p = (struct record*)r1_p;
	struct record *rec2_p = (struct record*)r2_p;
	
	if(rec1_p->field_three < rec2_p->field_three)
		return -1;
	if(rec1_p->field_three > rec2_p->field_three)
		return 1;
	else
		return 0;
}

static void load_array(const char* file_path,MergeBinArray* merge_bin_array){
    char *read_line_p;
    char buffer[1024];
    int buf_size = 1024;
    FILE *fp;
    printf("\nLoading data from file...\n");
    fp = fopen(file_path,"r");
    if(fp == NULL){
        fprintf(stderr,"main: unable to open the file %s\n",file_path);
        exit(EXIT_FAILURE);
    }
    int i=0;
    while(fgets(buffer,buf_size,fp) != NULL ){
        read_line_p = malloc((strlen(buffer)+1)*sizeof(char));
        if(read_line_p == NULL){
            fprintf(stderr,"main: unable to allocate memory for the read line");
            exit(EXIT_FAILURE);
        }   
        strcpy(read_line_p,buffer);   
        char *id_field_in_read_line_p = strtok(read_line_p,",");
        char *field_one_in_read_line_p = strtok(NULL,","); 
        char *field_two_in_read_line_p =  strtok(NULL,",");
        char *field_three_in_read_line_p =  strtok(NULL,"\n");
        int id_field = atoi(id_field_in_read_line_p); 
        char *field_one = malloc((strlen(field_one_in_read_line_p)+1)*sizeof(char));
        if(field_one == NULL){
            fprintf(stderr,"main: unable to allocate memory for the string field of the read record");
            exit(EXIT_FAILURE);
        }  
        strcpy(field_one,field_one_in_read_line_p);
        int field_two = atoi(field_two_in_read_line_p);  
        float field_three = strtof(field_three_in_read_line_p,NULL); 
        struct record *record_p = malloc(sizeof(struct record));
        if(record_p == NULL){
            fprintf(stderr,"main: unable to allocate memory for the read record");
            exit(EXIT_FAILURE);
        }
        record_p->id_field = id_field;
        record_p->field_one= field_one;
        record_p->field_two = field_two;
        record_p->field_three = field_three;
        merge_bin_array_add(merge_bin_array, (void*)record_p);
        free(read_line_p);
        i++;
    }   
    fclose(fp);
    printf("\nDONE\n");
}

void print_array(MergeBinArray * merge_bin_array){
		 long el_num = merge_bin_array_size(merge_bin_array);
    struct record *array_element;

    for( long i = 0;i<el_num;i++){
        array_element = (struct record *)merge_bin_array_get(merge_bin_array, i);
        printf("<%d,%s,%d,%f>\n",array_element->id_field,array_element->field_one,array_element->field_two,array_element->field_three);
    }
}

static void enter_array_function(const char* file_path,int (*field_to_order)(void*,void*)){
    MergeBinArray* merge_bin_array = merge_bin_array_create(field_to_order);
    load_array(file_path, merge_bin_array);
	//printf("\nARRAY BEFORE\n");//
   // print_array(merge_bin_array);//
    printf("\nstart\n");
   	MergeBinArray * ris = merge_sort(merge_bin_array, 0, merge_bin_array_size(merge_bin_array));
    printf("\ndone\n");//
    //printf("\nARRAY AFTER\n");//
    //print_array(ris);
    merge_bin_array_free_memory(merge_bin_array);
}

int main(int argc, char const *argv[]){
    if(argc < 2){
        printf("Usage: binary_insertion_sort_main <path_to_data_file>\n");
        exit(EXIT_FAILURE);
    }
    enter_array_function(argv[1],order_string_field);
    enter_array_function(argv[1],order_int_field);
    enter_array_function(argv[1],order_float_field);
    return (EXIT_SUCCESS);
}
