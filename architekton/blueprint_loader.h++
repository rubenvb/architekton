/**
The MIT License (MIT)

Copyright (c) 2014 Ruben Van Boxem

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
 * architekton - blueprint_loader.h++
 * Loads files with information on:
 *  - architectures,
 *  - toolchains,
 *  - OSes,
 *  - ...
 **/

#ifndef ARCHITEKTON_BLUEPRINT_LOADER_H
#define ARCHITEKTON_BLUEPRINT_LOADER_H

#include "architekton/global.h++"

#include "architekton/lexer.h++"

namespace architekton
{
struct blueprints;
struct options;

blueprints load_blueprints(const options& options);

class blueprint_parser : public lexer
{
  using lexer::lexer;

public:
  void parse(blueprints& blueprints);
};

void parse_blueprint(const std::string& filename,
                     blueprints& blueprints);

} // namespace architekton

#endif // ARCHITEKTON_BLUEPRINT_LOADER_H
