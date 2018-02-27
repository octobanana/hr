#ifndef OB_HR_HH
#define OB_HR_HH

#include <string>
#include <map>

namespace OB
{

class Hr
{
public:
  Hr();

  Hr& set_symbol(std::string const& symbol);
  Hr& set_bold(bool bold);
  Hr& set_color(std::string const& fg_color, std::string const& bg_color);
  Hr& set_rows(size_t rows);
  Hr& set_width(size_t width);
  std::string render();
  std::string str() const;

private:
  size_t width_ {0};
  size_t rows_ {1};
  bool bold_ {false};
  std::string symbol_ {"-"};
  std::string bg_color_;
  std::string fg_color_;
  std::string hr_;

  std::map<std::string, std::string> const fg_colors_ {
    {"black", "\033[30m"},
    {"red", "\033[31m"},
    {"green", "\033[32m"},
    {"yellow", "\033[33m"},
    {"blue", "\033[34m"},
    {"magenta", "\033[35m"},
    {"cyan", "\033[36m"},
    {"white", "\033[37m"}
  };

  std::map<std::string, std::string> const bg_colors_ {
    {"black", "\033[40m"},
    {"red", "\033[41m"},
    {"green", "\033[42m"},
    {"yellow", "\033[43m"},
    {"blue", "\033[44m"},
    {"magenta", "\033[45m"},
    {"cyan", "\033[46m"},
    {"white", "\033[47m"}
  };

  size_t term_width() const;
  std::string repeat(std::string const& val, size_t const num) const;
}; // class Hr

} // namespace OB

#endif // OB_HR_HH
