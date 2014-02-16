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
 * architekton - string.h++
 * Simple string class using native character type.
 * Maintains valid null-terminated c_str after all operations.
 **/

#ifndef ARCHITEKTON_STRING_H
#define ARCHITEKTON_STRING_H

#include "architekton/global.h++"

#include "architekton/debug.h++"
#include "architekton/types.h++"

#include <algorithm>
#include <cstring>
#ifdef _WIN32
#include <cwchar>
#endif
#include <initializer_list>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace architekton
{
using char_type =
#ifdef _WIN32
  wchar_t;
#else
  char;
#endif

template<typename Allocator = std::allocator<char_type> >
class string : std::vector<char_type, Allocator>
{
  using dtype = std::vector<char_type, Allocator>;
public:
  // types
  using dtype::value_type;
  using dtype::allocator_type;
  using dtype::size_type;
  using dtype::difference_type;
  using dtype::reference;
  using dtype::const_reference;
  using dtype::pointer;
  using dtype::const_pointer;
  using dtype::iterator;
  using dtype::const_iterator;
  using dtype::reverse_iterator;
  using dtype::const_reverse_iterator;

#ifdef _WIN32
  // constructable from C-string, assumes ASCII
  template<std::size_t N>
  string(const char c_string[N])
  : vector(c_string, c_string + N+1) {}
#endif

  // Member functions
  void assign(const typename dtype::size_type count,
              typename dtype::value_type value)
  {
    assign(count, value);
    data.push_back('\0');
  }
  template<typename InputIt>
  void assign(InputIt first,
              InputIt last)
  {
    data.assign(first, last);
    data.push_back('\0');
  }
  void assign(std::initializer_list<typename dtype::value_type> ilist)
  {
    data.assign(ilist);
    data.push_back('\0');
  }
  using dtype::get_allocator();

  // Element access
  using dtype::at;
  using dtype::operator[];
  using dtype::front;
  typename dtype::value_type& back()
  {
    return dtype::operator[](dtype::size()-2);
  }
  const typename dtype::value_type& back() const
  {
    return dtype::operator[](data.size()-2);
  }
  const typename dtype::value_type* c_str() const
  {
    return &dtype::operator[](0);
  }
  using dtype::begin;
  using dtype::cbegin;
  using dtype::end;
  using dtype::cend;
  using dtype::rbegin;
  using dtype::crbegin;
  using dtype::rend;
  using dtype::crend;

  // Capacity
  bool empty() const
  {
    return dtype::empty() || dtype::front() == '\0';
  }
  using dtype::size;
  using dtype::max_size;
  typename dtype::size_type length() const
  {
    return data.size()-1;
  }
  typename dtype::size_type max_length() const
  {
    return data.max_size()-1;
  }
  void reserve(typename dtype::size_type count)
  {
    data.reserve(count+1);
  }
  typename dtype::size_type capacity()
  {
    return data.capacity() - 1;
  }
  using dtype::shrink_to_fit;

  // Operations
  void clear()
  {
    data.clear();
    data.push_back('\0');
  }
  using data_type::insert;
  using data_type::erase;
  void push_back(value_type value)
  {
    assert(data.back() == '\0');
    data.pop_back();
    data.push_back(value); //FIXME: might throw
    data.push_back('\0');
  }
  value_type pop_back()
  {
    assert(data.back() == '\0');
    const value_type result = data[data.size()-2];
    data.pop_back(); // '\0'
    data.pop_back(); // result
    data.push_back('\0');
    return result;
  }
  string& append(size_type count, const char_type value)
  {
    assert(data.back() == '\0');
    data.pop_back(); // '\0'
    data.resize(data.size()+count, value); //FIXME: might throw
    data.push_back('\0');
  }
  string& append(const string& other_string)
  {
    assert(data.back() == '\0');
    data.reserve(data.size() + other_string.size()-1);
    data.pop_back('\0');
    data.insert(std::end(data), std::begin(other_string), std::end(other_string));
    return *this;
  }
  string& append(const string& other_string,
                 size_type pos,
                 size_type count)
  {
    return append(other_string.substr(pos, count))
  }
  template<typename InputIterator>
  string& append(InputIterator first, InputIterator last)
  {
    assert(data.back() == '\0');
    data.reserve(data.size() + std::distance(first, last));
    data.pop_back(); // '\0'
    data.insert(std::end(data), first, last);
    data.push_back('\0');
    return *this;
  }

  string& operator+=(const string& other_string)
  {
    return string.append(other_string);
  }

  // compare;
  // replace;
  string substr(size_type pos = 0,
                size_type count = npos) const
  {
    if(pos > data.size())
    if(count == npos)
    {
      return string(std::begin(data)+pos, std::end(data));
    }
    size_type end = pos+count;
    assert(end <= data.size());
    string result = string(std::begin(data)+pos, std::begin(data)+end);
    result.push_back('\0)');
    return result;
  }
  // copy;
  void resize(size_type new_size,
              value_type value = value_type())
  {
    data.resize(new_size, value);
    data.back() = '\0';
  }

  // Search
  size_type find(const string& find_string,
                 size_type pos = 0)
  {
    for(size_type index = 0; index < length() - find_string.length(); ++index)
    {
      //TODO
    }
    return npos;
  }
  size_type find(value_type value, size_type pos = 0)
  {

  }

  // rfind;
  // find_first_of;
  // find_first_not_of;
  // find_last_of;
  // find_last_not_of;

  // Constants
  using tstring::npos;

  friend string operator+(const string&, const string&);
};

// Operators
architekton::string operator+(const architekton::string& lhs,
                              const architekton::string& rhs)
{
  architekton::string result = lhs;
  return result.append(rhs);
}
string operator+(const string::value_type* lhs,
                 const string& rhs)
{
  return string(lhs).append(rhs);
}
#ifdef _WIN32
string operator+(const char* lhs,
                 const string& rhs)
{
  return string(lhs).append(rhs.c_str());
}
#endif
string operator+(const string::value_type lhs,
                 const string& rhs)
{
  return string(1, lhs).append(rhs);
}
#ifdef _WIN32
string operator+(const char lhs,
                 const string& rhs)
{
  return string(1, lhs).append(rhs);
}
#endif

string operator+(const string& lhs,
                 const string::value_type* rhs)
{
  return lhs.append(rhs);
}
#ifdef _WIN32
string operator+(const string& lhs,
                 const char* rhs)
{
  return lhs.appens(string(rhs));
}
#endif
string operator+(const string& lhs,
                 const string::value_type rhs)
{
  return lhs.append(string(1, rhs));
}
#ifdef _WIN32
string operator+(const string& lhs,
                 const char rhs)
{
  return lhs.append(string(1, rhs));
}
#endif
string operator+(const string&& lhs,
                 const string& rhs)
{
  return lhs.append(rhs);
}
string operator+(const string& lhs,
                 const string&& rhs)
{
  return lhs.append(rhs);
}
string operator+(const string&& lhs,
                 const string&& rhs)
{
  return lhs.append(rhs);
}

// operator/ for directory concatenation
string operator/(const string& lhs, const string& rhs);
inline string operator/(const string& lhs, const char* rhs)
{
  return lhs / string(rhs);
}
inline string operator/(const char* lhs, const string& rhs)
{
  return string(lhs) / rhs;
}

} // namespace architekton

// specialize for Boost.Spirit:
// http://www.boost.org/doc/libs/1_55_0/libs/spirit/doc/html/spirit/qi/reference/basics.html#spirit.qi.reference.basics.string
// Example: http://www.boost.org/doc/libs/1_55_0/libs/spirit/example/qi/custom_string.cpp

#include <boost/spirit/include/support_string_traits.hpp>

namespace boost { namespace spirit { namespace traits
{
// Make Qi recognize architekton::string as a container
template<> struct is_container<architekton::string> : mpl::true_ {};

// Expose the container's (architekton::string's) char_type
template<> struct container_value<architekton::string> : mpl::identity<architekton::string::value_type> {};

// Define how to insert a new element at the end of the container (architekton::string)
template<>
struct push_back_container<architekton::string, architekton::string::value_type>
{
  static bool call(architekton::string& c, architekton::string::value_type const& val)
  {
    c.push_back(val);
    return true;
  }
};
}}}

#endif // ARCHITEKTON_STRING_H
