#pragma once

#include <istream>

namespace libcsv {
template <typename T, std::size_t Nm>
class reader final {
   public: // definitions
    using container = std::array<T, Nm>;

    struct options final {
        char separator {','};
        char quotation {'"'};
    };

    auto convert(container row) -> T;

   public: // ctors
    reader(std::istream& is, options opts = {});

    reader(const reader&)                     = delete;
    auto operator =(const reader&) -> reader& = delete;

    reader(reader&&)                     = delete;
    auto operator =(reader&&) -> reader& = delete;

    ~reader(void) = delete;





   private: // methods
   private: // members
    std::istream& _is;
    std::optional<T> buffer {};
};

template <typename T, std::size_t Nm>
auto reader<T, Nm>::convert(reader<T, Nm>::container) -> T {
    static_assert(true, "Missing convert function definition for type T");
}
} // namespace libcsv
