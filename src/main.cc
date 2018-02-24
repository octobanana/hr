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
  pg.name("hr").version("0.1.0 (02.23.2018)");
  pg.description("a horizontal rule for the terminal");
  pg.usage("[flags] [options] [--] [arguments]");
  pg.usage("[-s symbol] [-c color] [-r rows] [-b]");
  pg.usage("[-v|--version]");
  pg.usage("[-h|--help]");
  pg.info("Colors", {"black", "red", "green", "yellow", "blue", "magenta", "cyan", "white"});
  pg.info("Exit Codes", {"0 -> normal", "1 -> error"});
  pg.info("Examples", {
    "hr --help",
    "hr --version",
  });
  pg.author("Brett Robinson (octobanana) <octobanana.dev@gmail.com>");

  // flags
  pg.set("help,h", "print the help output");
  pg.set("version,v", "print the program version");
  pg.set("bold,b", "print colored output in bold");

  // options
  pg.set("symbol,s", "-", "string", "set the output symbol");
  pg.set("color,c", "", "color", "print the output in color");
  pg.set("rows,r", "1", "integer", "number of rows to print");

  // pg.set_pos();
  // pg.set_stdin();

  int status {pg.parse()};
  // uncomment if at least one argument is expected
  // if (status > 0 && pg.get_stdin().empty())
  // {
  //   std::cout << pg.print_help() << "\n";
  //   std::cout << "Error: " << "expected arguments" << "\n";
  //   return -1;
  // }
  if (status < 0)
  {
    std::cout << pg.print_help() << "\n";
    std::cout << "Error: " << pg.error() << "\n";
    return -1;
  }
  if (pg.get<bool>("help"))
  {
    std::cout << pg.print_help();
    return 1;
  }
  if (pg.get<bool>("version"))
  {
    std::cout << pg.print_version();
    return 1;
  }
  return 0;
}

int main(int argc, char *argv[])
{
  Parg pg {argc, argv};
  int pstatus {program_options(pg)};
  if (pstatus > 0)
  {
    return 0;
  }
  else if (pstatus < 0)
  {
    return 1;
  }

  Hr hr;
  hr.set_symbol(pg.get("symbol"));
  hr.set_bold(pg.get<bool>("bold"));
  hr.set_color(pg.get("color"));
  hr.set_rows(pg.get<size_t>("rows"));
  hr.render();

  // output result
  std::cout << hr.str();

  return 0;
}
