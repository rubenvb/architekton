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
 * architekton - utility/string.h++
 * Simple string class using native character type.
 **/

#ifndef ARCHITEKTON_STRING_H
#define ARCHITEKTON_STRING_H

#include "architekton/global.h++"
#include "architekton/types.h++"

#include "architekton/utility/debug.h++"

#include <algorithm>
#include <cstring>
#ifdef _WIN32
#include <cwchar>
#endif
#include <utility>
#include <vector>

namespace architekton
{

namespace utility
{

inline std::size_t strlen(const char* c_string)
{
  return std::strlen(c_string);
}
inline std::size_t strlen(const wchar_t* c_string)
{
  return std::wcslen(c_string);
}

class string
{
public:
#ifdef _WIN32
  using char_type = wchar_t;
  string(const wchar_t* c_string)
  : data(c_string, c_string + strlen(c_string)+1) {}
#else
  using char_type = char;
#endif
  using size_type = std::vector<char_type>::size_type;
  using iterator = std::vector<char_type>::iterator;
  using const_iterator = std::vector<char_type>::const_iterator;

  string(size_type size = 0)
  : data(size) {}

  // constructable from plain (ASCII) C-string
  string(const char* c_string)
  : data(c_string, c_string + strlen(c_string)+1) {}

  static constexpr size_type npos = static_cast<size_type>(-1);

  // iteration
  const_iterator begin() const { return data.cbegin(); }
  const_iterator end() const { return data.cend(); }
  iterator begin() { return data.begin(); }
  iterator end() { return data.end(); }

  // raw C string
  char_type* raw() { return &data[0]; }
  const char_type* raw() const { return &data[0]; }

  // size
  size_type size() const { return data.size(); }
  void reserve(const size_type N) { data.reserve(N); }
  bool empty() const { return data.empty(); }

  // element access
  const char_type& operator[](size_type index) const { return data[index]; }
  char_type& operator[](size_type index) { return data[index]; }

  // comparison
  bool operator==(const string& rhs) const { return data == rhs.data; }
  bool operator<(const string& rhs) const { return data < rhs.data; }

  // bits and parts
  string substr(size_type pos,
                size_type count = npos) const;
  std::pair<string, string> split(string::size_type start,
                                  string::char_type split);

  // find
  size_type find(char_type c,
                 size_type pos = 0) const;

  // string& append(char c);
  //string append(const string& s);

private:
  std::vector<char_type> data;
};

// operator<<
inline std::ostream& operator<<(std::ostream& os, const string& s)
{
  return os << s.raw();
}
inline std::wostream& operator<<(std::wostream& os, const string& s)
{
  return os << s.raw();
}

// Operator+
string operator+(const string& lhs, const string& rhs);
inline string operator+(const string& lhs, const char* rhs)
{
  return lhs + string(rhs);
}
inline string operator+(const char* lhs, const string& rhs)
{
  return string(lhs) + rhs;
}

} // namespace utility

} // namespace architekton

#endif // ARCHITEKTON_STRING_H
