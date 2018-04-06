#ifndef OB_HR_HH
#define OB_HR_HH

#include "ansi_escape_codes.hh"
namespace AEC = OB::ANSI_Escape_Codes;

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
    {"black", AEC::fg_black},
    {"red", AEC::fg_red},
    {"green", AEC::fg_green},
    {"yellow", AEC::fg_yellow},
    {"blue", AEC::fg_blue},
    {"magenta", AEC::fg_magenta},
    {"cyan", AEC::fg_cyan},
    {"white", AEC::fg_white}
  };

  std::map<std::string, std::string> const bg_colors_ {
    {"black", AEC::bg_black},
    {"red", AEC::bg_red},
    {"green", AEC::bg_green},
    {"yellow", AEC::bg_yellow},
    {"blue", AEC::bg_blue},
    {"magenta", AEC::bg_magenta},
    {"cyan", AEC::bg_cyan},
    {"white", AEC::bg_white}
  };

  size_t term_width() const;
  std::string repeat(std::string const& val, size_t const num) const;
}; // class Hr

} // namespace OB

#endif // OB_HR_HH
