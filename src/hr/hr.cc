#include "hr.hh"

#include "ob/term.hh"
#include "ob/color.hh"
#include "ob/string.hh"

#include <cstddef>

#include <string>
#include <sstream>

namespace aec = OB::Term::ANSI_Escape_Codes;

namespace OB
{

std::string Hr::fill()
{
  return fill_;
}

Hr& Hr::fill(std::string const& val)
{
  fill_ = val;

  return *this;
}

std::string Hr::text()
{
  return text_;
}

Hr& Hr::text(std::string const& val)
{
  text_ = val;

  return *this;
}

std::string Hr::align()
{
  return align_;
}

Hr& Hr::align(std::string const& val)
{
  align_ = val;

  return *this;
}

bool Hr::bold()
{
  return bold_;
}

Hr& Hr::bold(bool const val)
{
  bold_ = val;

  return *this;
}

bool Hr::underline()
{
  return underline_;
}

Hr& Hr::underline(bool const val)
{
  underline_ = val;

  return *this;
}

std::string Hr::color()
{
  return color_;
}

Hr& Hr::color(std::string const& val)
{
  color_ = val;

  return *this;
}

std::string Hr::color_fg()
{
  return color_fg_.value();
}

bool Hr::color_fg(std::string const& val)
{
  return color_fg_.key(val);
}

std::string Hr::color_bg()
{
  return color_bg_.value();
}

bool Hr::color_bg(std::string const& val)
{
  return color_bg_.key(val);
}

std::size_t Hr::height()
{
  return height_;
}

Hr& Hr::height(std::size_t const val)
{
  height_ = val;

  return *this;
}

std::size_t Hr::width()
{
  return width_;
}

Hr& Hr::width(std::size_t const val)
{
  width_ = val;

  return *this;
}

std::string Hr::render()
{
  std::ostringstream os;

  auto const is_term = OB::Term::is_term(STDOUT_FILENO);
  auto const use_color = color_ == "auto" ? is_term : color_ == "on";

  if (use_color)
  {
    os
    << color_fg_
    << color_bg_;

    if (bold_)
    {
      os << aec::bold;
    }

    if (underline_)
    {
      os << aec::underline;
    }
  }

  auto const width = term_width(is_term);

  std::string line;

  if (text_.size())
  {
    if (align_ == "left")
    {
      line = text_.substr(0, width);

      if (line.size() < width)
      {
        line += repeat(width - line.size(), fill_);
      }
    }
    else if (align_ == "right")
    {
      line = text_.substr(text_.size() > width ? text_.size() - width : 0, width);

      if (line.size() < width)
      {
        line.insert(0, repeat(width - line.size(), fill_));
      }
    }
    else // center
    {
      line = text_.substr(0, width);

      if (line.size() < width)
      {
        line.insert(0, repeat((width - text_.size()) / 2, fill_));
      }

      if (line.size() < width)
      {
        line += repeat(width - line.size(), fill_);
      }
    }
  }
  else
  {
    line = repeat(width, fill_);
  }

  line += "\n";

  os << line;

  if (height_ > 1)
  {
    os << OB::String::repeat(height_ - 1, line);
  }

  if (use_color)
  {
    os << aec::clear;
  }

  buf_ = os.str();

  return buf_;
}

std::string Hr::str() const
{
  return buf_;
}

std::size_t Hr::term_width(bool const is_term) const
{
  if (width_ > 0)
  {
    return width_;
  }

  if (is_term)
  {
    std::size_t width {0};
    OB::Term::width(width);

    return width;
  }

  return width_default_;
}

std::string Hr::repeat(std::size_t const len, std::string const& str) const
{
  if (len == 0 || str.empty())
  {
    return {};
  }


  if (str.size() >= len)
  {
    return str.substr(0, len);
  }

  std::string res {OB::String::repeat(len / str.size(), str)};

  if (res.size() < len)
  {
    res += str.substr(0, len - res.size());
  }

  return res;
}

} // namespace OB
