#include <cassert>
#include <fstream>

#include "libcsv/reader.hxx"

using namespace libcsv;

struct empty {};

template <>
inline auto reader<empty, 4>::convert(container) -> empty {
    return {};
}

auto TestStreamEof(int, char**) -> int {
    std::ifstream ifs {"test-files/sample-data.csv"};
    reader<empty, 4> r {ifs};

    while (r.get() != std::nullopt);

    assert(r.eof());

    return 0;
}
