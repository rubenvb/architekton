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

CONFIG += debug_and_release

OTHER_FILES += Codestyle.txt

# mess to work with *.c++ extension
QMAKE_EXT_CPP = .c++
*msvc*:QMAKE_CXXFLAGS += /Tp
*g++*:QMAKE_CXXFLAGS += -std=c++0x -pedantic
#*win32*:LIBS += -lshell32

CONFIG(debug, debug|release)
{
  DEFINES += ARCHITEKTON_DEBUG
}

SOURCES += \
    main.c++ \
    utility/debug.c++ \
    error.c++ \
    types.c++ \
    utility/commandline.c++ \
    utility/string.c++ \
    utility/file.c++

HEADERS += \
    architekton/utility.h++ \
    architekton/utility/print.h++ \
    architekton/utility/debug.h++ \
    architekton/utility/make_unique.h++ \
    architekton/utility/commandline.h++ \
    architekton/global.h++ \
    architekton/types.h++ \
    architekton/error.h++ \
    architekton/utility/string.h++ \
    architekton/options.h++ \
    architekton/utility/file.h++