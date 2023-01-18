Indexing
========

This file covers the indexing operations supported by ``slap``.
All of these functions are low-level and low-overhead functions
that implement little to no error checking, so must be used with
care. It is the responsibility of the user to perform the correct
checks beforehand to avoid undefined behavior (like indexing out of
bounds or de-referencing a NULL pointer).

.. note:: Most of these methods are implemented as static inline functions so avoid
          the cost of the function call (and object copy).

Getters
-------

Use the following functions to obtain a pointer to an element of the matrix:


.. doxygenfunction:: slap_GetElement

.. doxygenfunction:: slap_GetElementConst

.. tip:: The pointer from the first (non-const) function can be used to modify the element.

Setters
-------
Use the following function to directly set elements directly.

.. doxygenfunction:: slap_SetElement


Index Manipulation
------------------
Use the following methods to switch between linear and Cartesian indexing.

**Terminology**:

 * ``Cart``: Cartesian, i.e. row and column
 * ``Linear`` Column-based linear index from ``0`` to ``N-1``, where ``N`` is the output of :cpp:func:`slap_NumElements`
 * ``Index``: Index into the underlying array in memory

 Note that `Linear` and `Index` are the same for a "dense" matrix, and different for a strided matrix.

.. doxygenfunction:: slap_Cart2Index

.. doxygenfunction:: slap_Linear2Index

.. doxygenfunction:: slap_Linear2Cart


Error Checking
--------------
.. doxygenfunction:: slap_CheckInbounds