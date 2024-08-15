#include <algorithm>

#include "delimiter.hpp"
#include "streamGuard.hpp"

std::istream& zhakha::operator>>(std::istream& in, delimiterStr&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::string s = "";
  char c = 0;
  for (size_t i = 0; i < exp.expected.size(); ++i)
  {
    in >> c;
    s += c;
  }
  std::string expUp = exp.expected;
  std::transform(exp.expected.begin(), exp.expected.end(), exp.expected.begin(), ::tolower);
  if (!(s == exp.expected || s == expUp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& zhakha::operator>>(std::istream& in, delimiterChar&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  zhakha::StreamGuard sguard(in);
  char c = 0;
  in >> c;
  if (!(c == exp.expected || c == std::tolower(exp.expected)))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
