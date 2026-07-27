#pragma once

#include <istream>

namespace libcsv {
template <typename T, std::size_t Nm>
class reader final {
   public: // definitions
    using container = std::array<T, Nm>;

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
} // namespace libcsv
