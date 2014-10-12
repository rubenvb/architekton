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
 * architekton - blueprint_loader.c++
 * Loads files with information on:
 *  - architectures,
 *  - toolchains,
 *  - OSes,
 *  - ...
 **/

#include "architekton/blueprint_loader.h++"

#include "architekton/debug.h++"
#include "architekton/error.h++"
#include "architekton/file.h++"

#include <string>
  using std::string;

namespace architekton
{

void load_blueprints(blueprints& blueprints)
{
  const string blueprint_directory = support_files_location() / "blueprints";
  debug_print(debug::blueprint, "Loading blueprints from: \'", blueprint_directory, "\'.");

  auto blueprint_files = find_files(blueprint_directory, "*.blueprint.txt");
  if(blueprint_files.empty())
    throw error("No blueprint files found. Looked in: \'" + blueprint_directory + "\'.");

}


} // namespace architekton
