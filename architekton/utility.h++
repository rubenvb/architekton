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
 * architekton - utility.h++
 * Various utilities.
 **/

#ifndef ARCHITEKTON_UTILITY_H
#define ARCHITEKTON_UTILITY_H

#include "architekton/global.h++"

#include "architekton/types.h++"

#include <algorithm>
#include <atomic>
#include <map>
#include <string>

namespace architekton
{
#ifdef _WIN32
constexpr char path_seperator = '\\';
#else
constexpr char path_seperator = '/';
#endif
void convert_path_seperators(std::string& path);

// Generate unique id for stuff (thanks to @Griwes in the Lounge<C++>)
template<typename> // tag so that each class has its own set
uuid id() { static std::atomic<uuid> current{ 1 }; return current++; }
// string extensions
string_pair split(const std::string& s,
                         char value = ' ',
                         std::string::size_type pos = 0);

std::string operator/(const std::string& left,
                      const std::string& right);

// output special char's in a readable form
inline const std::string output_form(const char c)
{
  if('\n' == c)
    return std::string("\\n (newline)");
  else
    return std::string(1,c);
}
inline const std::string output_form(const std::string token)
{
  if("\n" == token)
    return std::string("\\n");
  else
    return token;
}

// find helpers
inline bool contains(const std::string& token,
                     const std::string& characters)
{
  return (std::find_first_of(std::begin(token), std::end(token), std::begin(characters), std::end(characters)) != std::end(token));
}
// returns true if container contains element
template <class container>
bool contains(const container& cont,
              const typename container::value_type& elem)
{
  return (std::find(std::begin(cont), std::end(cont), elem) != std::end(cont));
}

// OS dependent utilities
std::string support_files_location();

#ifdef _WIN32
const std::string convert_to_utf8(const std::wstring& utf16_string);
const std::wstring convert_to_utf16(const std::string& utf8_string);
#endif

}

#endif // ARCHITEKTON_UTILITY_H
