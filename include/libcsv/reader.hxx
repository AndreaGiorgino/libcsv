#pragma once

#include <generator>
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

   public: // methods
    /**
     * @brief Get the next T
     * @return The next T or std::nullopt if eof
     */
    [[nodiscard]]
    auto get(void) -> std::optional<T>;

    /**
     * @brief Peek the next T
     * @return The next T or std::nullopt if eof
     */
    [[nodiscard]]
    auto peek(void) -> std::optional<T>;

    /**
     * @brief Ignore the next T/s
     *
     * @param n The number of tokens to ignore
     */
    auto ignore(size_t n = 1) -> void;

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
