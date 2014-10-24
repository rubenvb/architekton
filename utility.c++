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

#include "architekton/utility.h++"

#include "architekton/error.h++"

#include <string>
  using std::string;
  using std::wstring;

#ifdef _WIN32
#ifndef WIN32_MEAN_AND_LEAN
#define WIN32_MEAN_AND_LEAN
#endif
#include <windows.h>
#undef WIN32_MEAN_AND_LEAN
#endif

namespace architekton
{
void convert_path_seperators(std::string& path)
{
#ifdef _WIN32
  const static auto is_wrong_slash = [](char c){ return c == '/'; };
#else
  const static auto is_wrong_slash = [](char c){ return c == '\\'; };
#endif
  std::replace_if(path.begin(), path.end(), is_wrong_slash, path_seperator);
}

string_pair split(const string& s,
                  char value,
                  string::size_type pos)
{
  const size_t index = s.find(value, pos);
  return { s.substr(pos, index-pos), s.substr(index+pos) };
}

std::string operator/(const std::string& left,
                      const std::string& right)
{
  std::string result;
  if(left.empty())
    result = right;
  else if(right.empty())
    result = left;
  else if(path_seperator == left.back())
    result = left.substr(0,left.size()-1) + path_seperator + right;
  else
    result = left + path_seperator + right;

  return result;
}

std::string support_files_location()
{
  //TODO: make configurable with environment variable or some such
#ifdef _WIN32
  std::size_t size = MAX_PATH;
  std::wstring result;
  result.resize(size);
  while(size == GetModuleFileNameW(NULL, &result[0], size)) // should work... must check
  {
    size += MAX_PATH;
    result.resize(size);
  }
  result = result.substr(0, result.rfind('\\'));
  return convert_to_utf8(result);
#else
  return "/usr/share/architekton";
#endif
}

#ifdef _WIN32
// UTF-16 -> UTF-8 conversion
const string convert_to_utf8(const wstring& utf16_string)
{
  // get length
  int length = WideCharToMultiByte(CP_UTF8, 0, utf16_string.c_str(), static_cast<int>(utf16_string.size()),
                                   nullptr, 0, nullptr, nullptr);
  if(!(length > 0))
    return string();
  else
  {
    string result;
    result.resize(static_cast<string::size_type>(length));

    if(WideCharToMultiByte(CP_UTF8, 0, utf16_string.c_str(), static_cast<int>(utf16_string.size()),
                           &result[0], static_cast<int>(result.size()), nullptr, nullptr) == 0 )
      throw error("Failure to execute convert_to_utf8: call to WideCharToMultiByte failed.");
    else
      return result;
  }
}
// UTF-8 -> UTF-16 conversion
const wstring convert_to_utf16(const string& utf8_string)
{
  // get length
  int length = MultiByteToWideChar(CP_UTF8, 0, utf8_string.c_str(), static_cast<int>(utf8_string.size()), nullptr, 0);
  if(!(length > 0))
    return wstring();
  else
  {
    wstring result;
    result.resize(static_cast<string::size_type>(length));

    if(MultiByteToWideChar(CP_UTF8, 0, utf8_string.c_str(), static_cast<int>(utf8_string.size()),
                           &result[0], static_cast<int>(result.size())) == 0 )
      throw error("Failure to execute convert_to_utf16: call to MultiByteToWideChar failed.");
    else
      return result;
  }
}
#endif

}
