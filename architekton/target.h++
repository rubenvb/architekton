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
 * architekton - target.h++
 * Abstract target that can be built in various build configurations.
 **/

#ifndef ARCHITEKTON_TARGET_H
#define ARCHITEKTON_TARGET_H

#include "architekton/global.h++"

#include "architekton/string.h++"

namespace architekton
{
struct options;

class target
{
public:
  target(const string& name,
         const architekton::options& options)
  : name(name), options(options) {}

  const string name;
  const architekton::options& options;
};

} // namespace architekton

#endif // ARCHITEKTON_TARGET_H
