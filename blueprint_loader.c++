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

#include "architekton/blueprints.h++"
#include "architekton/debug.h++"
#include "architekton/error.h++"
#include "architekton/file.h++"
#include "architekton/lexer.h++"
#include "architekton/options.h++"

#include <string>
  using std::string;

namespace architekton
{

blueprints load_blueprints(const options& options)
{
  blueprints blueprints;
  debug_print(debug::blueprint, "Loading blueprints from:", options.blueprint_directories);

  auto blueprint_files = find_files(options.blueprint_directories, "*.blueprint.txt");
  if(blueprint_files.empty())
    throw error("No blueprint files found. Looked in: ", options.blueprint_directories);

  for(const auto& blueprint_file : blueprint_files)
  {
    auto stream_ptr = open_ifstream(blueprint_file);
    auto& stream = *stream_ptr;
    if(!stream)
      throw error("Failed to open file: \'" + blueprint_file.name + "\'.");

    blueprint_parser parser(stream, blueprint_file.name);
    parser.parse(blueprints);
  }


  throw error("load_blueprints implementation incomplete.");

  return blueprints;
}

void blueprint_parser::parse(blueprints& blueprints)
{
  string token;
  while(next_token(token))
  {
    if(token == "architecture")
    {
      if(next_token(token))
      {
        debug_print(debug::blueprint, "Found architecture: \'", token, "\'.");
        blueprints.architectures.insert(token);
      }
      else
        throw syntax_error("\'architecture\' must be followed by an architecture name.", filename, line_number);
    }
    else if(token == "os")
    {
      if(next_token(token))
      {
        debug_print(debug::blueprint, "Found os: \'", token, "\'.");
        if(next_token(token) && token == "{")
        {
          if(next_token(token))
          {
            if(token == "provides")
            {
               if(next_token(token))
               {
                 debug_print(debug::blueprint, "Blueprint provides \'", token, "\'.");


               }
            }
            else if(token == "prefers" && next_token(token))
            {
              debug_print(debug::blueprint, "Preferred toolchain found: \'", token, "\'.");
            }
          }
        }
      }
      else
        continue;
    }
    else
      throw syntax_error("Unexpected token: " + token, filename, line_number);
  }
}

} // namespace architekton
