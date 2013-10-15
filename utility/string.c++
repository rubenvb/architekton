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
 * architekton - string.c++
 *
 **/

#include "architekton/utility/string.h++"

namespace architekton
{
namespace utility
{

string string::substr(size_type pos,
                      size_type count) const
{
  string result;
  if(count == npos)
    count = size();

  result.reserve(count-pos+1);
  for(size_type i = pos; pos < data.size() && pos < count; ++i)
    result.data.push_back(data[i]);

  //print(data.back(), "\n");
  //result.data.push_back('\0');

  return result;
}

std::pair<string, string> string::split(size_type start,
                                        char_type split)
{
  const auto index = find(split);
  return { substr(start, index), substr(index, string::npos)};
}

string::size_type string::find(char_type c,
                               size_type pos) const
{
  auto result = std::find(std::begin(data)+pos, std::end(data), c);
  if(result != std::end(data))
    return std::distance(std::begin(data), result);
  else
    return npos;
}

string operator+(const string& lhs, const string& rhs)
{
  debug_print(debug::utility, "operator+ called on strings \'", lhs, "\' and \'", rhs, "\'.\n");
  string result(lhs.size()+rhs.size()-1);
  std::copy(std::begin(lhs), std::end(lhs)-1, std::begin(result));

  std::copy(std::begin(rhs), std::end(rhs), std::begin(result)+lhs.size()-1);

  return result;
}

} // namespace utility

} // namespace architekton
