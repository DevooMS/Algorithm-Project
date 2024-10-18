#include <stdlib.h>
#include <stdio.h>
#include "binary_insertion_sort.h"

#define INITIAL_CAPACITY 2


static MergeBinArray * binary_sort(MergeBinArray *, MergeBinArray *, long, long);
 long binary_sort_index_search(MergeBinArray * , void * ,  long ,  long );
static MergeBinArray * merge(MergeBinArray *, MergeBinArray *, long,  long);
//static void merge(MergeBinArray *, MergeBinArray *,  long,  long);

struct _MergeBinaryInsertionSort {
	  void **array;
	  long size;
	  unsigned long array_capacity;
	  int (*field_to_order)(void*, void*);
};

MergeBinArray * merge_bin_array_create(int (*field_to_order)(void*, void*)) {
	  if (field_to_order == NULL) {
	    fprintf(stderr, "merge_bin_array_create: precedes parameter cannot be NULL");
	    exit(EXIT_FAILURE);
	  }
	  MergeBinArray *merge_bin_array = (MergeBinArray*)malloc(sizeof(MergeBinArray));
	  if (merge_bin_array == NULL) {
	    fprintf(stderr, "merge_bin_array_create: unable to allocate memory for the binary_ins array");
	    exit(EXIT_FAILURE);
	  }
	  merge_bin_array->array = (void**)malloc(INITIAL_CAPACITY * sizeof(void*));
	  if (merge_bin_array->array == NULL) {
	    fprintf(stderr, "merge_bin_array_create: unable to allocate memory for the internal array");
	    exit(EXIT_FAILURE);
	  }
	  merge_bin_array->size = 0;
	  merge_bin_array->array_capacity = INITIAL_CAPACITY;
	  merge_bin_array->field_to_order = field_to_order;
	  return merge_bin_array;
}

void merge_bin_array_add(MergeBinArray * merge_bin_array, void * element) {
	  if (merge_bin_array == NULL) {
	    fprintf(stderr, "add_merge_bin_array_element: merge_bin_array parameter cannot be NULL");
	    exit(EXIT_FAILURE);
	  } 
	  if (element == NULL) {
	    fprintf(stderr, "add_merge_bin_array_element: element parameter cannot be NULL");
	    exit(EXIT_FAILURE);
	  }

	  if ((unsigned long)(merge_bin_array->size) >= merge_bin_array->array_capacity) {
	    merge_bin_array->array_capacity = 2 * merge_bin_array->array_capacity;
	    merge_bin_array->array = (void**)realloc(merge_bin_array->array, merge_bin_array->array_capacity * sizeof(void*));
	    if (merge_bin_array->array == NULL) {
	      fprintf(stderr,"merge_bin_array_add: unable to reallocate memory to host the new element");
	      exit(EXIT_FAILURE);
	    }
	  }
	  /* long index = get_index_to_insert(merge_bin_array, element);*/
	  /*insert_element(merge_bin_array, element, merge_bin_array->size);*/
	  merge_bin_array->array[merge_bin_array->size] = element; //aggiunge nel ultima posizione element che ho letto nel file
	  merge_bin_array->size++;
}

 long merge_bin_array_size(MergeBinArray * merge_bin_array) {
	  if (merge_bin_array == NULL) {
	    fprintf(stderr, "merge_bin_array_size: merge_bin_array parameter cannot be NULL");
	    exit(EXIT_FAILURE);
	  }
	  return merge_bin_array->size;
}

MergeBinArray * merge_sort(MergeBinArray * merge_bin_array, long index_start, long size){
	if(size<=0){ // puo fare binary  con k ??    2,1,      3,2,5 suppong che ho array diviso cosi
		MergeBinArray * sorted_array = merge_bin_array_create(merge_bin_array->field_to_order); //field_to_order contiene la funziona del main in questo caso order_int_field
		merge_bin_array_add(sorted_array,(merge_bin_array->array)[index_start]); //il mio primo elemento e 2 
		return binary_sort(merge_bin_array,sorted_array,index_start+1,size);	//vado al binary_sort start+1 punto al casella succesivo
	}else{
		 //long size = merge_bin_array_size(merge_bin_array);
		long k = size/2;
		//printf("\n%ld\n",k);
		MergeBinArray * array_left;
		MergeBinArray * array_right;
		
		array_left = merge_sort(merge_bin_array,index_start,k);
		array_right = merge_sort(merge_bin_array,index_start+k,size-k); //ripetto questo casino di merge_sort su right
		return merge(array_left, array_right, merge_bin_array_size(array_left),merge_bin_array_size(array_right));
		//merge uniscie mentre la stronza merge sort divide ... by nik
		
	} 
}

