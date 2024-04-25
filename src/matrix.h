/*
    matrix.h    version 2.0

    Header file for matrix.c module.
    ------------------------------------


    Jakub Novák     March 2024

*/

#ifndef MAT_FUN
#define MAT_FUN

// get the number of elements in C array
#define ARRAY_LEN(array) (sizeof(array) / sizeof((array)[0]))

typedef enum
{
    MATRIX_OK,
    MATRIX_INVARGS,
    MATRIX_NOMEM,
    MATRIX_OPENING_ERROR,
    MATRIX_CLOSING_ERROR,
    MATRIX_TYPE_ERROR,
    MATRIX_OTHER_ERROR,
    MATRIX_ERROR_COUNT
} matrix_error;

typedef struct
{
    int rows;
    int cols;
    double** data;
} matrix;

extern const char* const MATRIX_ERROR_STRS[];
extern matrix_error error;
extern const char* matrix_error_str(matrix_error error);

extern matrix* initialize_matrix(int rows, int cols);
extern matrix* create_zero_matrix(int rows, int cols);
extern matrix* create_unit_matrix(int rows, int cols);
extern void destroy_matrix(matrix* mat);
extern void print_matrix(matrix* mat);
extern matrix* add(matrix* mat1, matrix* mat2);
extern matrix* substract(matrix* mat1, matrix* mat2);
extern matrix* multiply_by_scalar(matrix* mat, float scalar);
extern matrix* transpose(matrix* mat);
extern matrix* multiply_by_matrix(matrix* mat1, matrix* mat2);
extern matrix* read_from_file(const char* file, const char delimiter);
extern void save_to_file(matrix* mat, const char* file, const char delimiter);
extern int get_size(matrix* mat, int dimension);
extern double get_value(matrix* mat, int i, int j);
extern void set_value(matrix* mat, int i , int j, double value);

#endif