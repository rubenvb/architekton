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
 * architekton - main.c++
 * Main function with execution timing.
 **/

#include "architekton/blueprint_loader.h++"
#include "architekton/blueprints.h++"
#include "architekton/commandline.h++"
#include "architekton/error.h++"
#include "architekton/options.h++"
#include "architekton/print.h++"
#include "architekton/project.h++"

#include <chrono>
#include <fstream>
#include <iterator>
#include <streambuf>
#include <string>
#include <ios>

using namespace architekton;
using namespace std::chrono;
using namespace std;

int main(int argc, char* argv[])
{
  const auto begin = high_resolution_clock::now();

  try
  {
    print("Architekton version ", version::major, ".", version::minor, " is building your software. Please stand by...\n");

    print("Starting build in \'", current_working_directory(), "\'.\n");

    options options;
    parse_commandline(argc, argv, options);

    blueprints blueprints = load_blueprints(options);

    project project(options);
    print("Loading project \'", project.name, "\'.\n");
    project.load_project();
  }
  catch(const error& e)
  {
    e.print();
  }

  catch(const std::exception& e)
  {
    print("A std::exception was thrown: ", e.what());
  }
  catch(...)
  {
    print("Something bad happened.\n");
  }

  auto time = high_resolution_clock::now() - begin;
  print("\n->Total architekton execution time was: ",
        duration<double, std::milli>(time).count(), " milliseconds.\n");
}
