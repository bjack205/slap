Linear Algebra
==============

Matrix Multiplication
---------------------
For general matrix multiplication, use :cpp:func:`slap_MatMulAdd`.

It is a 5-argument matrix multiplication of the form:

.. math::
   C = \alpha A B + \beta C

where any of the matrices can be transposed, and :math:`A` and :math:`B` can be aliased.

Here are some examples:

.. code-block:: c
   :linenos:

   // C = A * B
   slap_MatMulAdd(C, A, B, 1, 0);

   // C = A' * B
   slap_MatMulAdd(C, slap_Transpose(A), B, 1, 0);

   // C = A * A' + C
   slap_MatMulAdd(C, A, slap_Transpose(A), 1, 1);

Additionally, the following methods are specializations for performance, and are meant to be used
**ONLY WITH DENSE ARRAYS** that are **NOT TRANSPOSED**. Since the general indexing
functions (like :cpp:func:`slap_Cart2Index`) take both striding and transposes into
account they bring some overhead. For maximum performance, the following methods
discard the information from :cpp:func:`slap_IsTransposed` and :cpp:func:`slap_Stride`
and should be used with caution:

=============================== ========================================
Method                          Description
=============================== ========================================
:cpp:func:`slap_MatMulAB`       Dense matrix multiplication
:cpp:func:`slap_MatMulAtB`      Dense matrix-transposed multiplication
=============================== ========================================


Solving Linear Systems
----------------------

Currently the following linear system solves are supported:

 #. Positive-definite systems via :cpp:func:`slap_Cholesky`
 #. General square systems via :cpp:func:`slap_QR`
 #. Least-squares problems via :cpp:func:`slap_QR` and/or :cpp:func:`slap_LeastSquares`

Here's a summary of the relevant methods provided by `slap`:

=============================== =====================================================================================
Method                          Description
=============================== =====================================================================================
:cpp:func:`slap_TriSolve`       Solve a system with a triangular matrix, using back-substitution
:cpp:func:`slap_Cholesky`       Cholesky decomposition
:cpp:func:`slap_CholeskySolve`  Solve a system with a Cholesky decomposition
:cpp:func:`slap_QR`             "Q-less" QR decomposition via Householder reflections
:cpp:func:`slap_ComputeQ`       Compute the "Q" matrix from a QR decomposition
:cpp:func:`slap_QtB`            Calculate :math:`Q^T b` from a QR decomposition, without forming :math:`Q`.
:cpp:func:`slap_LeastSquares`   Solve a linear system using a QR decomposition, with support for "skinny" matrices.
=============================== =====================================================================================


Cholesky Example
^^^^^^^^^^^^^^^^^
The following example shows the basic flow for solving a linear system using Cholesky:

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


Least Squares Example
^^^^^^^^^^^^^^^^^^^^^
.. code-block:: c
    :linenos:

    // Initialize arrays
    int m = 10;
    int n = 5;
    Matrix A = slap_NewMatrix(m, n);
    Matrix b = slap_NewMatrix(m, 1);
    Matrix betas = slap_NewMatrix(m, 1);
    Matrix temp = slap_NewMatrix(m, 1);

    // Set data for A and b here...

    // Calculate QR decomposition
    //   Stores R in the upper-triangular portion of A
    //   Stores the Householder reflection vectors below the diagonal
    slap_QR(A, betas, temp);

    // Form Q (not usually recommended or needed)
    Matrix Q = slap_NewMatrix(m, m);
    Matrix Q_work = slap_NewMatrix(m, m);  // extra memory needed to form Q
    slap_ComputeQ(Q, A, beta, Q_work);

    // Solve for b
    //   Result is stored in the top n rows of b
    slap_Qtb(A, beta, b);                 // Calculate Q'b, directly from QR factorization
    slap_TriSolve(slap_TriUpper(A), b);

