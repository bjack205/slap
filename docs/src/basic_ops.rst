Basic Operations
================

This section covers basic operations on matrices, such as multiplication
or addition by a constant, or reshaping and transposing operations.
More advanced methods like matrix multiplication, matrix norms, or
decompositions are covered in :ref:`Linear Algebra`.

Unary Operations
----------------
These operations all operate on the data in the array.



============================== ====================================
Function                       Header
============================== ====================================
:cpp:func:`slap_SetConst`      ``src/unary_opts.h``
:cpp:func:`slap_ScaleByConst`  ``src/unary_ops.h``
:cpp:func:`slap_SetIdentity`   ``src/unary_ops.h``
:cpp:func:`slap_SetDiagonal`   ``src/unary_ops.h``
:cpp:func:`slap_AddIdentity`   ``src/unary_ops.h``
:cpp:func:`slap_SetRange`      ``src/unary_ops.h``
============================== ====================================


Transformations
---------------
These functions leave the array data untouched, but modify the meta-data, changing
the way the data is interpreted by later functions.

==========================  ================
      Method                 Header
==========================  ================
:cpp:func:`slap_Flatten`    ``src/matrix.h``
:cpp:func:`slap_Transpose`  ``src/matrix.h``
:cpp:func:`slap_Reshape`    ``src/matrix.h``
==========================  ================