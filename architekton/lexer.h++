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
 * architekton - lexer
 * Basic file reading and token extraction.
 **/

#ifndef ARCHITEKTON_LEXER
#define ARCHITEKTON_LEXER

#include "architekton/global.h++"

#include <architekton/types.h++>

#include <cstddef>
#include <istream>
#include <set>
#include <string>

namespace architekton
{

extern char_set special_characters;

class lexer
{
public:
  lexer(std::istream& stream,
        const std::string& full_filename,
        const std::size_t line_number = 1,
        const std::size_t column_number = 1,
        std::istream::pos_type stream_position = std::istream::pos_type());

  bool next_token(std::string& token,
                  const char_set& special_characters = ::architekton::special_characters);
  void previous_token(); // revert stream position to previous token
  bool next_list_token(std::string& token
                       /*,const configuration& configuration*/);

  // conditionals
  //bool process_conditional();
  //bool test_condition(const std::function<bool(const std::string&)>& config_contains);
  //void process_outer_conditional(const configuration& configuration); // skips full target
  //void process_dependency_set_conditional(const configuration& configuration); // skips dependenc(y/ies)
  //void process_inner_conditional(const configuration& configuration); // skips whole list
  //void process_inner_list_conditional(const configuration& configuration); // skips item in list

private:
  std::istream& stream;
  const std::string& filename;
  std::size_t line_number;
  std::size_t column_number;
  // store one-token-back-position
  std::istream::pos_type previous_position;
  std::size_t previous_line_number;
};

} // namespace architekton

#endif // ARCHITEKTON_LEXER
