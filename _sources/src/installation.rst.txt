Installation
============

This library currently supports the following mechanisms for incorporating
it as a dependency in your C (or C++) project
* CMake FetchContent
* CPM

While many libraries support local "installation" into system directories,
as a lightweight library, ``slap`` is meant to be downloaded directly into
the source project to be added as a dependency. This "new" way of using
libraries has many advantages over the traditional method of locally installing
all dependencies.

FetchContent
------------

CPM
----