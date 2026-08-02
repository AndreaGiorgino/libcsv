/*
 * main.cxx
 */

#include <iostream>
#include <sstream>

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

auto main(int, char**) -> int {
    std::stringstream ss {
        R"("Smith, John",30,"New York","Loves coding, reading, and \"coffee\"")"};

    reader<person, 4> r {ss};

    const auto opt {r.get()};
    const auto& p {opt.value_or({})};

    std::cout << "Person:" << std::endl
              << "  Name: " << p.name << std::endl
              << "  Age:  " << p.age << std::endl
              << "  City: " << p.city << std::endl
              << "  Bio:  " << p.bio << std::endl;

    return 0;
}
