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
 * architekton - commandline.c++
 * Function implementations.
 **/

#include "architekton/utility/commandline.h++"
#include "architekton/utility/debug.h++"
#include "architekton/utility/string.h++"

#include "architekton/options.h++"

namespace architekton
{
namespace utility
{

#ifdef _WIN32
void parse_commandline(int,
                       char*[],
                       options& options)
{
  int argc;
  auto argv = CommandLineToArgvW(GetCommandLineW(), &argc);
  if(argv == nullptr)
    throw std::runtime_error("Call to CommandLineToArgvW failed.");
#else
void parse_commandline(int argc,
                       char* argv[],
                       options& options)
{
#endif
  std::vector<ustring> args(argv, argv+argc);
  bool first_dashless_argument = true;
  for(auto&& arg : args)
  {
    //debug_print(debug::commandline, "Handling argument: ", arg, "\n");
    if(arg[0] == '-')
    {
      if(arg[1] == '-') // arguments should never be empty (min. length 2)
      {
        const auto key_value = split_string(arg, 2);
        debug_print(debug::commandline, "Project argument: key=\'", key_value.first, "\'', value=\'", key_value.second, "\'\n");
      }
      else
      {
        const auto key_value = split_string(arg, 1);
        debug_print(debug::commandline, "Architekton argument: key=\'", key_value.first, "\', value=\'", key_value.second, "\'\n");

      }
    }
    else
    {
      debug_print(debug::commandline, "Dashless argument: \'", arg, "\'\n");
      if(first_dashless_argument)
      {
        debug_print(debug::commandline, "Possible project file or directory: \'", arg, "\'.");


      }
      debug_print(debug::commandline, "Target to build: \'", arg, "\'\n");
      if(!options.targets_to_build.insert(arg).second)
        print("Commandline warning: target \'", arg, "\' specified twice on the commandline.");


    }

  }

}

} // namespace utility

} // namespace architekton


