/**
The MIT License (MIT)

Copyright (c) 2013 Ruben Van Boxem

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 **/

/**
 * architekton - utility.h++
 * Various utilities.
 **/

#ifndef ARCHITEKTON_UTILITY_H
#define ARCHITEKTON_UTILITY_H

#include "architekton/global.h++"

#include "architekton/types.h++"

#include <string>

namespace architekton
{
// string extensions
string_pair split(const std::string& s,
                         char value = ' ',
                         std::string::size_type pos = 0);

std::string operator/(const std::string& left,
                      const std::string& right);

// OS dependent utilities
std::string support_files_location();

#ifdef _WIN32
const std::string convert_to_utf8(const std::wstring& utf16_string);
const std::wstring convert_to_utf16(const std::string& utf8_string);
#endif

}

#endif // ARCHITEKTON_UTILITY_H
