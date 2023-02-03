Matrix Initialization
=====================

Here we cover the handful of ways ``slap`` provides for initializing matrices.

From an Array
-------------
As a lightweight wrapper around a raw ``double*``, :cpp:struct:`Matrix` is best
initialized from a pointer, along with the size information:

.. doxygenfunction:: slap_MatrixFromArray

It is often convenient to allocated storage for multiple arrays all at once, so that the memory
is all stored contiguously on the heap. The following method is more convenient for working with
memory buffers, since the pointer is automatically advanced by the size of the matrix.

.. doxygenfunction:: slap_MatrixFromBuffer

Default Initialization
----------------------
A "default initialized" matrix is considered a "Null" matrix, a internally-defined
state (that has a NULL pointer, 0 size, etc.). Use the following methods for
creating and checking for Null matrices:

.. doxygenfunction:: slap_NullMatrix

.. doxygenfunction:: slap_SetNull

.. doxygenfunction:: slap_IsNull

Allocating Initialization
-------------------------
While all methods in ``slap`` assumes the user owns the underlying data, these methods
provide some convenient methods for initializing matrices on the heap.

.. doxygenfunction:: slap_NewMatrix

.. doxygenfunction:: slap_NewMatrixZeros

.. doxygenfunction:: slap_FreeMatrix

.. note:: These functions are **NOT** included by default when including ``slap/slap.h``,
          and must be explicitly brought in by including ``slap/new_matrix.h``
