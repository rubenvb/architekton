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
 * architekton - types.h++
 * Various typedefs, including:
 *  - native character type (8-bit on Unix, 16-bit on Windows)
 *  - shorten verbose C++ types
 **/

#ifndef ARCHITEKTON_TYPEDEFS_H
#define ARCHITEKTON_TYPEDEFS_H

#include "architekton/global.h++"

#include <set>
#include <string>
#include <utility>
#include <vector>

namespace architekton
{

// Forward declarations
namespace utility
{
struct file;
class string;
}

using file_set = std::set<utility::file>;
using string_pair = std::pair<utility::string, utility::string>;
using string_set = std::set<utility::string>;
using string_vector = std::vector<utility::string>;

} // namespace architekton

#endif // ARCHITEKTON_TYPEDEFS_H
