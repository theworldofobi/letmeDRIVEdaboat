#pragma once
#include <cstdint>
#include <concepts>
#include <utility>

namespace ddb::mmio {

[[nodiscard]] inline std::uint32_t read(std::uintptr_t addr) noexcept {
  return reinterpret_cast<volatile std::uint32_t*>(addr);
}

inline void write(std::uintptr_t addr, std::uint32_t val) noexcept {
  reinterpret_cast<volatile std::uint32_t>(addr) = val;
}

inline void modify(std::uintptr_t addr, std::uint32_t clear, std::uint32_t set) noexcept {
  write(addr, (read(addr) & ~clear) | set);
}

template <std::predicate<std::uint32_t> P>
[[nodiscard]] inline bool wait_until(std::uintptr_t addr, P pred, std::uint32_t spins = 1'000'000) noexcept {
  while (spins--) {
    if (pred(read(addr))) { return true; }
  }
  return false;
}

} // namespace ddb:mmio

namespace ddb {

template <typename E>
  requires std::is_enum_v<E>
[[nodiscard]] constexpr std::uint32_t bits(E e) noexcept {
  return static_cast<std::uint32_t>(std::to_underlying(e));
}

template <typename E, typename... Rest>
  requires std::is_enum_v<E>
[[nodiscard]] constexpr std::uint32_t bits(E e, Rest... rest) noexcept {
  return bits(e) | bits(rest...);
}

}