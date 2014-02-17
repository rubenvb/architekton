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
CONFIG += c++11
CONFIG += debug_and_release

OTHER_FILES += Codestyle.txt \
    architekton.architekton.txt \
    CMakeLists.txt \
    blueprints/architectures.blueprint.txt \
    blueprints/toolchains.blueprint.txt \
    blueprints/OSes.blueprint.txt

# mess to work with *.c++ extension
QMAKE_EXT_CPP = .c++
QMAKE_EXT_H = .h++
*msvc*:QMAKE_CPPFLAGS += /Tp # doesn't work :(
*g++*:QMAKE_CXXFLAGS += -pedantic-errors -Wextra \#-Werror \
                        -Winit-self -Wmissing-include-dirs \
                        -Wstrict-aliasing \
                        -Wno-unused-local-typedefs # Boost.Concept 1.55.0 problem

INCLUDEPATH += .
win32*:INCLUDEPATH += M:\Development\boost_1_55_0

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
    string.c++ \
    blueprint_loaders.c++ \
    options.c++

HEADERS += \
    architekton/global.h++ \
    architekton/options.h++ \
    architekton/target.h++ \
    architekton/project.h++ \
    architekton/external.h++ \
    architekton/commandline.h++ \
    architekton/error.h++ \
    architekton/string.h++ \
    architekton/print.h++ \
    architekton/make_unique.h++ \
    architekton/file.h++ \
    architekton/debug.h++ \
    architekton/types.h++ \
    architekton/blueprint_loaders.h++ \
    architekton/assert.h++
