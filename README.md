# fas - a floating point arithmetic in software
*fas* is floating point arithmetic for arbitrary mantissa and exponent
types in *modern header-only C++*.  It lets you construct various
different float types using template parameters for the mantissa,
exponent and base.

The constructed float-types look and fell like a native float/double
for arithmetic operations. Furthermore all methods are performed on
the stack and do not require any heap space.

*fas* is *header-only*. 

## Features
### Choose your desired mantissa and exponent
```C++
fas::Float<int16_t, int8_t> f;
```
This will result in a float using a signed 16 bit mantissa and a signed 8 bit
exponent.

### Arithmetical operators
The arithmetical operations are supported using their corresponding operators
`+ - * / += -= *= /= ++ --`
```C++
fas::Float<int16_t, int8_t> f1 = 10;
auto f2 = f1;

f2 = -f1;     // => -10

f2 = f1 + 10; // => 20
f2 = f1 - f1; // => 0
f2 = f1 * f1; // => 100
f2 = f1 / 20; // => 0.5

f2 += 1;      // => 1.5
f2 -= 1;      // => 0.5
f2 *= 2;      // => 1
f2 /= 2;      // => 0.5

f1++;         // => 11
++f1;         // => 12
f1--;         // => 11
--f1;         // => 10
```

### Type boundaries
Each type knows its boundaries:
- `MAX()` returns the largest value
- `MIN()` returns the smallest positive value
- `LOWEST()` returns the smallest value
The naming is the same as with internal float/double.

There are overloadings for `std::numeric_limits` available:
`fas::Float<int8_t, int8_t>::MAX()` returns the same as
`std::numeric_limits<fas::Float<std::int16_t, std::int8_t>>::MAX()`
which is approx `2.16079e+40`.

### Type traits
*fas* supports type traits:
```C++
is_fundamental<int16_t, int16_t>::value               // => true
is_floating_point<fas::Float<int16_t, int16_t>::value // => true
is_arithmetic<int16_t, int16_t>::value                // => true
is_scalar<int16_t, int16_t>::value                    // => true
is_object<int16_t, int16_t>::value                    // => true
  ```

### Everything is a constant expression
```C++
constexpr c = fas::Float<std::int16_t, std::int8_t>(1);
```
Even the operations' results:
```C++
constexpr c1 = fas::Float<std::int16_t, std::int8_t>(1);
constexpr c2 = fas::Float<std::int16_t, std::int8_t>(2);

constexpr c3 = c1 + c2; // => 3
```

### *iostream* support
*fas* offers an output stream overload, which can be used for `std::cout`:
```C++
#include "fas/stream.hpp>

...

fas::Float<int8_t, int8_t> fas_float(1);
fas_float /= 3;
std::cout << fas_float << "\n"; // => 70 * 7 ^ fffffffd ≈ 0.32653061224489793313
```



### Arbitrary base
Typical floats such as `float` or `double` are to the base of
`2`. *fas* allows to construct floats to any base:
```C++
fas::Float<int8_t, int8_t, 7> fas_float(0);
double cpp_float = 0;

for(auto i=0; i<7; ++i) {
	fas_float += fas::Float<int8_t, int8_t, 7>(1)/7;
	cpp_float += 1.0/7;
}

std::cout << std::setprecision(20);
std::cout << fas_float << "\n";    // => exaclty 1
std::cout << cpp_float << "\n";    // => 0.99999999999999977796
```
The setting of different bases allows to represent specific fractions exaclty.
In this case the base is `7`, so any fraction by `7` is represented exactly.
Compare to the native `double` which is always to the base of `2`, thus can not
represent `1/7` exactly.

## How to use it
Download the
[float.hpp](https://raw.githubusercontent.com/clemensmanert/fas/master/fas/float.hpp)
and include it in your source. Don't forget to add it in your include path.
## Unit tests
To build and run unit tests type:
```bash
mkdir build; cd build; cmake ..; make && ./tests/tests
```
## Requirements
- The Stl's `std::numeric_limits` is required the limits of the specified types for mantissa and exponent.
- [Catch2](https://github.com/catchorg/Catch2) is required to build the unit tests.

## Todo
- (configurable) rounding support
- `exp`, `sqrt`, `pow` and other math.h functions
- string constructor
- string representation
- value constructor for all ints and other types
- a version without *stl*
