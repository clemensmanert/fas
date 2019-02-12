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

	//! Adjusts mantissa (and exponent) to show the maximum of trailing digits.
	//! The function is different from ieee implementation, where a one is
	//! considered in front of the mantissa.
	//! In contrast here the mantissa gets multiplied/divided with/by BASE  until
	//! the highest bit is one, except the bit indicating the sign.
	//! This allows to encode special states like NAN, INF and ZERO with
	//! _mantissa = 0 and the exponent indicating the special value.
	//! If the mantissa were always considered to have a leading 1, it would be
	//! necessary to use one value of the exponent to encode these states.
	//! The ieee definition says that this is the very lowest value, but here also
	//! unsigned exponents are allowed, which would make thinks more complicated.
	//!
	//! @param value The value to normalize.
	//!          Caution: If value overflows while it is < MANTISSA_MAX or
	//!          underflows while it is > MANTISSA_LOWEST,
	//!          this function does not return and results in an endless loop.
	//! @tparam value The value's type to normalize.
	template <typename Tvalue> constexpr void normalize(Tvalue value) noexcept {
		// Zero has a specific code.
		if (value == 0) {
			*this = ZERO();
			return;
		}

		// Make a positive mantissa as large as possible,
		// and a negative mantissa as small as possible.
		if (value > 0) {
			// Grows mantissa as needed.
			while (value <= MANTISSA_MAX / BASE) {
				if (_exponent == EXPONENT_LOWEST) {
					*this = ZERO();
					return;
				}
				--_exponent;
				value *= BASE;
			}

			// Shrinks mantissa as needed.
			while (value > MANTISSA_MAX) {
				if (_exponent == EXPONENT_MAX) {
					*this = INF();
					return;
				}
				++_exponent;
				value /= BASE;
			}
		} else {
			// Grows mantissa as needed.
			while (value >= MANTISSA_LOWEST / BASE) {
				if (_exponent == EXPONENT_LOWEST) {
					*this = ZERO();
					return;
				}
				--_exponent;
				value *= BASE;
			}

			// Shrinks mantissa as needed.
			while (value < MANTISSA_LOWEST) {
				if (_exponent == EXPONENT_MAX) {
					*this = NEGATIVE_INF();
					return;
				}
				++_exponent;
				value /= BASE;
			}
		}

		_mantissa = static_cast<Tmantissa>(value);
	}

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

	//! Default constructor.
	Float() = default;

	//! Default copy constructor.
	Float(const Float &) = default;

	// Default move constructor.
	Float(Float &&) = default;

	//! Conversion constructor. This version supports only integer like types.
	//! This constructor will result in `INF` or `NEGATIVE_INF` if the provided
	//! values result in an exponent larger than `EXPONENT_MAX`.
	//!
	//! @param value Not normalized mantissa value.
	//! @param exponent The values exponent.
	//! @tparam Tvalue The value's type.
	//! @tparam TvalueExponent The exponent's type.
	template <typename Tvalue, typename TvalueExponent>
	explicit constexpr Float(const Tvalue value,
	                         const TvalueExponent exponent) noexcept {
		if (exponent > EXPONENT_MAX) {
			*this = INF();
		} else if (exponent < EXPONENT_LOWEST) {
			*this = NEGATIVE_INF();
		} else {
			_exponent = exponent;

			// The function normalize operates on its parameter.
			// If the max(value) is smaller than max(_mantissa), value will overflow.
			// Same with min values.
			// In this case normalize operates on _mantissa.
			if (value < MANTISSA_MAX && value > MANTISSA_LOWEST) {
				_mantissa = static_cast<Tmantissa>(value);
				normalize(_mantissa);
			} else {
				normalize(value);
			}
		}
	}

	//! Default copy assignment operator.
	Float &operator=(const Float &) = default;

	//! Default move assignment operator.
	Float &operator=(Float &&) = default;
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