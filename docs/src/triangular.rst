Triangular Matrices
===================

This pages describes the methods for working with triangular matrices.

Triangular matrices are matrices that have all entries below or above the
diagonal equal to zero.  The following methods are available for working
with triangular matrices:

================================== =============================================
Method                             Description
================================== =============================================
:cpp:func:`slap_CheckUpperTri`     Check if a matrix is upper triangular
:cpp:func:`slap_CheckLowerTri`     Check if a matrix is lower triangular
:cpp:func:`slap_UpperTri`          Specify a matrix as upper triangular
:cpp:func:`slap_LowerTri`          Specify a matrix as lower triangular
:cpp:func:`slap_MakeUpperTri`      Make a matrix upper triangular
:cpp:func:`slap_MakeLowerTri`      Make a matrix lower triangular
:cpp:func:`slap_UpperTriMulAdd`    Multiply and add to a matrix with upper triangular
:cpp:func:`slap_LowerTriMulAdd`    Multiply and add to a matrix with lower triangular
:cpp:func:`slap_TriSolve`          Solve a triangular system of equations
================================== =============================================

Note there are two different options to work with triangular matrices:
1. Set the `slap_MatrixType` to either `slap_UpperTri` or `slap_LowerTri`.
   For supported operations (like :cpp:func:`slap_MatMulAdd`) this will simply
   ignore the entries below or above the diagonal.  This is the preferred
   method.
2. Use `slap_MakeUpperTri` or `slap_MakeLowerTri` to make a matrix upper or
   lower triangular.  This will set the entries below or above the diagonal
   to zero. This method works for all operations, but is slower than the
   first option, which ignores the entries below or above the diagonal entirely.