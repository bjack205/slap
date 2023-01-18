Linear Algebra
==============

Matrix Multiplication
---------------------
For general matrix multiplication, use the following:

.. doxygenfunction:: slap_MatMulAdd


The following methods are specializations for performance, and are meant to be used
**ONLY WITH DENSE ARRAYS** that are **NOT TRANSPOSED**. Since the general indexing
functions (like :cpp:func:`slap_Cart2Index`) take both striding and transposes into
account they bring some overhead. For maximum performance, the following methods
discard the information from :cpp:func:`slap_IsTransposed` and :cpp:func:`slap_Stride`
and should be used with caution:

.. doxygenfunction:: slap_MatMulAB

.. doxygenfunction:: slap_MatMulAtB


Solving Linear Systems
----------------------

Currently, only positive-definite systems are supported, via a Cholesky decomposition.

The following example shows the basic flow for solving a linear system:

.. code-block:: c

    // Make a positive-definite matrix
    Matrix A2 = slap_NewMatrix(3, 3);
    slap_MatMulAtB(A2, A, A);    // make it positive semi-definite
    slap_AddIdentity(A2, 1e-6);  // make it positive-definite
    slap_MatrixCopy(A, A2);      // copy back to A (used later)

    // Cholesky Decomposition
    slap_ErrorCode err;
    err = slap_Cholesky(A);
    if (err == SLAP_CHOLESKY_FAIL) {
        printf("Matrix is not Positive-Definite!\n");
    }

    // Solve linear system
    Matrix x = slap_NewMatrix(3, 1);
    slap_MatrixCopy(x, b);       // copy rhs vector to solution
    slap_CholeskySolve(A, x);

    // Check Solution
    Matrix y = slap_NewMatrix(3, 1);
    slap_MatMulAB(y, A, x);
    double err = slap_MatrixNormedDifference(y, b);

.. doxygenfunction:: slap_Cholesky

.. doxygenfunction:: slap_CholeskySolve
