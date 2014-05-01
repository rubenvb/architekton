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
 * architekton - project.h++
 * Project target.
 **/

#ifndef ARCHITEKTON_PROJECT_H
#define ARCHITEKTON_PROJECT_H

#include "architekton/global.h++"

#include "architekton/options.h++"
#include "architekton/target.h++"
#include "architekton/types.h++"
#include "architekton/utility.h++"

namespace architekton
{
struct options;

class project : public target
{
public:
  project(const architekton::options& options)
  : target(split(options.main_project_file, '.').first, options), filename(options.main_project_file) {}
  project(const std::string& filename,
          const architekton::options& options)
  : target(split(filename, '.').first, options) {}

  void load_project();

private:
  const std::string filename; // relative to general source directory in options
  target_vector targets; // targets defined in project file
};

} // namespace architekton

#endif // PROJECT
