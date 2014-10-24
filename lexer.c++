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
 * architekton - lexer.c++
 * Class implementation.
 **/

#include "architekton/lexer.h++"

#include "architekton/debug.h++"
#include "architekton/error.h++"

#include <cstddef>
  using std::size_t;
#include <istream>
  using std::istream;
#include <string>
  using std::string;

namespace architekton
{

const char_set special_characters = { '(', ')', '{', '}', ':', ',' };
const char_set special_characters_newline = { '(', ')', '{', '}', ':', ',', '\n' };
const char_set special_characters_conditional = { '(', ')', '|', '+', '!' };

lexer::lexer(istream& stream,
             const string& filename,
             std::istream::pos_type stream_position,
             const size_t line_number,
             const size_t column_number)
: filename(filename),
  line_number(line_number),
  column_number(column_number),
  stream(stream)
{
  stream.seekg(stream_position);
  if(!stream)
    throw error("Unable to seek to position in file: " + filename);
}

bool lexer::next_token(string& token,
                       const char_set& special_characters)
{
  // TODO: test the *full* hell out of this function
  // FIXME: ugly as hell, alternatives welcome.
  token.clear();
  bool inside_quotes = false;
  char c;
  // backup current position
  previous_position = stream.tellg();
  previous_line_number = line_number;

  while(stream.get(c))
  {
    debug_print(debug::lexer, "lexer::next_token::line number ", line_number, ", character: \'", output_form(c), "\', token so far: \'", output_form(token), "\'.");
    if(inside_quotes)
    {
      debug_print(debug::lexer, "lexer::next_token::Inside quotes.");
      if('\\' == c)
      {
        if(stream.get(c))
          token.append(1, c);
        else
          throw syntax_error("Valid escape character expected after \'\\\'", filename, line_number);
      }
      if('\"' == c)
        break; // end of token at end of quotes
      else if('\n' == c)
        throw syntax_error("Quoted strings cannot span several lines.", filename, line_number);
      else if(token.empty() && std::isspace(c, stream.getloc()))
        throw syntax_error("Beginning quote must not be followed by a whitespace.", filename, line_number);
      else
        token.append(1, c);
    }
    else
    {
      if(token.empty())
      {
        if('\n' == c)
          ++line_number;

        if(contains(special_characters, c))
        { // special characters are tokens of their own
          debug_print(debug::lexer, "lexer::next_token::Detected special character.");
          token.append(1, c);
          return true;
        }
        else if('\"' == c)
        {
          debug_print(debug::lexer, "lexer::next_token::Quote detected.");
          inside_quotes = true;
          continue;
        }
        else if(std::isspace(c, stream.getloc()))
          continue;
        else if('#' == c)
        { // skip over comments
          debug_print(debug::lexer, "lexer::next_token::Skipping over comments.");
          string temp;
          std::getline(stream, temp);
          stream.putback('\n');
        }
        else if('\\' == c)
        {
          string temp;
          std::getline(stream, temp);
          ++line_number;
        }
        else
          token.append(1, c);
      }
      else if(std::isspace(c, stream.getloc()) || contains(special_characters, c))
      { // special characters or whitespace seperate tokens
        debug_print(debug::lexer, "lexer::next_token::Detected special character or space.");
        stream.putback(c);
        break;
      }
      //else if('\"' == c)
      // throw syntax_error("Beginning quotes must be preceded by a whitespace or a special character.", filename, line_number);
      else
        token.append(1, c);
    }
  }
  if(!token.empty())
    debug_print(debug::lexer, "lexer::next_token:Token extracted: \'", output_form(token), "\'.");

  return !token.empty();
}

} // namespace architekton
