#include "Delimiter.hpp"
#include "streamGuard.hpp"
#include <cctype>

std::istream& chernikova::operator>>(std::istream& in, PunctuationI&& exp)
{
  StreamGuard streamGuard(in);
  in.unsetf(std::ios_base::skipws);
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = in.get();
  if (c != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& chernikova::operator>>(std::istream& in, DelimiterI&& exp)
{
  StreamGuard streamGuard(in);
  in.setf(std::ios_base::skipws);
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  bool isLowerCase = (!exp.upperСase) && (c != exp.expected);
  bool isRightCondition = isLowerCase || (std::tolower(c) != std::tolower(exp.expected));
  if (isRightCondition)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& chernikova::operator>>(std::istream& in, StringDelimiterI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (const char* i = dest.exp; (*i != '\0') && in; ++i)
  {
    in >> DelimiterI{ *i };
  }
  return in;
}
