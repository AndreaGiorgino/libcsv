#pragma once

#include <format>
#include <generator>
#include <istream>

#include "libcsv/parse_error.hxx"

namespace libcsv {
struct options final {
    bool hasHeader {true};
    char separator {','};
    char quotation {'"'};
};

template <std::size_t Nm>
concept NonZero = (Nm > 0);

template <typename T, std::size_t Nm>
    requires NonZero<Nm>
class reader final {
   public: // definitions
    using container = std::array<std::string, Nm>;

    auto convert(container) -> T {
        static_assert(
            sizeof(T) == 0, "Missing convert function definition for type T");
    }

   public: // ctors
    reader(std::istream& is, options opts = {}) : _is(is), _opts(opts) {}

    reader(const reader&)                     = default;
    auto operator =(const reader&) -> reader& = default;

    reader(reader&&)                     = default;
    auto operator =(reader&&) -> reader& = default;

    ~reader(void) = default;

   public: // methods
    /**
     * @brief Get the next T
     * @return The next T or std::nullopt if eof
     */
    [[nodiscard]]
    auto get(void) -> std::optional<T> {
        if (_is.eof())
            return {};
        else if (_buffer.has_value()) {
            auto ret = _buffer;
            _buffer  = {};
            return _buffer = std::move(ret);
        }

        std::string row {};

        // skip header
        if (_line == 0 && _opts.hasHeader) {
            std::getline(_is, row);

            row.clear();
            _line++;
        }

        // skip empty lines
        while (!_is.eof()) {
            std::getline(_is, row);
            if (!row.empty()) break;

            _line++;
        }

        if (row.empty()) return {};

        container data {};
        std::size_t index {};

        auto offset {row.begin()};

        while (index < Nm) {
            if (offset == row.end()) break;

            const auto start {offset};
            auto end {row.end()};

            // check for quoted value
            if (*offset == _opts.quotation) {
                while (true) {
                    offset++;

                    // check for row end
                    if (offset == row.end())
                        throw parse_error(std::format(
                            "Missing closing quotation mark at line {}",
                            _line));

                    end = std::find(offset, row.end(), _opts.quotation);

                    // check for missing quotation mark
                    if (end == row.end())
                        throw parse_error(std::format(
                            "Missing closing quotation mark at line {}",
                            _line));

                    // check for escaped quotation mark
                    if (*(end - 1) == '\\') {
                        offset = end;
                        continue;
                    }

                    offset = end == row.end() ? end : end + 1;
                    break;
                }

            } else
                end = std::find(offset, row.end(), _opts.separator);

            data[index++] = start == end ? std::string {}
                                         : std::string {start + 1, end - 1};
        }

        _line++;
        return _buffer = std::move(convert(data));
    }

    /**
     * @brief Peek the next T
     * @return The next T or std::nullopt if eof
     */
    [[nodiscard]]
    auto peek(void) -> std::optional<T> {
        if (_buffer.has_value()) return _buffer;
        return get();
    }

    /**
     * @brief Ignore the next T/s
     *
     * @param n The number of T/s to ignore
     */
    auto ignore(std::size_t n = 1) -> void {
        for (std::size_t i {}; i < n; i++) (void)get();
    }

    /**
     * @brief Get the stream offset
     */
    [[nodiscard]]
    auto tellg(void) -> std::streamoff;

    /**
     * @brief Set the stream offset
     *
     * @param streamoff The offset to set the file stream to
     */
    auto seekg(std::streamoff streamoff) -> void;

    /**
     * @brief Check if the stream has reached eof
     */
    [[nodiscard]]
    auto eof(void) const -> bool;

    /**
     * @brief Get the T/s in a sequence
     */
    [[nodiscard]]
    auto rows(void) -> std::generator<T>;

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
