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
 * architekton - utility/debug.h++
 * Debug print function.
 **/

#ifndef ARCHITEKTON_DEBUG_H
#define ARCHITEKTON_DEBUG_H

#ifndef ARCHITEKTON_DEBUG
#define debug_print(...)
#else

#include "architekton/global.h++"
#include "architekton/utility/print.h++"

#include <cstddef>

namespace architekton
{
namespace utility
{
namespace debug
{
enum debug : std::uint32_t
{
  commandline = 1,
  lexer = 2,
  parser = 4,
  parslexer = lexer ^ parser,
  utility = 8,
  // ...
  always = 0xffffffff,
  everything = always
};

extern debug level;

} // namespace debug

template<typename... ArgTypes>
inline void debug_print(debug::debug level, ArgTypes... args)
{
  if(0 != (debug::level & level))
  {
    switch(level)
    {
      case debug::commandline:
        print("~COMMANDLINE~");
        break;
      case debug::lexer:
        print("~LEXER~~~~~~~");
        break;
      case debug::parser:
        print("~PARSER~~~~~~");
        break;
      case debug::utility:
        print("~UTILITY~~~~~");
        break;
      default:
        print("~UNKNOWN~~~~~");
    }
    print(args...);
  }
}

} // namespace utility

} // namespace architekton

#endif

#endif // ARCHITEKTON_DEBUG_H
