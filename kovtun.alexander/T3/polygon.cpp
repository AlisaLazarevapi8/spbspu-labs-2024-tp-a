#include "polygon.hpp"


std::istream & kovtun::operator>>(std::istream & in, kovtun::Polygon & polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using dl = kovtun::DelimiterI;

  polygon.points.clear();
  size_t size = 0;
  in >> size;
  for (size_t i = 0; i < size; ++i)
  {
    kovtun::Point point = {};
    in >> dl{'('} >> point.x >> dl{';'} >> point.y >> dl{')'};
    polygon.points.push_back(point);
  }

  return in;
}

double kovtun::right_cross::operator()(const kovtun::Point & first, const kovtun::Point & second) const
{
  return first.x * second.y;
}

double kovtun::left_cross::operator()(const kovtun::Point & first, const kovtun::Point & second) const
{
  return first.y * second.x;
}

double kovtun::getArea(kovtun::Polygon & polygon)
{
  auto points = polygon.points;

  std::vector< kovtun::Point > rotatedPoints(points.size());
  std::rotate_copy(points.cbegin(), points.cend() - 1, points.cend(), rotatedPoints.begin());

  std::vector< double > positiveAccumulator(points.size());
  std::transform(points.cbegin(), points.cend(), rotatedPoints.cbegin(), positiveAccumulator.begin(), right_cross{});

  std::vector< double > negativeAccumulator(points.size());
  std::transform(points.cbegin(), points.cend(), rotatedPoints.cbegin(), positiveAccumulator.begin(), left_cross{});

  double positiveArea = std::accumulate(positiveAccumulator.cbegin(), positiveAccumulator.cend(), 0.0);
  double negativeArea = std::accumulate(negativeAccumulator.cbegin(), negativeAccumulator.cend(), 0.0);

  double area = std::abs(positiveArea - negativeArea) / 2.0;
  return area;
}
