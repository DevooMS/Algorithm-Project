#ifndef EDIT_DISTANCE_H
#define EDIT_DISTANCE_H

//It's the struct of the dictionary
typedef struct _Dictionary{
	char ** array;
	unsigned long size;
	unsigned long array_capacity;
} Dictionary;

//It's the struct of the correct_list with minimal edit_distance
typedef struct _CorrectList{
	char** array;
	long min;
	unsigned long size;
	unsigned long array_capacity;
} CorrectList;

//It calculate the list with minimal edit_distnce for every word
//in the file correctme.txt
void edit_distance_dyn(char *, Dictionary *);

//It calculate the edit_distance of a word
long edit_distance(char*, char*);

//It create the correct list of a word
CorrectList * correct_list_create();

//It read the file correctme.txt
void correct_me_read(Dictionary *, const char *);

#endif
