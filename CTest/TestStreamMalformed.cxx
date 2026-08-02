#include <cassert>
#include <fstream>

#include "libcsv/reader.hxx"

using namespace libcsv;

struct empty {};

template <>
inline auto reader<empty, 1>::convert(container) -> empty {
    return {};
}

auto TestStreamMalformed(int, char**) -> int {
    std::ifstream ifs {"TestFiles/malformed-data.csv"};
    reader<empty, 4> r {ifs};

    try {
        while (r.get() != std::nullopt);
    } catch (const parse_error&) {
    }

    return 0;
}
