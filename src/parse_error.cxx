#include "libcsv/parse_error.hxx"

namespace libcsv {
parse_error::parse_error(std::string_view message) : _message(message) {}

auto parse_error::what(void) const noexcept -> const char* {
    return _message.data();
}
} // namespace libcsv
