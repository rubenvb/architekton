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
 * architekton - file.c++
 * Class and function implementation.
 **/

#include "architekton/utility/file.h++"

#ifdef _WIN32
#ifndef WIN32_MEAN_AND_LEAN
#define WIN32_MEAN_AND_LEAN
#endif
#include <windows.h>
#undef WIN32_MEAN_AND_LEAN
#endif

namespace architekton
{
namespace utility
{

bool directory_exists(const ustring& name)
{
#ifdef _WIN32
  DWORD attributes = GetFileAttributesW(name.c_str());
  return (attributes != INVALID_FILE_ATTRIBUTES
          && (attributes & FILE_ATTRIBUTE_DIRECTORY));
#else
  stat info;
  if(stat(name.c_str(), &info) == 0)
    return false;
  else
    return S_ISDIR(info.st_mode);
#endif
}

bool file_exists(const ustring& name)
{
#ifdef _WIN32
  DWORD attributes = GetFileAttributesW(name.c_str());
  return (attributes != INVALID_FILE_ATTRIBUTES
          && !(attributes & FILE_ATTRIBUTE_DIRECTORY));
#else
  stat info;
  if(stat(name.c_str(), &info) == 0)
    return false;
  else
    return S_ISREG(info.st_mode);
#endif
}

file::file(const ustring& /*filename*/)
{}

} // namespace utility

} // namespace architekton

