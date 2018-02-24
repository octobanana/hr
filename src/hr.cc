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

Hr& Hr::set_color(std::string const& color)
{
  if (color.empty())
  {
    return *this;
  }
  if (colors_.find(color) == colors_.end())
  {
    throw std::runtime_error("invalid color '" + color + "'\nsee --help for a list of valid colors");
  }
  color_ = colors_.at(color);
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

std::string Hr::render()
{
  width_ = term_width() / symbol_.size();
  std::string line {repeat(symbol_, width_)};
  std::string out;

  // set bold
  if (bold_)
  {
    out += "\033[1m";
  }

  // set color
  if (color_.empty())
  {
    out += line + "\n";
  }
  else
  {
    out += color_ + line + "\033[0m" + "\n";
  }

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
