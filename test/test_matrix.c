#include <stdio.h>
#include "unity.h"
#include "matrix.h"
#include "math.h"
 
matrix *mat1, *mat2, *mat3;

int compare_2d_arrays(double expected[3][3], double** actual, int rows, int cols) {
    // Compare each element of the arrays
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (expected[i][j] != actual[i][j]) {
                return 0; // Arrays are not equal
            }
        }
    }
    return 1; // Arrays are equal
}


void setUp(void) {
    // This function is called before each test
}


void tearDown(void) {
    // This function is called after each test
}


void test_matrix_should_be_initialized(void) {
    mat1 = initialize_matrix(3, 3);

    // Test matrix initialization
    TEST_ASSERT_NOT_NULL(mat1);
    TEST_ASSERT_EQUAL_INT(3, mat1->rows);
    TEST_ASSERT_EQUAL_INT(3, mat1->cols);
    
    destroy_matrix(mat1);
}


void test_matrix_should_fail_initialization(void) {
    mat1 = initialize_matrix(-1, -3);

    TEST_ASSERT_NULL(mat1);
    TEST_ASSERT_EQUAL(MATRIX_INVARGS, error);

    destroy_matrix(mat1);
}


void test_matrix_should_be_unit(void) {
    mat1 = create_unit_matrix(3, 3);
    double expected_mat[][3] = { {1.0, 0.0, 0.0},
                                {0.0, 1.0, 0.0},
                                {0.0, 0.0, 1.0}};

    TEST_ASSERT_NOT_NULL(mat1);
    TEST_ASSERT_TRUE(compare_2d_arrays(expected_mat, mat1->data, 3, 3));

    destroy_matrix(mat1);
}


void test_matrix_should_be_zero(void) {
    mat1 = create_zero_matrix(3, 3);
    double expected_mat[3][3] = {0};

    TEST_ASSERT_NOT_NULL(mat1);
    TEST_ASSERT_TRUE(compare_2d_arrays(expected_mat, mat1->data, 3, 3));

    destroy_matrix(mat1);
}


void test_matrix_add(void){
    mat1 = create_unit_matrix(3, 3);
    mat2 = create_unit_matrix(3, 3);
    mat3 = add(mat1, mat2);
    double expected_mat[][3] = { {2.0, 0.0, 0.0},
                                {0.0, 2.0, 0.0},
                                {0.0, 0.0, 2.0}};

    // Test matrix addition
    TEST_ASSERT_NOT_NULL(mat1);
    TEST_ASSERT_TRUE(compare_2d_arrays(expected_mat, mat3->data, 3, 3));

    destroy_matrix(mat1);
    destroy_matrix(mat2);
    destroy_matrix(mat3);
}


void test_matrix_substract(void){
    mat1 = create_unit_matrix(3, 3);
    mat2 = create_unit_matrix(3, 3);
    mat3 = substract(mat1, mat2);
    double expected_mat[][3] = { {0.0, 0.0, 0.0},
                                {0.0, 0.0, 0.0},
                                {0.0, 0.0, 0.0}};

    // Test matrix substraction
    TEST_ASSERT_NOT_NULL(mat1);
    TEST_ASSERT_TRUE(compare_2d_arrays(expected_mat, mat3->data, 3, 3));

    destroy_matrix(mat1);
    destroy_matrix(mat2);
    destroy_matrix(mat3);
}


void test_matrix_multiply_by_scalar(void){
    mat1 = create_unit_matrix(3, 3);
    mat3 = multiply_by_scalar(mat1, 5);
    double expected_mat[][3] = { {5.0, 0.0, 0.0},
                                {0.0, 5.0, 0.0},
                                {0.0, 0.0, 5.0}};

    // Test matrix addition
    TEST_ASSERT_NOT_NULL(mat1);
    TEST_ASSERT_TRUE(compare_2d_arrays(expected_mat, mat3->data, 3, 3));

    destroy_matrix(mat1);
    destroy_matrix(mat3);
}


