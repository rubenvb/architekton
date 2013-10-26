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
 * architekton - utility/print.h++
 * Type-safe simple output function.
 **/

#ifndef ARCHITEKTON_PRINT_H
#define ARCHITEKTON_PRINT_H

#include "architekton/global.h++"
#include "architekton/types.h++"

#ifdef _WIN32
#define WIN32_MEAN_AND_LEAN
#include <windows.h>
#undef WIN32_MEAN_AND_LEAN
#include <fcntl.h>
#include <io.h>
#endif

#include <iostream>

#include <typeinfo>

namespace architekton
{
namespace utility
{

inline void print() {}

template <typename T, typename ...ArgTypes>
inline void print(T t, ArgTypes ...args)
{
  std::wcout << t;
  if(sizeof...(args))
    print(args...);
}

/*template<typename... ArgTypes>
inline void print(ArgTypes... args)
{
  // trick to expand variadic argument pack without recursion
  using expand_variadic_pack  = int[];
  // first zero is to prevent empty braced-init-list
  // void() is to prevent overloaded operator, messing things up
  // trick is to use the side effect of list-initializer to call a function
  //  on every argument.
  // (void) is to suppress "statement has no effect" warnings
  (void)expand_variadic_pack{0, ((std::wcout << args), void(), 0)... };
}*/

} // namespace utility

} // namespace architekton

#endif // ARCHITEKTON_PRINT_H
