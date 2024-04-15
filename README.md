# matrix-operations

Jednoduchá knihovna pro práci s maticemi v jazyce C.

## Instalace
Pro použití této knihovny v rámci svého projektu můžete stáhnout zdrojové soubory přímo z tohoto repozitáře. Zde je odkaz ke stažení:

[Stáhnout zdrojové soubory](https://github.com/NovakJakub7/matrix-operations)

Po stažení můžete zahrnout zdrojové soubory knihovny do vašeho projektu a začít je používat podle potřeby.

## Příklad použití
Ukázka použití knihovny pro vytvoření a operaci s maticemi.

```
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main (){
   
    matrix* mat1 = create_zero_matrix(5, 5);
    matrix* mat2 = create_unit_matrix(5, 5);
    matrix* result;
    set_value(mat1, 1, 2, 4);
    printf("Error: %d\n", error);

    result = multiply_by_matrix(mat1, mat2);
    print_matrix(result);
    
    printf("Error: %d\n", error);
    destroy_matrix(mat1);
    destroy_matrix(mat2);
    
    return 0;
}
```

## Dokumentace

### Inicializace

**matrix\* initialize_matrix(int m, int n);**
Vytvoří matici velikosti m*n a alokuje paměť pro všechny její prvky.
- 'm': počet řádků matice
- 'n': počet sloupců matice
- vrací ukazatel na nově vytvořenou matici

**matrix\* create_zero_matrix(int m, int n);**
Vytvoří nulovou matici velikosti m*n.
- 'm': počet řádků matice
- 'n': počet sloupců matice
- vrací ukazatel na nově vytvořenou matici

**matrix\* create_unit_matrix(int m, int n);**
Vytvoří jednotkovou matici velikosti m*n.
- 'm': počet řádků matice
- 'n': počet sloupců matice
- vrací ukazatel na nově vytvořenou matici

**void destroy_matrix(matrix\* mat)**
Uvolní paměť matice.
- 'mat': ukazatel na matici

**void print_matrix(matrix\* mat);**
Vypíše matici ve formátovaném stylu do konzole.
- 'mat': ukazatel na matici

### Operace s maticemi

**int get_size(matrix\* mat, int dimension);**
Získá velikost matice podle dané dimenze. 1 - počet řádků, 2 - počet sloupců.
- 'mat': ukazatel na matici
- 'dimension': ukazatel na matici
- vrací počet řádků nebo sloupců

**float get_value(matrix\* mat, int i, int j);**
Získá hodnotu prvku matice na souřadnicích i,j.
- 'mat': ukazatel na matici
- 'i': i-tý řádek
- 'j': j-tý sloupec
- vrací hodnotu prvku jako číslo s řadovou čárkou

**void set_value(matrix\* mat, int i , int j, float value);**
Vloží do matice hodnotu pro prvek na souřadnicích i,j.
- 'mat': ukazatel na matici
- 'i': i-tý řádek
- 'j': j-tý sloupec
- 'value': číslo s řadovou čárkou vloženo do matice

**matrix\* add(matrix\* mat1, matrix\* mat2);**
Vytvoří matici, která vznikne součtem matic mat1 a mat2.
- 'mat1': ukazatel na matici
- 'mat2': ukazatel na matici
- vrací ukazatel na nově vytvořenou matici

**matrix\* substract(matrix\* mat1, matrix\* mat2);**
Vytvoří matici, která vznikne odečtením matic mat1 a mat2.
- 'mat1': ukazatel na matici
- 'mat2': ukazatel na matici
- vrací ukazatel na nově vytvořenou matici

**matrix\* multiply_by_scalar(matrix\* mat, float scalar);**
Vytvoří matici, vynásobením matice skalárem.
- 'mat': ukazatel na matici
- 'scalar': skalár násobící matici
- vrací ukazatel na nově vytvořenou matici

**matrix\* multiply_by_matrix(matrix\* mat1, matrix\* mat2);**
Vytvoří matici, vzájemným vynásobením dvou matic.
- 'mat1': ukazatel na matici
- 'mat2': ukazatel na matici
- vrací ukazatel na nově vytvořenou matici

**matrix\* transpose(matrix\* mat);**
Vytvoří matici, která vznikne jako transpozice matice mat.
- 'mat': ukazatel na matici
- vrací ukazatel na nově vytvořenou matici

**matrix\* read_from_file(const char\* file, char delimiter);**
Vytvoří matici, přečtením ze souboru.
- 'file': název souboru
- 'delimiter': oddělovací znak
- vrací ukazatel na přečtenou matici

**void save_to_file(matrix\* mat, const char\* file, char delimiter);**
Uloží matici do souboru.
- 'mat': ukazatel na matici
- 'file': název souboru
- 'delimiter': oddělovací znak
