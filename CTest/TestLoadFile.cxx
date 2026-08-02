#include <fstream>

#include "libcsv/reader.hxx"

using namespace libcsv;

struct empty {};

template <>
inline auto reader<empty, 1>::convert(container) -> empty {
    return {};
}

auto TestLoadFile(int, char**) -> int {
    std::ifstream ifs {"TestFiles/sample-data.csv"};
    reader<empty, 1> r {ifs};

    return 0;
}
