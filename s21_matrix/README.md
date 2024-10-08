# s21_matrix
В данном проекте нужно было реализовать свою библиотеку для обработки числовых матриц на языке программирования С.

Структура матрицы:
```c
typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;
```


## Операции которые были реализованы

Все операции (кроме сравнения матриц) возвращают результирующий код:
- 0 - OK
- 1 - Ошибка, некорректная матрица   
- 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой нельзя провести вычисления и т.д.)

### Создание матриц (create_matrix)

```c
int s21_create_matrix(int rows, int columns, matrix_t *result);
```

### Очистка матриц (remove_matrix)

```c
void s21_remove_matrix(matrix_t *A);
```

### Сравнение матриц (eq_matrix)

```c
#define SUCCESS 1
#define FAILURE 0

int s21_eq_matrix(matrix_t *A, matrix_t *B);
```
### Сложение (sum_matrix) и вычитание матриц (sub_matrix)

```c
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
```

### Умножение матрицы на число (mult_number). Умножение двух матриц (mult_matrix)

```c
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
```

### Транспонирование матрицы (transpose)

```c
int s21_transpose(matrix_t *A, matrix_t *result);
```

### Минор матрицы и матрица алгебраических дополнений (calc_complements)

```c
int s21_calc_complements(matrix_t *A, matrix_t *result);
```

### Определитель матрицы (determinant)

```c
int s21_determinant(matrix_t *A, double *result);
```

### Обратная матрица (inverse_matrix)

```c
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
```

## Сборка библиотеки
```
make
```

## Запуск тестов
Для тестов использовалась библиотека check: https://github.com/libcheck/check
```
make test
```

## Структура проекта
```
s21_matrix
├── README.md
└── src
    ├── Makefile
    ├── s21_matrix.c
    ├── s21_matrix.h
    ├── s21_matrix_help.c
    └── test
        ├── logs
        ├── s21_help_func_test.c
        ├── test_s21_calc_complements.c
        ├── test_s21_create_remove_matrix.c
        ├── test_s21_determinant.c
        ├── test_s21_eq_matrix.c
        ├── test_s21_inverse_matrix.c
        ├── test_s21_matrix.c
        ├── test_s21_matrix.h
        ├── test_s21_mult_matrix.c
        ├── test_s21_mult_number.c
        ├── test_s21_sub_matrix.c
        ├── test_s21_sum_matrix.c
        └── test_s21_transpose.c
```
