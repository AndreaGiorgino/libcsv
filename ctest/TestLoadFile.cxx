#include <iostream>
#include <fstream>

#include "libcsv/reader.hxx"

using namespace libcsv;

struct empty {};

template<>
inline auto reader<empty, 1>::convert(container) -> empty {
    return {};
}

auto TestLoadFile(int, char**) -> int {
    try {
        std::ifstream ifs {"test-files/sample-data.csv"};

        reader<empty, 1> r {ifs};
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
