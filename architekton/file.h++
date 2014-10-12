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
 * architekton - file.h++
 * File/directory abstraction and helper functions.
 **/

#ifndef ARCHITEKTON_FILE_H
#define ARCHITEKTON_FILE_H

#include "architekton/global.h++"

#include "architekton/types.h++"

#include <ctime>
#include <iostream>
#include <memory>
#include <string>

#ifdef _WIN32
#ifndef WIN32_MEAN_AND_LEAN
#define WIN32_MEAN_AND_LEAN
#endif
#include <windows.h>
#undef WIN32_MEAN_AND_LEAN
#endif

namespace architekton
{

extern const std::string original_working_directory; // original working directory
std::string current_working_directory();

#ifdef _WIN32
std::time_t filetime_to_time_t(FILETIME ft);
#endif

bool directory_exists(const std::string& name);

bool file_exists(const std::string& name);

file_set find_files(const std::string& directory,
                    const std::string& pattern = "");

struct file
{
  file(std::string filename,
#ifdef _WIN32
       FILETIME last_modified)
  : name(filename), last_modified(filetime_to_time_t(last_modified)) {}
#else
       time_t last_modified = 0)
    : name(filename), last_modified(last_modified) {}
#endif

  bool operator<(const file& rhs) const { return name < rhs.name; }

  const std::string name;
  time_t last_modified;
};

// File stream opening wrappers for better Unicode filename support (Windows)
std::unique_ptr<std::istream> open_ifstream(const file& file);
std::unique_ptr<std::ostream> open_ofstream(const file& file);

} // namespace architekton

#endif // ARCHITEKTON_FILE_H
