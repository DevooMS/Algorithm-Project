#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "binary_insertion_sort.h"
struct record{
    int id_field;
    char* field_one;
    int field_two;
    float field_three;
};

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
static int merge_bin_float_field(void* i1_p,void* i2_p){
    int* int1_p = (int*)i1_p;
    int* int2_p = (int*)i2_p;
    if((*int1_p) < (*int2_p)) return(1);
    return(0);
}
static int merge_bin_string_field(void* i1_p,void* i2_p){
    int* int1_p = (int*)i1_p;
    int* int2_p = (int*)i2_p;
    if((*int1_p) < (*int2_p)) return(1);
    return(0);
}
// Data elements that are initialized before each test
static int i1,i2,i3;
char c1[] = "Simone";
char c2[] = " V ";
char c3[] = "Tombino";
static double f1,f2,f3;
 
static MergeBinArray *merge_bin_array_int ,*merge_bin_array_float,*merge_bin_array_char;

void setUp(void){
	i1 = -12;
    i2 = 0;
    i3 = 4;

	f1 = 1.0;
	f2 = 0.0;
	f3 = 3.2;
    merge_bin_array_int = merge_bin_array_create(order_int_field);
	merge_bin_array_float = merge_bin_array_create(merge_bin_float_field);
	merge_bin_array_char = merge_bin_array_create(merge_bin_string_field);
}

void tearDown(void){
    merge_bin_array_free_memory(merge_bin_array_int);
	merge_bin_array_free_memory(merge_bin_array_char);
	merge_bin_array_free_memory(merge_bin_array_float);
	
}

static void test_merge_bin_array_is_empty_zero_el(void){
    TEST_ASSERT_TRUE(merge_bin_array_is_empty(merge_bin_array_int));
	TEST_ASSERT_TRUE(merge_bin_array_is_empty(merge_bin_array_float));
	TEST_ASSERT_TRUE(merge_bin_array_is_empty(merge_bin_array_char));
}

static void test_merge_bin_array_is_empty_one_el(void){
    merge_bin_array_add(merge_bin_array_int,&i1);
	merge_bin_array_add(merge_bin_array_char,&c1);
	merge_bin_array_add(merge_bin_array_float,&f1);
    TEST_ASSERT_FALSE(merge_bin_array_is_empty(merge_bin_array_int));
	TEST_ASSERT_FALSE(merge_bin_array_is_empty(merge_bin_array_char));
	TEST_ASSERT_FALSE(merge_bin_array_is_empty(merge_bin_array_float));
	
}

static void test_merge_bin_array_size_zero_el(void){
    TEST_ASSERT_EQUAL_INT(0,merge_bin_array_size(merge_bin_array_int));
	TEST_ASSERT_EQUAL_HEX(0,merge_bin_array_size(merge_bin_array_char));
	TEST_ASSERT_EQUAL_FLOAT(0,merge_bin_array_size(merge_bin_array_float));
}

static void test_merge_bin_array_size_one_el(void){
    merge_bin_array_add(merge_bin_array_int,&i1);
	merge_bin_array_add(merge_bin_array_char,&c1);
	merge_bin_array_add(merge_bin_array_float,&f1);
    TEST_ASSERT_EQUAL_INT(1,merge_bin_array_size(merge_bin_array_int));
	TEST_ASSERT_EQUAL_HEX(1,merge_bin_array_size(merge_bin_array_char));
	TEST_ASSERT_EQUAL_FLOAT(1,merge_bin_array_size(merge_bin_array_float));
}

static void test_merge_bin_array_size_two_el(void){
    merge_bin_array_add(merge_bin_array_int,&i1);
    merge_bin_array_add(merge_bin_array_int,&i2);
	merge_bin_array_add(merge_bin_array_char,&c1);
    merge_bin_array_add(merge_bin_array_char,&c2);
	merge_bin_array_add(merge_bin_array_float,&f1);
    merge_bin_array_add(merge_bin_array_float,&f2);
    TEST_ASSERT_EQUAL_INT(2,merge_bin_array_size(merge_bin_array_int));
	TEST_ASSERT_EQUAL_HEX(2,merge_bin_array_size(merge_bin_array_char));
	TEST_ASSERT_EQUAL_FLOAT(2,merge_bin_array_size(merge_bin_array_float));
}

static void test_merge_bin_array_add_get_three_el(void){
    int* array_expected[] = {&i1,&i2,&i3};
    merge_bin_array_add(merge_bin_array_int,&i3);
    merge_bin_array_add(merge_bin_array_int,&i1);
    merge_bin_array_add(merge_bin_array_int,&i2);
    MergeBinArray * actual_array = merge_bin_array_create (order_int_field);
    for(long i=0;i<3;i++){
       merge_bin_array_add(actual_array,merge_bin_array_get(merge_bin_array_int,i));
    }
	actual_array= merge_sort(actual_array,0,merge_bin_array_size(actual_array));
    TEST_ASSERT_EQUAL_PTR_ARRAY(array_expected,actual_array->array,3);
}

int main(void){
    // test session
    UNITY_BEGIN();

    RUN_TEST(test_merge_bin_array_is_empty_zero_el);
    RUN_TEST(test_merge_bin_array_is_empty_one_el);
    RUN_TEST(test_merge_bin_array_size_zero_el);
    RUN_TEST(test_merge_bin_array_size_one_el);
    RUN_TEST(test_merge_bin_array_size_two_el);
    RUN_TEST(test_merge_bin_array_add_get_three_el);

    return UNITY_END();
}
