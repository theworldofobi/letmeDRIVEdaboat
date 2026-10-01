#pragma once

#include <cstdint>
#include <expected>
#include <string_view>

namespace ddb {

enum class errc : std::uint8_t {
  invalid_argument = 1,
  io,
  timed_out,
  would_block,
  no_device,
  no_space
};

template <typename T = void>
using result = std::expected<T, errc>;

[[nodiscard]] constexpr std::string_view to_string(errc e) {
  switch (e) {
    case errc::invalid_argument: return "invalid argument";
    case errc::io:               return "i/o error";
    case errc::timed_out:        return "timed out";
    case errc::would_block:      return "would block";
    case errc::no_device:        return "no device";
    case errc::no_space:         return "no space";
  }
  return "unknown";
}

} // namespace ddb