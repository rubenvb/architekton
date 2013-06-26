architekton
===========

Master builder. Builds your software reliably and fast. Anything, Anywhere.

Origin and Goals
----------------

This project is an evolved [Ambrosia](https://github.com/rubenvb/Ambrosia),
which grew out of the need for a high-level build system. Current solutions
miss the boat on at least one of the goals set forth for architekton below:
 - strict project description only without build tool information creeping in,
 - execute build commands themselves instead of relying on a next build step,
 - independent of environment; no shell assumptions,
 - easily extensible for new platforms, toolsets, and languages,
 - intuitive, concise syntax that does not require learning a new language,
 - fast rebuilds,
 - ...

Current status
--------------

architekton is currently under heavy development. Help is welcome.
[Ambrosia](https://github.com/rubenvb/Ambrosia), the previous iteration of
architekton, progressed as far as to build itself using the GNU toolchain on
Windows. This means much code can be borrowed and enhanced from there, allowing
for an improved design, while minimizing the effort to rewrite the codebase.

How to use
----------

To use architecton, you need a modern C++11 compiler:
 - MSVC 12.0 (Visual Studio 2013)
 - GCC 4.8
 - Clang 3.3

architecton itself can be built by running one of the following commands:

    cl /Ehsc /O2 *.cpp /Iarchitecton /link /out:architecton
    g++ -std=c++11 -O2 -I"architecton" *.cpp -o architecton
    clang++ -std=c++11 -O2 -I"architecton" *.cpp -o architecton

Once architecton can build itself, you can run

    architekton

and watch the fireworks.
