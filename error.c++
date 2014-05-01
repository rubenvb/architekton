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

error::~error()
{}

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
           "\t" << message.c_str() << "\n";
  if(!list.empty())
    {
      for(auto&& item : list)
      {
        wcerr << "\t" << item.c_str() << "\n";
      }
    }
}

} // namespace architekton
