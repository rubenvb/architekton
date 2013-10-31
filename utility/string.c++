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

#include "architekton/utility/debug.h++"

namespace architekton
{
namespace utility
{

string string::substr(size_type pos,
                      size_type count) const
{
  //TODO: make better
  if(pos+count > data.size())
    throw std::out_of_range("substr called for out of range blabla");

  if(count != npos)
  {
    const size_type end = pos+count == data.size() ? pos+count-1 : pos+count;
    return string(&data[pos], &data[end]);
  }
  else
    return string(&data[pos], &data[data.size()-1]);
}

std::pair<string, string> string::split(char_type split,
                                        size_type start)
{
  const auto index = find(split, start);

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

string operator+(const string& left, const string& right)
{
  debug_print(debug::string, "Concatenating strings \'", left, "\' and \'", right, "\'.");
  string result(left.size() + right.size()-1);
  std::copy(std::begin(left), std::end(left)-1, std::begin(result));

  std::copy(std::begin(right), std::end(right), std::begin(result) + left.size()-1);

  debug_print(debug::string, "Result: \'", result, "\'.");
  return result;
}

string operator/(const string& left, const string& right)
{
  debug_print(debug::string, "Concatenating paths: \'", left, "\' and \'", right, "\'.");
  string result;
  if(left.empty())
    result = right;
  else if(right.empty())
    result = left;
  else if('/' == left.back())
    result = left.substr(0,left.size()-2) + "/" + right;
  else
    result = left + "/" + right;

  debug_print(debug::string, "Result: \'", result, "\'.");
  return result;
}

} // namespace utility

} // namespace architekton
