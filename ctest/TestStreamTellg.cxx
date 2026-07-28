#include <cassert>
#include <fstream>

#include "libcsv/reader.hxx"

using namespace libcsv;

struct empty {};

template <>
inline auto reader<empty, 4>::convert(container) -> empty {
    return {};
}

auto TestStreamTellg(int, char**) -> int {
    std::ifstream ifs {"test-files/sample-data.csv"};
    reader<empty, 4> r {ifs};

    assert(r.tellg() == 0);

    r.ignore();

    assert(r.tellg() == 86);

    return 0;
}
