#include "hr/hr.hh"

#include "ob/parg.hh"
#include "ob/color.hh"
#include "ob/string.hh"

#include <cstddef>

#include <string>
#include <iostream>
#include <vector>
#include <map>

using Parg = OB::Parg;
using Hr = OB::Hr;

int program_options(Parg& pg);

int program_options(Parg& pg)
{
  pg.name("hr").version("0.5.0 (13.05.2019)");

  pg.description("A horizontal rule for the terminal.");

  pg.usage("[--text|-t <string>] [--string|-s <string>] [--align|-a <left|center|right>] [--bold|-B] [--underline|-U] [--colour-fg|-f <colour>] [--colour-bg|-b <colour>] [--columns|-c <integer>] [--rows|-r <integer>] [--colour|-C <auto|on|off>]");
  pg.usage("[--help|-h]");
  pg.usage("[--version|-v]");
  pg.usage("[--license]");

  pg.info("Colours", {
    "clear",
    "reverse",
    "0-255",
    "#000-#fff",
    "#000000-#ffffff",
    "black[-bright]",
    "red[-bright]",
    "green[-bright]",
    "yellow[-bright]",
    "blue[-bright]",
    "magenta[-bright]",
    "cyan[-bright]",
    "white[-bright]",
  });

  pg.info("Examples", {
    "hr",
    "hr --help",
    "hr --version",
    "hr --license",
    "hr -s '-~' -f green",
    "hr -s 'octo ' -f white-bright -c 50 -B",
    "hr -s ' ' -b cyan-bright -r 2",
    "hr -t OCTOBANANA -s '*' -f magenta-bright",
    "hr -t OCTOBANANA -s ' ' -f '#f34b7d' -BU",
    "hr -t OCTOBANANA -s ' ' -f '#55ff00' -a left -BU",
    "hr -t OCTOBANANA -s ' ' -f '#55ff00' -a right -BU",
    "hr -s 'SUCCESS ' -f green-bright -b reverse",
    "hr -s 'ERROR ' -f '#1b1e24' -b red-bright -B",
    "hr -s 'WARNING ' -f '#1b1e24' -b yellow-bright",
  });

  pg.info("Exit Codes", {"0 -> normal", "1 -> error"});

  pg.info("Repository", {
    "https://github.com/octobanana/hr.git",
  });

  pg.info("Homepage", {
    "https://octobanana.com/software/hr",
  });

  pg.author("Brett Robinson (octobanana) <octobanana.dev@gmail.com>");

  // flags
  pg.set("help,h", "Print the programs help output.");
  pg.set("version,v", "Print the programs version.");
  pg.set("license", "Print the programs license.");

  pg.set("bold,B", "set the output text to use bold styling");
  pg.set("underline,U", "set the output text to use underline styling");

  // options
  pg.set("string,s", "-", "string", "set the output fill string");
  pg.set("text,t", "", "string", "set the output text");
  pg.set("align,a", "left", "left|center|right", "set the output text alignment");
  pg.set("colour-fg,f", "", "colour", "set the output foreground colour");
  pg.set("colour-bg,b", "", "Colour", "set the output background colour");
  pg.set("rows,r", "1", "integer", "number of rows to print");
  pg.set("columns,c", "0", "integer", "number of columns to print");
  pg.set("colour,C", "auto", "auto|on|off", "set the output colour preference");

  pg.set_stdin();

  int status {pg.parse()};

  if (status < 0)
  {
    std::cerr << "Usage:\n" << pg.usage() << "\n";
    std::cerr << "Error: " << pg.error() << "\n";

    auto const similar_names = pg.similar();
    if (similar_names.size() > 0)
    {
      std::cerr
      << "Did you mean:\n";
      for (auto const& e : similar_names)
      {
        std::cerr
        << "  --" << e << "\n";
      }
    }

    return -1;
  }

  if (pg.get<bool>("help"))
  {
    std::cout << pg.help();
    return 1;
  }

  if (pg.get<bool>("version"))
  {
    std::cout << pg.name() << " v" << pg.version() << "\n";
    return 1;
  }

  if (pg.get<bool>("license"))
  {
    std::cout << R"(MIT License

Copyright (c) 2018-2019 Brett Robinson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.)" << "\n";

    return 1;
  }

  if (pg.find("colour") && ! OB::String::assert_rx(pg.get<std::string>("colour"),
    std::regex("^auto|on|off$")))
  {
    std::cerr << "Usage:\n" << pg.usage() << "\n";
    std::cerr << "Error: invalid colour preference '" << pg.get<std::string>("colour") << "', value must be either 'auto', 'on', or 'off'\n";

    return -1;
  }

  if (pg.find("align") && ! OB::String::assert_rx(pg.get<std::string>("align"),
    std::regex("^left|center|right$")))
  {
    std::cerr << "Usage:\n" << pg.usage() << "\n";
    std::cerr << "Error: invalid alignment '" << pg.get<std::string>("align") << "', value must be either 'left', 'center', or 'right'\n";

    return -1;
  }

  if (pg.find("colour-fg") && ! OB::Color::valid(pg.get<std::string>("colour-fg")))
  {
    std::cerr << "Usage:\n" << pg.usage() << "\n";
    std::cerr << "Error: invalid colour '" << pg.get<std::string>("colour-fg") << "'\n";

    return -1;
  }

  if (pg.find("colour-bg") && ! OB::Color::valid(pg.get<std::string>("colour-bg")))
  {
    std::cerr << "Usage:\n" << pg.usage() << "\n";
    std::cerr << "Error: invalid colour '" << pg.get<std::string>("colour-bg") << "'\n";

    return -1;
  }

  if (pg.find("columns") &&
    (pg.get<std::size_t>("columns") == 0 || pg.get<std::size_t>("columns") > 1000))
  {
    std::cerr << "Usage:\n" << pg.usage() << "\n";
    std::cerr << "Error: invalid number of columns '" << pg.get<std::size_t>("columns") << "', value must be > 0 and <= 1000\n";

    return -1;
  }

  if (pg.find("rows") &&
    (pg.get<std::size_t>("rows") == 0 || pg.get<std::size_t>("rows") > 1000))
  {
    std::cerr << "Usage:\n" << pg.usage() << "\n";
    std::cerr << "Error: invalid number of rows '" << pg.get<std::size_t>("rows") << "', value must be > 0 and <= 1000\n";

    return -1;
  }

  return 0;
}

int main(int argc, char *argv[])
{
  Parg pg {argc, argv};
  int pstatus {program_options(pg)};
  if (pstatus > 0) return 0;
  if (pstatus < 0) return 1;

  try
  {
    Hr hr;
    hr.fill(OB::String::replace(pg.get<std::string>("string"), "\n", ""));
    hr.text(OB::String::replace(pg.get<std::string>("text") + pg.get_stdin(), "\n", ""));
    hr.align(pg.get<std::string>("align"));
    hr.bold(pg.get<bool>("bold"));
    hr.underline(pg.get<bool>("underline"));
    hr.color(pg.get<std::string>("colour"));
    hr.color_fg(pg.get<std::string>("colour-fg"));
    hr.color_bg(pg.get<std::string>("colour-bg"));
    hr.width(pg.get<std::size_t>("columns"));
    hr.height(pg.get<std::size_t>("rows"));
    hr.render();

    std::cout << "\r" << hr.str();
  }
  catch (std::exception const& e)
  {
    std::cerr << "Error: " << e.what() << "\n";

    return 1;
  }

  return 0;
}
