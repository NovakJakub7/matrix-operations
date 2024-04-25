/*
    matrix.c    version 2.0

    Module for matrix operations.
    --------------------------


    Jakub Novák     March 2024

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

// Define a macro for logging errors
#ifdef ENABLE_LOGGING
#define LOG_ERROR(fmt, ...) fprintf(stderr, "[ERROR] %s:%d: " fmt "\n", __func__, __LINE__, ##__VA_ARGS__)
#else
#define LOG_ERROR(fmt, ...)
#endif

matrix_error error = MATRIX_OK;

const char* const MATRIX_ERROR_STRS[] = 
{
    "MATRIX_ERROR_OK",
    "MATRIX_ERROR_INVARG",
    "MATRIX_ERROR_NO_MEMORY",
    "MATRIX_ERROR_OPENING_FAILED",
    "MATRIX_ERROR_CLOSING_FAILED",
    "MATRIX_ERROR_WRONG_TYPE",
    "MATRIX_ERROR_OTHER"
};


const char* matrix_error_str(matrix_error error)
{
    const char* err_str = NULL;

    // Ensure error codes are within the valid array index range
    if (error < MATRIX_ERROR_COUNT && error >=0)
    {
        err_str = MATRIX_ERROR_STRS[error];
    }

    return err_str;
}


static int is_matrix_file(const char* filename, const char delimiter) {
    /* Check if the file format represents a matrix.*/
    FILE *file;
    int rows = 0;
    int cols = 0;  // Initialize to an invalid value
    int prev_cols = -1;
    char *token;
    char buffer[100];  // Adjust the buffer size as needed

    if ((file = fopen(filename, "r")) == NULL) {
        error = MATRIX_OPENING_ERROR;
        LOG_ERROR("Failed opening file");
        return 0;
    }

    // Read the file buffer by buffer
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (prev_cols != -1 && strlen(buffer) == 1)
        {
            break;
        }
        
        if (strchr(buffer, delimiter) == NULL)
        {
            prev_cols = -1;
            break;
        }
        
        // Count the number of columns in every row
        token = strtok(buffer, &delimiter);
        while (token != NULL) {
            cols++;
            token = strtok(NULL, &delimiter);
        }
        if (prev_cols == -1)
        {
            prev_cols = cols;
        }
        // Compare with previous columns number
        if (cols != prev_cols) {
            prev_cols = -1;
            break;
        } else {
            prev_cols = cols;
            cols = 0;
        }
        rows++;
    }

    fclose(file);

    // Determine if the file represents a matrix
    if (rows > 0 && prev_cols > 0) {
        error = MATRIX_OK;
        return 1;
    } else {
        error = MATRIX_TYPE_ERROR;
        LOG_ERROR("File does not represent a matrix");
        return 0;
    }
}


matrix* initialize_matrix(int rows, int cols){
    /* Creates a matrix m * n and allocates an array for matrix elements. */
    
    int i;
    matrix *mat = malloc(sizeof(matrix));

    if (!mat) {
        error = MATRIX_NOMEM;
        LOG_ERROR("Failed memory allocation");
        return NULL;
    }

    if (rows <= 0 || cols <= 0)
    {
        error = MATRIX_INVARGS;
        LOG_ERROR("Invalid arguments");
        free(mat);
        return NULL;
    }

    mat->rows = rows;
    mat->cols = cols;

    mat->data = malloc(rows * sizeof(double *));

    if (mat->data == NULL)
    {
        error = MATRIX_NOMEM;
        LOG_ERROR("Failed memory allocation");
        free(mat);
        return NULL;
    }

    for (i = 0; i < rows; i++)
    {
        mat->data[i] = malloc(cols * sizeof(double));
        if (mat->data[i] == NULL)
        {   
            // free already allocated memory
            for (int j = 0; j < i; j++) {
                free(mat->data[j]);
            }
            free(mat->data);  
            free(mat);     
            error = MATRIX_NOMEM;
            LOG_ERROR("Failed memory allocation");
            return NULL;
        }
    }
    
    error = MATRIX_OK;
    return mat;
}


matrix* create_zero_matrix(int rows, int cols){
    /* Creates a zero matrix of size rows * cols. */

    int i, j;
    matrix *mat = initialize_matrix(rows, cols);

    if (error != MATRIX_OK)
    {
        return NULL;
    }

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            mat->data[i][j] = 0.0;
        }
    }

    error = MATRIX_OK;
    return mat;
}

matrix* create_unit_matrix(int rows, int cols){
    /* Creates a unit matrix of size m * n. */

    int i, j;
    matrix* mat = initialize_matrix(rows, cols);

    if (error != MATRIX_OK)
    {
        return NULL;
    }
    
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (i == j)
            {
                mat->data[i][j] = 1.0;
            }else{
                mat->data[i][j] = 0.0;
            }
        }
    }

    error = MATRIX_OK;
    return mat;
}


