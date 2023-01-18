.. _matrix-basics:
Matrix Basics
=============================

This page covers the basics of the matrix struct in ``slap`` and
several of the fundamental operations.

The ``Matrix`` struct
---------------------

In ``slap``, a matrix is a lightweight ``struct`` (and matching ``typedef``) that
holds the pointer to the start of the matrix, along with some additional meta
for things like the size, stride, and type.

.. doxygenstruct:: Matrix

The underlying data pointer should be accessed via the getter:

.. doxygenfunction:: slap_GetData

.. warning:: The fields of a :cpp:struct:`Matrix` *should be considered private* and
             are not meant to be directly altered. Please use the function API, as the
             internal representation of the API is subject to change in future versions.

Size Information
----------------
The following functions are useful for obtaining information about the
size of a matrix. Please use these functions over directly accessing the
fields of the :cpp:struct:`Matrix` type. All size information in ``slap``
is represented by the ``int`` type.


======================================== ==========================================================
Name                                     Description
======================================== ==========================================================
:cpp:func:`slap_NumRows`                 Get the number of rows (:math:`m`)
:cpp:func:`slap_NumCols`                 Get the number of columns  (:math:`n`)
:cpp:func:`slap_NumElements`             Get the number of elements  (:math:`m * n`)
:cpp:func:`slap_Stride`                  Get the column stride of the matrix
:cpp:func:`slap_MinDim`                  Get the number of elements  (:math:`\text{min}(m, n)`)
:cpp:func:`slap_IsEmpty`                 True if either dimension is zero
:cpp:func:`slap_IsSquare`                True if dimensions are equal
======================================== ==========================================================

.. note:: In the future, the default type used for size information might be
          set by the user as a CMake variable.

Boolean Checks
--------------
Use the following functions to perform various checks on a matrix.

======================================== ==========================================================
Name                                     Description
======================================== ==========================================================
:cpp:func:`slap_IsTransposed`            Checks if the matrix is transposed.
:cpp:func:`slap_IsDense`                 Checks if memory is contiguous (default stride)
:cpp:func:`slap_IsNull`                  Checks if the matrix is a default-initialized Null matrix
:cpp:func:`slap_IsValid`                 Checks if the data pointer for a matrix is valid
======================================== ==========================================================
