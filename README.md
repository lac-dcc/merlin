# Merlin 

<p align="center">
  <img alt="merlin drawing" src="assets/img/repoBanner.png" width="95%" height="auto"/></br>
</p>

## Introduction
Merlin is a tool that tries to infer the computational cost of C/C++ programs using polynomial interpolation. Merlin consists of two parts: a
`clang` plugin that adds instrumentation to programs by inserting counters, and a polynomial interpolator that uses the information generated by instrumentation to find a curve relating program inputs with computational cost. The figure below gives an overview of how Merlin works. For more details, check out our [paper](https://homepages.dcc.ufmg.br/~fernando/publications/papers/Merlin.pdf).
<p align="center">
  <img alt="merlin overview" src="assets/img/MerlinOverview.png" width="65%" height="auto"/></br>
</p>

### Instrumentation
Merlin's instrumentation was implemented as a `clang` plugin that inserts counters inside loops bodies to count the number of iterations required by a program. The resulting program after instrumentation generate output in `stdout` that is used by Merlin's interpolator to find a curve that describes the computational cost of that program.

### Interpolation
Merlin, when dealing with programs influenced by a single input variable, uses [Newton's Divided Differences](https://en.wikipedia.org/wiki/Newton_polynomial) method for interpolating data points to find polynomials that fit the given data exactly. However, when dealing with programs costs that are influenced by multiple variables, Merlin uses the [least squares method](https://en.wikipedia.org/wiki/Linear_least_squares) to find good approximations for the function costs of the programs.

## Building 
To compile the instrumentation, access the script `merlin/instrumentation/scripts/setup.sh` and set the variable `LLVM_BUILD_DIR` to the directory where LLVM is built on your computer. Then, in the `merlin/instrumentation` directory, execute the script by running `scripts/setup.sh` to create your own build. After that, access the directory `merlin/interpolation` and run `make` to compile the interpolator code.

### Dependencies
These are the most important dependencies for building and running Merlin:

| Dependency | Version   | Installation Link                            |
|------------|-----------|----------------------------------------------|
| LLVM       | >= 14.0.0 | [llvm.org](https://llvm.org/docs/CMake.html) |
| CMake      | >= 3.20   | [cmake.org](https://cmake.org/install/)      |

Building LLVM on your computer may be troublesome. To make things easier, we have made a Docker image with all Merlin's dependencies that is available [here](./docker/).

## Running
To run the instrumentation,  access the script `merlin/instrumentation/scripts/run.sh` and set the variable `LLVM_BUILD_DIR` to the directory where LLVM is built on your computer. Then, in the `merlin/instrumentation` directory, execute the script by running `scripts/run.sh input_file output_file_name target_function`. `input_file` is the directory for the file you want to instrument, `output_file_name` is just the name for the output file, and `target_function` is the name of the function to be instrumented. There are additional optional arguments that can be seen in the script's documentation. After running the instrumentation, the instrumented program will be available in the `output` folder.

## Simplified Execution
Consider the following Matrix Multiplication implementation:
```c++
int matrix_multiplication(int** A, int** B, int** C, int a_row, int a_col, int b_row, int b_col) {
  if (a_col != b_row)
    return 0;
  for (int i = 0; i < a_row; i++) {
    for (int j = 0; j < a_col; j++) {
      for (int k = 0; k < b_col; k++) {
        C[i][k] += A[i][j] * B[j][k];
      }
    }
  }
  return 1;
}
```
We need to add a `main` function in the same file. This function will take input values to test the matrix multiplication. In this case, we can use the following `main` function: 
````c++
int main() { 
    int** A; int** B; int** C;
    int rowsA, colsA, rowsB, colsB;
    cin >> rowsA >> colsA >> rowsB >> colsB;
    
    alocateMatrixNxM(A, rowsA, colsA);
    alocateMatrixNxM(B, rowsB, colsB);
    alocateMatrixNxM(C, rowsA, colsB);
    fillMatrix(A, rowsA, colsA);
    fillMatrix(B, rowsB, colsB);
    cleanMatriz(C, rowsA, colsB);
    matrix_multiplication(A, B, C, rowsA, colsA, rowsB, colsB);
    deleteMatrix(A, rowsA, colsA);
    deleteMatrix(B, rowsB, colsB);
    deleteMatrix(C, rowsA, colsB);

    return 0; 
}
````
After that, we need to create the test bench. The test bench must be in a separeted folder containing all the test files, as the following example: 
```
matrix_multiplication
|_ matrix_multiplication.cpp
|_ tests
. |_ input0.txt
. |_ input1.txt
. |_ input2.txt
. |_ input3.txt
```
In our case, an example of input file contains the matrices constraints, it could be:
```
3 3
3 3
```

Finnaly, all we need to do is to run the script `merlin.sh`. The script `merlin.sh` receives three inputs: the path to the program file, the name of the function we will analyze, and the path to the directory of the test bench. 
To run this script for our matrix_multiplication example, we can do the following:
`merlin.sh matrix_multiplication/matrix_multiplication.cpp matrix_multiplication matrix_multiplication/tests`

Merlin will emit the following result for this example: 
```
At line 19 : a_row              --> Program Point analysed 
x: a_row                        --> Variable represented by x
Expected Nesting Depth: 1
F(x) = x                        --> Interpolated function for the Program Point

At line 20 : a_col a_row        --> Program Point analysed 
x: a_col                        --> Variable represented by x
y: a_row                        --> Variable represented by y
Expected Nesting Depth: 2
F(x, y) = 1*xy                  --> Interpolated function for the Program Point

At line 21 : b_col a_col a_row  --> Program Point analysed 
x: b_col                        --> Variable represented by x
y: a_col                        --> Variable represented by y
z: a_row                        --> Variable represented by z
Expected Nesting Depth: 3
F(x, y, z) = 1*xyz              --> Interpolated function for the Program Point
````

### Step By Step 
Consider the following Bubble Sort algorithm implementation:
```c++
void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void bubble_sort(int n, int *arr) {
  int i = 0;
  while (i < n) {
    int j = i + 1;
    while (j < n) {
      if (arr[j] < arr[i])
        swap(&arr[i], &arr[j]);
      j++;
    }
    i++;
  }
}
```

After instrumenting this code by using `scripts/run.sh BubbleSort.c BubbleSort.c bubble_sort`, the following instrumented code is generated:
``` c++
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void bubble_sort(int n, int *arr) {
  unsigned counterbubble_sort0 = 0;
  unsigned counterbubble_sort1 = 0;

  int tempn = n;

  int i = 0;
  while (i < n) {
    counterbubble_sort0++;
    int j = i + 1;
    while (j < n) {
      counterbubble_sort1++;
      if (arr[j] < arr[i]) { // compare
        swap(&arr[i], &arr[j]);
      }
      j++;
    }
    i++;
  }

  printf("Number of counters: 2\n");
  printf("At line 9 :");
  printf(" n\n");
  printf("Nesting depth: 1\n");
  printf("At line 11 :");
  printf(" n\n");
  printf("Nesting depth: 2\n");
  printf("%d %d\n", tempn, counterbubble_sort0);
  printf("%d %d\n", tempn, counterbubble_sort1);
  printf("\nend\n");
}
```

Having instrumented the code, our subsequent task involves compiling the program and executing it using a range of input entries. This is essential for generating the necessary sample data, which will be used for conducting the interpolation. Specifically, the code was executed for the following input values:

``` c++
int main() {
  int v1[5] = {1, 2, 3, 4, 5};
  int v2[3] = {1, 2, 3};
  int v3[7] = {1, 2, 3, 4, 5, 6, 7};
  int v4[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  bubble_sort(5, v1);
  bubble_sort(3, v2);
  bubble_sort(7, v3);
  bubble_sort(10, v4);
  return 0;
}
```

By compiling and running the program with these specific inputs, we obtained the following results:
```
Number of counters: 2
At line 9 : n
Nesting depth: 1
At line 11 : n
Nesting depth: 2
5 5
5 10

end
Number of counters: 2
At line 9 : n
Nesting depth: 1
At line 11 : n
Nesting depth: 2
3 3
3 3

end
Number of counters: 2
At line 9 : n
Nesting depth: 1
At line 11 : n
Nesting depth: 2
7 7
7 21

end
Number of counters: 2
At line 9 : n
Nesting depth: 1
At line 11 : n
Nesting depth: 2
10 10
10 45

end
```
In order to perform the interpolation on this data, it is essential to eliminate any repetitions in both the counter numbers and the program point indications. Additionally, you should include the number of points being used after the number of counters. In this case, we are utilizing three points for the interpolation. You can use the script `produceInput.py` in the interpolation directory to execute this task automatically. You can use this script as follows: `python3 produceInput.py programOutput.txt interpolationInput.txt`.
The first argument is the name of the program output and the second argument is the desired name of the interpolation input. After running this script, the interpolation input will look like this:
```
2
3
At line 9 : n
Nesting depth: 1
At line 11 : n
Nesting depth: 2
5 5
5 10
3 3
3 3
7 7
7 21
```

You can generate the interpolations using the compiled interpolator by running the command, in the `interpolation` directory, `bin/interpolator < input/bubbleSortData.txt`. When this command is executed, it produces the following result:
```
At line 9 : n
x: n
Expected Nesting Depth: 1
F(x) = x

At line 11 : n
x: n
Expected Nesting Depth: 2
F(x) = 0.5*x*(x - 1)
```

This output indicates the following:
```
At line 9 : n           --> Program Point analysed 
x: n                    --> Variable represented by x
Expected Nesting Depth: 1
F(x) = x                --> Interpolated function for the Program Point

At line 11 : n          --> Program Point analysed 
x: n                    --> Variable represented by x
Expected Nesting Depth: 2
F(x) = 0.5*x*(x - 1)    --> Interpolated function for the Program Point
```
In this case, the first program point is the outer while statement, which is influenced by the variable `n` and has the cost function `F(n) = n`. For the second program point, representing the inner while statement, which is solely influenced by the variable `n`, the cost function is `F(n) = 0.5 * n * (n - 1)`.

## Cite this Work

The ideas in this work are described in more details in [this paper](https://homepages.dcc.ufmg.br/~fernando/publications/papers/Merlin.pdf), which was published in the Brazilian Symposium on Programming Languages (SBLP 2023).
You can cite it as follows:

```
@inproceedings{SumitaniSBLP23,
    author = {Rafael Fontes Sumitani and Lucas Victor da Silva Costa and Frederico F. Campos and Fernando Magno Quintao Pereira},
    title = {A Class of Programs that Admit Exact Complexity Analysis via Newton’s Polynomial Interpolation},
    year = {2023},
    publisher = {Association for Computing Machinery},
    booktitle = {Proceedings of the 2023 Brazilian Symposium on Programming Languages},
    location = {Campo Grande, Brazil},
    series = {SBLP'23},
    doi={10.1145/3624309.3624311},
}
```
