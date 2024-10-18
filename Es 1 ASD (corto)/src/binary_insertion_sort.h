#ifndef BINARY_INSERTION_SORT_H_saasaasdfkjdjf
#define BINARY_INSERTION_SORT_H_saasaasdfkjdjf

typedef struct _MergeBinaryInsertionSort MergeBinArray;

MergeBinArray * merge_bin_array_create(/*int (*precedes)(void*,void*)*/);

void merge_bin_array_add(MergeBinArray *, void *);

 long merge_bin_array_size(MergeBinArray *);

MergeBinArray * merge_sort(MergeBinArray *, long, long);

int merge_bin_array_is_empty(MergeBinArray *);

void* merge_bin_array_get(MergeBinArray *,  long);

void merge_bin_array_free_memory(MergeBinArray *);

#endif /* ORDERED_ARRAY_H_saasaasdfkjdjf */
