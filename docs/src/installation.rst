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

Arduino
-------
This repository is compliant with the Arduino library format.
Either clone the repository directly into the system Arduino
library path (if using the IDE), or include it via the ``--library`` or ``--libraries``
flags in the CLI.

For instance, to compile the sketch in ``examples/arduino_slap``
with the Arduino CLI, run the following from inside the ``examples/`` directory:

.. code-block:: shell

    arduino-cli core install arduino:avr
    arduino-cli compile -b arduino:avr:nano --libraries ../.. arduino_slap

To use the library from within an Arduino script, simply include

.. code-block:: c

    #include "slap_arduino.h"

See ``examples/arduino_slap/README.md`` for more details.

.. note::
    This package may be added as an official Arduino library
    package in the future, which will simplify adding it to
    Arduino projects.