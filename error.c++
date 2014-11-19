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
 * architekton - error.c++
 * Class implementations.
 **/

#include "architekton/error.h++"

#include "architekton/file.h++"
#include "architekton/types.h++"

#include <iostream>
  using std::wcerr;
#include <string>
  using std::string;

namespace architekton
{

error::error(std::string message,
             const file_set& files)
: message(message),
  list()
{
  list.reserve(files.size());
  for(auto&& item : files)
  {
    list.push_back(item.name);
  }
}

void error::print() const
{
  wcerr << "Error:\n"
           "  " << message.c_str() << "\n";
  if(!list.empty())
    {
      for(auto&& item : list)
      {
        wcerr << "    " << item.c_str() << "\n";
      }
    }
}

void syntax_error::print() const
{
   std::cerr << "Error in: " << filename << "\n"
             << "line: " << std::to_string(line_number) << "\n";
   error::print();
}

#ifdef _WIN32
std::string win32_error_message()
{
  DWORD error = ::GetLastError();
  if(error == 0)
    return "No error message has been recorded";

  //LPWSTR buffer = nullptr;
  std::unique_ptr<char, decltype(&LocalFree)> buffer(nullptr, &LocalFree);
  size_t size = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                               NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&buffer, 0, NULL);

  std::wstring message((wchar_t*)buffer.get(), size);

  //LocalFree(buffer);

  return convert_to_utf8(message);
}
#endif

} // namespace architekton
