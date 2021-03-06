# The MIT License (MIT)
#
# Copyright (c) 2013 Ruben Van Boxem
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

#
# the architekton project
#

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
win32:CONFIG += debug_and_release # use the debug and release subdirs in a single build directory
DEFINES -= UNICODE

OTHER_FILES += Codestyle.txt \
    architekton.architekton.txt \
    CMakeLists.txt \
    blueprints/architectures.blueprint.txt \
    blueprints/OSes.blueprint.txt \
    blueprints/toolchains.blueprint.txt

# mess to work with *.c++ extension
QMAKE_EXT_CPP = .c++
QMAKE_EXT_H = .h++
#*msvc*:QMAKE_CPPFLAGS += /Tp # doesn't work :(

MY_CXXFLAGS = -std=c++1y -pedantic -Wextra \
              -Winit-self -Wmissing-include-dirs \
              -Wstrict-aliasing
*g++*:QMAKE_CXXFLAGS += $${MY_CXXFLAGS} #-Wno-unused-local-typedefs # Boost.Concept 1.55.0 problem
*clang*:QMAKE_CXXFLAGS += $${MY_CXXFLAGS} -stdlib=libc++
*clang*:QMAKE_LFLAGS += -stdlib=libc++
*clang*:LIBS += -lc++abi
*icc*:QMAKE_CXXFLAGS += $${MY_CXXFLAGS}

INCLUDEPATH += .

CONFIG(debug, debug|release)
{
  DEFINES += ARCHITEKTON_DEBUG
}

SOURCES += \
    main.c++ \
    target.c++ \
    project.c++ \
    external.c++ \
    commandline.c++ \
    error.c++ \
    debug.c++ \
    file.c++ \
    utility.c++ \
    lexer.c++ \
    blueprint_loader.c++ \
    options.c++

HEADERS += \
    architekton/global.h++ \
    architekton/options.h++ \
    architekton/target.h++ \
    architekton/project.h++ \
    architekton/external.h++ \
    architekton/commandline.h++ \
    architekton/error.h++ \
    architekton/print.h++ \
    architekton/file.h++ \
    architekton/debug.h++ \
    architekton/types.h++ \
    architekton/assert.h++ \
    architekton/utility.h++ \
    architekton/lexer.h++ \
    architekton/blueprint_loader.h++ \
    architekton/architecture.h++ \
    architekton/os.h++ \
    architekton/toolchain.h++ \
    architekton/blueprints.h++
