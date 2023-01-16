Matrix Initialization
=====================

Here we cover the handful of ways ``slap`` provides for initializing matrices.

From an Array
-------------
As a lightweight wrapper around a raw ``double*``, :cpp:struct:`Matrix` is best
initialized from a pointer, along with the size information:

.. doxygenfunction:: slap_MatrixFromArray

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
