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

#include "architekton/commandline.h++"
#include "architekton/debug.h++"
#include "architekton/error.h++"
#include "architekton/file.h++"
#include "architekton/options.h++"
#include "architekton/string.h++"

namespace architekton
{

#ifdef _WIN32
void parse_commandline(int,
                       char*[],
                       options& options)
{
  int argc;
  auto argv = CommandLineToArgvW(GetCommandLineW(), &argc);
  if(argv == nullptr)
    throw error("Call to CommandLineToArgvW failed.");
#else
void parse_commandline(int argc,
                       char* argv[],
                       options& options)
{
#endif
  debug_print(debug::commandline, "Step 1: Commandline arguments.");

  string_vector args(argv+1, argv+argc); // skip argv[0]
  bool first_dashless_argument = true;
  for(auto&& arg : args)
  {
    if(arg[0] == '-')
    {
      if(arg[1] == '-') // arguments should never be empty (min. length 2)
      {
        const auto key_value = arg.split(2, '=');
        debug_print(debug::commandline, "Project argument (-key[=value]): key=\'", key_value.first, "\'', value=\'", key_value.second, "\'.");
      }
      else
      {
        const auto key_value = arg.split(1, '=');
        set_option(key_value.first, key_value.second, options);
      }
    }
    else
    {
      debug_print(debug::commandline, "Dashless argument: \'", arg, "\'.");
      if(first_dashless_argument)
      {
        first_dashless_argument = false;
        if(directory_exists(arg))
        {
          debug_print(debug::commandline, "Possible source directory: \'", arg, "\'.");
          auto project_files = find_files(arg, "*.architekton.txt");

          if(project_files.empty())
          {
            debug_print(debug::commandline, "No project file found in \'", arg, "\', checking \'.\'.");
            project_files = find_files(".", "*.architekton.txt");
            if(project_files.empty())
              throw error("No project file found. Please specify the path to a *.architekton.txt file to be built.");

            // get rid of goto
            goto target_to_build;
          }
          if(project_files.size() > 1)
            throw error("Multiple *.architekton.txt files found. Please specify the filename for the project to be built. Files found:", project_files);

          // We now have exactly one project file
          options.main_project_file = project_files.begin()->name;
          debug_print(debug::commandline, "Main project file set: \'", options.main_project_file, "\'.");
          continue;
        }
        else if(file_exists(arg))
        {
          debug_print(debug::commandline, "Possible project file: \'", arg, "\'.");
          auto project_files = find_files(arg);
          // failure here would mean a bug in file_exists or find_files that needs fixing
          options.main_project_file = project_files.begin()->name;
          continue;
        }
      }
      target_to_build:
      debug_print(debug::commandline, "Target to build: \'", arg, "\'.");
      if(!options.targets_to_build.insert(arg).second)
        print("Warning: target \'", arg, "\' specified twice on the commandline.");
    }
  }

  // reality check
  if(options.main_project_file.empty())
    throw error("No project file found. Please specify a path to an *.architekton.txt file.");
}

void set_option(const string &key,
                const string &value,
                options &options)
{
  debug_print(debug::commandline, "Architekton argument (--key[=value]): key=\'", key, "\', value=\'", value, "\'.");
  if(key == "debug")
  {
    debug_print(debug::commandline, "\'debug\' option currently unhandled.");
  }
}

} // namespace architekton


