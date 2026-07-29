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

auto TestStreamSeekg(int, char**) -> int {
    std::ifstream ifs {"test-files/sample-data.csv"};
    reader<person, 4> r {ifs};

    r.seekg(86);

    const auto p {r.get()};
    assert(p.has_value());
    assert(p.value().name == "Alice");
    assert(p.value().age == 25);
    assert(p.value().city == "London");
    assert(p.value().bio == "Software Engineer");

    return 0;
}