void test_matrix_multiply_by_matrix(void){
    mat1 = create_unit_matrix(3, 3);
    set_value(mat1, 1, 1, 5);
    mat2 = create_unit_matrix(3, 3);
    set_value(mat2, 3, 3, -5);
    set_value(mat2, 1, 3, 5);
    mat3 = multiply_by_matrix(mat1, mat2);
    double expected_mat[][3] = { {5.0, 0.0, 25.0},
                                {0.0, 1.0, 0.0},
                                {0.0, 0.0, -5.0}};

    // Test matrix addition
    TEST_ASSERT_NOT_NULL(mat1);
    TEST_ASSERT_TRUE(compare_2d_arrays(expected_mat, mat3->data, 3, 3));

    destroy_matrix(mat1);
    destroy_matrix(mat2);
    destroy_matrix(mat3);
}


void test_matrix_should_transposed(void) {
    mat1 = create_unit_matrix(3, 3);
    set_value(mat1, 1, 2, 5);
    mat2 = transpose(mat1);
    double expected_mat[][3] = { {1.0, 0.0, 0.0},
                                {5.0, 1.0, 0.0},
                                {0.0, 0.0, 1.0}};

    TEST_ASSERT_NOT_NULL(mat1);
    TEST_ASSERT_TRUE(compare_2d_arrays(expected_mat, mat2->data, 3, 3));

    destroy_matrix(mat1);
}


void test_matrix_file_operations(void) {
    const char* temp_filename = "temp_test_matrix.txt";
    const char delimiter = ' ';
    double expected_mat[][3] = { {1.0, 0.0, 0.0},
                                {0.0, 1.0, 0.0},
                                {0.0, 0.0, 1.0}};

    mat1 = create_unit_matrix(3, 3);
    save_to_file(mat1, temp_filename, delimiter);
    mat2 = read_from_file(temp_filename, delimiter);

    TEST_ASSERT_NOT_NULL_MESSAGE(mat1, "Failed saving to save");
    TEST_ASSERT_NOT_NULL_MESSAGE(mat2, "Failed reading from file");
    TEST_ASSERT_TRUE(compare_2d_arrays(expected_mat, mat2->data, 3, 3));

    destroy_matrix(mat1);
    destroy_matrix(mat2);
    remove(temp_filename);
}


void test_matrix_get_size(void) {
    mat1 = create_unit_matrix(3, 3);
    int val1, val2;
    val1 = get_size(mat1, 1);
    val2 = get_size(mat1, 2);

    TEST_ASSERT_NOT_NULL(mat1);
    TEST_ASSERT_EQUAL(3, val1);
    TEST_ASSERT_EQUAL(3, val2);

    destroy_matrix(mat1);
}


void test_matrix_get_value(void) {
    mat1 = create_unit_matrix(3, 3);
    int val1, val2;
    val1 = get_value(mat1, 1, 1);
    val2 = get_value(mat1, 2, 1);

    TEST_ASSERT_NOT_NULL(mat1);
    TEST_ASSERT_EQUAL(1, val1);
    TEST_ASSERT_EQUAL(0, val2);

    destroy_matrix(mat1);
}


void test_matrix_set_value(void) {
    mat1 = create_zero_matrix(3, 3);
    int val1;
    set_value(mat1, 1, 1, 5);
    val1 = get_value(mat1, 1, 1);

    TEST_ASSERT_NOT_NULL(mat1);
    TEST_ASSERT_EQUAL(5, val1);

    destroy_matrix(mat1);
}

// Add more test functions for other matrix operations...

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_matrix_should_be_initialized);
    RUN_TEST(test_matrix_should_be_unit);
    RUN_TEST(test_matrix_should_be_zero);
    RUN_TEST(test_matrix_add);
    RUN_TEST(test_matrix_substract);
    RUN_TEST(test_matrix_multiply_by_scalar);
    RUN_TEST(test_matrix_multiply_by_matrix);
    RUN_TEST(test_matrix_should_transposed);
    RUN_TEST(test_matrix_file_operations);
    RUN_TEST(test_matrix_get_size);
    RUN_TEST(test_matrix_get_value);
    RUN_TEST(test_matrix_set_value);
    return UNITY_END();
}