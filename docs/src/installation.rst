Installation
============

This library currently supports the following mechanisms for incorporating
it as a dependency in your C (or C++) project

#. CMake ``FetchContent``.
#. `CPM <https://github.com/cpm-cmake/CPM.cmake>`_.

While many libraries support local "installation" into system directories,
as a lightweight library, ``slap`` is meant to be downloaded directly into
the source project to be added as a dependency. This "new" way of using
libraries has many advantages over the traditional method of locally installing
all dependencies.

FetchContent
------------
Add the following to your ``CMakeLists.txt``

.. code-block:: cmake

    include(FetchContent)
    FetchContent_Declare(slap
        GIT_REPOSITORY https://github.com/bjack205/slap
        GIT_TAG main
    )
    FetchContent_MakeAvailable(slap)

    add_executable(main main.c)
    target_link_libraries(main PRIVATE slap::slap)

CPM
----

Add the following to your ``CMakeLists.txt``

.. code-block:: cmake

    include(CPM.cmake)
    CPMAddPackage("gh:bjack205/slap#main")

    add_executable(main main.c)
    target_link_libraries(main PRIVATE slap::slap)
