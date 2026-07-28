#include <cassert>
#include <fstream>
#include <iostream>

#include "libcsv/reader.hxx"

using namespace libcsv;

struct person {
    std::string name {};
    int age {};
    std::string city {};
    std::string bio {};
};

template <>
inline auto reader<person, 4>::convert(container data) -> person {
    return {
        .name = data[0],
        .age  = std::stoi(data[1]),
        .city = data[2],
        .bio  = data[3],
    };
}

auto TestStreamGet(int, char**) -> int {
    try {
        std::ifstream ifs {"test-files/sample-data.csv"};

        reader<person, 4> r {ifs};
        const auto p {r.get()};

        assert(p.has_value());
        assert(p.value().age == 30);
        assert(p.value().name == "Smith, John");
        assert(p.value().city == "New York");
        assert(p.value().bio == "Loves coding, reading, and \"coffee\"");
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
