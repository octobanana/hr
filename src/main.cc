#include "parg.hh"
using Parg = OB::Parg;

#include "hr.hh"
using Hr = OB::Hr;

#include <string>
#include <iostream>
#include <vector>
#include <map>

int program_options(Parg& pg);

int program_options(Parg& pg)
{
  pg.name("hr").version("0.4.2 (09.04.2018)");
  pg.description("a horizontal rule for the terminal");
  pg.usage("[flags] [options] [--] [arguments]");
  pg.usage("[-s symbol] [-c color] [-b color] [-r rows] [-w width] [-B]");
  pg.usage("[-v|--version]");
  pg.usage("[-h|--help]");
  pg.info("Colors", {"black", "red", "green", "yellow", "blue", "magenta", "cyan", "white", "any hex color code"});
  pg.info("Examples", {
    "hr -c magenta -s '~' -B",
    "hr -c magenta -b cyan",
    "hr -c #000 -b #ff33aa",
    "hr -c green -r 2",
    "hr -c cyan -w 8",
    "hr --help",
    "hr --version",
  });
  pg.info("Exit Codes", {"0 -> normal", "1 -> error"});
  pg.author("Brett Robinson (octobanana) <octobanana.dev@gmail.com>");

  // flags
  pg.set("help,h", "print the help output");
  pg.set("version,v", "print the program version");
  pg.set("bold,B", "print colored output in bold");

  // options
  pg.set("symbol,s", "-", "string", "set the output symbol");
  pg.set("color,c", "", "color", "set the output text color");
  pg.set("background,b", "", "color", "set the output background color");
  pg.set("rows,r", "1", "integer", "number of rows to print");
  pg.set("width,w", "0", "integer", "number of columns to print");

  int status {pg.parse()};
  if (status < 0)
  {
    std::cout << pg.help() << "\n";
    std::cout << "Error: " << pg.error() << "\n";
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
  if (pg.get<size_t>("rows") > 1000)
  {
    std::cout << pg.help() << "\n";
    std::cout << "Error: " << "invalid argument, rows must be > 0 and <= 1000" << "\n";
    return -1;
  }
  if (pg.get<size_t>("width") > 1000)
  {
    std::cout << pg.help() << "\n";
    std::cout << "Error: " << "invalid argument, width must be > 0 and <= 1000" << "\n";
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
    hr.set_symbol(pg.get("symbol"));
    hr.set_bold(pg.get<bool>("bold"));
    hr.set_color(pg.get("color"), pg.get("background"));
    hr.set_rows(pg.get<size_t>("rows"));
    hr.set_width(pg.get<size_t>("width"));
    hr.render();

    // output result
    std::cout << hr.str();
  }
  catch (std::exception const& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
