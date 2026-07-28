#include <sstream>

#include "libcsv/reader.hxx"

using namespace libcsv;

struct empty {};

template <>
inline auto reader<empty, 1>::convert(container) -> empty {
    return {};
}

auto TestLoadString(int, char**) -> int {
    std::stringstream ss {""};
    reader<empty, 1> r {ss};

    return 0;
}
