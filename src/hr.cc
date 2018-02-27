#include "hr.hh"

#include <string>
#include <sstream>
#include <map>
#include <sys/ioctl.h>
#include <unistd.h>

namespace OB
{

Hr::Hr()
{
}

Hr& Hr::set_symbol(std::string const& symbol)
{
  symbol_ = symbol;
  return *this;
}

Hr& Hr::set_bold(bool bold)
{
  bold_ = bold;
  return *this;
}

Hr& Hr::set_color(std::string const& fg_color, std::string const& bg_color)
{
  if (! fg_color.empty())
  {
    if (fg_colors_.find(fg_color) != fg_colors_.end())
    {
      fg_color_ = fg_colors_.at(fg_color);
    }
    else
    {
      throw std::runtime_error("invalid color '" + fg_color + "'\nsee --help for a list of valid colors");
    }
  }

  if (! bg_color.empty())
  {
    if (bg_colors_.find(bg_color) != bg_colors_.end())
    {
      bg_color_ = bg_colors_.at(bg_color);
    }
    else
    {
      throw std::runtime_error("invalid color '" + bg_color + "'\nsee --help for a list of valid colors");
    }
  }

  return *this;
}

Hr& Hr::set_rows(size_t rows)
{
  if (rows == 0)
  {
    throw std::runtime_error("argument 'rows' has invalid value 0");
  }
  rows_ = rows;
  return *this;
}

Hr& Hr::set_width(size_t width)
{
  width_ = width;
  return *this;
}

std::string Hr::render()
{
  size_t width = (width_ > 0 ? width_ : term_width()) / symbol_.size();
  std::string line {repeat(symbol_, width)};
  std::string out;

  // set bold
  if (bold_)
  {
    out += "\033[1m";
  }

  // set color
  out += fg_color_ + bg_color_ + line + "\033[0m" + "\n";

  // set rows
  if (rows_ > 1)
  {
    out = repeat(out, rows_);
  }

  // set hr variable
  hr_ = out;

  return hr_;
}

std::string Hr::str() const
{
  return hr_;
}

size_t Hr::term_width() const
{
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_col;
}

std::string Hr::repeat(std::string const& val, size_t const num) const
{
  if (num < 2)
  {
    return val;
  }
  std::string out;
  for (size_t i = 0; i < num; ++i)
  {
    out.append(val);
  }
  return out;
}

} // namespace OB
