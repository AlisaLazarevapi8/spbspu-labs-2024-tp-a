#include "commands.hpp"


void kovtun::area(const std::vector< kovtun::Polygon > & polygons, std::istream & in, std::ostream & out)
{;
  std::function< double(const kovtun::Polygon &) > calculator;

  std::map< std::string, std::pair<
      std::function< bool(const kovtun::Polygon & polygon) >,
      std::function< double(size_t count, const kovtun::Polygon & polygon) > > > args
      {
          {"EVEN", std::make_pair(isEven, getTotalArea)},
          {"ODD", std::make_pair(isOdd, getTotalArea)},
          {"MEAN", std::make_pair(notEmpty, getMeanArea)}
      };

  std::string arg;
  in >> arg;

  std::vector< kovtun::Polygon > selection;
  if (args.find(arg) == args.end())
  {
    // TODO: vertexes
  }

  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(selection), args.at(arg).first);
  if (selection.empty())
  {
    throw std::invalid_argument("none of the polygons met the criteria");
  }

  std::vector< double > result(selection.size());
  calculator = std::bind(args.at(arg).second, selection.size(), std::placeholders::_1);
  std::transform(selection.cbegin(), selection.cend(), result.begin(), calculator);
  out << std::accumulate(result.cbegin(), result.cend(), 0.0);
}

bool kovtun::isEven(const kovtun::Polygon & polygon)
{
  return polygon.points.size() % 2 == 0 && notEmpty(polygon);
}

bool kovtun::isOdd(const kovtun::Polygon & polygon)
{
  return polygon.points.size() % 2 != 0 && notEmpty(polygon);
}

bool kovtun::notEmpty(const kovtun::Polygon & polygon)
{
  return !polygon.points.empty();
}

double kovtun::getTotalArea(size_t count, const kovtun::Polygon & polygon)
{
  return getArea(polygon);
}

double kovtun::getMeanArea(size_t count, const kovtun::Polygon & polygon)
{
  return getArea(polygon) / count;
}
