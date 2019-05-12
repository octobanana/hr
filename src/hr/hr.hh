#ifndef OB_HR_HH
#define OB_HR_HH

#include "ob/term.hh"
#include "ob/color.hh"

#include <cstddef>

#include <string>

namespace aec = OB::Term::ANSI_Escape_Codes;

namespace OB
{

class Hr
{
public:

  std::string fill();
  Hr& fill(std::string const& val);

  std::string text();
  Hr& text(std::string const& val);

  std::string align();
  Hr& align(std::string const& val);

  bool bold();
  Hr& bold(bool const val);

  bool underline();
  Hr& underline(bool const val);

  std::string color();
  Hr& color(std::string const& val);

  std::string color_fg();
  bool color_fg(std::string const& val);

  std::string color_bg();
  bool color_bg(std::string const& val);

  std::size_t height();
  Hr& height(std::size_t const val);

  std::size_t width();
  Hr& width(std::size_t const val);

  std::string render();

  std::string str() const;

private:

  std::size_t const width_default_ {80};
  std::string fill_ {"-"};
  std::string text_ {""};
  std::string align_ {""};
  std::string color_ {""};
  bool bold_ {false};
  bool underline_ {false};
  std::size_t width_ {0};
  std::size_t height_ {1};
  OB::Color color_fg_ {"", OB::Color::Type::fg};
  OB::Color color_bg_ {"", OB::Color::Type::bg};
  std::string buf_;

  std::size_t term_width(bool const is_term) const;
  std::string repeat(std::size_t const len, std::string const& str) const;
}; // class Hr

} // namespace OB

#endif // OB_HR_HH
