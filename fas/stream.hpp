#ifndef FLOATING_POINT_STREAMS_HPP
#define FLOATING_POINT_STREAMS_HPP
#include "fas/float.hpp"

#include <cmath>
#include <iostream>
#include <string>

namespace fas {

//! @returns the target as it is. This should work for all non
//! char types, since these are shown as numbers.
template <typename Ttarget> Ttarget char_to_int(Ttarget target) {
	return target;
}

//! @returns the char converted into an int, since we want to print the
//! values and not their ascii letter.
template <char> char char_to_int(char target) { return (int)target; }

//! Converts the given Floating_Point into a double.
template <typename Ttarget> double double_value(const Ttarget &target) {
	return target.mantissa() *
	       std::pow(target.EXPONENT_BASE(), target.exponent());
}

//! Pretty prints the given Floating_Point to the given stream.
template <typename Tmantissa, typename Texponent, Tmantissa BASE>
std::ostream &operator<<(std::ostream &target,
                         const fas::Float<Tmantissa, Texponent, BASE> &source) {
	if (fas::Float<Tmantissa, Texponent>::ZERO() == source) {
		target << "ZERO";
	} else if (fas::Float<Tmantissa, Texponent>::ONE() == source) {
		target << "One";
	} else if (fas::Float<Tmantissa, Texponent>::INF() == source) {
		target << "INF";
	} else if (fas::Float<Tmantissa, Texponent>::NEGATIVE_INF() == source) {
		target << "NEGATIVE INF";
	} else if (fas::Float<Tmantissa, Texponent>::NOT_A_NUMBER() == source) {
		target << "NOT A NUMBER";
	} else if (fas::Float<Tmantissa, Texponent>::MIN() == source) {
		target << "MIN";
	} else if (fas::Float<Tmantissa, Texponent>::LOWEST() == source) {
		target << "LOWEST";
	} else if (fas::Float<Tmantissa, Texponent>::MAX() == source) {
		target << "MAX";
	} else {
		target << std::hex << char_to_int((int) source.mantissa()) << " * "
		       << char_to_int((int) source.EXPONENT_BASE()) << " ^ "
		       << char_to_int((int) source.exponent()) << " ≈ " << double_value(source);
	}
	return target;
}
} // namespace fas
#endif // FLOATING_POINT_STREAMS_HPP
