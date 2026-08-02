#include <cassert>
#include <fstream>
#include <vector>

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

const std::vector<person> expected {
    {{
         .name = "Smith, John",
         .age  = 30,
         .city = "New York",
         .bio  = "Loves coding, reading, and \"coffee\"",
     }, {
            .name = "Alice",
            .age  = 25,
            .city = "London",
            .bio  = "Software Engineer",
        }, {
            .name = "Bob \"The Builder\"",
            .age  = 40,
            .city = "Los Angeles",
            .bio  = "",
        }}
};

auto TestStreamRows(int, char**) -> int {
    std::ifstream ifs {"test-files/sample-data.csv"};
    reader<person, 4> r {ifs};

    std::size_t i {};
    for (const auto& opt : r.rows()) {
        assert(i < expected.size());
        assert(opt.has_value());

        const auto& p1 {expected[i++]};
        const auto& p2 {opt.value()};
        assert(p1.name == p2.name);
        assert(p1.age == p2.age);
        assert(p1.city == p2.city);
        assert(p1.bio == p2.bio);
    }

    return 0;
}
