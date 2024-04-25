# matrix-operations

Simple module for working with matrices written in C.
Including some basic unit testing for the library functions and error logging.
Feel free to improve and/or to change what you need.

## Instalation
To use this library in your project, you can download the source files directly from this repository. Here is the download link:

[Download the source code here](https://github.com/NovakJakub7/matrix-operations)

Once downloaded, you can include the library source files in your project and start using them as needed.

## Example
Example how to use the module for creating and working with matrices.

```
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main (){
   
    matrix* mat1 = create_zero_matrix(5, 5);
    matrix* mat2 = create_unit_matrix(5, 5);
    matrix* result;

    set_value(mat1, 1, 2, 4);
    result = multiply_by_matrix(mat1, mat2);
    print_matrix(result);

    destroy_matrix(mat1);
    destroy_matrix(mat2);
    
    return 0;
}
```

## Documentation

- to enable error logs use "-DENABLE_LOGGING" flag

### Structures
**matrix**
Structure representing a matrix
- 'rows': number of rows
- 'cols': number of columns
- 'data': 2D array containing the matrix values

**error**
Variable of enum type **matrix_error** representing error status. Possible **matrix_error** values:
- 'MATRIX_OK': no error
- 'MATRIX_INVARGS': invalid argument values
- 'MATRIX_ALLOCATION_ERROR': allocation error
- 'MATRIX_OPENING_ERROR': opening error
- 'MATRIX_CLOSING_ERROR': closing error
- 'MATRIX_TYPE_ERROR': type error
- 'MATRIX_OTHER_ERROR': other error

**const char\* matrix_error_str(matrix_error error);**
- 'error': value of error variable
- returns readable error string based on error

### Initialization

**matrix\* initialize_matrix(int rows, int cols);**
Creates a matrix and allocates an array for matrix elements.
- 'rows': number of rows
- 'cols': number of columns
- returns a pointer to the created matrix or NULL if error occurred

**matrix\* create_zero_matrix(int rows, int cols);**
Creates a zero matrix.
- 'rows': number of rows
- 'cols': number of columns
- returns a pointer to the created matrix or NULL if error occurred

**matrix\* create_unit_matrix(int rows, int cols);**
Creates a unit matrix.
- 'rows': number of rows
- 'cols': number of columns
- returns a pointer to the created matrix or NULL if error occurred

**void destroy_matrix(matrix\* mat)**
Frees memory allocated for matrix.
- 'mat': matrix pointer

**void print_matrix(matrix\* mat);**
Prints out matrix in a formatted style.
- 'mat': matrix pointer

### Operace s maticemi

**int get_size(matrix\* mat, int dimension);**
Returns the size of a matrix in dimension.
Dimension = 1 for number of rows.
Dimension = 2 for number of columns.
- 'mat': matrix pointer
- 'dimension': number specifying dimension
- returns number of rows or columns or 0 if error occurred

**float get_value(matrix\* mat, int i, int j);**
Get the value of the element from the matrix in the i-th row and j-th column.
- 'mat': matrix pointer
- 'i': i-th row
- 'j': j-th column
- returns the value of the element as a number or 0 if error occurred

**void set_value(matrix\* mat, int i , int j, float value);**
Set the value of a matrix element in the i-th row and j-th column.
- 'mat': matrix pointer
- 'i': i-th row
- 'j': j-th column
- 'value': number to be set

**matrix\* add(matrix\* mat1, matrix\* mat2);**
Creates a new matrix that is equal to an addition of two matrices mat1 and mat2.
- 'mat1': matrix pointer
- 'mat2': matrix pointer
- returns a matrix pointer to the created matrix or NULL if error occurred

**matrix\* substract(matrix\* mat1, matrix\* mat2);**
Creates a new matrix that is equal to a substraction of matrices mat1 and mat2.
- 'mat1': matrix pointer
- 'mat2': matrix pointer
- returns a matrix pointer to the created matrix or NULL if error occurred

**matrix\* multiply_by_scalar(matrix\* mat, float scalar);**
Creates a new matrix that is equal to a matrix mat multiplied by a scalar.
- 'mat': matrix pointer
- 'scalar': number multiplying the matrix
- returns a matrix pointer to the created matrix or NULL if error occurred

**matrix\* multiply_by_matrix(matrix\* mat1, matrix\* mat2);**
Creates a new matrix that is equal to a multiplication of two matrices mat1 and mat2.
- 'mat1': matrix pointer
- 'mat2': matrix pointer
- returns a matrix pointer to the created matrix or NULL if error occurred

**matrix\* transpose(matrix\* mat);**
Creates a new matrix that is equal to a transposition of matrix mat.
- 'mat': matrix pointer
- returns a matrix pointer to the created matrix or NULL if error occurred

**matrix\* read_from_file(const char\* file, char delimiter);**
Creates a new matrix by reading it from a text file.
Every row in the file represents a row in a matrix and elements must be seperated by some separator character.
- 'file': file name
- 'delimiter': separator character
- return a matrix pointer to the read matrix or NULL if error occurred

**void save_to_file(matrix\* mat, const char\* file, char delimiter);**
Saves matrix to a file.
- 'mat': matrix pointer
- 'file': file name
- 'delimiter': separator character
