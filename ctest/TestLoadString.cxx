#include <iostream>
#include <sstream>

#include "libcsv/reader.hxx"

using namespace libcsv;

struct empty {};

template<>
inline auto reader<empty, 1>::convert(container) -> empty {
    return {};
}

auto TestLoadString(int, char**) -> int {
    try {
        std::stringstream ss {""};

        reader<empty, 1> r {ss};
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
