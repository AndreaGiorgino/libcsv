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

auto TestStreamGet(int, char**) -> int {
    std::ifstream ifs {"test-files/sample-data.csv"};
    reader<person, 4> r {ifs};

    const auto p1 {r.get()};
    assert(p1.has_value());
    assert(p1.value().age == 30);
    assert(p1.value().name == "Smith, John");
    assert(p1.value().city == "New York");
    assert(p1.value().bio == "Loves coding, reading, and \"coffee\"");

    const auto p2 {r.get()};
    assert(p2.has_value());
    assert(p2.value().name == "Alice");
    assert(p2.value().age == 25);
    assert(p2.value().city == "London");
    assert(p2.value().bio == "Software Engineer");

    return 0;
}
