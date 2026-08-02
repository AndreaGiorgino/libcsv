#include <cassert>
#include <fstream>

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

auto TestStreamIgnoreMultiple(int, char**) -> int {
    std::ifstream ifs {"TestFiles/sample-data.csv"};
    reader<person, 4> r {ifs};

    r.ignore(2);

    const auto p {r.get()};
    assert(p.has_value());
    assert(p.value().name == "Bob \"The Builder\"");
    assert(p.value().age == 40);
    assert(p.value().city == "Los Angeles");
    assert(p.value().bio == "");

    return 0;
}
