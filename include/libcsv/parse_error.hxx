#pragma once

#include <string>

namespace libcsv {
class parse_error final : public std::exception {
   public: // ctors
    parse_error(std::string_view message = {"Unknown parse error"});

    parse_error(const parse_error&)                     = default;
    auto operator =(const parse_error&) -> parse_error& = default;

    parse_error(parse_error&&) = default;
    auto operator =(parse_error&&) -> parse_error&;

    ~parse_error(void) = default;

   public:
    auto what(void) const noexcept -> const char* override;

   private: // members
    std::string _message {};
};
} // namespace libcsv
