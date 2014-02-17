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
class string : private std::vector<char_type, Allocator>
{
  using dtype = std::vector<char_type, Allocator>;
public:
  // types
  using value_type = typename dtype::value_type;
  using allocator_type = typename dtype::allocator_type;
  using size_type = typename dtype::size_type;
  using difference_type = typename dtype::difference_type;
  using reference = typename dtype::reference;
  using const_reference = typename dtype::const_reference;
  using pointer = typename dtype::pointer;
  using const_pointer = typename dtype::const_pointer;
  using iterator = typename dtype::iterator;
  using const_iterator = typename dtype::const_iterator;
  using reverse_iterator = typename dtype::reverse_iterator;
  using const_reverse_iterator = typename dtype::const_reverse_iterator;

#ifdef _WIN32
  // constructable from C-string, assumes ASCII
  template<std::size_t N>
  string(const char c_string[N])
  : vector(c_string, c_string + N+1) {}
#endif

  // Member functions
  void assign(const size_type count,
              value_type value)
  {
    assign(count, value);
    dtype::push_back('\0');
  }
  template<typename InputIterator>
  void assign(InputIterator first,
              InputIterator last)
  {
    dtype::assign(first, last);
    dtype::push_back('\0');
  }
  void assign(std::initializer_list<value_type> ilist)
  {
    dtype::assign(ilist);
    dtype::push_back('\0');
  }
  using dtype::get_allocator;

  // Element access
  using dtype::at;
  using dtype::operator[];
  using dtype::front;
  value_type& back()
  {
    return operator[](size()-2);
  }
  const typename dtype::value_type& back() const
  {
    return operator[](size()-2);
  }
  const typename dtype::value_type* c_str() const
  {
    return &operator[](0);
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
    return empty() || front() == '\0';
  }
  using dtype::size;
  using dtype::max_size;
  size_type length() const
  {
    return size()-1;
  }
  size_type max_length() const
  {
    return max_size()-1;
  }
  void reserve(size_type count)
  {
    dtype::reserve(count+1);
  }
  size_type capacity()
  {
    return dtype::capacity() - 1;
  }
  using dtype::shrink_to_fit;

  // Operations
  void clear()
  {
    dtype::clear();
    dtype::push_back('\0');
  }
  using dtype::insert;
  using dtype::erase;
  void push_back(value_type value)
  {
    assert(dtype::back() == '\0');
    dtype::push_back(value);
    std::swap(dtype::operator[](size()-2), dtype::back());
  }
  value_type pop_back()
  {
    assert(dtype::back() == '\0');
    value_type result;

    std::swap(dtype::operator[](size()-2), dtype::back());
    std::swap(dtype::back(), result);

    return result;
  }
  string& append(size_type count, const char_type value)
  {
    assert(dtype::back() == '\0');
    resize(size()+count, value); // leaves '\0' at new size()-count
    std::swap(operator[](size()-count), dtype::back()); // place '\0' at end
  }
  string& append(const string& other_string)
  {
    assert(dtype::back() == '\0');
    dtype::reserve(size() + other_string.size()-1);
    dtype::insert(end()-1, std::begin(other_string), std::end(other_string));
    return *this;
  }
  string& append(const string& other_string,
                 size_type pos,
                 size_type count)
  {
    return append(other_string.substr(pos, count));
  }
  template<typename InputIterator>
  string& append(InputIterator first, InputIterator last)
  {
    assert(dtype::back() == '\0');
    dtype::reserve(size() + std::distance(first, last));
    dtype::insert(end()-1, first, last);

    if(dtype::back() != '\0')
      dtype::push_back('\0');

    return *this;
  }

  string& operator+=(const string& other_string)
  {
    return append(other_string);
  }

  // compare;
  // replace;
  string substr(size_type pos = 0,
                size_type count = npos) const
  {
    if(pos > size())
    if(count == npos)
    {
      return string(begin() + pos, end());
    }
    size_type end = pos+count;
    assert(end <= size());
    string result = string(begin() + pos, begin()+end);

    return result;
  }
  // copy;
  void resize(size_type new_size,
              value_type value = value_type())
  {
    const size_type old_size = size();
    dtype::resize(new_size, value);
    std::swap(dtype::operator[](old_size), dtype::back());
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
    //TODO
    return npos;
  }

  // rfind;
  // find_first_of;
  // find_first_not_of;
  // find_last_of;
  // find_last_not_of;

  // Constants
  static const constexpr size_type npos = -1;
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
