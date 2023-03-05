matrix.h
========

Initialization
--------------
.. doxygenfunction:: slap_MatrixFromArray

.. doxygenfunction:: slap_NullMatrix

.. doxygenfunction:: slap_SetNull


Boolean Checks
--------------

.. doxygenfunction:: slap_IsTransposed

.. doxygenfunction:: slap_IsEmpty

.. doxygenfunction:: slap_IsSquare

.. doxygenfunction:: slap_IsDense

.. doxygenfunction:: slap_IsValid

.. doxygenfunction:: slap_IsNull


Dimensions
----------
.. doxygenfunction:: slap_MinDim

.. doxygenfunction:: slap_NumRows

.. doxygenfunction:: slap_NumCols

.. doxygenfunction:: slap_NumElements

.. doxygenfunction:: slap_Stride


Indexing
--------
.. doxygenfunction:: slap_Cart2Index

.. doxygenfunction:: slap_Linear2Cart

.. doxygenfunction:: slap_Linear2Index

.. doxygenfunction:: slap_CheckInbounds

.. doxygenfunction:: slap_GetElement

.. doxygenfunction:: slap_GetElementConst

.. doxygenfunction:: slap_SetElement

Transformations
----------------
.. doxygenfunction:: slap_Flatten

.. doxygenfunction:: slap_Transpose

.. doxygenfunction:: slap_Reshape

.. doxygenfunction:: slap_UpperTri

.. doxygenfunction:: slap_LowerTri

