// Copyright 2018 Clemens Manert
#ifndef FLOATING_POINT_HPP
#define FLOATING_POINT_HPP

#include <limits>
#include <type_traits>

namespace fas {

//! Represents a floating point number using a mantissa and an exponent.
//!
//! @tparam Tmantissa The type used to store the mantissa.
//! @tparam Texponent The type used to store the exponent.
//!         Caution: This type needs to be signed. Its lowest possible value
//!         must be `>= log BASE max(Tmantissa)` and its greatest possible value
//!         must be `<= log BASE min(Tmantissa)`.
//!         This is not (yet) checked by traits.
//! @tparam BASE Specifies the base of the exponent used to shift the mantissa.
//! @tparam MANTISSA_LOWEST The mantissa's lowest value possible.
//!         The default: `std::numeric_limits<Tmantissa>::lowest()`.
//! @tparam MANTISSA_MAX The mantissa's highest value possible.
//!         The default: `std::numeric_limits<Tmantissa>::max()`.
//! @tparam EXPONENT_LOWEST The exponent's lowest value possible.
//!         The default: `std::numeric_limits<Texponent>::lowest()`.
//! @tparam EXPONENT_MAX The exponent's highest value possible.
//!         The default: `std::numeric_limits<Texponent>::max()`.
template <typename Tmantissa, typename Texponent, Tmantissa BASE = 2,
          Tmantissa MANTISSA_LOWEST = std::numeric_limits<Tmantissa>::lowest(),
          Tmantissa MANTISSA_MAX = std::numeric_limits<Tmantissa>::max(),
          Texponent EXPONENT_LOWEST = std::numeric_limits<Texponent>::lowest(),
          Texponent EXPONENT_MAX = std::numeric_limits<Texponent>::max()>
class Float {
	//! The type of `this`.
	using self_t = Float<Tmantissa, Texponent, BASE, MANTISSA_LOWEST,
	                     MANTISSA_MAX, EXPONENT_LOWEST, EXPONENT_MAX>;

	//! Specifies the mantissa.
	Tmantissa _mantissa = 0;

	//! Specifies the exponent.
	Texponent _exponent = 0;

	//! Creates an instance using the given values, without normalising it.
	//!
	//! @param mantissa The value for the mantissa.
	//! @param exponent The value for the exponent.
	constexpr static self_t of(Tmantissa mantissa, Texponent exponent) {
		self_t target = self_t();
		target._mantissa = mantissa;
		target._exponent = exponent;
		return target;
	}

public:
	//! @returns The type's zero representation.
	constexpr static const self_t ZERO() { return self_t(); }

	//! @returns The type's zero representation.
	constexpr static const self_t ONE() { return self_t(1); }

	//! @returns The type's infinity representation.
	constexpr static const self_t INF() { return of(0, 1); }

	//! @returns The type's negative infinity representation.
	constexpr static const self_t NEGATIVE_INF() { return of(0, 2); }

	//! @returns The type's not a number representation.
	constexpr static const self_t NOT_A_NUMBER() { return of(0, 3); }

	//! @returns The type's smallest positive value.
	constexpr static const self_t MIN() { return of(1, EXPONENT_LOWEST); }

	//! @returns The type's smallest value.
	constexpr static const self_t LOWEST() {
		return of(MANTISSA_LOWEST, EXPONENT_MAX);
	}

	//! @returns The type's largest value.
	constexpr static const self_t MAX() { return of(MANTISSA_MAX, EXPONENT_MAX); }

	//! @returns The type's base.
	constexpr static const Tmantissa EXPONENT_BASE() { return BASE; }

	//! @returns The value's mantissa.
	constexpr Tmantissa mantissa() const noexcept { return _mantissa; }

	//! @returns The value's exponent.
	constexpr Texponent exponent() const noexcept { return _exponent; }
};
} // namespace fas

namespace std {
// Type traits -----------------------------------------------------------------
template <typename... args>
struct is_fundamental<fas::Float<args...>>
    : std::integral_constant<bool, true> {};

template <typename Tmantissa, typename Texponent, Tmantissa BASE,
          Tmantissa MANTISSA_LOWEST, Tmantissa MANTISSA_MAX,
          Texponent EXPONENT_LOWEST, Texponent EXPONENT_MAX>

struct is_floating_point<
    fas::Float<Tmantissa, Texponent, BASE, MANTISSA_LOWEST, MANTISSA_MAX,
               EXPONENT_LOWEST, EXPONENT_MAX>>
    : std::integral_constant<bool, true> {};

template <typename Tmantissa, typename Texponent, Tmantissa BASE,
          Tmantissa MANTISSA_LOWEST, Tmantissa MANTISSA_MAX,
          Texponent EXPONENT_LOWEST, Texponent EXPONENT_MAX>
struct is_arithmetic<fas::Float<Tmantissa, Texponent, BASE, MANTISSA_LOWEST,
                                MANTISSA_MAX, EXPONENT_LOWEST, EXPONENT_MAX>>
    : std::integral_constant<bool, true> {};

template <typename Tmantissa, typename Texponent, Tmantissa BASE,
          Tmantissa MANTISSA_LOWEST, Tmantissa MANTISSA_MAX,
          Texponent EXPONENT_LOWEST, Texponent EXPONENT_MAX>
struct is_scalar<fas::Float<Tmantissa, Texponent, BASE, MANTISSA_LOWEST,
                            MANTISSA_MAX, EXPONENT_LOWEST, EXPONENT_MAX>>
    : std::integral_constant<bool, true> {};

template <typename Tmantissa, typename Texponent, Tmantissa BASE,
          Tmantissa MANTISSA_LOWEST, Tmantissa MANTISSA_MAX,
          Texponent EXPONENT_LOWEST, Texponent EXPONENT_MAX>
struct is_object<fas::Float<Tmantissa, Texponent, BASE, MANTISSA_LOWEST,
                            MANTISSA_MAX, EXPONENT_LOWEST, EXPONENT_MAX>>
    : std::integral_constant<bool, true> {};

//! Numeric limits -------------------------------------------------------------
template <typename Tmantissa, typename Texponent, Tmantissa BASE,
          Tmantissa MANTISSA_LOWEST, Tmantissa MANTISSA_MAX,
          Texponent EXPONENT_LOWEST, Texponent EXPONENT_MAX>
struct numeric_limits<fas::Float<Tmantissa, Texponent, BASE, MANTISSA_LOWEST,
                                 MANTISSA_MAX, EXPONENT_LOWEST, EXPONENT_MAX>> {
	using Ttarget = fas::Float<Tmantissa, Texponent, BASE, MANTISSA_LOWEST,
	                           MANTISSA_MAX, EXPONENT_LOWEST, EXPONENT_MAX>;
	//! @returns The type's largest value.
	static const Ttarget max() noexcept { return Ttarget::MAX(); }

	//! @returns The type's smallest positive value.
	static const Ttarget min() noexcept { return Ttarget::MIN(); }

	//! @returns The type's smallest value.
	static const Ttarget lowest() noexcept { return Ttarget::LOWEST(); }
};
} // namespace std
#endif // FLOATING_POINT_HPP
