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

auto TestStreamPeek(int, char**) -> int {
    std::ifstream ifs {"test-files/sample-data.csv"};

    reader<person, 4> r {ifs};

    const auto p1 {r.peek()};
    std::cout << "p1 loaded" << std::endl;
    assert(p1.has_value());
    assert(p1.value().name == "Smith, John");
    assert(p1.value().age == 30);
    assert(p1.value().city == "New York");
    assert(p1.value().bio == "Loves coding, reading, and \"coffee\"");

    const auto p2 {r.get()};
    std::cout << "p2 loaded" << std::endl;
    assert(p2.has_value());
    assert(p2.value().name == p1.value().name);
    assert(p2.value().age == p1.value().age);
    assert(p2.value().city == p1.value().city);
    assert(p2.value().bio == p1.value().bio);

    const auto p3 {r.peek()};
    std::cout << "p3 loaded" << std::endl;
    assert(p3.has_value());
    assert(p3.value().name == p2.value().name);
    assert(p3.value().age == p2.value().age);
    assert(p3.value().city == p2.value().city);
    assert(p3.value().bio == p2.value().bio);

    return 0;
}
