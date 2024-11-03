#include <iostream>
#include <fstream>

#include "polygon.hpp"

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "must be 2 arguments\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "file not open\n";
    return 1;
  }

  using input_it = std::istream_iterator< kovtun::Polygon >;
  std::vector< kovtun::Polygon > polygons;
  while (!file.eof())
  {
    if (!file.fail())
    {
      std::copy(input_it{ file }, input_it{}, std::back_inserter(polygons));
    }
    else
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  for (int i = 0; i < polygons.size(); i++)
  {
    std::cout << "Polygon " << i << ":\n";
    std::cout << polygons[i].points.size() << '\n';
  }

  return 0;
}
