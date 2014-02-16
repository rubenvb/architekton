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
#include <string>
#include <utility>
#include <vector>

namespace architekton
{
#ifdef _WIN32
using tstring = std::wstring;
#else
using tstring = std::string;
#endif

class string : public tstring
{
public:
  // types
  using tstring::traits_type;
  using tstring::value_type;
  using tstring::allocator_type;
  using tstring::size_type;
  using tstring::difference_type;
  using tstring::reference;
  using tstring::const_reference;
  using tstring::pointer;
  using tstring::const_pointer;
  using tstring::iterator;
  using tstring::const_iterator;
  using tstring::reverse_iterator;
  using tstring::const_reverse_iterator;

  // constructors
  using tstring::tstring;
#ifdef _WIN32
  // constructable from plain (ASCII) C-string
  string(const char* c_string)
  : tstring(c_string, c_string + std::strlen(c_string)+1) {}
#endif

  // Member functions
  using tstring::operator=;
  using tstring::assign;
  using tstring::get_allocator;

  // Element access
  using tstring::at;
  using tstring::operator[];
  using tstring::front;
  using tstring::back;
  using tstring::c_str;
  using tstring::begin;
  using tstring::cbegin;
  using tstring::end;
  using tstring::cend;
  using tstring::rbegin;
  using tstring::crbegin;
  using tstring::rend;
  using tstring::crend;

  // Capacity
  using tstring::empty;
  using tstring::size;
  using tstring::length;
  using tstring::max_size;
  using tstring::reserve;
  using tstring::capacity;
  using tstring::shrink_to_fit;

  // Operations
  using tstring::clear;
  using tstring::insert;
  using tstring::erase;
  using tstring::push_back;
  using tstring::pop_back;
  using tstring::append;
  using tstring::operator+=;
  using tstring::compare;
  using tstring::replace;
  using tstring::substr;
  using tstring::copy;
  using tstring::resize;
  using tstring::swap;

  // Search
  using tstring::find;
  using tstring::rfind;
  using tstring::find_first_of;
  using tstring::find_first_not_of;
  using tstring::find_last_of;
  using tstring::find_last_not_of;

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
