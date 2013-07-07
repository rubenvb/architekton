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
 * main function and execution timing.
 **/

#include "architekton/utility.h++"

#include <chrono>

using namespace architekton;
using namespace architekton::utility;
using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[])
{
  const auto begin = high_resolution_clock::now();

  try
  {
    print("Architekton version ", version::major, ".", version::minor, " is building your software. Please stand by...\n");

    debug_print(debug::always, "Step 1: Commandline arguments.\n");
    parse_commandline(argc, argv);



  }
  catch(const std::exception& e)
  {
    print("A std::exception was thrown: ", e.what());
  }
  catch(...)
  {
    print("Something bad happened.");
  }

  auto time = high_resolution_clock::now() - begin;
  print("\nTotal architekton execution time was: ",
        duration<double, milli>(time).count(), " milliseconds.\n");
}
