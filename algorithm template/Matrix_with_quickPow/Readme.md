# Matrix with quickPow Guideline

### Tips
This template can solve Fibonacci sequence use quickPow.

### IO
This template support IO of matrix
```C++
Matrix x;
MatrixRead(x); // input a matrix
MatrixPrint(x); // output a matrix
```
### Standard Matrix
This template support standard matrix
```C++
Matrix e;
initE(e, r, c); // initialize 'e' to standard matrix
```
### Mathematical Operation
This template support check and some operation
```C++
Matrix a, b;
int c;
checkTimes(a, b); // check a * b, return bool
checkAdd(a, b); // check a + b, return bool
a * b; // matrix times matrix
a * c; // matrix times integer
a + b; // matrix add matrix
a - b; // matrix minus matrix
quickPow(a, c); // matrix to the power of integer
```