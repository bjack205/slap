.. slap documentation master file, created by
   sphinx-quickstart on Sat Jan 14 08:21:04 2023.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to slap's documentation!
================================

.. toctree::
   :maxdepth: 2
   :caption: Contents:


Why a library for **s**\ imple **l**\ inear **a**\ lgebra **p**\ rotocols?
Sometimes you just need something simple. Something you can understand.
Something you can debug. Something that just works.

When it comes to linear algebra in C, the go-to options are often huge
dependencies, difficult to install, hard to learn, and difficult to read.
(I'm looking at you, BLAS, like who would guess that ``potrf`` is a Cholesky
decomposition?)


Priorities
==========
While most linear algebra packages prioritize speed and performance (often at the
cost of everything else), this library prioritizes the following:

1. **Simplicity**: a new-comer should be able to start using it effectively within 10-30 minutes.
2. **Readability**: code using this library should be easy to read and follow
3. **Debugging**: it should be easy to step through and quickly find and fix errors.
4. **Lightweight**: it should be able to be used on almost any platform, especially those with limited compute

Key Design Principles
=====================
The library uses the following design principles:

#. Matrices are stored in a column-major format
#. All matrices are a single data type (``double``)
#. Matrices have a row stride of 1 (all elements in a column are adjacent in memory)
#. A matrix is just a pointer with some metadata
#. A matrix (as just a pointer with some metadata) is passed by value
#. Memory is owned by the user, and is never allocated by the library (except by the explicit ``NewMatrix`` and ``FreeMatrix`` commands)
#. Error checking is primarily the responsibility of the user, since extensive error checking is computationally expensive
  (especially for low-level functions like indexing)


Table of Contents
=================
.. toctree::
   :maxdepth: 2

   src/getting_started
   src/installation
   src/matrix_overview
   src/initialization
   src/indexing
   src/basic_ops
   src/linear_algebra
   src/api
   src/documentation

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`