#include <iostream>
#include <sstream>

#include "libcsv/reader.hxx"

using namespace libcsv;

template<>
auto reader<std::nullptr_t, 1>::convert(container) -> std::nullptr_t {
    return nullptr;
}

auto TestLoadString(int, char**) -> int {
    try {
        std::stringstream ss {""};

        reader<std::nullptr_t, 1> r {ss};
        r.ignore();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
