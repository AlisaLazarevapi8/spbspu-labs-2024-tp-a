#include "commands.hpp"


void kovtun::area(const std::vector< kovtun::Polygon > & polygons, std::istream & in, std::ostream & out)
{;
  std::map< std::string, std::pair<
      std::function< bool(const kovtun::Polygon & polygon) >,
      std::function< double(const kovtun::Polygon & polygon, size_t count) > > > args
      {
          {"EVEN", std::make_pair(isEven, getTotalArea)},
          {"ODD", std::make_pair(isOdd, getTotalArea)},
          {"MEAN", std::make_pair(notEmpty, getMeanArea)}
      };

  std::string arg;
  in >> arg;

  std::function< double(const kovtun::Polygon &) > calculator;
  std::vector< kovtun::Polygon > selection;
  if (args.find(arg) == args.end())
  {
    size_t vertexNum = std::stoul(arg);
    auto predicate = std::bind(equalVertex, vertexNum, std::placeholders::_1);
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(selection), predicate);
    calculator = std::bind(getTotalArea, std::placeholders::_1, selection.size());
  }
  else
  {
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(selection), args.at(arg).first);
    calculator = std::bind(args.at(arg).second, std::placeholders::_1, selection.size());
  }

  if (selection.empty())
  {
    throw std::invalid_argument("none of the polygons met the criteria");
  }

  std::vector< double > result(selection.size());
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

double kovtun::getTotalArea(const kovtun::Polygon & polygon, size_t count)
{
  count = 1;
  return getMeanArea(polygon, count);
}

double kovtun::getMeanArea(const kovtun::Polygon & polygon, size_t count)
{
  return getArea(polygon) / count;
}

bool kovtun::equalVertex(size_t count, const kovtun::Polygon & polygon)
{
  return count == polygon.points.size();
}
