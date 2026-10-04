#pragma once
#include <concepts>
#include <cstdint>
#include "../error.hpp"

namespace ddb::hal {

enum class pin_mode : std::uint8_t { input, output, alternate, analog };
enum class pin_pull : std::uint8_t { none, up, down };

struct pin_config {
  pin_mode mode = pin_mode::input;
  pin_pull pull = pin_pull::none;
  bool open_drain = false;
  std::uint8_t alt = 0;
};

template <typename T>
concept InputPin = requires(const T& p) {
  { p.read() } noexcept -> std::same_as<bool>;
}

template <typename T>
concept OutputPin = requires(T& p, bool v) {
  { p.write(v) } noexcept -> std::same_as<void>;
  { p.toggle() } noexcept -> std::same_as<void>;
};

template <typename T>
concept Pin = InputPin<T> && OutputPin<T> && requires(T& p, pin_config c) {
  { p.configure(c) } noexcept -> std::same_as<result<>>;
};

} // namespace ddb::hal

