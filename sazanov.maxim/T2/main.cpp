#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>
#include "DataStruct.hpp"

int main()
{
  using namespace sazanov;
  std::list< DataStruct > data;

  using input_it_t = std::istream_iterator< DataStruct >;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(
      input_it_t{std::cin},
      input_it_t{},
      std::back_inserter(data)
    );
  }

  data.sort();

  std::vector< DataStruct > result(data.begin(), data.end());
  using output_it_t = std::ostream_iterator< DataStruct >;
  std::copy(
    result.cbegin(),
    result.cend(),
    output_it_t{std::cout, "\n"}
  );
  return 0;
}