static MergeBinArray * merge(MergeBinArray * array_left, MergeBinArray * array_right,  long array_left_size,  long array_right_size){
	MergeBinArray * merged_array = merge_bin_array_create(array_left->field_to_order);
	 long i=0, j=0;
	

	
	for( long k=0; k<array_left_size+array_right_size;k++){
		if(array_left_size==0 || i==array_left_size){
			merge_bin_array_add(merged_array,(array_right->array)[j]);
			j++;
		}else if(array_right_size==0 || j==array_right_size){
			merge_bin_array_add(merged_array,(array_left->array)[i]);
			i++;
		}else if ((*(array_left->field_to_order))((array_left->array)[i],(array_right->array)[j])<0){
			merge_bin_array_add(merged_array,(array_left->array)[i]);
			i++;
		}else{
			merge_bin_array_add(merged_array,(array_right->array)[j]);
			j++;
		}
	}
	return merged_array; //ritorna merge sort e return nel main e ti dice all its okay
}
																					// start 1 size 2 
MergeBinArray * binary_sort(MergeBinArray * merge_bin_array, MergeBinArray * sorted_array, long index_start, long array_size){
	void * element;                       
	long i, index_insert, sorted_size;
	
	sorted_size = merge_bin_array_size(sorted_array);
	
	if(sorted_size==array_size){
		return sorted_array;
	}else{
		//printf("\nok\n");
		element = (merge_bin_array->array)[index_start]; //element ha 1 
		
		merge_bin_array_add(sorted_array,element);  // chiamo function merge_bin_array_add e ci attaco 1 a 2 ->[2][1]
		
		index_insert = binary_sort_index_search(sorted_array,element,0,sorted_size-1);
		//index_insert ho 0
		i=sorted_size;   //1 
		while(i>index_insert){
			(sorted_array->array)[i] = (sorted_array->array)[i-1];
			i--;
		}
		
		(sorted_array->array)[i] = element; // temp  
		
		return binary_sort(merge_bin_array,sorted_array,index_start+1,array_size);
	}		//ritorni left 
}
                                                                      //2                 0                  size-1
 long binary_sort_index_search(MergeBinArray * merge_bin_array, void * element,  long index_start,  long index_stop){
	//printf("\n%lu %lu\n", index_start,index_stop);
	if(index_stop<=index_start){ 
		if ((*(merge_bin_array->field_to_order))(element,(merge_bin_array->array)[index_start])>0)// ((*... punta field -> (element,(merge_bin_array->array)[index_start])>0) van nel int field
			return (index_start+1);
		else
			return index_start; //ritorna 0
	}
	else{
		long index_mid; 
		
		index_mid = (index_start+index_stop)/2;
		//printf("\n%lu\n",index_mid);
		if ((*(merge_bin_array->field_to_order))(element,(merge_bin_array->array)[index_mid])==0)
			return index_mid+1;
		
		if ((*(merge_bin_array->field_to_order))(element,(merge_bin_array->array)[index_mid])>0){
			return binary_sort_index_search(merge_bin_array,element,index_mid+1,index_stop);
		}else{
				return binary_sort_index_search(merge_bin_array,element,index_start,index_mid-1);
		}
	}
}

/*static void merge_bin_array_insert_element(MergeBinArray * merge_bin_array, void * element,  long element_index,  long index_insert) {
   long i;
  for (i = element_index; i >index_insert; i--)
    merge_bin_array->array[i] = merge_bin_array->array[i-1];
  merge_bin_array->array[i] = element;
}*/

int merge_bin_array_is_empty(MergeBinArray * merge_bin_array) {
	  if (merge_bin_array == NULL) {
	    fprintf(stderr, "merge_bin_array_is_empty: merge_bin_array parameter cannot be NULL");
	    exit(EXIT_FAILURE);
	  }
	  return merge_bin_array->size == 0;
}


void * merge_bin_array_get(MergeBinArray * merge_bin_array,  long i) {
  if (merge_bin_array == NULL) {
    fprintf(stderr, "merge_bin_array_get: merge_bin_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (i >= merge_bin_array->size) {
    fprintf(stderr, "merge_bin_array_get: Index %lu is out of the array bounds", i);
    exit(EXIT_FAILURE);
  }
  return merge_bin_array->array[i];
}

void merge_bin_array_free_memory(MergeBinArray * merge_bin_array) {
  if (merge_bin_array == NULL) {
    fprintf(stderr, "merge_bin_array_free_memory: merge_bin_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  free(merge_bin_array->array);
  free(merge_bin_array);
}

//returns the position where the new element must be inserted
/*static  long get_index_to_insert(MergeBinArray * merge_bin_array, void * element) {
   long i = 0;

  while (i < merge_bin_array->size) {
    // this would be an equivalent call
    // if ((*ordered_array->precedes)(element, ordered_array->array[i])) {
    if (merge_bin_array->precedes(element, merge_bin_array->array[i]))
      break;
    i++;
  }
  return i;
}*/
