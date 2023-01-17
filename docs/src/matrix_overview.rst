.. _matrix-basics:
Matrix Basics
=============================

This page covers the basics of the matrix struct in ``slap`` and
several of the fundamental operations.

In ``slap``, a matrix is a lightweight ``struct`` (and matching ``typedef``) that
holds the pointer to the start of the matrix, along with some additional meta
for things like the size, stride, and type.

.. doxygenstruct:: Matrix

.. warning:: The fields of a :cpp:struct:`Matrix` *should be considered private* and
             are not meant to be directly altered. Please use the function API, as the
             internal representation of the API is subject to change in future versions.

Size Information
----------------
The following functions are useful for obtaining information about the
size of a matrix. Please use these functions over directly accessing the
fields of the :cpp:struct:`Matrix` type. All size information in ``slap``
is represented by the ``int`` type.

.. note:: In the future, the default type used for size information be
          set by the user as a CMake variable.

.. doxygenfunction:: slap_NumRows

.. doxygenfunction:: slap_NumCols

.. doxygenfunction:: slap_NumElements

.. doxygenfunction:: slap_MinDim

.. doxygenfunction:: slap_IsEmpty

.. doxygenfunction:: slap_IsSquare

Boolean Checks
--------------
.. doxygenfunction:: slap_IsTransposed

.. doxygenfunction:: slap_IsDense

.. doxygenfunction:: slap_IsNull

.. doxygenfunction:: slap_IsValid

.. doxygenfunction:: slap_NullMatrix