void destroy_matrix(matrix* mat){
    /* Frees memory allocated for matrix mat. */
    int i;

    if (!mat) {
        return;
    }
    
    for (i = 0; i < mat->rows; i++)
    {
        free(mat->data[i]);
        mat->data[i] = NULL;
    }
    
    free(mat->data);
    mat->data = NULL;
    free(mat);
    mat = NULL;
}

void print_matrix(matrix* mat){
    /* Prints out matrix in a formatted style. */
    int i, j;

    if (!mat) {
        error = MATRIX_INVARGS;
        LOG_ERROR("Invalid arguments");
        return;
    }

    for (i = 0; i < mat->rows; i++)
    {
        for (j = 0; j < mat->cols; j++)
        {
            printf("%lf ", mat->data[i][j]);
        }
        printf("\n");
    }
}


matrix* add(matrix* mat1, matrix* mat2){
    /* Returns an addition of two matrices mat1 and mat2. */

    matrix* mat3;
    int i, j;

    if (!mat1 || !mat2) {
        error = MATRIX_INVARGS;
        LOG_ERROR("Invalid arguments");
        return NULL;
    }

    mat3 = initialize_matrix(mat1->rows, mat1->cols);

    if (error != MATRIX_OK)
    {
        return NULL;
    }

    if (mat1->rows == mat2->rows && mat1->cols == mat2->cols)
    {
        for (i = 0; i < mat1->rows; i++)
        {
            for (j = 0; j < mat1->cols; j++)
            {
                mat3->data[i][j] = mat1->data[i][j] + mat2->data[i][j];
            }
        }
    }else{
        error = MATRIX_TYPE_ERROR;
        LOG_ERROR("Invalid matrix types");
        destroy_matrix(mat3);
        return NULL;
    }
    
    error = MATRIX_OK;
    return mat3;
}


matrix* substract(matrix* mat1, matrix* mat2){
    /* Returns a substraction of matrices mat1 and mat2. */

    matrix* mat3;
    int i, j;

    if (!mat1 || !mat2) {
        error = MATRIX_INVARGS;
        LOG_ERROR("Invalid arguments");
        return NULL;
    }

    mat3 = initialize_matrix(mat1->rows, mat1->cols);

    if (error != MATRIX_OK)
    {
        return NULL;
    }

    if (mat1->rows == mat2->rows && mat1->cols == mat2->cols)
    {
        for (i = 0; i < mat1->rows; i++)
        {
            for (j = 0; j < mat1->cols; j++)
            {
                mat3->data[i][j] = mat1->data[i][j] - mat2->data[i][j];
            }
            
        }
    }else{
        error = MATRIX_TYPE_ERROR;
        LOG_ERROR("Invalid matrix types");
        return NULL;
    }
    
    error = MATRIX_OK;
    return mat3;
}


matrix* multiply_by_scalar(matrix* mat, float scalar){
    /* Return a matrix mat multiplied by a scalar. */

    matrix* mat2;
    int i, j;

    if (!mat) {
        error = MATRIX_INVARGS;
        LOG_ERROR("Invalid arguments");
        return NULL;
    }

    mat2 = initialize_matrix(mat->rows, mat->cols);

    if (error != MATRIX_OK)
    {
        return NULL;
    }

    for (i = 0; i < mat->rows; i++)
    {
        for (j = 0; j < mat->cols; j++)
        {
            mat2->data[i][j] = mat->data[i][j] * scalar;
        }
    }

    error = MATRIX_OK;
    return mat2;
}


matrix* transpose(matrix* mat){
    /* Returns a transposition of matrix mat. */

    matrix* mat2;
    int i, j;

    if (!mat) {
        error = MATRIX_INVARGS;
        LOG_ERROR("Invalid arguments");
        return NULL;
    }

    mat2 = initialize_matrix(mat->rows, mat->cols);

    if (error != MATRIX_OK)
    {
        return NULL;
    }

    for (i = 0; i < mat->cols; i++)
    {
        for (j = 0; j < mat->rows; j++)
        {
            if (i == j)
            {
                mat2->data[i][j] = mat->data[i][j];
            }else{
                mat2->data[i][j] = mat->data[j][i];
            }
        }
    }

    error = MATRIX_OK;
    return mat2;
}


matrix* multiply_by_matrix(matrix* mat1, matrix* mat2){
    /* Returns a multiplication of two matrices mat1 and mat2. */

    matrix* mat3;
    int i, j, k, sum = 0;

    if (!mat1 || !mat2) {
        error = MATRIX_INVARGS;
        LOG_ERROR("Invalid arguments");
        return NULL;
    }

    mat3 = initialize_matrix(mat1->rows, mat2->cols);

    if (error != MATRIX_OK)
    {
        return NULL;
    }

    if (mat1->cols == mat2->rows)
    {
        for (i = 0; i < mat1->rows; i++)
        {
            for (j = 0; j < mat2->cols; j++)
            {
                for (k = 0; k < mat1->cols; k++)
                {
                    sum += mat1->data[i][k] * mat2->data[k][j];
                }
                mat3->data[i][j] = sum;
                sum = 0;
            }
        }   
    }else{
        error = MATRIX_TYPE_ERROR;
        LOG_ERROR("Invalid matrix types");
        return NULL;
    }
    
    error = MATRIX_OK;
    return mat3;
}


