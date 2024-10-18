#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "edit_distance_dyn.h"

static void test_edit_distance_dyn_first(void){
  TEST_ASSERT_EQUAL_INT(1,edit_distance("casa","cassa"));
}

static void test_edit_distance_dyn_second(void){
  TEST_ASSERT_EQUAL_INT(2,edit_distance("casa","cara"));
}

static void test_edit_distance_dyn_third(void){
  TEST_ASSERT_EQUAL_INT(4,edit_distance("tassa","passato"));
}

static void test_edit_distance_dyn_fourth(void){
  TEST_ASSERT_EQUAL_INT(0,edit_distance("pioppo","pioppo"));
}

int main(void){
    UNITY_BEGIN();

    RUN_TEST(test_edit_distance_dyn_first);
    RUN_TEST(test_edit_distance_dyn_second);
    RUN_TEST(test_edit_distance_dyn_third);
    RUN_TEST(test_edit_distance_dyn_fourth);

    return UNITY_END();
}
