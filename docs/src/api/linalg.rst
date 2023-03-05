linalg.h
========

.. note:: These files are actually split among multiple header files,
          which are all included by ``linalg.h``


Matrix Multiplication
---------------------
.. doxygenfunction:: slap_MatMulAdd

.. doxygenfunction:: slap_MatMulAB

.. doxygenfunction:: slap_MatMulAtB

.. doxygenfunction:: slap_MatMulAtB

.. doxygenfunction:: slap_LowerTriMulAdd

.. doxygenfunction:: slap_UpperTriMulAdd

Triangular Matrices
-------------------

.. doxygenfunction:: slap_MakeLowerTri

.. doxygenfunction:: slap_MakeUpperTri

.. doxygenfunction:: slap_CheckLowerTri

.. doxygenfunction:: slap_CheckUpperTri

Cholesky
--------
.. doxygenfunction:: slap_Cholesky

.. doxygenfunction:: slap_TriSolve

.. doxygenfunction:: slap_CholeskySolve

QR
----

.. doxygenfile:: qr.h
