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
 * Class and function implementations.
 **/

#include "architekton/debug.h++"
#include "architekton/error.h++"
#include "architekton/file.h++"
#include "architekton/string.h++"

#include <ctime>
  using std::time_t;
#include <fstream>
  using std::ifstream;
  using std::ofstream;
#include <iostream>
  using std::istream;
  using std::ostream;
#include <memory>
  using std::unique_ptr;

#ifdef _WIN32
#ifndef WIN32_MEAN_AND_LEAN
#define WIN32_MEAN_AND_LEAN
#endif
#include <windows.h>
#undef WIN32_MEAN_AND_LEAN
#else
#include <dirent.h>
#include <fnmatch.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

namespace architekton
{

string current_working_directory()
{
  string cwd(256); // ooh, magic number!
  while(cwd.size() < 1024*1024) // more magic numbers!
  {
#ifdef _WIN32
    DWORD result = GetCurrentDirectoryW(static_cast<DWORD>(cwd.size()), cwd.raw());
#else
    char* result = getcwd(cwd.raw(), cwd.size());
#endif
    if(result != 0) // nullptr (Unix) or 0 (Windows)
      break;
  }
  return cwd;
}
bool directory_exists(const string& name)
{
  debug_print(debug::utility, "directory_exists called on ", name);
#ifdef _WIN32
  DWORD attributes = GetFileAttributesW(name.raw());
  return (attributes != INVALID_FILE_ATTRIBUTES
          && (attributes & FILE_ATTRIBUTE_DIRECTORY));
#else
  struct stat info;
  if(stat(name.raw(), &info) == 0)
    return S_ISDIR(info.st_mode);
  else
    return false;
#endif
}

bool file_exists(const string& name)
{
  debug_print(debug::utility, "file_exists called on ", name);
#ifdef _WIN32
  DWORD attributes = GetFileAttributesW(name.raw());
  return (attributes != INVALID_FILE_ATTRIBUTES
          && !(attributes & FILE_ATTRIBUTE_DIRECTORY));
#else
  struct stat info;
  if(stat(name.raw(), &info) == 0)
    return S_ISREG(info.st_mode);
  else
    return false;
#endif
}

file_set find_files(const string& directory,
                    const string& pattern)
{
  file_set files;
#ifdef _WIN32
  WIN32_FIND_DATAW data;
  const string filename = //"\\\\?\\" + current_working_directory() +
                          directory / pattern;

  HANDLE result = FindFirstFileW(filename.raw(), &data);
  if(result == INVALID_HANDLE_VALUE)
    throw error("Cannot find file: " + filename);

  do
  {
    debug_print(debug::utility, "Found file or directory: \'", data.cFileName, "\'.");
    if(!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
    {
      debug_print(debug::utility, "Found file: \'", data.cFileName, "\'.");
      files.insert(file(data.cFileName, data.ftLastWriteTime));
    }
  } while(FindNextFileW(result, &data) != 0);
#else
  // TODO implement for Unix
  // use fnmatch for wildcard matching
  DIR* dir = opendir(directory.raw());

  if(dir == nullptr)
    throw error("Unable to open directory: " + directory);

  const string filename = directory / pattern;
  for(dirent* entry = readdir(dir); entry != nullptr; entry = readdir(dir))
  {
    // skip . and ..
    if(string(entry->d_name) == "." || string(entry->d_name) == "..")
      continue;

    struct stat attributes;
    const string entry_name = directory / entry->d_name;
    if(stat(entry_name.raw(), &attributes) == -1)
      throw error("Stat call failed for: \'" + entry_name + "\'.");

    debug_print(debug::utility, "Found file or directory: \'", entry_name);
    if(S_ISREG(attributes.st_mode))
    {
      debug_print(debug::utility, "Matching \'", filename, "\' to \'", entry_name.raw(), "\'.");
      if(fnmatch(filename.raw(), entry_name.raw(), FNM_PATHNAME) == 0)
      {
        debug_print(debug::utility, "Match found.");
        files.insert(file(entry->d_name, attributes.st_mtime));
      }
    }
  }
#endif
  return files;
}

#ifdef _WIN32
time_t filetime_to_time_t(FILETIME ft)
{
  ULARGE_INTEGER ull;
  ull.LowPart = ft.dwLowDateTime;
  ull.HighPart = ft.dwHighDateTime;
  return time_t(ull.QuadPart / 10000000ULL - 11644473600ULL); // yay magic numbers!
}
# ifdef __GLIBCXX__
#include <ext/stdio_filebuf.h>
unique_ptr<istream> open_ifstream(const file& file)
{
  FILE* c_file = _wfopen(file.name.raw(), L"r");
  __gnu_cxx::stdio_filebuf<char>* buffer = new __gnu_cxx::stdio_filebuf<char>(c_file, std::ios_base::in, 1);

  return unique_ptr<istream>(new istream(buffer));
}
unique_ptr<ostream> open_ofstream(const file& file)
{
  FILE* c_file = _wfopen(file.name.raw(), L"w+");
  __gnu_cxx::stdio_filebuf<char>* buffer = new __gnu_cxx::stdio_filebuf<char>(c_file, std::ios_base::out, 1);

  return unique_ptr<ostream>(new ostream(buffer));
}
# elif defined(_MSC_VER)
unique_ptr<istream> open_ifstream(const file& file)
{
  return unique_ptr<istream>(new ifstream(file.name.raw()));
}
unique_ptr<ostream> open_ofstream(const file& file)
{
  return unique_ptr<ostream>(new ofstream(file.name.raw()));
}
# else
#error unknown fstream implementation - no unicode filename support
# endif
#else
unique_ptr<istream> open_ifstream(const file& file)
{
  return unique_ptr<istream>(new ifstream(file.name.raw()));
}
unique_ptr<ostream> open_ofstream(const file& file)
{
  return unique_ptr<ostream>(new ofstream(file.name.raw()));
}
#endif

} // namespace architekton