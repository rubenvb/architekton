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
 * architekton - blueprint_loaders.c++
 * Function implementations.
 **/

#include "architekton/blueprint_loaders.h++"

#include <istream>

#include <boost/spirit/include/qi.hpp>
  namespace spirit = boost::spirit;
  namespace qi = spirit::qi;
  using spirit::ascii::space;
  using spirit::ascii::char_;
  using qi::eol;
  using qi::lit;

namespace architekton
{

string_set load_architectures(const std::string& input)
{
  string_set architectures;

  const auto comment_skipper = space | '#' >> *(char_ - eol) >> eol;

  const auto grammar = lit("architecture") >> *(char_) % eol;

  qi::phrase_parse(std::begin(input), std::end(input), grammar, comment_skipper, architectures);
  return architectures;
}

string_set load_OSes()
{
  string_set OSes;

  return OSes;
}

string_set load_toolchains()
{
  string_set toolchains;

  return toolchains;
}

} // namespace architekton
