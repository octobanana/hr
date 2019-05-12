#ifndef OB_STRING_HH
#define OB_STRING_HH

#include <cstddef>

#include <regex>
#include <string>
#include <vector>

namespace OB::String
{

std::string replace(std::string str, std::string const& key, std::string const& val);

bool starts_with(std::string const& str, std::string const& val);

bool assert_rx(std::string const& str, std::regex rx);

std::string repeat(std::size_t const num, std::string const& str);

std::size_t damerau_levenshtein(std::string const& lhs, std::string const& rhs,
  std::size_t const weight_insert = 1, std::size_t const weight_substitute = 1,
  std::size_t const weight_delete = 1, std::size_t const weight_transpose = 1);

} // namespace OB::String

#endif // OB_STRING_HH