matrix* read_from_file(const char *filename, const char delimiter){
    /*  Reads matrix from a text file.
        Every row represents a matrix row and elements must be seperated by separator. */
    
    FILE *f;
    matrix *mat;
    int rows = 0, cols = 0, i, j, ch, prev_ch;
    float num;

    if (filename == NULL){
        error = MATRIX_INVARGS;
        LOG_ERROR("Invalid arguments");
        return NULL;
    }

    // Check if file represents a matrix
    if (is_matrix_file(filename, delimiter) == 0)
    {
        return NULL;
    }

    if ((f = fopen(filename, "r")) == NULL)
    {
        error = MATRIX_OPENING_ERROR;
        LOG_ERROR("Failed opening file");
        return NULL;
    }
    
    ch = fgetc(f);
    while (ch != EOF)
    {
        if(ch == '\n' || ch == EOF){
            rows++;
        }
        prev_ch = ch;
        ch = fgetc(f);
        // add last row
        if (ch == EOF && prev_ch != '\n')
        {
            rows++;
        }
        // break if newlines after matrix
        if (ch == '\n' && prev_ch == '\n')
        {
            break;
        }
    }

    rewind(f);

    while (fscanf(f, "%f", &num) == 1) {
        // Increment count for each successfully read float value
        cols++;

        // Skip over the delimiter ';'
        if (fgetc(f) != delimiter) {
            break;  // Exit loop if ';' is not found
        }
    }
    
    rewind(f);
    
    mat = initialize_matrix(rows, cols);
    if (mat == NULL) {
        fclose(f);
        return NULL;
    }

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {   
            if (fscanf(f, "%lf", &mat->data[i][j]) != 1) {
                error = MATRIX_OTHER_ERROR;
                LOG_ERROR("Failed reading from file");
                destroy_matrix(mat); // Free matrix of already loaded values
                fclose(f);
                return NULL;
            }
            // skip the next character - delimiter but not the last one in the row
            if (j < cols - 1) {
                fgetc(f);
            }
        }
    }
    
    if (fclose(f) == EOF) {
        error = MATRIX_CLOSING_ERROR;
        LOG_ERROR("Failed closing file");
        destroy_matrix(mat);
        return NULL;
    }
    
    error = MATRIX_OK;
    return mat;
}


void save_to_file(matrix* mat, const char* filename, const char delimiter){
    /* Saves matrix to a file. KONTROLA*/

    FILE *f;
    int i, j;

    if (mat == NULL || filename == NULL){
        error = MATRIX_INVARGS;
        LOG_ERROR("Invalid arguments");
        return;
    }

    if ((f = fopen(filename, "w")) == NULL)
    {
        error = MATRIX_OPENING_ERROR;
        LOG_ERROR("Failed opening file");
        return;
    }

    for (i = 0; i < mat->rows; i++)
    {
        for (j = 0; j < mat->cols; j++)
        {
            if (j > 0)
            {
                fprintf(f, &delimiter);
            }
            
            fprintf(f, "%lf", mat->data[i][j]);
        }
        fprintf(f, "\n");
    }

    if (fclose(f) == EOF)
    {
        error = MATRIX_CLOSING_ERROR;
        LOG_ERROR("Failed closing file");
        return;
    }

    error = MATRIX_OK;

}


int get_size(matrix* mat, int dimension){
    /*  Returns the size of a matrix in dimension. 
        Dimension = 1 for number of rows.
        Dimension = 2 for number of columns. */

    if (dimension == 1)
    {
        error = MATRIX_OK;
        return mat->rows;
    }
    else if (dimension == 2)
    {
        error = MATRIX_OK;
        return mat->cols;
    }
    else
    {
        error = MATRIX_INVARGS;
        LOG_ERROR("Invalid arguments");
        return 0;
    }
}


double get_value(matrix* mat, int i, int j){
    /* Returns the value of the element from the matrix in the i-th row and j-th column. */
    
    if (i > mat->rows || j > mat->cols || j < 0 || i < 0)
    {
        error = MATRIX_INVARGS;
        LOG_ERROR("Invalid arguments");
        return 0;
    }
    
    error = MATRIX_OK;
    return mat->data[i-1][j-1];
}


void set_value(matrix* mat, int i , int j, double value){
    /* Set the value of a matrix element in the i-th row and j-th column. */

    if (!mat) {
        error = MATRIX_INVARGS;
        LOG_ERROR("Invalid arguments");
        return;
    }
    if ((i > mat->rows || j > mat->cols)|| i < 0 || j < 0)
    {
        error = MATRIX_INVARGS;
        return;
    }
    error = MATRIX_OK;
    mat->data[i-1][j-1] = value;
}