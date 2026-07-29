#pragma once

#include <format>
#include <generator>
#include <istream>

#include "libcsv/parse_error.hxx"

namespace libcsv {
/**
 * @struct options
 * @brief Represent the CSV reader parse options
 *
 */
struct options final {
    bool hasHeader {true};
    char separator {','};
    char quotation {'"'};
};

template <std::size_t Nm>
concept NonZero = (Nm > 0);

/**
 * @brief Represents the CSV interface
 */
template <typename T, std::size_t Nm>
    requires NonZero<Nm>
class reader final {
   public: // definitions
    using container = std::array<std::string, Nm>;

    /**
     * @brief Convert the CSV row values into T
     */
    auto convert(container) -> T {
        static_assert(
            sizeof(T) != 0, "Missing convert function definition for type T");
        return {};
    }

   public: // ctors
    reader(std::istream& is, options opts = {}) : _is(is), _opts(opts) {
        if (!is) throw std::runtime_error("Invalid stream provided");
    }

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
        if (_is.eof()) return std::nullopt;

        if (_buffer.has_value() && _is.tellg() == _bufferPos) return _buffer;

        _bufferPos = _is.tellg();
        std::string row {};

        // skip header
        if (_bufferPos == 0 && _opts.hasHeader) std::getline(_is, row);

        std::getline(_is, row);
        if (row.empty()) return std::nullopt;

        container data {};
        std::size_t index {};

        auto offset {row.begin()};

        while (index < Nm) {
            if (offset == row.end()) break;

            const auto start {offset};
            auto end {row.end()};

            // check for quoted value
            if (*offset == _opts.quotation) {
                offset++;
                while (true) {
                    // check for row end
                    if (offset == row.end())
                        throw parse_error(std::format(
                            "Missing closing quotation mark at position {}",
                            _bufferPos));

                    end = std::find(offset, row.end(), _opts.quotation);

                    // check for missing quotation mark
                    if (end == row.end())
                        throw parse_error(std::format(
                            "Missing closing quotation mark at position {}",
                            _bufferPos));

                    // check for escaped quotation mark
                    if (*(end - 1) == '\\') {
                        offset = end + 1;
                        continue;
                    }

                    // check for double quotation mark
                    if (*(end + 1) == _opts.quotation) {
                        offset = end + 2;
                        continue;
                    }

                    offset = (end + 1) == row.end() ? row.end() : end + 2;
                    break;
                }

                auto buffer = start == end ? std::string {}
                                           : std::string {start + 1, end};

                std::size_t innerPos {};
                while ((innerPos = buffer.find(_opts.quotation, innerPos))
                       != std::string::npos) {
                    if (innerPos != 0 && buffer[innerPos - 1] == '\\')
                        buffer.replace(innerPos - 1, 1, "");
                    else
                        buffer.replace(innerPos, 1, "");
                    innerPos++;
                }

                data[index++] = std::move(buffer);

            } else {
                end    = std::find(offset, row.end(), _opts.separator);
                offset = end == row.end() ? end : end + 1;

                data[index++]
                    = start == end ? std::string {} : std::string {start, end};
            }
        }

        return _buffer = std::move(convert(data));
    }

    /**
     * @brief Peek the next T
     * @return The next T or std::nullopt if eof
     */
    [[nodiscard]]
    auto peek(void) -> std::optional<T> {
        const auto start {_is.tellg()};
        auto buffer {_buffer.has_value() ? _buffer : get()};

        _is.seekg(start);
        return std::move(buffer);
    }

    /**
     * @brief Ignore the next T/s
     *
     * @param n The number of T/s to ignore
     */
    auto ignore(std::size_t n = 1) -> void {
        for (std::size_t i {}; i < n; i++) (void)get();
        _buffer = std::nullopt;
    }

    /**
     * @brief Get the stream offset
     */
    [[nodiscard]]
    auto tellg(void) -> std::streamoff {
        return _is.tellg();
    }

    /**
     * @brief Set the stream offset
     *
     * @param streamoff The offset to set the file stream to
     */
    auto seekg(std::streamoff streamoff) -> void {
        _is.seekg(streamoff);
        _bufferPos = streamoff;
        _buffer    = {};
    }

    /**
     * @brief Check if the stream has reached eof
     */
    [[nodiscard]]
    auto eof(void) const -> bool {
        return _is.eof();
    }

    /**
     * @brief Get the T/s in a sequence
     */
    [[nodiscard]]
    auto rows(void) -> std::generator<std::optional<T>> {
        while (_is.eof()) co_yield get();
    }

   private: // members
    std::istream& _is;
    options _opts {};

    std::streamoff _bufferPos {_is.tellg()};
    std::optional<T> _buffer {};
};
} // namespace libcsv
